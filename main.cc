#include "parser.cc"
#include "cla.cc"
vector<string> data_types={"int","String","byte","short","long","float","double","boolean","char"};
vector<string> inbr(vector<string>lines)
{
	vector<string>li;
	int br=1;
	if(lines[0]!="{")
	{
		cout<<"error bracket not found";
		exit(0);
	}
	for(int i=1;i<lines.size();i++)
	{
		if(lines[i]=="{")
			br++;
		if(lines[i]=="}")
			br--;
		if(br==0)
			return li;
		li.push_back(lines[i]);
	}
	return li;
}
vector<cla> findcl(vector<string> lines)
{
	vector<cla> tmp;
	return tmp;
}
int main()
{
	//string line="class node{";
	//vector<string> lines=handlebr(trim(line),"{");
	vector<string> lines=parse("test/Test.java");
	vector<string> x;
	for(int i=2;i<lines.size();i++)
		x.push_back(lines[i]);
//	print_lines(x);
	x=inbr(x);
	print_lines(x);
}
