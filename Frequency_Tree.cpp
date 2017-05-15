//	Frequency Tree class implementations
//	Author: João Pedro de Araújo Xavier
//	Latest version: 05/15/2017
//	Tested with c++11.
#include "Frequency_Tree.h"

using namespace std;

// Custom operator for priority_queues of Trees

struct OrdKey{
	bool operator()(Frequency_Tree* &p1, Frequency_Tree* &p2){
		return p1->get_key() > p2->get_key();
	}
};

unsigned char processed(string &buff){

//	"buff" is a string of 'bits' (in fact, they're characters '0' or '1') 
//	which behaves like a character for our purposes. ("00100110" == 68 == 'D' (unsigned)).
//
//	This function gets the corresponding character of the buff string.

	int k=0, p=128;
	for(int i=0;i<8;++i){
		char d = buff[i];
		k += (d - '0')*p;
		p/=2;
	}
	buff.erase(0, 8);
	return (unsigned char)k;
}

//	'get' and 'set' functions with proper handling.

int Frequency_Tree::get_key(){
	return key;
}

unsigned char* Frequency_Tree::get_char(){
	return character;
}

void Frequency_Tree::set_code(string par[256]){
	code = new string[256];
	for(int i=0;i<256;++i) code[i] = par[i];
}

string Frequency_Tree::get_encrypted(int i){
	return code[i];
}

//	Encrypting part: Once the tree is built and you have the codes for each character,
//	You're able to compress your file.

void Frequency_Tree::encrypt(const char* file, const char* outfile){

	int sz=0;
	Frequency_Array f = Frequency_Array(file);
	ifstream ip;
	ofstream op;
	string buff = string();
	ip.open(file);
	if(!ip.is_open()){
		cerr << "Couldn't open input file!" << endl;
		return;
	}
	char a;
	while(ip.get(a)){
		if(ip.eof()) break;
		unsigned char c = a;
		sz += get_encrypted(c).size();
	}
	ip.close();
	op.open(outfile);
	if(!op.is_open()){
		cerr << "Couldn't open output file!" << endl;
		return;
	}

	//It writes the size (i.e the number of bits) on the file to handle the last character.
	
	op << sz << endl;

	//	After that, it writes the frequencies of each character to make building of the tree possible in Decryption.

	for(int i=0;i<256;++i) op << f.get_freq(i) << endl;

	// Finally, it writes the encrypted file.
	
	ip.open(file);
	while(ip.get(a)){
		if(ip.eof()) break;
		unsigned char c = a;
		buff = buff + get_encrypted(c);
		while(buff.size() >= 8)	op << processed(buff);
	}

	//Fills the remaining bits to carry a last character containing them.

	while(buff.size() < 8) buff = buff + "0";
	op << processed(buff);
	ip.close();
	op.close();

}

//Constructors of the Frequency Tree

Frequency_Tree::Frequency_Tree(){
	key=0, left = NULL, right = NULL, character = NULL;
}

Frequency_Tree::Frequency_Tree(unsigned char c, int freq){
	key=freq, left = NULL, right = NULL, character = new unsigned char(c);
}

Frequency_Tree::Frequency_Tree(int freq){
	key=freq, left = NULL, right = NULL, character = NULL;
}

Frequency_Tree::Frequency_Tree(Frequency_Array f){
	mount(f);
}

Frequency_Tree::Frequency_Tree(const char* file){
	Frequency_Array f = Frequency_Array(file);
	mount(f);
}

//	Implementation of the two more complex constructors (mount)
//
//	Our tree depends of the frequencies of each character.
//	The most frequent characters will need less bits to be stored, compressing the file.
//
//	To do so, we use Huffman's Algorithm. Implementation is made below. 
//	
//	To more information, see 
//	"Introduction to Algorithms", by Thomas H. Cormen, Ronald Riverst, Charles E. Leiserson and Clifford Stein, in the section of Greedy Algorithms.

void Frequency_Tree::mount(Frequency_Array f){

	character = NULL;
	priority_queue<Frequency_Tree*, vector<Frequency_Tree*>, OrdKey > qu; //	Priority Queue which sorts by the key of the Trees. The lesser, the better.
	for(int i=0;i<256;++i){
		if(f.get_freq(i) != 0){
			Frequency_Tree* t = new Frequency_Tree((unsigned char)i, f.get_freq(i));
			qu.push(t);
		}
	}

	//	Tree construction. In short, it is a greedy algorithm which links the two lesser trees (i.e the trees which have the least keys)
	//	and creates a parent for them with a key equal to the sum of them. The process is repeated till there is only one tree left, which is the root.

	while(qu.size() > 1){
		Frequency_Tree* t1 = qu.top();
		qu.pop();
		Frequency_Tree* t2 = qu.top();
		qu.pop();
		Frequency_Tree* t3 = new Frequency_Tree(t1->key + t2->key);
		t3->left = t1;
		t3->right = t2;
		qu.push(t3);
	}

	key = qu.top()->key;
	left = qu.top()->left, right = qu.top()->right;
	delete qu.top();

}
