#ifndef HUFFMAN
#define HUFFMAN
#include <string>
using namespace std;
class QueryList
{
public:
	//QueryList(int a = 0):bits(a){}
    //unsigned char c;//���ù�ϣɢ�У�C��������list[c]��λ��
	int bits;
	string s;
};
class HNode
{
public:
	HNode(int b = -1,int c = -1):left(b),right(c){}
	int left;
	int right;
//	unsigned char c;////���ù�ϣɢ�У�C��������HTree[c]��λ��.
};
class HNode_mem:public HNode
{
public:
	HNode_mem(int b = -1,int c = -1,int e = 0,int a = -2):HNode(b,c),freq(e),parent(a){}
	long freq;
	int parent;
};
#endif