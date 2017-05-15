//	Decrypter of files zipped with Encrypter.cpp
//	Author: João Pedro de Araújo Xavier
//	Latest Version: 05/15/2017
//	Tested with c++11.
//	Make sure that you have Frequency_Tree.cpp, Frequency_Array.cpp and their Headers as well, and bring the cpp files when you compile it. (Example: g++ -std=c++11 Encrypter.cpp -o Encrypter Frequency_Tree.cpp Frequency_Array.cpp

#include <bits/stdc++.h>
#include "Frequency_Tree.h"

using namespace std;

string get_decrypted(unsigned char c){

	// The inverse process of the get_codes in Encrypter.cpp. It gets a unsigned character and returns the "bit string" correspondent.

	string s; int k=128;
	for(int i=0;i<8;++i){
		if(c >= k) s = s + "1";
		else s = s + "0";
		c = c%k;
		k/=2;
	}
	return s;
}

int main(int argc, const char* argv[]){

	//	Handling inappropriate usage.
	
	if(argc != 2 and argc != 3){
		cerr << "Usage: ./Decrypter <Your encrypted file> <Name of your output file>" << endl << "Another usage: ./Decrypter <Your encrypted file>. In this case, your output file will be named as 'RUNNINGINTHE90S.txt'" << endl;
		return -1;
	}
	else if(argc == 2) cerr << "Warning: You didn't especified the output file name. It will be named as 'RUNNINGINTHE90S.txt'" << endl;

	// Opening files and generating Frequency Array/Tree by them.

	ifstream ip;
	ip.open(argv[1]);
	if(!ip.is_open()){
		cerr << "Error: Couldn't find encrypted file." << endl;
		return -1;
	}
	cerr << "Opening encrypted file... Done" << endl;
	ofstream op;
	op.open(((argc == 2) ? "RUNNINGINTHE90S.txt" : argv[2]));
	if(!op.is_open()){
		cerr << "Error: Couldn't open output file." << endl;
		return -1;
	}
	cerr << "Opening output file... Done" << endl;
	int size, freq[256];
	ip >> size;
	for(int i=0;i<256;++i) ip >> freq[i];
	cerr << "Generating Frequency Array... Done" << endl;
	Frequency_Array f = Frequency_Array(freq);
	Frequency_Tree *t = new Frequency_Tree(f);
	Frequency_Tree *p = new Frequency_Tree(f);
	cerr << "Generating Frequency Tree... Done" << endl;
	string buff = string();
	char a; int sizebuff=0; //	sizebuff is a counter which will help us to fix the last character.
	ip.get(a); //	Avoiding the '\n' error

	//Decryption part
	
	while(ip.get(a)){
		if(ip.eof()) break;
		unsigned char c = a;
		sizebuff += 8;
		string s = get_decrypted(c);
		if(abs(sizebuff - size) < 8)	while(sizebuff >= size) s.pop_back(), sizebuff--;
		buff = buff + s;
		while(!buff.empty()){
			if(buff.front() == '1') t = t->right;
			else t = t->left;
			buff.erase(0, 1);
			if(t->left == NULL and t->right == NULL){
				//	When we reach a leaf, we have to print the character in it and then go back to the root.
				op << *(t->get_char());
				t = p;
			}
		}
	}
	cerr << "Making Decryption... Done" << endl;

	return 0;
}
