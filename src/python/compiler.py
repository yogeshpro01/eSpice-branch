"""
Program to compile Brainfuck to Python
(c) 2017 Kabir Goel
"""

class BrainfuckCompilerError(Exception):
    pass


def _get_code(cmd):
    """
    Accepts a Brainfuck command and returns the corresponding Python code
    as well as the level to which the block should be indented.

    :param cmd: Brainfuck instruction
    :type cmd: str
    :return: Python code corresponding to the Brainfuck command and relative
             number indicating the level to which the following block should
             be indented
    :rtype: (tuple, int)
    """
    subs = {
        '+': 'mem[ptr] += 1',
        '>': 'ptr += 1',# 'if ptr > len(mem):', '    mem.append(0)',
        '-': 'mem[ptr] -= 1',
        '<': 'ptr -= 1',# 'if ptr < 0:', '    ptr = 0', 'mem.insert(0, 0)',
        '[': 'while mem[ptr] > 0:',
        ']': '',
        '.': 'print(chr(mem[ptr]), end="", flush=True)',
        ',': 'mem[ptr] = sys.stdin.read(1)',
    }
    # handle indentation
    indent = 0
    if cmd == '[':
        # if the command is '[', then a while loop will be created
        # in this case, increase indent by one level
        indent = 1
    elif cmd == ']':
        # if the command is ']', then a while loop will be ended
        # in this case, decrease indent by one level
        indent = -1
    return subs.get(cmd, ''), indent


def _indent_level(n):
    """
    Return indentation corresponding to n levels of nesting.

    :param n: levels of nesting
    :type n: int
    :return: indentation (in spaces of 4) corresponding to n levels of nesting
    :rtype: str
    """
    return ' ' * 4 * n


def compile(src, join=False):
    """
    Compile the given Brainfuck source code to well formatted Python code.
    Raises a BrainfuckError if there is an error in the source.

    :param src: Brainfuck source code
    :param join: whether to join the return value using newlines
                 (defaults to returning list of lines)
    :return: either a list of lines of code or a string, depending on the value
             of join
    """
    # output code
    res = ['mem, ptr = [0] * 30000, 0']

    # keeps track of nesting level, for indentation
    level = 0
    # keep track of line in source code for useful error messages
    lnum, charnum = 1, 1
    # keep track of number of opening and closing brackets
    # if l != r at the end then it means that the program is incorrect
    l, r = 0, 0

    for char in src:
        # if a newline is hit, set position accordingly
        if char == '\n':
            lnum += 1
            charnum = 1
        elif char == '[':
            l += 1
        elif char == ']':
            r += 1

        code, indent = _get_code(char)
        # removing the following `if' will have the effect of littering the
        # output with empty lines
        if code == '':
            level += indent
            continue

        if level < 0:
            raise BrainfuckCompilerError(
                    "unexpected token ']' at {}:{} (no corresponding '[')"
                    .format(lnum, charnum)
                )

        res.append(_indent_level(level) + code)

        level += indent
        charnum += 1

    if l != r:
        raise BrainfuckCompilerError('unclosed loop')
    if len(res) == 1:
        return ''

    return '\n'.join(res) if join else res
