/*
 * main.cpp
 */

#include "lex.h"
#include "parse.h"
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

int
main(int argc, char *argv[])
{
	ifstream file;
	istream *in;
	int linenum = 0;

	if( argc == 1 ) {
		in = &cin;
	}

	else if( argc == 2 ) {
		file.open(argv[1]);
		if( file.is_open() == false ) {
			cout << "COULD NOT OPEN " << argv[1] << endl;
			return 1;
		}
		in = &file;
	}

	else {
		cout << "TOO MANY FILENAMES" << endl;
		return 1;
	}

	ParseTree *prog = Prog(*in, linenum);

	if( prog == 0 )
		return 0;

    map<string,bool> declaredId;
    if( prog->CheckLetBeforeUse(declaredId) != 0)
        return 1;
    
	//cout << "BANG COUNT: " << prog->BangCount() << endl;
    //cout << "MAX DEPTH: " << prog->MaxDepth() << endl;

    map<string,Val> syms;
    try
    {
        prog->Eval(syms);
    }
    catch (std::invalid_argument ie)
    {
        cout<< ie.what()<<endl;
    }
    
	return 0;
}
