#include<iostream>
#include<fstream>
#include"Gfunction.h"
#include<conio.h>
using namespace std;

bool mem[65536];	//memory,16^4
bool DO=1; 

int write(string,string);
string read(string);
int run(string,int,int);


int RUNFILE(string fname)
{
	fname=fname.substr(0,fname.length()-4);
	string code=read(fname);
	int move=0;
	int i=0;
	while(i*4+8+move<=code.length())
	{
		move+=run(hex_bin(code.substr(i*4+move,4)),hex_dec(code.substr(i*4+4+move,4)),hex_dec(code.substr(i*4+8+move,4)));
		i++;
	}
}

int RUNCODE(string code)
{
	int move=0;
	int i=0;
	while(i*4+8+move<=code.length())
	{
		move+=run(hex_bin(code.substr(i*4+move,4)),hex_dec(code.substr(i*4+4+move,4)),hex_dec(code.substr(i*4+8+move,4)));
		i++;
	}
}
string read(string s)
{
	s+=".gal";
	ifstream in;
	in.open(s.c_str(),ios::in);
	in>>s;
	return s;
}
int write(string FNAME,string s)
{
	FNAME+=".gal";
	ofstream out;
	out.open(FNAME.c_str(),ios::out);
	out<<s;
} 
int run(string code,int mem_1,int mem_2)
{
//	code="1010 1111 0001 0101";
	int rt;
	bool FFF0=!mem[65520];	//MEM_FFF0 (reg_0,R_JMP)

	#define mem1 mem[mem_1]
	#define mem2 mem[mem_2]
	
	if(code==hex_bin("0000")){
		if(FFF0)mem1=0;
		rt=4;
	}
	if(code==hex_bin("0001")){
		if(FFF0)mem1=1;
		rt=4;
	}
	if(code==hex_bin("0002")){
		if(FFF0)mem1=!mem1;
		rt=4;
	}
	if(code==hex_bin("0003")){
		if(FFF0)mem1=mem1^mem2;
		rt=8;
	}
	if(code==hex_bin("0004")){
		if(FFF0)mem1=mem1|mem2;
		rt=8;
	}
	if(code==hex_bin("0005")){
		if(FFF0)mem1=mem1&mem2;
		rt=8;
	}
	if(code==hex_bin("0006")){
		if(FFF0)mem1=mem2;
		rt=8;
	}
	if(code==hex_bin("f000")){
		if(FFF0)cout<<mem1;
		rt=4;
	}
	if(code==hex_bin("f001")){
		if(FFF0)cout<<ASCII(mem_1);
		rt=4;
	}
	if(code==hex_bin("f002")){
		if(FFF0){
		string asciicode="";
		for(int kk=0;kk<7;kk++)	asciicode+=tostr(mem[mem_1+kk]);
		cout<<bin_dec(asciicode);
		}
		rt=4;
	}
	if(code==hex_bin("f003")){
		if(FFF0)
			mem1=(getch()!='0');
		rt=4;
	} 
	if(code==hex_bin("ffff")){
		if(FFF0){
		cout<<"\nprogram done with:"<<mem_1<<".\n";
		getch();
		exit(0);
		}
		rt=4;
	}
	
	
	mem[65520]=0;
	
	return rt;
		
		
}
