################################################################################
# Integration test runner for Team YACC PAL compiler.
################################################################################

import unittest
import os
import re
import types
from subprocess import check_output

PAL_EXE = "../../../bin/pal"
LEXTEST_EXE = "../../../bin/lextest"
TEST_DIR = "./integration/syntax/"


def addFailureSansTraceback(self, test, err):
    err_sans_tb = (err[0], err[1], None)
    self.failures.append((test, self._exc_info_to_string(err_sans_tb, test)))
    self._mirrorOutput = True


class NoTraceTestCase(unittest.TestCase):
    """
    Override run method to suppress python traceback on assertion failures.
    
    See http://stackoverflow.com/questions/11908784/\
        django-how-to-hide-traceback-in-unit-tests-for-readability
    """
    def run(self, result=None):
        result.addFailure = types.MethodType(addFailureSansTraceback, result)
        super(NoTraceTestCase, self).run(result)


class SyntaxUnitTests(NoTraceTestCase):
    """
    Run all integration tests in ./integration/syntax

    The test runner expects .pal files that have a comma-separated list
    of line number that contain error as the first line in the file.
    """


def get_error_lines_from_output(output):
    """
    Extract error line numbers from parser output.

    Return a list of line numbers.
    """
    line_numbers = list()

    for line in output.split("\n"):
        # ignore empty lines
        if line == "":
            continue

        num = re.findall(r"^\d+", line)
        if len(num) == 1:
            num = num[0]
            line_numbers.append(int(num))
        else:
            raise RuntimeError("Error output from parser in wrong format.")

    return line_numbers


def make_lexer_test_function(filename, expected_tokens):
    """
    Make a new test function.

    The test function runs the filename through the lexer test parser
    and checks that the expected tokens are returned in turn.
    
    Return a function object.
    """
    def new_test(self):
        output = check_output([LEXTEST_EXE, filename])
        actual_tokens = [
            re.sub(r"\(.*\)", "", line).strip()
                for line in output.split("\n") if line != ''
        ]
        
        self.assertEqual(len(expected_tokens), len(actual_tokens),
            "Number of expected tokens and actual tokens differs.\n" +
            "Expected:\t{}\ngot\t\t{}".format(expected_tokens, actual_tokens)
        )
        for i in xrange(0,len(expected_tokens)):
            self.assertEqual(expected_tokens[i], actual_tokens[i],
                "TOKEN MISMATCH at {f}. Expected {expected} got {actual}"\
                    .format(
                        f=filename,
                        expected=expected_tokens[i],
                        actual=actual_tokens[i],
                    )
            )
    
    return new_test


def make_parser_test_function(filename, expected_errors):
    """
    Make a new test function.

    The test function runs the filename through the parser
    and checks that all (and only) the expected errors are caught py the parser.

    Return a function object.
    """
    def new_test(self):
        output = check_output([PAL_EXE, filename])
        actual_errors = get_error_lines_from_output(output)
        
        for error in actual_errors:
            self.assertIn(error, expected_errors,
                "CAUGHT ERROR at {f}, line {l} where none is expected."\
                .format(l=error, f=filename)
            )
        for error in expected_errors:
            self.assertIn(error, actual_errors,
                "MISSED ERROR at {f}, line {l} but one is expected."\
                .format(l=error, f=filename)
            )

    return new_test


def construct_tests():
    """
    For each discovered file, add a test to SyntaxUnitTests.
    """
    files = dict()

    os.chdir(TEST_DIR)

    # get all test files
    for f in os.listdir("."):
        if f.endswith(".pal"):
            files.update({f:''});

    # for each file, extract error line numbers
    for f in files:
        with open(f) as fp:
            line = fp.readline()
            files[f] = {
                'errors': None,
                'tokens': None,
            }
            
            # remove comment braces, newline, and whitespace
            mapping = [("\n", ""), (" ", ""), ("{", ""), ("}", "")]
            for k,v in mapping:
                line = line.replace(k,v)
            
            # if errors are specified, add them to the error list for this file
            if line != '':
                files[f]['errors'] = line.split(",")            
                # convert to int
                if len(files[f]['errors']) > 0:
                    files[f]['errors'] = [int(s) for s in files[f]['errors']]
            else:
                files[f]['errors'] = []
    
    # look for .tokens pairing
    for f in files.keys():
        tokens_pair = f[:-4] + '.tokens'
        try:
            with open(tokens_pair) as fp:
                files[f]['tokens'] = list()
                for line in fp.read().split("\n"):
                    if line != '':
                        files[f]['tokens'].append(line)
        except:
            # do nothin if file can't be opened
            pass


    # for each file, make a parser test case
    for filename, values in files.items():
        expected_errors = values['errors']
        name = "test_parser_{}".format(filename[:-4])

        new_test = make_parser_test_function(filename, expected_errors)

        if getattr(SyntaxUnitTests, name, None) is not None:
            raise RuntimeError("Duplicate test name: {}".format(name))
        else:
            setattr(SyntaxUnitTests, name, new_test)

    # if a file with expected tokens is given, make tokenizer test case
    for filename, values in files.items():
        expected_tokens = values['tokens']
        name = "test_lexer_{}".format(filename[:-4])
        if expected_tokens is not None:
            new_test = make_lexer_test_function(filename, expected_tokens)

            if getattr(SyntaxUnitTests, name, None) is not None:
                raise RuntimeError("Duplicate test name: {}".format(name))
            else:
                setattr(SyntaxUnitTests, name, new_test)
            

if __name__ == "__main__":
    construct_tests()
    unittest.main()
