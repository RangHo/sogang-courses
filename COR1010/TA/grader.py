#!/usr/bin/env python

# Module imports
import sys

import argparse
import csv
import difflib
import subprocess
import re

from pathlib import Path

# Type imports
from typing import Optional, Final

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

class RunResult:
    """Result of a program."""

    IGNORE_WHITESPACE = False
    STRIP_WHITESPACE = False

    def __init__(self, target: str, input: Optional[str], success: bool, output: str):
        self.target = target
        self.input = input if input is not None else "N/A"
        self.success = success
        self.output = output.splitlines(keepends=True)

    def __eq__(self, other):
        """Compare two results."""
        if isinstance(other, str):
            return self.output == other.splitlines(keepends=True)

        if not self.success or not other.success:
            return False

        # Strip whitespace for each line if needed
        self_output = [line.strip() for line in self.output] \
            if self.STRIP_WHITESPACE else self.output
        other_output = [line.strip() for line in other.output] \
            if other.STRIP_WHITESPACE else other.output

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
        """Return a string representation of the result."""
        return "".join(self.output)

    def diff(self, other) -> str:
        """Return a diff of the output of two results."""
        result = difflib.unified_diff(
            self.output,
            other.output,
            fromfile=self.target,
            tofile=other.target,
        )
        return "".join(result)


def log_error(*args, **kwargs):
    print("[ERROR]", *args, **kwargs)


def log_info(*args, **kwargs):
    """Log an informational message."""
    if LOG_LEVEL > 0:
        print(*args, **kwargs)


def log_debug(*args, **kwargs):
    """Log a debugging message."""
    if LOG_LEVEL > 1:
        print(*args, **kwargs)


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

    # Of course, their code can set this computer on fire
    try:
        result = None
        if input_path is None:
            result = run_without_input(script_path)
            return RunResult(
                target=script_path.name,
                input=None,
                success=True,
                output=result
            )
        else:
            result = run_with_input(script_path, input_path)
            return RunResult(
                target=script_path.name,
                input=input_path.read_text(),
                success=True,
                output=result
            )

    except subprocess.CalledProcessError as e:
        # Oh no who would've guessed
        error_output = try_decode(e.output)

        log_info("Student's code failed to run!")
        log_info("Output:", error_output)

        return RunResult(
            target=script_path.name,
            input=input_path.read_text() if input_path is not None else None,
            success=False,
            output=error_output
        )


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

    # Arguments related to the result output
    parser.add_argument(
        '--csv-out',
        nargs='?',
        const='output.csv',
        help='The file name of the CSV file containing the result'
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
    results: list[dict] = []

    # Find all student code
    student_code_paths = Path(args.directory).glob('*.py')

    # Whoopsie, filter out the unneeded ones
    student_code_paths = filter(
        lambda path: re.search(args.filter, path.name) is not None,
        student_code_paths
    )

    # For each student's code run this madness
    for student_code in student_code_paths:
        # Run the student's code for each test cases
        for testcase, answer in zip(testcase_paths, answer_list):
            # Gathering some info before running the code
            student_id = re.search(args.id_regex, student_code.name).group(0)
            student_result = run(student_code, testcase)

            results.append({
                'id': student_id,
                'code': student_code.name,
                'testcase': testcase.name if testcase is not None else None,
                'success': student_result.success,
                'correct': answer == student_result,
                'answer_result': answer,
                'student_result': student_result,
            })

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
                writer.writerow(results[0].keys())
                writer.writerows(
                    [str(value).replace('\n', '\\n') for _, value in item.items()]
                    for item in results
                )
    except Exception as e:
        log_error("Failed to write to a CSV file:", e)

    # Save the diff files if the user asked to do so
    try:
        if args.diff_out is not None:
            log_info("Writing diff files to directory:", args.diff_out)

            # Create the directory if it doesn't exist
            Path(args.diff_out).mkdir(parents=True, exist_ok=True)

            # Filter out correct students
            incorrect_results = [item for item in results if not item['correct']]

            # Start processing
            for item in incorrect_results:
                # Create a diff file for each incorrect student
                diff_file = Path(args.diff_out) / f"{item['id']}.diff"
                with open(diff_file, 'a') as f:
                    # Print the diff result to the file
                    log_debug(f"Writing diff file for student {item['id']}...")
                    f.write(item['answer_result'].diff(item['student_result']))
                    f.write("\n")
    except Exception as e:
        log_error("Failed to write to the diff file:", e)
