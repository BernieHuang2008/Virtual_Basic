#ifndef GFUNCTION_H
#define GFUNCTION_H

#include<iostream>
#include<math.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>
#include<iomanip>
#include<algorithm>

using namespace std;


/*	Copyright H.G.Cucumber	*/

/*	==Function==			==Return==
 *	gcd(int,int)			-Greatest common factor		//�������
 *	strsim(string,string)	-The similarit of strings	//�ַ������ƶ�
 *	print(i/f/c/s)			(void)						//print
 *	input(char)				(string)					//input
 *	toint(ch/str)			(int)						//toint
 *	tostr(int)				(string)					//tostr
 *	strfind(str1,str2)		(int)						//str1��str2���ֵĴ���
 *	color(int)				(void)						//change text color
 *	position(int,int)		(void)						//set print position
 *  coutfloat(int)			(void)						//set decimal digits of 'cout' output
 *  hex_bin(str)			(string)					//turn HEX to BIN
 *  hex_dec(str)			(int)						//turn HEX to DEX
 *  dec_bin(int)			(string)					//turn DEC to BIN
 */



int gcd(int m,int n)
{
	if(m%n==0)    return n;
	else    return gcd(n,m%n);
}

float strsim(string a,string b)
{
	int n[a.length()+1][b.length()+1]= {0};
	int mi=0;
	for(int i=0; i<=a.length(); i++) n[i][0]=i;
	for(int i=0; i<=b.length(); i++) n[0][i]=i;
	for(int i=1; i<=a.length(); i++)
	{
		int mini=max(a.length(),b.length());//mini value in a;
		for(int j=1; j<=b.length(); j++)
		{
			int c=n[i-1][j-1];
			if(a[i-1]!=b[j-1]) c++;
			n[i][j]=min(n[i-1][j]+1,min(n[i][j-1]+1,c));
			mini=min(mini,n[i][j]);
		}
		mi=max(mini,mi);
	}
	return 1-(mi*1.0/max(a.length(),b.length()));
}

int toint(string s)
{
	int rt=0;
	if(s[0]=='-')
	{
		for(int i=1; i<s.length(); i++)
		{
			rt*=10;
			char lstc[10]= {'0','1','2','3','4','5','6','7','8','9'};
			for(int j=0; j<10; j++)
				if(s[i]==lstc[j])	rt+=j;

		}
		rt*=-1;
		return rt;
	}
	for(int i=0; i<s.length(); i++)
	{
		rt*=10;
		char lstc[11]= {'0','1','2','3','4','5','6','7','8','9','a'};
		for(int j=0; j<11; j++)
			if(s[i]==lstc[j])	rt+=j;
	}
	return rt;
}

int toint(char c)
{
	string s;
	s=c;
	return toint(s);
}

string tostr(int it)
{
	string rt="";
	bool pm=(it<0);
	if(it<0)	it*=-1;
	while(it>=1)
	{
		int i=it%10;
		char lstc[10]= {'0','1','2','3','4','5','6','7','8','9'};
		rt=lstc[i]+rt;
		it=it/10;
	}
	if(pm)	rt="-"+rt;
	return rt;
}

string tostr(bool b)
{
	if(b)	return "1";
	return "0";
}

int strfind(string s,string c)
{
	int sum=0;
	while(s.find(c)!=string::npos)
	{
		s=s.substr(s.find(c)+1);
		sum++;
	}
	return sum;
}

void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void position(int x,int y)
{
	COORD pos= {x,y};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out,pos);
}

string turn(string s)
{
	for(int i=0; i<s.length()/2; i++)
	{
		swap(s[i],s[s.length()-i-1]);
	}
	return s;
}

void coutfloat(int f_num)
{
	cout<<fixed;
	cout<<setprecision(f_num);
}

string hex_bin(string hex)
{
	string sReturn = "";
    unsigned int len = hex.length();
    for (unsigned int i = 0; i<len; i++)
    {
        switch (hex[i])
        {
            case '0': sReturn.append ("0000"); break;
            case '1': sReturn.append ("0001"); break;
            case '2': sReturn.append ("0010"); break;
            case '3': sReturn.append ("0011"); break;
            case '4': sReturn.append ("0100"); break;
            case '5': sReturn.append ("0101"); break;
            case '6': sReturn.append ("0110"); break;
            case '7': sReturn.append ("0111"); break;
            case '8': sReturn.append ("1000"); break;
            case '9': sReturn.append ("1001"); break;
            case 'A': sReturn.append ("1010"); break;
            case 'B': sReturn.append ("1011"); break;
            case 'C': sReturn.append ("1100"); break;
            case 'D': sReturn.append ("1101"); break;
            case 'E': sReturn.append ("1110"); break;
            case 'F': sReturn.append ("1111"); break;
            case 'a': sReturn.append ("1010"); break;
            case 'b': sReturn.append ("1011"); break;
            case 'c': sReturn.append ("1100"); break;
            case 'd': sReturn.append ("1101"); break;
            case 'e': sReturn.append ("1110"); break;
            case 'f': sReturn.append ("1111"); break;
        }
    }
    return sReturn;
}

int hex_dec(string hex)
{
//	cout<<"hex:"<<hex<<endl;
    int i=0,count,sum;
    count=hex.length();  
    sum=0;  
    for(i=count-1;i>=0;i--)	//��ʮ�����Ƹ�λ��ʼ��ÿλ��ת����ʮ����  
    {
        if(hex[i]>='0'&&hex[i]<='9')	//�����ַ���ת��  
            sum+=(hex[i]-48)*pow(16,count-i-1);  
        else if(hex[i]>='A'&&hex[i]<='F')	//��ĸ�ַ���ת��
            sum+=(hex[i]-55)*pow(16,count-i-1);  
        else if(hex[i]>='a'&&hex[i]<='f')	//��ĸ�ַ���ת��
            sum+=(hex[i]-87)*pow(16,count-i-1);  
    }  
    return sum;
}

string dec_bin(int a)
{
	int result=0;
	int temp=a;
	int j=1;
	while(temp)
	{
		result=result+j*(temp%2);
		temp=temp/2;
		j=j*10;
	}
	return tostr(result);
}

int bin_dec(string bin)
{
	int sum;	//����ת��Ϊʮ���Ƶ�����Ϊsum
	for(int i=0;i<bin.size();i++)
	{
		//�жϵ�ǰ�ַ���n[i]�Ƿ�Ϊ1����Ϊ����1����0��Ϊ0�Ļ���0��2�η����ǵ���0������Ҫ�ӷ����㡣
		if(bin[i]=='1') 
		{
			int j=pow(2,bin.size()-i-1);	//���￼�Ǻö�����ת����ʮ���ƹ�ʾ����i�ʹη��Ĺ�ϵ
			sum+=j;
		}
	}
	return sum;
}

char ASCII(int code)
{
	char ch;
	ch=code;
	return ch;
}

int ASCII(char ch)
{
	return ch;
}
#endif
