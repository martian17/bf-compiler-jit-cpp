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
    char* position;
    INS* next;
    IS_type type;
    uint8_t data8;

    INS(INS_type t): type(t), position(pos){}
    INS(INS_type t, uint8_t u8): type(t), position(pos), data8(u8){}
    INS(INS_type t, size_t u64): type(t), position(pos), data64(u64){}
    INS(INS_type t, size_t u64, uint8_t u8): type(t), position(pos), data64(u64), data8(u8){}
};


INS getInstruction(char* it){
    INS ins;
    switch(*it){
        case '+':
        ins = INS(INC,(uint8_t)1);
        case '-':
        ins = INS(INC,(uint8_t)-1);
        case '>':
        ins = INS(MOV,(size_t)1);
        case '<':
        ins = INS(MOV,(size_t)-1);
        case ',':
        ins = INS(IN);
        case '.':
        ins = INS(OUT);
        case '[':
        ins = INS(JZ);
        case ']':
        ins = INS(JNZ);
        break;
        default:
        return nullptr;
    }
    ins.position = it;
    return ins;
};

vector<INS> optimize(vector<INS> code, size_t loop_start, size_t loop_end, bool& opt_success, char* &it, cahr* end){
    vector<INS> block;
    int mptr = 0;
	int min_mptr = 0;
	int max_mptr = 0;
	//check if inner MOV adds up to 0
	//as well as calculate max and min relative mptr
	for(size_t pc = loop_start+1; pc < loop_end; pc++){
		if(code[pc].type == InstructionType::MOV){
			mptr += code[pc].data;
			if(mptr < min_mptr){
				min_mptr = mptr;
			}else if(mptr > max_mptr){
				max_mptr = mptr;
			}
		}else if(
			//no IO in optimized chunk
			code[pc].type == InstructionType::IN ||
			code[pc].type == InstructionType::OUT
		){
			mptr = 1;
			break;
		}
	}
	if(mptr != 0)break;
	std::vector<uint8_t> memfield(max_mptr - min_mptr + 1);
	//tally up all the pluses and minuses
	for(size_t pc = loop_start+1; pc < loop_end; pc++){
		if(code[pc].type == InstructionType::MOV){
			mptr += code[pc].data;
		}else if(code[pc].type == InstructionType::INC){
			memfield[mptr-min_mptr] += code[pc].data;
		}
	}
	if(memfield[-min_mptr] != 255 && memfield[-min_mptr] != 1){
		//result unpredictable, not optimizing
		break;
	}
	//all conditions cleared, optimization possible
	std::vector<Instruction> block;

	//handling cases like [+>++<]
	//[+>++<] is equivalent to INVERT() MEMMOV(1,2) MEMSET(0)
	if( memfield[-min_mptr] == 1 &&
		//in case of [+], no INVERT is needed
		max_mptr - min_mptr != 0){
		//converting [+>+<] to [->+<] equivalent
		block.push_back(Instruction(InstructionType::INVERT));
	}
	for(mptr = min_mptr; mptr <= max_mptr; mptr++){
		if(mptr == 0 || memfield[mptr-min_mptr] == 0)continue;
		block.push_back(Instruction(InstructionType::MEMMOV,mptr,memfield[mptr-min_mptr]));
	}

	//lookahead_incr(it,str) finds cases like [-]+++++ and converts them to MEMSET(5)
	//arguments are passed as reference
	//`std::str::iterator it` gets overwritten to a new position as a side effect
	//returns the number of total increments
	block.push_back(Instruction(InstructionType::MEMSET,lookahead_incr(it,str)));
    return block;
};

vector<INS> parse(char* buff, size_t size){
    int i = 0;
    vector<INS> code;
    stack<size_t> loop;
    char* end = buff+size;
    bool innermost_flag = true;
    for(cahr* it = buff; it < end; it++){
        INS ins = getInstruction(it);
        if(ins == nullptr){
            continue;
        }
        //stackable case
        if(code.size() != 0 && ins.type == code.back().type){
            if(code.back().type == INC){
                code.back().data8 += ins.data8;
                continue;
            }else if(code.back().type == MOV){
                code.back().data64 += ins.data64;
                continue;
            }
        }

        if(ins.type == JZ){
            loop.push(code.size());
            innermost_flag = true;
        }else if(ins.type == JNZ){
            if(loops.empty())ERREXIT("no matching \"]\" at char " << ins->position);
            //try optimize
            size_t loop_start = loops.top();//points to "["
			size_t loop_end = code.size();
            loops.pop();
            bool opt_success = false;
            vector<INS> block;
            if(innermost_flag)block = optimize(code,loop_start,loop_end,opt_success,it,end);
            innermost_flag = false;
            if(opt_success){
                //discard the existing instruction field
				code.resize(loop_start);
				//append block to code
				code.insert(code.end(), block.begin(), block.end());
                continue;
            }else{
                code[loop_start].data = loop_end;
            }
        }

        code.push_back(ins);
    }
}


void parse(char* buff, char* end, vector<INS> &vec){
    for(;buff < end; buff++){

    }
}


vector<ins> parseBody(char* buff, size_t size){
    vector<INS> vec;
    parse(buff,size,i,vec);
    return vec;
}

INS* parse(char* buff, size_t size){
    INS* head = nullptr;
    INS* tail = nullptr;
    vector<INS> aaaaaa
    stack<INS*> loops;

    size_t i = 0;
    for(; i < size; i++){
        INS ins = getInstruction(buff,i);
        if(ins == nullptr)continue;
        head = ins;
        tail = ins;
        if(ins->type == JZ)loops.push(ins);
        if(ins->type == JNZ)ERREXIT("no matching \"]\" at char " << ins->position);
        break;
    }
    if(head == nullptr)return head;
    //loop through the rest
    for(; i < size; i++){
        INS ins = getInstruction(buff,i);
        if(ins->type == tail->type){
            if(ins->type == INC){
                tail->data8 += ins->data8;
                delete ins;
            }else if(ins->type == MOV){
                tail->data64 += ins->data64;
                delete ins;
            }
        }
        if(ins->type == INC){


        }
        break;
    }

}



void brainfuck(char* buff, size_t size){

};










