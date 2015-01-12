#include <errno.h>
#include <string>
#include <string.h>
#include <sys/stat.h>

#include "rtl_exec.h"

namespace rtl {

void file$mkdir(const std::string &path)
{
    int r = mkdir(path.c_str(), 0755);
    if (r != 0) {
        switch (errno) {
            case EACCES: throw RtlException("PermissionDenied", path);
            case EEXIST: throw RtlException("DirectoryExists", path);
            case ENOENT: throw RtlException("PathNotFound", path);
            default:
                throw RtlException("FileError", path + ": " + strerror(errno));
        }
    }
}

} // namespace rtl
