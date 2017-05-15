//	Frequency Array class definition
//	Author: João Pedro de Araújo Xavier
//	Latest version: 05/15/2017
//	Tested with c++11.
#ifndef FREQUENCY_ARRAY_H
#define FREQUENCY_ARRAY_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Frequency_Array{
	public:
		Frequency_Array();
		Frequency_Array(int f[256]);
		Frequency_Array(const char* file);
		void print();
		int get_freq(int p);
		int get_freq(unsigned char c);
	private:
		int frequency[256];
};

#endif
