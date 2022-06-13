# simplyBytecode
Simple bytecode thingy which transforms an int statement into bytes which can be read if you write a compiler for it

Example:

int a = 5

 |
 V

INTSTORE_1
INTCONST_a_5

long b = 5.2

 |
 V

LONGSTORE_1
LONGCONST_b_5.2
