#ifndef OPCODE_H
#define OPCODE_H

enum Opcode {
    PUSHB,
    PUSHN,
    PUSHS,
    LOADGB,
    LOADGN,
    LOADGS,
    STOREGB,
    STOREGN,
    STOREGS,
    NEGN,
    ADDN,
    SUBN,
    MULN,
    DIVN,
    EXPN,
    EQN,
    NEN,
    LTN,
    GTN,
    LEN,
    GEN,
    EQS,
    NES,
    LTS,
    GTS,
    LES,
    GES,
    ANDB,
    ORB,
    NOTB,
    CALLP,
    CALLF,
    JUMP,
    JZ,
    RET,
};

#endif
