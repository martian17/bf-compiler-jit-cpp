#include <stack>
#include <iostream.h>
using namespace std;
#define ERREXIT(x) cerr << x << endl; exit(1);

#ifdef DEBUG
#define DEBUG_PRINT(x) std::cout << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

#ifdef DEBUG
namespace fmt{
    std::string to_string(const std::vector<uint8_t> vec){

        std::stringstream ss;
        ss << "[ ";
        for (auto i = vec.begin(); i != vec.end(); i++){
            if(i != vec.begin()){
                 ss << ", ";
            }
            ss << (int)*i;
        }
        ss << " ]";
        return ss.str();
    }
    std::string to_string(const std::vector<Instruction> instructions){

        std::stringstream ss;
        ss << "[ ";
        for (auto i = instructions.begin(); i != instructions.end(); i++){
            if(i != instructions.begin()){
                 ss << ", ";
            }
            Instruction ins = *i;
            switch(ins.type){
                case InstructionType::INC:
                ss << "INC(" << ins.data << ")";
                break;
                case InstructionType::MOV:
                ss << "MOV(" << ins.data << ")";
                break;
                case InstructionType::JMZ:
                ss << "JMZ(" << ins.data << ")";
                break;
                case InstructionType::JNZ:
                ss << "JNZ(" << ins.data << ")";
                break;
                case InstructionType::IN:
                ss << "IN";
                break;
                case InstructionType::OUT:
                ss << "OUT";
                break;
                case InstructionType::COMMENT:
                ss << "COMMENT";
                break;
                case InstructionType::MEMSET:
                ss << "MEMSET(" << ins.data << ")";
                break;
                case InstructionType::MEMMOV:
                ss << "MEMMOV(" << ins.data << "," << ins.data2 << ")";
                break;
                case InstructionType::INVERT:
                ss << "INVERT";
                break;
            }
        }
        ss << " ]";
        return ss.str();
    }
}

#include"fmt.hpp"
#endif