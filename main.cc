#include "parser.cc"
#include "classes.cc"
vector<string> data_types={"int","String","byte","short","long","float","double","boolean","char","void"};
vector<string> modifiers={"public","private","protected"};
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
	int pc=0;
	while(pc<lines.size())
	{
		while(lines[pc].find("class")==string::npos)
		{
			pc++;	
		}
		int c=lines[pc].find("class");
		string na=trim(lines[pc].substr(c+5,lines[pc].size()-c-5));
		cout<<na<<"\n";
		data_types.push_back(na);
		//print_lines(data_types);
		vector<string> cl(lines.begin()+pc+1,lines.end());
		//print_lines(cl);
		vector<string> in_class=inbr(cl);
		//print_lines(in_class);
		int cc=0;
		while(cc<in_class.size())
		{
			string x=in_class[cc];		
			string z=trim(na)+"(";
			if(x.find(z)==0)
			{
				cout<<"constructor\n";
				vector<string>ml(in_class.begin()+cc+1,in_class.end());
				//print_lines(ml);
				vector<string> in_ml=inbr(ml);
				print_lines(in_ml);
				cc=cc+in_ml.size()+3;
				
			}
			else
			{
				
				int s=x.find(" ");
				string ac=x.substr(0,s);
				//cout<<"checking "<<ac<<"\n";	
				auto it=find(modifiers.begin(),modifiers.end(),ac);
				if(it==modifiers.end())
				{
					
					//if int value;
					string re=x.substr(s+1,x.size()-s-1);
					auto it=find(data_types.begin(),data_types.end(),ac);
					if(it==data_types.end())
					{
						cout<<"1. checked "<<ac<<" error \n";
						exit(0);
					}
					else
					{
						cout<<"initialization statement "<<ac<<" "<<re<<"\n";
					}
					cc++;
					
					
				}
				else
				{
					//public static int value
					string re=x.substr(s+1,x.size()-s-1);
					int s=re.find(" ");
					string da=re.substr(0,s);
					if(trim(da)=="static")
					{
						re=re.substr(s+1,re.size()-s-1);
						s=re.find(" ");
						da=re.substr(0,s);
					}
					auto it=find(data_types.begin(),data_types.end(),da);
					if(it==data_types.end())
					{
						cout<<"2. checked ["<<ac<<"] ["<<da<<"]\n";
						cout<<"error \n";
						exit(0);
					}
					else
					{
						string na=re.substr(s+1,re.size()-s-1);
						cout<<"method name "<<na<<"\n";
						vector<string>ml(in_class.begin()+cc+1,in_class.end());
						vector<string> in_ml=inbr(ml);
						print_lines(in_ml);
						cc=cc+in_ml.size()+3;
					}
					
				}
			}
		}
		pc=pc+in_class.size()+3;
		//cout<<"pc is"<<pc<<"\n";
	}
	return tmp;
}
int main()
{
	//string line="class node{";
	//vector<string> lines=handlebr(trim(line),"{");
	vector<string> lines=parse("test/Test.java");
//	print_lines(lines);
	cout<<"no of lines is"<<lines.size()<<"\n";
	vector<cla> res=findcl(lines);
//	vector<string> x;
//	for(int i=2;i<lines.size();i++)
//		x.push_back(lines[i]);
//	print_lines(x);
//	x=inbr(x);
//	print_lines(x);
}
