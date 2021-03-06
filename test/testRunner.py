################################################################################
# Integration test runner for Team YACC PAL compiler.
################################################################################

import unittest
import os
import re
import types
import sys
import getopt
import difflib
import subprocess
from subprocess import check_output
from subprocess import check_call

ASC_EXE = "../../../bin/asc"
GEN_ASC_DIR = "./generated_asc"
TEST_ASC_DIR = "./test_asc"

PAL_EXE = "../../../bin/pal"
PAL_OPTION1 = "-n"
PAL_OPTION2 = "-c"
PAL_OPTION3 = "-S"

LEXTEST_EXE = "../../../bin/lextest"

TEST_TYPE = {
    'syntax' : 0,
    'semantic': 1,
    'full': 2,
    'asc': 3,
}

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


class AscUnitTests(NoTraceTestCase):
    """
    Class for tests which assert the correctness of the ASC code generated by
    the compiler.
    
    Tests runner assumes the existence for each a .pal file a corresponding
    .asc file against which the file generated by the compiler is to be 
    compared.  Optionally, a comma separated list of the expected output
    can be passed as the first line of the function againt which the output
    produced will be tested.
    """

def filter_line_by_test_type(line, test_type):
    """
    Return True if the line should be evaluated for the given test_type.
    """
    # skip empty lines
    if line == '':
        return False

    if test_type == TEST_TYPE['syntax']:
        prog = re.compile(r'^\d+ Syntax.*$', re.IGNORECASE)
        if prog.search(line) is None:
            return False
    elif test_type == TEST_TYPE['semantic']:
        prog = re.compile(r'^\d+ Semantic.*$', re.IGNORECASE)
        if prog.search(line) is None:
            return False
    elif test_type == TEST_TYPE['full']:
        prog = re.compile(r'^\d+ .*', re.IGNORECASE)
        if prog.search(line) is None:
            return False
    elif test_type == TEST_TYPE['asc']:
        prog = re.compile(r'Running...\n', re.IGNORECASE)
        if prog.search(line) is not None:
            return False
    else:
        return False

    return True


def get_error_lines_from_output(output, test_type):
    """
    Extract error line numbers from parser output.

    Return a list of line numbers.
    """
    line_numbers = list()

    for line in output.split("\n"):
        # ignore empty lines
        if filter_line_by_test_type(line, test_type) == False:
            continue

        num = re.findall(r"^\d+", line)
        if len(num) == 1:
            num = num[0]
            line_numbers.append(int(num))
        else:
            raise RuntimeError("Error output from parser in wrong format.")

    return line_numbers

def get_metadata_from_output(output):
    """
    Extract expected output values from the parser output.
    Return a list of the output received.
    """
    output_list = list()
    
    for line in output.split("\n"):
        # Ignore the default output produced by the asc runner
	if filter_line_by_test_type(line, test_type) == False:
            continue;
        output_list.append(line)
    return output_list

def make_lexer_test_function(filename, expected_tokens):
    """
    Make a new test function.

    The test function runs the filename through the lexer test parser
    and checks that the expected tokens are returned in turn.
    
    Return a function object.
    """
    def new_test(self):
        output = check_output([LEXTEST_EXE, PAL_OPTION1, PAL_OPTION2,\
            filename])
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


def make_parser_test_function(filename, expected_errors, test_type):
    """
    Make a new test function.

    The test function runs the filename through the parser and
    checks that all (and only) the expected errors are caught by the parser.

    Return a function object.
    """

    def new_test(self):
        output = check_output([PAL_EXE, PAL_OPTION1, PAL_OPTION2, filename])
        actual_errors = get_error_lines_from_output(output, test_type)

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

def make_asc_test_function(filename, expected_output, asc_filename):
    """
    Creates a new test function.
    
    The test function runs the compiler on the given file (specified by
    filename) and asserts that the generated .asc file differs from the hand
    crafted .asc file (specified by asc_file) in only the allowable way (e.g.,
    whitespace, comments, etc.) and then runs the generated .asc file and 
    insures the output generated is as expected.
    """
    def new_test(self):
        # First, the compiler is run on the given file (specified by filename)
        # in order to determine if the generated asc file is as expected.

        try:
            check_call([PAL_EXE, PAL_OPTION1, PAL_OPTION2, PAL_OPTION3,\
                filename])

        except OSError:
            print "Failed to open pal executable with filename = ", filename
            #exit    

        # Move the generated asc file into the appropriate directory (makes
        # later inspection easier)
        try:
            check_call(["mv", filename[:-4] + ".asc", GEN_ASC_DIR])

        except OSError:
            print "Failed to call bash cmd \"mv\"", filename
            #exit    
        
        # We first strip the comments from the hand-crafted .asc file.
	testasc_filepath = TEST_ASC_DIR + '/' + asc_filename
	strip_comments_regexp = r'#(.*)(\n)'
        asc_file_text = ''
        with open(testasc_filepath, "r") as asc_file:
            asc_file_text= asc_file.read()
            asc_file_text = re.sub(strip_comments_regexp, '\n', asc_file_text)

        # Now we strip the comments from the newly generated .asc file
        genasc_filepath = GEN_ASC_DIR + '/' + (filename[:-4] + ".asc")
        genasc_file_text = ''
        with open(genasc_filepath, "r") as genasc_file:
            genasc_file_text = genasc_file.read()
            genasc_file_text = re.sub(strip_comments_regexp, '\n', 
                genasc_file_text)
      

        # Next we strip whitespace characters (' ', '\t', '\n')
        whitespace_chars = ' \t\n'
        asc_file_text = asc_file_text.translate(None, whitespace_chars)
        genasc_file_text = genasc_file_text.translate(None, whitespace_chars)

        # Then we convert both strings to upper case
        asc_file_text = asc_file_text.upper()
        genasc_file_text = genasc_file_text.upper()

        # Now, using difflib, we assure that the two files are equal modulo
        # whitespace and other unimportant characteristics.
        sm = difflib.SequenceMatcher(None, asc_file_text, genasc_file_text)

        # If ratio != 1.0, we print the diff output to help in debugging
        if sm.ratio() != 1.0:
            err_str = "{}: Generated asc file does match expected output".\
                format(asc_filename) 
            print err_str
            print genasc_filepath
            diff_args = "-I \"#(.*)(\n)\" --ignore-case --ignore-all-space"

            try:
                check_call(["diff", diff_args, testasc_filepath, \
                    genasc_filepath])
            except subprocess.CalledProcessError as e:
                print e

            self.assertEqual(sm.ratio(), 1.0) 
 
        # Now we run the generated asc file and compare the output we got
        # with the output that we expected. 
       # output = check_output([ASC_EXE, genasc_filepath])
        
       #actual_output = get_metadata_from_output(output)
	
       # self.assertSequenceEqual(expected_output, actual_output,
       #   "Mismatched outputs.")
    return new_test

def construct_tests(test_type, test_dir, ignore_expected_errors):
    """
    For each discovered file, add a test to SyntaxUnitTests.
    """
    files = dict()

    os.chdir(test_dir)

    print test_dir

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
                'output': None,
            }
            
            # remove comment braces, newline, and whitespace
            mapping = [("\n", ""), ("{", ""), ("}", "")]
            for k,v in mapping:
                line = line.replace(k,v)
            
            #if we are performing an asc test, then the first line corresponds
            # to the the expected output of the file, else it corresponds to
            # the errors we expect to see in the program
            if test_type == TEST_TYPE['asc']:
                meta_data = 'output'
            else:
                meta_data = 'errors'
            
            # if meta_data specified, we populate the appropriate list
            # for this file
            if line != '':
                files[f][meta_data] = line.split(",")            
                # convert to int
                if len(files[f][meta_data]) > 0 and meta_data == 'errors':
                    files[f][meta_data] =[int(s) for s in files[f][meta_data]]
            else:
                files[f][meta_data] = []
   
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

    if test_type == TEST_TYPE["asc"]:
        for filename, values in files.items():
            expected_output = values['output']
            name = "test_ascgen_{}".format(filename[:-4])

            new_test = make_asc_test_function(filename, expected_output,
                filename[:-4] + ".asc")
            if getattr(AscUnitTests, name, None) is not None:
                raise RuntimeError("Duplicate test name: {}".formate(name))
            else:
                setattr(AscUnitTests, name, new_test)
    
    else:
        for filename, values in files.items():
            expected_errors = values['errors']
            name = "test_parser_{}".format(filename[:-4])

            if ignore_expected_errors:
                expected_errors = []

            new_test = make_parser_test_function(filename, expected_errors, 
                                                 test_type)

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
    """
    Parse arguments and run appropriate tests.
    """
    test_dir = '/'
    bin_dir = '/../bin/'
    test_type = TEST_TYPE['full'];
    test_type_set = False            # set true if an arg has already been
                                     # parsed such that it defined the type of
                                     # the tests to be run
    ignore_expected_errors = False

    # copy argv and then clear it so that unittest.main() doesn't get our args
    argv = sys.argv[1:]
    sys.argv = sys.argv[0:1]
    usage = "Run with -x option for syntax tests or -c option for semantic "\
            "tests.\n"\
            "By default both types of tests are run.\n"\
            "Use -i option to ignore expected error list.\n"\
            "Use -d option to specify test directory.\n"\
            "Use -a option to run asc tests."
    
    try:
        opts, args = getopt.getopt(argv, "h?xcitad:")
    except getopt.GetoptError:
        print usage
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h' or opt == '-?':
            print usage
            sys.exit()
        elif opt == '-x':
            if not test_type_set:
                test_type = TEST_TYPE['syntax']
                test_type_set = True
            else:
                print usage
                sys.exit()
        elif opt == '-c':
            if not test_type_set:
                test_type = TEST_TYPE['semantic']
                test_type_set = True
            else:
                print usage
                sys.exit()
        elif opt == '-a':
            if not test_type_set:
                test_type = TEST_TYPE['asc']
                test_type_set = True
            else:
                print usage
                sys.exit()
                
        elif opt == '-d':
            test_dir = arg
        elif opt == '-i':
            ignore_expected_errors = True

    construct_tests(test_type, test_dir, ignore_expected_errors)
    unittest.main()
