//	Frequency Array class implementations
//	Author: João Pedro de Araújo Xavier
//	Latest version: 05/15/2017
//	Tested with c++11.
#include "Frequency_Array.h"

using namespace std;

Frequency_Array::Frequency_Array(){
	memset(frequency, 0, sizeof(frequency));
}

Frequency_Array::Frequency_Array(int f[256]){
	memset(frequency, 0, sizeof(frequency));
	for(int i=0;i<256;++i) frequency[i] = f[i];
}

Frequency_Array::Frequency_Array(const char* file){
	memset(frequency, 0, sizeof(frequency));
	ifstream fp;
	fp.open(file);
	if(!fp.is_open()) cerr << "Não foi possível abrir o arquivo!" << endl;
	else{
		char c;
		while(fp.get(c)){
			if(fp.eof()) break;
			unsigned char a = c;
			frequency[a]++;
		}
	}
}

void Frequency_Array::print(){
	for(int i=0;i<256;++i) cout << (char)i << " (" << i << ") " << ": " << frequency[i] << endl;
}

int Frequency_Array::get_freq(int p){
	return frequency[p];
}

int Frequency_Array::get_freq(unsigned char c){
	return frequency[(int)c];
}
