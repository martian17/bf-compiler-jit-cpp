#include "./command-args.hpp"


map<string, char> cmd_arg_string_mapping = {
	{"optimize", 'o'},
	{"debug", 'd'},
	{"save", 's'}
};

args_t parseArgs(int argc, char** argv){
	args_t args;
	args.source = "";
	for(int i = 1; i < argc; i++){
		char* arg = argv[i];
		if(arg[0] == '-'){
			if(arg[1] == '-'){
				//string argument
				arg += 2;
				string arg_str = arg;//slice and cast to string
				if(!cmd_arg_string_mapping.count(arg_str)){
					cerr << "argument " << arg_str << " unrecofnized" << endl;
					exit(1);
				}
				args.flags[cmd_arg_string_mapping[arg_str]] = true;
			}else{
				arg += 1;
				//list of single character arguments
				for(; *arg != '\0'; arg++){
					args.flags[*arg] = true;
				}
			}
		}else{
			//then it must be the source
			args.source = arg;
		}
	}
	if(args.source.empty()){
		cerr << "Please provede the source file location"<< endl;
		exit(1);
	}
	return args;
}