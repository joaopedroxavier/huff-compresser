//	Encrypter of files
//	Author: João Pedro de Araújo Xavier
//	Latest Version: 05/15/2017
//	Tested with c++11.
//	Make sure that you have Frequency_Tree.cpp, Frequency_Array.cpp and their Headers as well, and bring the cpp files when you compile it. (Example: g++ -std=c++11 Encrypter.cpp -o Encrypter Frequency_Tree.cpp Frequency_Array.cpp

#include <bits/stdc++.h>
#include "Frequency_Tree.h"

using namespace std;

string* rf;

void get_codes(Frequency_Tree *t, string &s){

	//	For each character, sets the corresponding 'bit' string of it.
	//	The string represents the path to traverse in the tree. A '0' means that I'm going left, A '1' means I'm going right.

	if(t->get_char() != NULL){
		unsigned char c = *(t->get_char());
		rf[c] = s;
	}
	else{
		s = s + "0";
		get_codes(t->left, s);
		s.pop_back();
		s = s + "1";
		get_codes(t->right, s);
		s.pop_back();
	}
}

int main(int argc, const char* argv[]){

	//	Handling inappropriate usage.

	if(argc != 2 and argc != 3){
		cerr << "Usage: ./Encrypter <Your file> <Name of your output file>" << endl << "Another usage: ./Encrypter <Your file>. In this case, your output file will be named as 'AEDRIFT86.txt'" << endl;
		return -1;
	}
	else if(argc == 2) cerr << "Warning: You didn't especified the output file name. It will be named as 'AE86DRIFT.txt'" << endl;

	//	Opening files and generating Frequency Array/Tree by them.

	ofstream op;
	Frequency_Array f = Frequency_Array(argv[1]);
	cerr << "Generating Frequency Array... Done" << endl;
	Frequency_Tree *t = new Frequency_Tree(f);
	cerr << "Generating Frequency Tree... Done" << endl;
	string s = string();
	rf = new string[256];
	get_codes(t, s);
	t->set_code(rf);
	t->encrypt(argv[1], ((argc == 2) ? "AE86DRIFT.txt" : argv[2]));
	cerr << "Making Encryption... Done" << endl;

	return 0;
}
