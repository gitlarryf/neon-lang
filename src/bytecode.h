#ifndef BYTECODE_H
#define BYTECODE_H

#include <string>
#include <utility>
#include <vector>

class Bytecode {
public:
    Bytecode();
    bool load(const std::vector<unsigned char> &bytes);

    typedef std::vector<unsigned char> Bytes;

    /*
     * Type descriptors are one of the following patterns:
     *
     * B        - boolean
     * N        - number
     * S        - string
     * Y        - bytes
     * A<x>     - array
     * D<x>     - dictionary
     * R[xyz..] - record, fields x, y, z
     * P<x>     - pointer
     * E[id1,id2,...] - enum
     */

    struct Type {
        Type(): name(0), descriptor(0) {}
        unsigned int name;
        unsigned int descriptor;
    };

    struct Constant {
        Constant(): name(0), type(0), value() {}
        unsigned int name;
        unsigned int type;
        Bytes value;
    };

    struct Variable {
        Variable(): name(0), type(0), index(0) {}
        unsigned int name;
        unsigned int type;
        unsigned int index;
    };

    struct Function {
        Function(): name(0), descriptor(0), entry(0) {}
        unsigned int name;
        unsigned int descriptor;
        unsigned int entry;
    };

    struct ExceptionExport {
        ExceptionExport(): name(0) {}
        unsigned int name;
    };

    struct FunctionInfo {
        FunctionInfo(): name(0), entry(0) {}
        FunctionInfo(unsigned int name, unsigned int entry): name(name), entry(entry) {}
        unsigned int name;
        unsigned int entry;
    };

    struct ExceptionInfo {
        unsigned int start;
        unsigned int end;
        unsigned int excid;
        unsigned int handler;
    };

    Bytes obj;
    std::string source_hash;
    size_t global_size;
    std::vector<std::string> strtable;
    std::vector<Type> export_types;
    std::vector<Constant> export_constants;
    std::vector<Variable> export_variables;
    std::vector<Function> export_functions;
    std::vector<ExceptionExport> export_exceptions;
    std::vector<std::pair<unsigned int, std::string> > imports;
    std::vector<FunctionInfo> functions;
    std::vector<ExceptionInfo> exceptions;
    Bytes code;

    Bytes getBytes() const;
};

#endif
