const interpreter = require('./interpreter');
const assert = require('assert');
const parse = interpreter.parse;
const eval = interpreter.eval;

/*
 * Tests for parser
 */
assert.deepEqual(parse('++,.-').res, ['+', '+', ',', '.', '-'], 'test primitive operators');
assert.deepEqual(parse('[..++><,-]').res, [['.', '.', '+', '+', '>', '<', ',', '-']], 'test loop');
assert.deepEqual(parse('[.,[+,.[]]]').res, [['.', ',', ['+', ',', '.', []]]], 'test nested loop');
assert.equal(parse('++[.[]').error, 'unterminated loop');


/*
 * Tests for eval
 */
assert.equal(eval('+++').mem[0], 3, 'test memory');
assert.equal(eval('++>>><').ptrPos, 2, 'test memory navigation');
assert.equal(eval('++++++++[>+++++++++<-]>.').stdout[0], 'H', 'test stdout');
assert.equal(eval('[[]').error, 'unterminated loop');
assert.deepEqual(
  eval(
    '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.\
    >---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'
  ).stdout,
  ['H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\n'],
  'test hello world'
);