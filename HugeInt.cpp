#include "HugeInt.h"

HugeInt::HugeInt(long num)
{
	sign = (num>0)? true: false;
	stringstream ss;
	long unum = (sign)? num: (-1)*num;
	ss << unum;
	string str = ss.str();
	int len = str.length();
	number = new int[len];
	this->len = len;
	for(int i=len-1; i>=0; i--)
		number[i]=unum%10, unum /=10;
}

HugeInt::HugeInt(const char *strnum)
{
	sign = (strnum[0]=='-')? false: true;
	int len = (sign)? strlen(strnum): strlen(strnum)-1;
	this->len = len;
	number = new int[len];
	int d = (sign)? 0: 1;
	for(int i=0; i<len; i++)
		number[i]=strnum[i+d]-'0';
}


HugeInt::HugeInt(const HugeInt &copy)
{
	this->len = copy.len;
	this->sign = copy.sign;
	number = new int[len];
	memcpy(this->number, copy.number, sizeof(int)*len);
}

HugeInt::~HugeInt()
{
	delete []number;
}

const HugeInt HugeInt::operator+ (const HugeInt & x)
{
	int lonlen = (len>x.len)? len: x.len;
	int ext[lonlen];
	memset(ext, 0, sizeof(ext));
	bool les = (len>x.len)? 0: 1;
	int leslen = (les)? len: x.len;
	int d = lonlen - leslen;

	int sum[lonlen];
	memset(sum, 0, sizeof(sum));

	if(les)
	{
		for(int i=d; i<lonlen; i++)
			ext[i] = number[i-d];
		for(int i=0; i<lonlen; i++)
			sum[i] = x.number[i]+ext[i];
	}
	else
	{
		for(int i=d; i<lonlen; i++)
			ext[i] = x.number[i-d];
		for(int i=0; i<lonlen; i++)
			sum[i] = number[i]+ext[i];
	}

	for(int i=lonlen-1; i>0; i--)
	{
		sum[i-1] += sum[i]/10;
		sum[i] %= 10;
	}
	
	bool over=false;
	if(sum[0]/10)
		lonlen++, over=true;
	sum[0] %= 10;
	HugeInt result;
	result.len = lonlen;
	delete [] result.number; // reallocate
	result.number = new int[lonlen];
	if(over)
	{
		for(int i=1; i<lonlen; i++)
			result.number[i] = sum[i-1];
		result.number[0] = 1;
	}
	else
		memcpy(result.number, sum, sizeof(sum));

	return result; 
}


const HugeInt HugeInt::operator- (const HugeInt & x)
{
	int lonlen = (len>x.len)? len: x.len;
	int ext[lonlen];
	memset(ext, 0, sizeof(ext));
	bool les = (len<x.len)? 1: 0;
	int leslen = (les)? len: x.len;
	int d = lonlen - leslen;

	int sub[lonlen];
	memset(sub, 0, sizeof(sub));
	if(les)
	{
		for(int i=d; i<lonlen; i++)
			ext[i] = number[i-d];
		for(int i=0; i<lonlen; i++)
			sub[i] = ext[i]-x.number[i];
	}
	else
	{
		for(int i=d; i<lonlen; i++)
			ext[i] = x.number[i-d];
		for(int i=0; i<lonlen; i++)
			sub[i] = number[i]-ext[i];
	}

	
	bool nsign = 1;
	int cnt=0;
	for(int i=0; i<lonlen; i++, cnt++)
		if(sub[i]!=0)
		{
			if(sub[i]<0)
			{
				for(int j=0; j<lonlen; j++)
					sub[j] *= -1;
				nsign = 0;
				break;
			}
			else
				break;
		}
	
	for(int i=lonlen-1; i>0; i--)
		if(sub[i]<0)
		{
			sub[i-1]--;
			sub[i] += 10;
		}

	HugeInt result;
	result.sign = nsign;
	result.len = lonlen-cnt;
	result.number = new int[result.len];
	for(int i=0; i<result.len; i++)
		result.number[i] = sub[i+cnt];

	return result; 
}

ostream & operator<< (ostream &out, const HugeInt &num)
{
	for(int i=0; i<num.len; i++)
		out << num.number[i];
	return out;
}

istream & operator>> (istream &in, HugeInt &num)
{
	string strnum;
	in >> strnum;
	num.sign = (strnum[0]=='-')? false: true;
	int len = (num.sign)? strnum.length(): strnum.length()-1;
	num.len = len;
	num.number = new int[len];
	int d = (num.sign)? 0: 1;
	for(int i=0; i<len; i++)
		num.number[i]=strnum[i+d]-'0';
	return in;
}


const HugeInt & HugeInt::operator= (const HugeInt & copy)
{
	if(number)
		delete []number;
	this->len = copy.len;
	this->sign = copy.sign;
	number = new int[len];
	memcpy(this->number, copy.number, sizeof(int)*len);
}

