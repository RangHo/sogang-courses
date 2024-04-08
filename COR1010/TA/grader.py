#!/usr/bin/env python

# Module imports
import sys

import argparse
import csv
import difflib
import json
import subprocess
import re

# Signal library is only available on UNIX
if sys.platform == 'linux' or sys.platform == 'darwin':
    import signal
    def timeout_handler(signum, frame):
        raise TimeoutError("Student's code timed out!")

    def set_alarm(seconds: int):
        signal.alarm(seconds)

    signal.signal(signal.SIGALRM, timeout_handler)
else:
    def set_alarm(seconds: int):
        log_info("Timeout feature is not supported on this platform.")
        log_info("Student's code will run indefinitely.")


from dataclasses import dataclass
from pathlib import Path

# Type imports
from typing import Any, Optional, Final

# List of encodings to try before tapping out
POSSIBLE_ENCODINGS: Final = [
    sys.stdout.encoding or sys.getdefaultencoding(),
    sys.stdin.encoding or sys.getdefaultencoding(),
    'euc-kr',
    'utf-8',
    'utf-16',
    'ascii'
]

# Logging level
#  - 0: No logging
#  - 1: Informational info
#  - 2: Debugging info
LOG_LEVEL: int = 1

# Seconds to wait before calling timeout
TIMEOUT_SECONDS = 5


@dataclass
class RunResult:
    """Result of a single run of a Python program."""

    # Class constants
    IGNORE_WHITESPACE = False
    STRIP_WHITESPACE = False

    # Required fields
    target: str
    output_str: str
    is_success: bool

    # Optional fields
    input_str: Optional[str]

    def __eq__(self, other):
        """Compare two results."""
        if isinstance(other, str):
            return self.output_str == other.splitlines(keepends=True)

        if not self.is_success or not other.is_success:
            return False

        # Strip whitespace for each line if needed
        self_output = [line.strip() for line in self.output_str] \
            if self.STRIP_WHITESPACE else self.output_str
        other_output = [line.strip() for line in other.output_str] \
            if other.STRIP_WHITESPACE else other.output_str

        # Ignore whitespace if needed
        self_output = [line.replace(" ", "") for line in self_output] \
            if self.IGNORE_WHITESPACE else self_output
        other_output = [line.replace(" ", "") for line in other_output] \
            if other.IGNORE_WHITESPACE else other_output

        return self_output == other_output

    def __ne__(self, other):
        """Compare two results."""
        return not self.__eq__(other)

    def __str__(self):
        """Return the output string when stringified."""
        return self.output_str

    def diff(self, other) -> str:
        """Return a diff of the output of two results."""
        result = difflib.unified_diff(
            self.output_str,
            other.output_str,
            fromfile=self.target,
            tofile=other.target,
        )
        return "".join(result)


@dataclass
class TestResult:
    """Result of a comparison of a student's code with the answer."""

    # Required fields
    student_id: str
    code_file: str
    is_success: bool
    is_correct: bool
    answer_result: RunResult
    student_result: RunResult

    # Optional fields
    testcase_file: str = "N/A"


def log_error(*args, **kwargs):
    print("[ERROR]", *args, **kwargs)


def log_info(*args, **kwargs):
    """Log an informational message."""
    if LOG_LEVEL > 0:
        print("[INFO]", *args, **kwargs)


def log_debug(*args, **kwargs):
    """Log a debugging message."""
    if LOG_LEVEL > 1:
        print("[DEBUG]", *args, **kwargs)


def serialize(target: Any) -> dict:
    return vars(target)


def try_decode(s: bytes) -> str:
    """Try to decode a string using a list of encodings."""
    for encoding in POSSIBLE_ENCODINGS:
        try:
            log_debug(f"Trying encoding {encoding}...")
            decoded_s = s.decode(encoding)
            log_debug(f"Success! Decoded result is: {decoded_s}")
            return decoded_s
        except UnicodeError as e:
            log_debug(f"Failed! {e}")

    log_info(f"Failed to decode {s}!")
    log_info(f"I tried: {POSSIBLE_ENCODINGS}")
    raise UnicodeError("Failed to decode a byte array.")


def run_without_input(script_path: Path) -> str:
    """Run a file and return its output."""
    log_info(f"Running file {script_path}...")
    output = subprocess.check_output(
        ['python', script_path],
        stderr=subprocess.STDOUT
    )
    return try_decode(output)


def run_with_input(script_path: Path, input_path: Path) -> str:
    """Run a file with a given input as stdin and return its output."""
    log_info(f"Running file {script_path} with input {input_path}...")
    with open(input_path, "r") as f:
        output = subprocess.check_output(
            ['python', script_path],
            stdin=f,
            stderr=subprocess.STDOUT
        )
    return try_decode(output)


def run(script_path: Path, input_path: Optional[Path] = None) -> RunResult:
    """Run a script and return its output."""

    # Set up an alarm
    set_alarm(5)

    # Of course, their code can set this computer on fire
    try:
        result = None
        if input_path is None:
            result = run_without_input(script_path)
            return RunResult(
                target=script_path.name,
                input_str=None,
                is_success=True,
                output_str=result
            )
        else:
            result = run_with_input(script_path, input_path)
            return RunResult(
                target=script_path.name,
                input_str=input_path.read_text(),
                is_success=True,
                output_str=result
            )

    except subprocess.CalledProcessError as e:
        # Oh no who would've guessed
        error_output = try_decode(e.output)

        log_info("Student's code failed to run!")
        log_info(f"Output:\n{error_output}")

        return RunResult(
            target=script_path.name,
            input_str=input_path.read_text() if input_path is not None else None,
            is_success=False,
            output_str=error_output
        )
    except TimeoutError as e:
        log_info("Student's code took too long to run!")

        return RunResult(
            target=script_path.name,
            input_str=input_path.read_text() if input_path is not None else None,
            is_success=False,
            output_str="Timeout"
        )
    finally:
        set_alarm(0)


if __name__ == '__main__':
    # Create a parser object
    parser = argparse.ArgumentParser(
        prog='grader.py',
        description='Automatic assignment validator for Sogang University COR1010 class',
        epilog='This program is written to assist TAs in grading assignments. It is not intended to be used by students.'
    )

    # Arguments defining the grading strategy
    parser.add_argument(
        '--testcase',
        nargs='*',
        help='The test cases to be provided to the submitted code'
    )
    parser.add_argument(
        '--answer-code',
        nargs='?',
        help='The code that produces the correct answer'
    )
    parser.add_argument(
        '--answer-text',
        nargs='*',
        help='The verbatim text file that contains the answer'
    )
    parser.add_argument(
        '--ignore-whitespace',
        action='store_true',
        default=False,
        help='Ignore whitespace when comparing the output of the submitted code with the answer'
    )
    parser.add_argument(
        '--strip-whitespace',
        action='store_true',
        default=False,
        help='Strip whitespace from the output of the submitted code before comparing it with the answer'
    )

    # Arguments related to information gathering
    parser.add_argument(
        '--id-regex',
        default='20[0-9]{6}',
        help='The regex to extract student ID from the file name'
    )
    parser.add_argument(
        '--filter',
        default='.*',
        help='The regex to filter out files that should not be graded'
    )
    parser.add_argument(
        '--exclude',
        default=None,
        help='The regex to exclude files that should not be graded'
    )

    # Arguments related to the result output
    parser.add_argument(
        '--csv-out',
        nargs='?',
        const='output.csv',
        help='The file name of the CSV file containing the result'
    )
    parser.add_argument(
        '--json-out',
        nargs='?',
        const='output.json',
        help='The file name of the JSON file containing the result'
    )
    parser.add_argument(
        '--diff-out',
        nargs='?',
        const='diff',
        help='The directory name of the diff files'
    )

    # How talkative should I be?
    parser.add_argument(
        '-v',
        '--verbose',
        action='store_true',
        help='Make this program talkative'
    )
    parser.add_argument(
        '-q',
        '--quiet',
        action='store_true',
        help='Make this program shut up'
    )

    # Directory setting
    parser.add_argument(
        'directory',
        help='Directory where student code is saved'
    )

    # Parse the command line arguments
    args = parser.parse_args()

    # Let's set the log level first
    if args.verbose:
        LOG_LEVEL += 1
    if args.quiet:
        LOG_LEVEL -= 1

    # There are four different ways to provide the grading strategy:
    #  - Provide an answer code;
    #  - Provide an answer text file;
    #  - Provide an answer code with one or more test cases;
    #  - Provide one or more answer text files with the same number of test cases.
    #
    # 1. Providing one answer code or one answer text file
    # Answer code and answer text file cannot be provided at the same time. When the answer code is
    # provided, the answer code is executed and the output is compared with the output of the
    # submitted student code. When the answer text file is provided, the contents of the file is
    # compared with the output of the submitted student code.
    #
    # 2. Providing an answer code with one or more test cases
    # When an answer code is provided with one or more test cases, the answer code is executed with
    # each test cases, and the output is compared with the output of the student-submitted code
    # executed with the same test case. Test cases are provided as if they are typed into the
    # standard input of the submitted code.
    #
    # 3. Providing one or more answer text files with the same number of test cases
    # When one or more answer text files are provided with the same number of test cases, the
    # contents of each answer text file is compared with the output of the student-submitted code.
    # For this case, the order of the answer text files must be the same as the order of the
    # corresponding test cases.

    # Make sure that either answer code or answer text file is provided but not both...
    if args.answer_code is not None and args.answer_text is not None:
        raise ValueError("Only one test criterion can be given, but not both.")

    # ...or at least one answer criterion must be given
    if args.answer_code is None and args.answer_text is None:
        raise ValueError("Either answer code or answer text file must be provided.")

    # If there are testcases provided with answer files then...
    if args.testcase is not None and args.answer_text is not None:
        # ...make sure that the # of testcases match the # of answer text files
        if len(args.testcase) != len(args.answer_text):
            raise ValueError("The number of test cases must match the number of answer text files.")

    # Set whitespace flags
    RunResult.IGNORE_WHITESPACE = args.ignore_whitespace
    RunResult.STRIP_WHITESPACE = args.strip_whitespace

    # Convert the list of test cases into a list of Path objects
    # If no testcases are available then return a list of None
    testcase_paths = [Path(testcase) for testcase in args.testcase] \
        if args.testcase is not None else [None]

    # Find the correct answer for each test cases
    # When answer code is given, then run that code for each test case;
    # otherwise, read all answer texts into a list
    answer_list = []
    if args.answer_code is not None:
        for testcase_path in testcase_paths:
            answer_result = run(Path(args.answer_code), testcase_path)
            answer_list.append(answer_result)
    else:
        for answer_text in args.answer_text:
            with open(answer_text, 'r') as f:
                answer_list.append(f.read())

    # Set up a list to store results
    results: list[TestResult] = []

    # Find all student code
    student_code_paths = Path(args.directory).glob('*.py')

    # Whoopsie, filter out the unneeded ones
    student_code_paths = filter(
        lambda path: re.search(args.filter, path.name) is not None,
        student_code_paths
    )
    student_code_paths = filter(
        lambda path: re.search(args.exclude, path.name) is None,
        student_code_paths
    ) if args.exclude is not None else student_code_paths

    # For each student's code run this madness
    for student_code in student_code_paths:
        # Run the student's code for each test cases
        for testcase, answer in zip(testcase_paths, answer_list):
            # Gathering some info before running the code
            student_id_match = re.search(args.id_regex, student_code.name)
            student_id = student_id_match.group(0) \
                if student_id_match is not None else "N/A"
            student_result = run(student_code, testcase)

            results.append(TestResult(**{
                'student_id': student_id,
                'code_file': student_code.name,
                'testcase_file': testcase.name if testcase is not None else None,
                'is_success': student_result.is_success,
                'is_correct': answer == student_result,
                'answer_result': answer,
                'student_result': student_result,
            }))

    # Print the result first
    for item in results:
        log_info(item)

    # Save it as CSV if the user asked to do so
    try:
        if args.csv_out is not None:
            log_info("Writing to a CSV file:", args.csv_out)

            # Add BOM as Excel doesn't like CSV files without metadata
            with open(args.csv_out, 'w', encoding='utf-8-sig') as f:
                writer = csv.writer(f)
                writer.writerow(
                    [it for it in vars(results[0])]
                )
                writer.writerows(
                    [getattr(item, attr) for attr in vars(item)]
                    for item in results
                )
    except Exception as e:
        log_error("Failed to write to a CSV file:", e)

    # Save it as JSON if the user asked to do so
    try:
        if args.json_out is not None:
            log_info("Writing to a JSON file:", args.json_out)

            with open(args.json_out, 'w', encoding='utf-8') as f:
                json.dump(results, f, default=serialize)
    except Exception as e:
        log_error("Failed to write to a JSON file:", e)

    # Save the diff files if the user asked to do so
    try:
        if args.diff_out is not None:
            log_info("Writing diff files to directory:", args.diff_out)

            # Create the directory if it doesn't exist
            Path(args.diff_out).mkdir(parents=True, exist_ok=True)

            # Filter out correct students
            incorrect_results = [item for item in results if not item.is_correct]

            # Start processing
            for item in incorrect_results:
                # Create a diff file for each incorrect student
                diff_file = Path(args.diff_out) / f"{item.student_id}.diff"
                with open(diff_file, 'a') as f:
                    # Print the diff result to the file
                    log_debug(f"Writing diff file for student {item.student_id}...")
                    f.write(item.answer_result.diff(item.student_result))
                    f.write("\n")
    except Exception as e:
        log_error("Failed to write to the diff file:", e)
