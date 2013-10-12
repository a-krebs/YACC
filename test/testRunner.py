################################################################################
# Integration test runner for Team YACC PAL compiler.
################################################################################

import unittest
import os
import re
from subprocess import Popen, PIPE


class SyntaxUnitTests(unittest.TestCase):
    """
    Run all integration tests in ./integration/syntax

    The test runner expects .pal files that have a comma-separated list
    of line number that contain error as the first line in the file
    """


def get_error_lines_from_stderr(output):
    """
    Parse stderr output and extract error line numbers.

    Return a list of line numbers.
    """
    lines = list()

    for line in output:
        num = re.findall(r"^\d+", line)
        if len(num) == 1:
            num = num[0]
            lines.append(int(num))
        else:
            raise RuntimeError("Error output in wrong format.")

    return lines


def construct_tests():
    """
    For each discovered file, add a test to SyntaxUnitTests.
    """
    files = dict()
    os.chdir("./integration/syntax");

    # get all test files
    for f in os.listdir("."):
        if f.endswith(".pal"):
            files.update({f:''});

    # for each file, extract error line numbers
    for f in files:
        with open(f) as fp:
            line = fp.readline()

            mapping = [("\n", ""), (" ", ""), ("{", ""), ("}", "")]
            for k,v in mapping:
                line = line.replace(k,v)

            files[f] = line.split(",")
            # convert to int
            files[f] = [int(s) for s in files[f]]

    # for each file, make test case
    for filename, expected_errors in files.items():
        name = "test_{}".format(f.rstrip(".pal"))

        def new_test(self):
            output = Popen(["../../../bin/pal", filename], stdout=PIPE)\
                .communicate()[0]
            actual_errors = get_error_lines_from_stderr(output)
            
            for error in actual_errors:
                self.assertIn(error, expected_errors,
                    "{f}:{l} has an error where none is expected"\
                    .format(l = error, f = filename)
                )
            for error in expected_errors:
                self.assertIn(error, actual_errors,
                    "{f}:{l} doesn't have an error, but one is expected."\
                    .format(l = error, f = filename)
                )

        if getattr(SyntaxUnitTests, name, None) is not None:
            raise RuntimeError("Duplicate test name: {}".format(name))
        else:
            setattr(SyntaxUnitTests, name, new_test) 
            

if __name__ == "__main__":
    construct_tests()
    unittest.main()
