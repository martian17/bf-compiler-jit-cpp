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

args_t parseArgs(int argc, char** argv);
