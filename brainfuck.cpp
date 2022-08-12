#include <brainfuck.cpp>

enum INS_type {
    INC,     //INC(u8) add n to mem[mptr]
    MOV,     //MOV(u64) add n to mptr
    JZ,      //JMZ(u64) Jump if Zero     pc = n if mem[mptr] is zero
    JNZ,     //JNZ(u64) Jump if Not Zero pc = n if mem[mptr] is non zero
    IN,      //IN()   mem[mptr] = input
    OUT,     //OUT()  output += mem[mptr]
    //optimizing instructions
    MEMSET,  //MEMSET(u8)   set mem[mptr] to n
    MEMMOV,  //MEMMOV(u64 u8) mem[mptr+n] += mem[mptr]*m
    BLOCK   //BLOCK(INS*) Basic block represenatation
};


class INS {
    union{
        INS* start;// for basic blocks
        size_t data64;
    };
    INS* next;
    IS_type type;
    uint8_t data8;
    
    INS(INS_type t): type(t){}
    INS(INS_type t, uint8_t u8): type(t), data8(u8){}
    INS(INS_type t, size_t u64): type(t), data64(u64){}
    INS(INS_type t, size_t u64, uint8_t u8): type(t), data64(u64), data8(u8){}
    INS(INS* st): start(st){}
};


INS* getInstruction(char c){
    switch(c){
        case '+':
        return new INS(INC,(uint8_t)1);
        case '-':
        return new INS(INC,(uint8_t)-1);
        case '>':
        return new INS(MOV,(size_t)1);
        case '<':
        return new INS(MOV,(size_t)-1);
        case ',':
        return new INS(IN);
        case '.':
        return new INS(OUT);
        case '[':
        return new INS(JZ);
        case ']':
        return new INS(JNZ);
    }
    return nullptr;
}

INS* parse(char* buff, size_t size){
    INS* head = nullptr;
    INS* tail = nullptr;
    
    size_t i = 0;
    for(; i < size; i++){
        INS* ins = getInstruction(buff[i]);
        if(ins == nullptr)continue;
        head = ins;
        tail = ins;
        break;
    }
    
}



void brainfuck(char* buff, size_t size){
    
};










