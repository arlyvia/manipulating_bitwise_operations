/* REMEMBER:
 * - This is the only file that you need to edit!
 * - Declare variables only at the beginning of a function (as in C89).
 * - Do not include <stdio.h> header (it confuses dlc)
 * - Check correctness with ./btest -f funcName
 * - Check operator constraints with ./dlc bits.c
 * - Run ./grade before you commit/push your solution
 */

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 1
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
  //return 2;
}

/*
 * bitAnd - x&y using only ~ and |
 * (tip: always remember De Morgan's laws!)
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 4
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
  //return 2;
}

/*
 * negate - return -x
 * (tip: remember the definition of two's complement!)
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int negate(int x) {
  return ~x + 1;
  //return 2;
}

/*
 * isEqual - return 1 if x == y, and 0 otherwise
 * (tip: which bitwise op computes the difference?)
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x^y);
  //return 2;
}

/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 3
 */
int addOK(int x, int y) {
  int x_sign = x >> 31 & 1;
  int y_sign = y >> 31 & 1;
  int result_sign = (x + y) >> 31 & 1;

  return !(~(x_sign ^ y_sign) & (x_sign ^ result_sign));
  //return 2;
}

/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  return (0x1F << 24 >> (x >> 1)) & !(x >> 6);
  //return 2;
}

/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum negative value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 4
 */
int satAdd(int x, int y) {
  //return 2;
  int add = x + y;

  int x_sign = x >> 31;
  int y_sign = y >> 31;
  int xy_sign = add >> 31;

  int overflow = (~(x_sign ^ y_sign)) & (x_sign ^ xy_sign);
  
  //pos overflow
  //overflow & x < 0
  int pos_over = overflow & (~(x_sign ^ 0));
  
  //neg overflow
  //overflow & x > 0
  int neg_over = ~(overflow & (~(x_sign ^ 0)));
  
  //min neg and max pos
  int min = 1 << 31;
  int max = ~min;
  
  int result = (~overflow & add) | (overflow & ((pos_over & max) | (neg_over & min)));
  return result;
}

/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int dividePower2(int x, int n) {
  int neg = x >> 31;
  int tmp = ((neg & 1) << n) + neg;

  return (x + tmp) >> n;
  //return 2;
}

/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int a= n << 3;
	int masker= 0xFF << a;
	int shifter = c << a;
	return (x & ~masker) | shifter;
  //return 2;
}

/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 5
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  //return 2;
  unsigned mask = uf & 0x007fffff;
  unsigned exp = (uf & 0x7f800000);

  return (exp == 0x7f800000 && mask) ? uf : (0x7fffffff & uf);
}

/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 19
 *   Rating: 3
 */
int floatIsEqual(unsigned uf, unsigned ug) {
  int mask = 0x7fffffff;
  int exp_mask = 0x7f800000;

  int is_NaN = ((uf & mask) > exp_mask || (ug & mask) > exp_mask);
  int zeros = (!((uf & mask) || ((ug & mask))));

  return (!is_NaN) && (zeros || (uf == ug));
  //return 2;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 16
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  if (x < -149) {
    return 0;
  }
  if (x < -126) {
    return 0x800000 >> (-126 - x);
  }
  if (x <= 127) {
    return (x + 127) << 23;
  } else {
    return 0xff << 23;
  }
}
