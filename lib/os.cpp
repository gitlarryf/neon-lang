#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <ctype.h>
#include <iso646.h>
#include <stdlib.h>
#include <string>

#include "number.h"
#include "utf8string.h"

namespace rtl {

namespace ne_os {

utf8string getenv(const utf8string &name)
{
    const char *r = ::getenv(name.c_str());
    if (r == NULL) {
        return utf8string();
    }
    return utf8string(r);
}

Number system(const utf8string &command)
{
    std::string cmd = command.str();
#ifdef _WIN32
    // Terrible hack to change slashes to backslashes so cmd.exe isn't confused.
    // Probably better handled by calling a lower level function than system().
    for (std::string::iterator i = cmd.begin(); not isspace(*i); ++i) {
        if (*i == '/') {
            *i = '\\';
        }
    }
#endif
    return number_from_sint32(::system(cmd.c_str()));
}

} // namespace ne_os

} // namespace rtl
