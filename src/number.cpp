#include "number.h"

#if defined(NUMBER_DOUBLE)

#include <math.h>

Number number_add(Number x, Number y)
{
    return x.x + y.x;
}

Number number_subtract(Number x, Number y)
{
    return x.x - y.x;
}

Number number_multiply(Number x, Number y)
{
    return x.x * y.x;
}

Number number_divide(Number x, Number y)
{
    return x.x / y.x;
}

Number number_modulo(Number x, Number y)
{
    return fmod(x.x, y.x);
}

Number number_pow(Number x, Number y)
{
    return pow(x.x, y.x);
}

Number number_negate(Number x)
{
    return - x.x;
}

Number number_abs(Number x)
{
    return fabs(x.x);
}

Number number_ceil(Number x)
{
    return ceil(x.x);
}

Number number_floor(Number x)
{
    return floor(x.x);
}

Number number_exp(Number x)
{
    return exp(x.x);
}

Number number_log(Number x)
{
    return log(x.x);
}

Number number_sqrt(Number x)
{
    return sqrt(x.x);
}

Number number_acos(Number x)
{
    return acos(x.x);
}

Number number_asin(Number x)
{
    return asin(x.x);
}

Number number_atan(Number x)
{
    return atan(x.x);
}

Number number_cos(Number x)
{
    return cos(x.x);
}

Number number_sin(Number x)
{
    return sin(x.x);
}

Number number_tan(Number x)
{
    return tan(x.x);
}

bool number_is_zero(Number x)
{
    return x.x == 0;
}

bool number_is_equal(Number x, Number y)
{
    return x.x == y.x;
}

bool number_is_not_equal(Number x, Number y)
{
    return x.x != y.x;
}

bool number_is_less(Number x, Number y)
{
    return x.x < y.x;
}

bool number_is_greater(Number x, Number y)
{
    return x.x > y.x;
}

bool number_is_less_equal(Number x, Number y)
{
    return x.x <= y.x;
}

bool number_is_greater_equal(Number x, Number y)
{
    return x.x >= y.x;
}

bool number_is_integer(Number x)
{
    return x.x == trunc(x.x);
}

std::string number_to_string(Number x)
{
    std::string r = std::to_string(x.x);
    
    // TODO: This hack converts a canonical string like 42.00000 to just 42
    const auto d = r.find('.');
    if (d != std::string::npos) {
        auto i = d + 1;
        while (i < r.length() && r.at(i) == '0') {
            i++;
        }
        if (i >= r.length()) {
            r = r.substr(0, d);
        }
    }

    return r;
}

uint8_t number_to_uint8(Number x)
{
    // TODO: handle out of range exception
    return static_cast<uint8_t>(trunc(x.x));
}

int8_t number_to_sint8(Number x)
{
    // TODO: handle out of range exception
    return static_cast<int8_t>(trunc(x.x));
}

uint16_t number_to_uint16(Number x)
{
    // TODO: handle out of range exception
    return static_cast<uint16_t>(trunc(x.x));
}

int16_t number_to_sint16(Number x)
{
    // TODO: handle out of range exception
    return static_cast<int16_t>(trunc(x.x));
}

uint32_t number_to_uint32(Number x)
{
    // TODO: handle out of range exception
    return static_cast<uint32_t>(trunc(x.x));
}

int32_t number_to_sint32(Number x)
{
    // TODO: handle out of range exception
    return static_cast<int32_t>(trunc(x.x));
}

uint64_t number_to_uint64(Number x)
{
    // TODO: handle out of range exception
    return static_cast<uint64_t>(trunc(x.x));
}

int64_t number_to_sint64(Number x)
{
    // TODO: handle out of range exception
    return static_cast<int64_t>(trunc(x.x));
}

float number_to_float(Number x)
{
    // TODO: handle out of range exception
    return static_cast<float>(trunc(x.x));
}

double number_to_double(Number x)
{
    // TODO: handle out of range exception
    return static_cast<double>(trunc(x.x));
}

Number number_from_string(const std::string &s)
{
    return stod(s);
}

Number number_from_uint8(uint8_t x)
{
    return x;
}

Number number_from_sint8(int8_t x)
{
    return x;
}

Number number_from_uint16(uint16_t x)
{
    return x;
}

Number number_from_sint16(int16_t x)
{
    return x;
}

Number number_from_uint32(uint32_t x)
{
    return x;
}

Number number_from_sint32(int32_t x)
{
    return x;
}

Number number_from_uint64(uint64_t x)
{
    return static_cast<double>(x);
}

Number number_from_sint64(int64_t x)
{
    return static_cast<double>(x);
}

Number number_from_float(float x)
{
    return x;
}

Number number_from_double(double x)
{
    return x;
}

#elif defined(NUMBER_DECIMAL)

Number number_add(Number x, Number y)
{
    return bid64_add(x.x, y.x);
}

Number number_subtract(Number x, Number y)
{
    return bid64_sub(x.x, y.x);
}

Number number_multiply(Number x, Number y)
{
    return bid64_mul(x.x, y.x);
}

Number number_divide(Number x, Number y)
{
    return bid64_div(x.x, y.x);
}

Number number_modulo(Number x, Number y)
{
    return bid64_rem(x.x, y.x);
}

Number number_pow(Number x, Number y)
{
    return bid64_pow(x.x, y.x);
}

Number number_negate(Number x)
{
    return bid64_negate(x.x);
}

Number number_abs(Number x)
{
    return bid64_abs(x.x);
}

Number number_ceil(Number x)
{
    // TODO: find proper ceil function to handle full range of decimal64
    return bid64_from_int64(bid64_to_int64_ceil(x.x));
}

Number number_floor(Number x)
{
    // TODO: find proper floor function to handle full range of decimal64
    return bid64_from_int64(bid64_to_int64_floor(x.x));
}

Number number_exp(Number x)
{
    return bid64_exp(x.x);
}

Number number_log(Number x)
{
    return bid64_log(x.x);
}

Number number_sqrt(Number x)
{
    return bid64_sqrt(x.x);
}

Number number_acos(Number x)
{
    return bid64_acos(x.x);
}

Number number_asin(Number x)
{
    return bid64_asin(x.x);
}

Number number_atan(Number x)
{
    return bid64_atan(x.x);
}

Number number_cos(Number x)
{
    return bid64_cos(x.x);
}

Number number_sin(Number x)
{
    return bid64_sin(x.x);
}

Number number_tan(Number x)
{
    return bid64_tan(x.x);
}

bool number_is_zero(Number x)
{
    return bid64_isZero(x.x) != 0;
}

bool number_is_equal(Number x, Number y)
{
    return bid64_quiet_equal(x.x, y.x) != 0;
}

bool number_is_not_equal(Number x, Number y)
{
    return bid64_quiet_not_equal(x.x, y.x) != 0;
}

bool number_is_less(Number x, Number y)
{
    return bid64_quiet_less(x.x, y.x) != 0;
}

bool number_is_greater(Number x, Number y)
{
    return bid64_quiet_greater(x.x, y.x) != 0;
}

bool number_is_less_equal(Number x, Number y)
{
    return bid64_quiet_less_equal(x.x, y.x) != 0;
}

bool number_is_greater_equal(Number x, Number y)
{
    return bid64_quiet_greater_equal(x.x, y.x) != 0;
}

bool number_is_integer(Number x)
{
    BID_UINT64 i = bid64_round_integral_zero(x.x);
    return bid64_quiet_equal(x.x, i) != 0;
}

std::string number_to_string(Number x)
{
    char buf[40];
    bid64_to_string(buf, x.x);
    std::string sbuf(buf);
    const std::string::size_type E = sbuf.find('E');
    if (E == std::string::npos) {
        // Inf or NaN
        return sbuf;
    }
    int exponent = std::stoi(sbuf.substr(E+1));
    sbuf = sbuf.substr(0, E);
    const std::string::size_type last_significant_digit = sbuf.find_last_not_of('0');
    if (last_significant_digit == 0) {
        return "0";
    }
    const int trailing_zeros = static_cast<int>(sbuf.length() - (last_significant_digit + 1));
    exponent += trailing_zeros;
    sbuf = sbuf.substr(0, last_significant_digit + 1);
    if (exponent != 0) {
        if (exponent > 0 && sbuf.length() + exponent <= 17) {
            sbuf.append(exponent, '0');
        } else if (exponent < 0 && -exponent < static_cast<int>(sbuf.length()-1)) {
            sbuf = sbuf.substr(0, sbuf.length()+exponent) + "." + sbuf.substr(sbuf.length()+exponent);
        } else if (exponent < 0 && -exponent == static_cast<int>(sbuf.length()-1)) {
            sbuf = sbuf.substr(0, 1) + "0." + sbuf.substr(1);
        } else if (exponent < 0 && sbuf.length() - exponent <= 18) {
            sbuf.insert(1, "0." + std::string(-exponent-1, '0'));
        } else {
            exponent += static_cast<int>(sbuf.length() - 2);
            if (sbuf.length() >= 3) {
                sbuf.insert(2, 1, '.');
            }
            sbuf.push_back('e');
            sbuf.append(std::to_string(exponent));
        }
    }
    if (sbuf.at(0) == '+') {
        sbuf = sbuf.substr(1);
    }
    return sbuf;
}

uint8_t number_to_uint8(Number x)
{
    return bid64_to_uint8_int(x.x);
}

int8_t number_to_sint8(Number x)
{
    return bid64_to_int8_int(x.x);
}

uint16_t number_to_uint16(Number x)
{
    return bid64_to_uint16_int(x.x);
}

int16_t number_to_sint16(Number x)
{
    return bid64_to_int16_int(x.x);
}

uint32_t number_to_uint32(Number x)
{
    return bid64_to_uint32_int(x.x);
}

int32_t number_to_sint32(Number x)
{
    return bid64_to_int32_int(x.x);
}

uint64_t number_to_uint64(Number x)
{
    return bid64_to_uint64_int(x.x);
}

int64_t number_to_sint64(Number x)
{
    return bid64_to_int64_int(x.x);
}

float number_to_float(Number x)
{
    return bid64_to_binary32(x.x);
}

double number_to_double(Number x)
{
    return bid64_to_binary64(x.x);
}

Number number_from_string(const std::string &s)
{
    return bid64_from_string(const_cast<char *>(s.c_str()));
}

Number number_from_uint8(uint8_t x)
{
    return bid64_from_uint32(x);
}

Number number_from_sint8(int8_t x)
{
    return bid64_from_int32(x);
}

Number number_from_uint16(uint16_t x)
{
    return bid64_from_uint32(x);
}

Number number_from_sint16(int16_t x)
{
    return bid64_from_int32(x);
}

Number number_from_uint32(uint32_t x)
{
    return bid64_from_uint32(x);
}

Number number_from_sint32(int32_t x)
{
    return bid64_from_int32(x);
}

Number number_from_uint64(uint64_t x)
{
    return bid64_from_uint64(x);
}

Number number_from_sint64(int64_t x)
{
    return bid64_from_int64(x);
}

Number number_from_float(float x)
{
    return binary32_to_bid64(x);
}

Number number_from_double(double x)
{
    return binary64_to_bid64(x);
}

#endif
