#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

#include "./command-args.hpp"



int main(int argc, char** argv){
	//parse the arguments
	args_t args = parseArgs(argc, argv);
	for(auto const& pair : args.flags){
		cout << "flag: " << pair.first << endl;
	}
	cout << "source: " << args.source << endl;
};