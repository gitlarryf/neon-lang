#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4001)      /* Disable single line comment warnings that appear in MS header files. */
#endif

#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"
#include "number.h"

char *number_to_string(Number x)
{
    static char buf[50];
    char val[50];
    bid128_to_string(val, x);
    sprintf(buf, "%g", atof(val));
    return buf;
}

/* ToDo: Implement proper number to string formatter. */
void number_toString(Number x, char *buf, size_t len)
{
    const int PRECISION = 34;
    int iLeadingZeros = 0;

    len = len;
    PRECISION;

    char val[50];
    char lead[50];
    bid128_to_string(val, x);

    char *s = &val[0];

    /* Skip over the leading +, if there is one. */
    while(*s != '\0' && (*s == '+')) s++;

    char *v = s;

    while (*s != '\0' && (*s != 'E')) s++;

    char *E = s;

    if (*s == 'E') {
        /* Deal with the exponent. */
        int i;
        iLeadingZeros = abs(atoi(++s));
        for (i = 0; i < iLeadingZeros; i++) {
            lead[i] = '0';
        }
        lead[i++] = '.';
        lead[i++] = '\0';
        strcpy(buf, lead);
    }

    *E = '\0';
    strcat(buf, v);
}

Number number_modulo(Number x, Number y)
{
    Number m = bid128_abs(y);
    if (bid128_isSigned(x)) {
        Number q = bid128_round_integral_positive(bid128_div(bid128_abs(x), m));
        x = bid128_add(x, bid128_mul(m, q));
    }
    Number r = bid128_fmod(x, m);
    if (bid128_isSigned(y) && !bid128_isZero(r)) {
        r = bid128_sub(r, m);
    }
    return r;
}

BOOL number_is_integer(Number x)
{
    Number i = bid128_round_integral_zero(x);
    return bid128_quiet_equal(x, i) != 0;
}

/*
 * Number TO functions
 */

int32_t number_to_sint32(Number x)
{
    return bid128_to_int32_int(x);
}

uint32_t number_to_uint32(Number x)
{
    return bid128_to_uint32_int(x);
}

int64_t number_to_sint64(Number x)
{ 
    return bid128_to_int64_int(x);
}

uint64_t number_to_uint64(Number x)
{
    return bid128_to_uint64_int(x);
}


/*
 * Number FROM functions
 */

Number number_from_uint64(uint64_t x)
{
    return bid128_from_uint64(x);
}

Number number_from_sint64(int64_t x)
{
    return bid128_from_int64(x);
}

#ifdef __NUMBER_TESTS
void main()
{
    assert(number_to_string(number_from_string("1234.5678e5")) == "123456780");
    assert(number_to_string(number_from_string("1234.5678e4")) == "12345678");
    assert(number_to_string(number_from_string("1234.5678e3")) == "1234567.8");
    assert(number_to_string(number_from_string("1234.5678e2")) == "123456.78");
    assert(number_to_string(number_from_string("1234.5678e1")) == "12345.678");
    assert(number_to_string(number_from_string("1234.5678e0")) == "1234.5678");
    assert(number_to_string(number_from_string("1234.5678e-1")) == "123.45678");
    assert(number_to_string(number_from_string("1234.5678e-2")) == "12.345678");
    assert(number_to_string(number_from_string("1234.5678e-3")) == "1.2345678");
    assert(number_to_string(number_from_string("1234.5678e-4")) == "0.12345678");
    assert(number_to_string(number_from_string("1234.5678e-5")) == "0.012345678");
}
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif