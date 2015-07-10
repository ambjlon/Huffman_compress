#ifndef HUFFMAN
#define HUFFMAN
#include <string>
using namespace std;
class QueryList
{
public:
	//QueryList(int a = 0):bits(a){}
    //unsigned char c;//利用哈希散列，C被放置在list[c]的位置
	int bits;
	string s;
};
class HNode
{
public:
	HNode(int b = -1,int c = -1):left(b),right(c){}
	int left;
	int right;
//	unsigned char c;////利用哈希散列，C被放置在HTree[c]的位置.
};
class HNode_mem:public HNode
{
public:
	HNode_mem(int b = -1,int c = -1,int e = 0,int a = -2):HNode(b,c),freq(e),parent(a){}
	long freq;
	int parent;
};
#endif