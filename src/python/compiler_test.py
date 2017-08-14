from unittest import TestCase, main
from unittest.mock import patch, call
import compiler


class CompilerTest(TestCase):
    def setUp(self):
        pass
        self.output = print

    def test_plus(self):
        self.assertIn('+', compiler.compile('+', join=True))

    def test_minus(self):
        self.assertIn('-', compiler.compile('-', join=True))

    def test_right(self):
        self.assertIn('+', compiler.compile('>', join=True))

    def test_left(self):
        self.assertIn('-', compiler.compile('<', join=True))

    def test_input(self):
        self.assertIn('read', compiler.compile(',', join=True))

    def test_loop(self):
        compiled = compiler.compile('[]', join=True)
        self.assertTrue('while' in compiled or 'for' in compiled)

    def test_print(self):
        compiled = compiler.compile('++.', join=True)
        self.assertIn('print', compiled)

    @patch('sys.stdin.read', autospec=True)
    @patch('builtins.print', autospec=True)
    def test_hello_world(self, mock_print, mock_read):
        compiled = compiler.compile(
            """++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++
            ..+++.>>.<-.<.+++.------.--------.>>+.>++.""",
            join=True
        )
        exec(compiled)
        calls = [call(i, end='', flush=True) for i in 'Hello World!']
        mock_print.assert_has_calls(calls)

    def test_exception_raised_when_unclosed_loop(self):
        with self.assertRaises(compiler.BrainfuckCompilerError):
            compiler.compile('[')

    def test_exception_raised_when_unexpected_token(self):
        with self.assertRaises(compiler.BrainfuckCompilerError):
            compiler.compile(']')


if __name__ == '__main__':
    main()
