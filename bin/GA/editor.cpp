#include<iostream>
#include<fstream> 
#include<conio.h>
#include"Gfunction.h"
using namespace std;

string FNAME;

char* GetTextFromClipboard();
void print(string);
string open();

int main()
{
	string code,s;
	int back;
	int ch=13;
	ofstream out;
	input:
	while(ch!=27)
	{
		ch=getch();
//		cout<<ch<<"\n";
		if(ch==10||ch==13)	code+="\n";
		else if(ch==8)		code=code.substr(0,code.length()-back-1)+code.substr(code.length()-back,code.length());
		else if(ch==22)		code+=GetTextFromClipboard();
		else if(ch==15)		code=open();
		else if(ch==19)		goto save;
		else if(ch==20)		goto test;
		else if(ch==224)
			switch(getch())
			{
	            case 75: back+=(back<code.length()?1:0);break;
	            case 77: back-=(back>0?1:0);break;
			}
		else				code=code.substr(0,code.length()-back)+ASCII(ch)+code.substr(code.length()-back,code.length());
		system("cls");
		print(code);
		for(int i=0;i<back;i++)	cout<<"\b";
	}
	color(7); 
	if(FNAME==""){
		cout<<"\n\n Save as:";
		getline(cin,FNAME);
		FNAME+=".gacode";
	}
	if(FNAME==".gacode")		exit(1);
	out.open(FNAME.c_str());
	out<<code;
	return 0;
	test:
		color(7); 
		if(FNAME==""){
			cout<<"\n\n[Test]\n Save as:";
			cin>>FNAME;
			FNAME+=".gacode";
		}
		out.open(FNAME.c_str());
		out<<code;
		out.close();
		
		s="compiler \""+FNAME+"\"";
		system(s.c_str());
		s="cc ga compiler%20\""+FNAME+"\"";
		system(s.c_str());
//		cout<<s;system("pause");
		
		s="bin \""+FNAME.substr(0,FNAME.length()-1)+"l\"&cls";
		system(s.c_str());
		s="cc ga bin%20\""+FNAME.substr(0,FNAME.length()-1)+"l\"&cls";
		system(s.c_str());
		
		print(code);
		goto input;
	save:
		color(7); 
		if(FNAME==""){
			cout<<"\n\nSave as:";
			cin>>FNAME;
			FNAME+=".gacode";
		}
		out.open(FNAME.c_str());
		out<<code;
		goto input;
}

char* GetTextFromClipboard()
{
    if(::OpenClipboard(NULL))
    {
        //获得剪贴板数据
        HGLOBAL hMem = GetClipboardData(CF_TEXT);
        if(NULL != hMem)
        {
            char* lpStr = (char*)::GlobalLock(hMem); 
            if(NULL != lpStr)
            {
                return lpStr;
                ::GlobalUnlock(hMem);
            }
        }
        ::CloseClipboard();
    }
    return "";
}

void print(string code)
{
	int i=0;
	while(i<code.length())
	{
		color(6);
		while(code[i]!=' ' && i<code.length())
		{
			cout<<code[i];
			i++;
		}
		color(5);
		while(code[i]!='\n' && i<code.length())
		{
			cout<<code[i];
			i++;
		}
	}
}


string open()
{
	string f,code;
	color(7);
	cout<<"\n\n[Open]\nFile Path:";
	cin>>f;
	f=f+".gacode"; 
	FNAME=f;
	cout<<f;
	ifstream in;
	in.open(f.c_str());
	while(getline(in,f))	code+=f+"\n";
	system("cls");
//	cout<<code<<"ecode;";
//	system("pause");
//	print(code);
	return code;
}
