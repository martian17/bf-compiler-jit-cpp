#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;


typedef struct {
	map<char,bool> flags;
	string source;
}args_t;

//typedef map<string,string> strmap;

map<string, char> argmap = {
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
				if(!argmap.count(arg_str)){
					cerr << "argument " << arg_str << " unrecofnized" << endl;
					exit(1);
				}
				args.flags[argmap[arg_str]] = true;
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


int main(int argc, char** argv){
	//parse the arguments
	args_t args = parseArgs(argc, argv);
	for(auto const& pair : args.flags){
		cout << "flag: " << pair.first << endl;
	}
	cout << "source: " << args.source << endl;
};