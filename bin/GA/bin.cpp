#include<iostream>
#include<fstream>
#include"Gfunction.h"
#include<conio.h>
using namespace std;

bool mem[65536];	//memory,16^4
bool DO=1; 
int g_FFF0=0;

int write(string,string);
string read(string);
int run(string,int,int);


int main(int argc,char* argv[])
{
	system("title GA");

	string fname;
	fname=argv[1];
	fname=fname.substr(0,fname.length()-3);

	string code=read(fname);
	int move=0;
	int i=0;
	while(i*4+8+move<=code.length())
	{
		move+=run(hex_bin(code.substr(i*4+move,4)),hex_dec(code.substr(i*4+4+move,4)),hex_dec(code.substr(i*4+8+move,4)));
		i++;
	}
}
int get_reg_argu(){
	int reg_argu=0;
	for(int i=15;i>=0;i++){
		reg_argu+=mem[0xFFE0+i]*pow(2, i);
		mem[0xFFE0+i]=0;
	}
	return reg_argu;
}
string read(string s)
{
	s+=".ga";
	ifstream in;
	in.open(s.c_str(),ios::in);
	in>>s;
	return s;
}
int write(string FNAME,string s)
{
	FNAME+=".ga";
	ofstream out;
	out.open(FNAME.c_str(),ios::out);
	out<<s;
} 
int run(string code,int mem_1,int mem_2)
{
	// e.g. code="1010 1111 0001 0101";
	int rt;
	int FFF0 = !mem[0xFFF0];	// MEM_FFF0 (reg_0: REG_JMP)
	bool FFF1 = mem[0xFFF1]; 	// MEM_FFF1 (reg_1: REG_BACK) 
	
	if(FFF1){
		mem[0xFFF1]=0;
		int reg_argu=get_reg_argu();
		return -reg_argu-4;	// @29: i++;
	}

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
		if(FFF0)
//			cout<<mem_1;
			if(mem_1==0x13)
				cout<<'\n';
			else
				cout<<ASCII(mem_1);
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
		cout<<"\n\n=== program end with:"<<mem_1<<". ===\n";
		getch();
		exit(0);
		}
		rt=4;
	}
	
	
	mem[0xFFF0]=0;
	
	return rt;
		
		
}
