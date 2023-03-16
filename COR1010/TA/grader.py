#!/usr/bin/env python

import os
import sys

import argparse
import csv
import logging
import subprocess
import re
import traceback

from pathlib import Path


# Standard I/O's encoding
STDOUT_ENCODING = sys.stdout.encoding or sys.getdefaultencoding()
STDIN_ENCODING = sys.stdin.encoding or sys.getdefaultencoding()

# Logging level
#  - 0: No logging
#  - 1: Informational info
#  - 2: Debugging info
LOG_LEVEL = 1


def log_info(*args, **kwargs):
    """Log an informational message."""
    if LOG_LEVEL > 0:
        print(*args, **kwargs)


def log_debug(*args, **kwargs):
    """Log a debugging message."""
    if LOG_LEVEL > 1:
        print(*args, **kwargs)


def run_without_input(script_path: Path) -> str:
    """Run a file and return its output."""
    log_info(f"Running file {script_path}...")
    output = subprocess.check_output(
        ['python', script_path],
        stderr=subprocess.STDOUT
    )
    return True, output.decode(STDOUT_ENCODING)


def run_with_input(script_path: Path, input_path: Path) -> str:
    """Run a file with a given input as stdin and return its output."""
    log_info(f"Running file {script_path} with input {input_path}...")
    with open(input_path, "r") as f:
        output = subprocess.check_output(
            ['python', script_path],
            stdin=f,
            stderr=subprocess.STDOUT
        )
    return True, output.decode(STDOUT_ENCODING)


def run(script_path: Path, input_path: Path = None) -> str:
    """Run a script and return its output."""

    # Of course, their code can set this computer on fire
    try:
        if input_path is None:
            return run_without_input(script_path)
        else:
            return run_with_input(script_path, input_path)
    except subprocess.CalledProcessError as e:
        # Oh no who would've guessed
        log_info("Student's code failed to run!")
        log_info("Output:", e.output.decode("utf-8"))
        
        return False, e.output.decode("utf-8")

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

    # Enable CSV output?
    parser.add_argument(
        '--csv-out',
        nargs='?',
        const='output.csv',
        help='The file name of the CSV file containing the result'
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
            normal_exit, answer_output = run(Path(args.answer_code), testcase_path)
            answer_list.append(answer_output)
    else:
        for answer_text in args.answer_text:
            with open(answer_text, 'r') as f:
                answer_list.append(f.read())

    # Set up a list to store results
    results = [['Student ID', 'Filename', 'Student Output', 'Correct Output', 'Result']]

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
            
            normal_exit, student_output = run(student_code, testcase)

            results.append([
                student_id,
                student_code.name,
                'Failed to run' if not normal_exit else student_output,
                answer,
                'correct' if student_output == answer else 'incorrect'
            ])

    # Print the result just in case...
    for row in results:
        log_info(f"{row[0]}'s code in {row[1]} is {row[4]}.")

    # ...and save it if the user asked to do so
    if args.csv_out is not None:
        log_info("Writing to a CSV file: " + args.csv_out)
        with open(args.csv_out, 'w', encoding='utf-8-sig') as f:
            writer = csv.writer(f)
            writer.writerows([s.replace('\n', '\\n') for s in row] for row in results)
