#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

string parse_function(char* file, char* func_name)
{
	string str, name;
	string line; 
	ifstream in;
	int count=-1, flag=0;

	in.open(file);
	name=func_name;
	//cout<<name<<endl;
	
	size_t found;
		
	while ( getline (in,line) )
	{
		found = line.find(name);
		if(found!=std::string::npos)
		{
			str+=line;
			str+="\n";
			flag++;
			break;
		}
	}

	if(flag)
	{
		while ( getline (in,line) )
		{
			for(int i=0; i<line.size();i++)
			{
				if(line[i]=='{' && count==-1) count=1;
				else if(line[i]=='{') count++;
				if(line[i]=='}') count--;
				//cout<<count<<endl;
				if(count==0)
				{
					str+=line[i];
					//cout<<str<<endl;
					in.close();
					/*out.open(argv[3]);
					out<<str;
					out.close();*/
					return str;
				}
				str+=line[i];
			}
			str+="\n";
		}
	}
	in.close();
	return str;

}

string create_new_function(char* templ, vector<string> names)
{
	string str, line;
	ifstream in;
	in.open(templ);
	
	while ( getline (in,line) )
	{
		for(int i=0; i<line.size();)
		{
			if(line[i]=='$')
			{
				string number;
				int j;
				for(j=i+1;line[j]!='$';j++)
				{
					number+=line[j];
				}
				int n = atoi(number.c_str());
				str+=names[n-1];
				cout<<number<<endl;
				i=j+1;
			}
			else
			{
				str+=line[i];
				i++;
			}
		}
		str+="\n";
	}	
	in.close();
	//cout<<str<<endl;
	return str;
}

int main(int argc, char* argv[])
{
	vector<string> names;
	string str;
	ofstream out;
	out.open(argv[argc-1]);
	for(int i=2; i<argc-1; i+=2)
	{
		names.push_back(argv[i+1]);
		str+=parse_function(argv[i], argv[i+1]);
		str+="\n";
		str+="\n";
		
	}
	for(int i=0;i<(argc-3)/2;i++) cout<<names[i]<<endl;	
	
	str+=create_new_function(argv[1], names);
	out<< str<<endl;

	out.close();
}
