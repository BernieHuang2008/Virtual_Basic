#include<iostream>
#include<fstream>
#include"Gfunction.h"
using namespace std;
int main(int argc,char* argv[])
{
	int still_str=false;
	
	string s;
	ifstream in;
	string fname;fname=argv[1];fname=fname.substr(0,fname.length()-7)+".gacode";
	cout<<"input: "<<fname<<endl; 
	in.open(fname.c_str());
	ofstream out;
	fname=argv[1];fname=fname.substr(0,fname.length()-7)+".ga";
	cout<<"output:"<<fname<<endl; 
	out.open(fname.c_str());
	
	while(in>>s)
	{
		int str_end=0;
		if(s.find('\'')!=-1 and s.find('\'')!=s.rfind('\'')){
			// have multiple '\''
			still_str=1;
			str_end=2;
		}
		else if(s.find('\'')!=-1)
		{
			// have single '\''
			str_end=still_str;
			still_str=1;
		}
		if(still_str){
			for(int i=0;i<s.length();i++)
			{
				if(s[i]=='\'')
					if(str_end==1)
						break;
					else
						continue;
				out<<"F001";
				int a=ASCII(s[i]);
				out<<"00"<<hex<<a;
			}
			out<<"F0010020";
			if(!str_end)
				continue;
		}
		if(str_end)
		{
			out<<"F0010008";
			still_str=!still_str;
			continue;
		}
		
		if(s=="false")		s="0000";
		else if(s=="true")	s="0001";
		else if(s=="not")	s="0002";
		else if(s=="xor")	s="0003";
		else if(s=="or")	s="0004";
		else if(s=="and")	s="0005";
		else if(s=="mov")	s="0006";
		else if(s=="out")	s="F000";
		else if(s=="in")	s="F003";
		else if(s=="ascii")	s="F001";
		else if(s=="ASCII")	s="F002";
		else if(s=="return")s="FFFF";
		else if(s=="end")	s="FFFF0000FFFF";
		else if(s=="jmp")	s="0006fff0";
		else if(s=="print")	continue;

		else if(s[0]==';')
		{
			getline(in,s);
			continue;
		}
		
		out<<s;
	}
	out<<"FFFF0000FFFF";
}
