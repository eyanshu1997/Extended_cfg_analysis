#include<bits/stdc++.h>
using namespace std;
string WHITESPACE = " \n\r\t\f\v";

void print_lines(vector<string> lines)
{
	cout<<"no of lines "<<lines.size()<<"\n";
	for(auto x:lines)
	{
		cout<<x<<"\n";
	}
	cout<<"\n";
}

string ltrim(string s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(string s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(string s)
{
	return rtrim(ltrim(s));
}


vector<string> handlebr(string line,string br)
{
	//cout<<line;
	line=trim(line);
	vector<string>lines;
	size_t fo;
	fo=line.rfind(br);
	//cout<<fo<<"\n";
	if(fo!=string::npos)
	{
		if(line.size()==1)
		{
			lines.push_back(trim(line));
			return lines;
		}
		string l1=line.substr(0,fo);
		//cout<<"{"<<l1<<"}\n"<<"{"<<l2<<"}\n";
		//return lines;
		vector<string>x1=handlebr(l1,br);
		for(auto x:x1)
			lines.push_back(trim(x));
		if(fo!=line.size()-1)
		{
			lines.push_back(br);
			lines.push_back(trim(line.substr(fo+1,line.size()-fo-1)));
		}
		else
			lines.push_back(br);
	}
	else
		lines.push_back(trim(line));
	return lines;
}
vector<string> rememp(vector<string> lines)
{
	vector<string> ne;
	for(auto a:lines)
	{
		a=trim(a);
		if(a!=""&&a!=";")
			ne.push_back(a);
	}
	return ne;
}
vector<string> parse(string f)
{
	vector<string> lines;
	ifstream fi(f);
	if (!fi.is_open())
  	{
  		cout<<"file open error\n";
  	}
	string line;
	while(getline(fi,line))
	{
		line=trim(line);
		vector<string> li=handlebr(line,"}");
		for(auto x:li)
		{
			vector<string> z=handlebr(x,"{");
			for(auto y:z)
			{
				vector<string> a=handlebr(y,";");
				for(auto b:a)
					lines.push_back(trim(b));
			}
		}
	}
	lines=rememp(lines);
	return lines;
}


