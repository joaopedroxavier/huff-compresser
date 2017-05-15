//	Frequency Tree class definition
//	Author: João Pedro de Araújo Xavier
//	Latest version: 05/15/2017
//	Tested with c++11.
#ifndef FREQUENCY_TREE_H
#define FREQUENCY_TREE_H

#include <queue>
#include "Frequency_Array.h"

class Frequency_Tree{
	public:
		Frequency_Tree();
		Frequency_Tree(int freq);
		Frequency_Tree(unsigned char c, int freq);
		Frequency_Tree(Frequency_Array f);
		Frequency_Tree(const char* file);
		int get_key();
		unsigned char* get_char();
		string get_encrypted(int i);
		void mount(Frequency_Array f);
		void set_code(string* par);
		void encrypt(const char* file, const char* outfile);

		Frequency_Tree* left;
		Frequency_Tree* right;

	private:
		int key;
		string* code;
		unsigned char* character;
};

#endif
