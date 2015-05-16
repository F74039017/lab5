#ifndef HUGEINT_H
#define HUGEINT_H
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;

class HugeInt
{
	friend ostream & operator<< (ostream &, const HugeInt &);
	friend istream & operator>> (istream &, HugeInt &);
	

public:
	HugeInt(long num=0);
	HugeInt(const char *strnum);
	HugeInt(const HugeInt &copy);
	~HugeInt();
	const HugeInt operator+ (const HugeInt &);
	const HugeInt operator- (const HugeInt &);
	const HugeInt & operator= (const HugeInt &);
	
private:
	int *number;
	int len;
	bool sign;

};

#endif
