#include <thread>
#include <sys/select.h>
#include <sys/time.h>

#include "number.h"
#include "rtl_platform.h"

namespace rtl {

namespace time {

void sleep(Number seconds)
{
    //std::chrono::microseconds us(number_to_uint64(number_multiply(seconds, number_from_uint32(1000000))));
    struct timeval tv;
    tv.tv_usec = number_to_uint64(number_multiply(seconds, number_from_uint32(1000000)));
    select(0, NULL, NULL, NULL, &tv);
//    std::this_thread::sleep_for(us);
}

} // namespace time

} // namespace rtl
