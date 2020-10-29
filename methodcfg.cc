void printall()
{
	for(auto a:classes)
	{
		a.print();
	}
}
void reprint(vector<inst>::iterator it)
{
	it->cprint();
	for (auto iti = it->instlist.begin(); iti != it->instlist.end(); iti += 1)
	{
		reprint(iti);
	}
}
void printinst()
{
	for (auto it = classes.begin(); it != classes.end(); it += 1)
	{
		cout<<"class is "<<it->name<<"\n";
		for (auto itm = it->methodlist.begin(); itm != it->methodlist.end(); itm += 1)
		{
			cout<<"method is "<<itm->name<<"\n";
			for (auto iti = itm->instlist.begin(); iti != itm->instlist.end(); iti += 1)
			{
				reprint(iti);
			}
			cout<<"\n";
		}
	}
}
unordered_map<int,method> methodmap;
unordered_map<int,inst> instructionmap;
unordered_map<int,cla> classmap;
void mapmethods()
{
	for(auto a:classes)
	{
		for (auto b:a.methodlist)
		{
			methodmap[b.no]=b;	
		}
	}
}
void inmap(inst a)
{
	instructionmap[a.no]=a;
	for (auto b:a.instlist)
	{
		inmap(b);
	}
}
void mapinstructions()
{
	for (auto it = classes.begin(); it != classes.end(); it += 1)
	{
		for (auto itm = it->methodlist.begin(); itm != it->methodlist.end(); itm += 1)
		{
			//cout<<"method is "<<itm->name<<"\n";
			for (auto a:itm->instlist)
			{
				inmap(a);
			}
			//cout<<"\n";
		}
	}
}
vector<vector<int>> methodcfg;
void gcfg(vector<inst> a,int c)
{
//	cout<<"call back is "<<c<<"\ninstructions are:\n";
//	for(auto x:a)
//	{
//		cout<<x.no<<" "<<x.instruction<<"\n";
//	}
//	cout<<"\n";
	for(int i=0;i<a.size()-1;i++)
	{
		if(a[i].type==2)
		{
			methodcfg[a[i].no][a[i+1].no]=1;
			methodcfg[a[i].no][(a[i].instlist[0]).no]=1;
			gcfg(a[i].instlist,a[i].no);
		}
		else
		{
			if(a[i].type!=6&&a[i].type!=7)
			{
				methodcfg[a[i].no][a[i+1].no]=1;
	//			cout<<"h  "<<a[i].no<<" "<<a[i+1].no<<"\n";
			}
			else
			{
				if(a[i].type==6)
				{
					methodcfg[a[i].no][a[i+1].no]=1;
					methodcfg[a[i].no][(a[i].instlist[0]).no]=1;
	//					cout<<"h  "<<a[i].no<<" "<<a[i+1].no<<"\n";
	//					cout<<"h  "<<a[i].no<<" "<<(a[i].instlist[0]).no<<"\n";
					if(a[i+1].type==7)
						if(i+2<a.size())
							gcfg(a[i].instlist,a[i+2].no);
						else
							gcfg(a[i].instlist,c);
					else
						gcfg(a[i].instlist,a[i+1].no);
				}
				else
				{
					methodcfg[a[i].no][(a[i].instlist[0]).no]=1;
	//				cout<<"h  "<<a[i].no<<" "<<(a[i].instlist[0]).no<<"\n";
					gcfg(a[i].instlist,a[i+1].no);
				}
				
			}
		}
	}
	int i=a.size()-1;
	if(a[i].type==2)
	{
			methodcfg[a[i].no][c]=1;
			methodcfg[a[i].no][(a[i].instlist[0]).no]=1;
			gcfg(a[i].instlist,a[i].no);
	}
	else
	{
		if(a[i].type!=6&&a[i].type!=7)
		{
			methodcfg[a[i].no][c]=1;
	//		cout<<a[i].no<<" "<<c<<"\n";
		}
		else
		{
			if(a[i].type==6)
			{
					methodcfg[a[i].no][c]=1;
					methodcfg[a[i].no][(a[i].instlist[0]).no]=1;
	//				cout<<a[i].no<<" "<<c<<"\n";
	//				cout<<a[i].no<<" "<<(a[i].instlist[0]).no<<"\n";
			}
			else
			{
				methodcfg[a[i].no][(a[i].instlist[0]).no]=1;
	//			cout<<a[i].no<<" "<<(a[i].instlist[0]).no<<"\n";
			}
			gcfg(a[i].instlist,c);
		}
	}
}
void generatemecfg()
{

	for (long long i = 0; i < instructionmap.size(); i += 1)
	{
		vector<int>x;
		for (long long j = 0; j < instructionmap.size(); j += 1)
		{
			x.push_back(0);
		}
		methodcfg.push_back(x);
	}
//	cout<<"methodcfg size() "<<methodcfg.size()<<" "<<methodcfg[0].size()<<"\n";
	for(auto c:classes)
	{
		for(auto a:c.methodlist)
		{
			if(a.instlist.size()>0)
			{
				vector<inst>b(a.instlist.begin(),a.instlist.begin()+(a.instlist.size()-1));
				gcfg(b,a.instlist[a.instlist.size()-1].no);
			}
		}
	}
}
void printmecfg(int x)
{
	if(x==1)
		cout<<"the paths are :\n";
	for (long long i = 0; i < methodcfg.size(); i += 1)
	{
		for (long long j = 0; j < methodcfg[0].size(); j += 1)
		{
			if(x==1)
			{
				if(methodcfg[i][j]==1)
					cout<<i<<" "<<j<<"\n";
			}
			else
				cout<<methodcfg[i][j]<<" ";
		}
		if(x!=1)
			cout<<"\n";
	}
}

//namespace fs = boost::filesystem;
#include<sys/types.h>
#include<dirent.h>
void prepro()
{
	vector<cla>res=classes;
	for(auto it=res.begin();it!=res.end();it++)
		it->iprocess();
	
	for(auto it=res.begin();it!=res.end();it++)
	{
//		it->print();
		it->process();
		//a.print();	
	}
	for (auto it = res.begin(); it != res.end(); it += 1)
	{
		for (auto im = (it->methodlist).begin(); im != (it->methodlist).end(); im += 1)
		{
			for (auto iti = im->instlist.begin(); iti != im->instlist.end(); iti += 1)
			{
				assignno(iti);
			}
		}
	}
	classes=res;
}
void mapclasses()
{
	for(auto a:classes)
	{
		classmap[a.no]=a;
	}
}
class cfg
{
	public:
	string methodname;
	string classname;
	map<int,inst> instructions;
	method meth;
	vector<pair<int,int>> adj;
	int complexity;
	void calculatecomplexity()
	{
		complexity=adj.size()-instructions.size()+2;
	}
	void print()	
	{
		cout<<"class is "<<classname<<" \nmethod is "<<methodname<<"\ncomplexity is"<<complexity<<"\n";
		for(auto a:instructions)
		{
			cout<<a.first<<" "<<a.second.instruction<<"\n";
		}
		for(auto a:adj)
		{
			cout<<"["<<a.first<<" "<<a.second<<"] ";
		}
		cout<<"\n\n\n";
	}
	cfg(int start,int end,string n,string x,method y)
	{
		meth=y;
		methodname=n;
		classname=x;
		for(int i=start;i<end+1;i++)
		{
			instructions[i]=instructionmap[i];
		}
		for (long long i = start; i < end+1; i += 1)
		{
			for (long long j = start; j < end+1; j += 1)
			{
				if(methodcfg[i][j]==1)
					adj.push_back(make_pair(i,j));
			}
		}
		/*
		for(int i=0;i<methodcfg.size();i++)
		{
			for (long long j = 0; j < methodcfg[0].size(); j += 1)
			{
				if(start<=i&&i<=end&&start<=j&&j<=end)
				{
					adj.push_back(make_pair(i,j));
				}
			}
		}
		*/
		calculatecomplexity();
	}
};
vector<vector<int>>extendedmethodcfg;
void generateextendedmfg()
{
	extendedmethodcfg=methodcfg;
	for(auto a:instructionmap)
	{
		if(a.second.type==3)
		{
//			cout<<a.second.instruction<<" ";
//			cout<<methodmap[a.second.meno].instlist[0].no<<"\n";
			extendedmethodcfg[a.second.no][methodmap[a.second.meno].instlist[0].no]=1;
			extendedmethodcfg[a.second.no][methodmap[a.second.meno].instlist[methodmap[a.second.meno].instlist.size()-1].no]=1;
		}
	}
}
void printextendedmfg(int x)
{
	if(x==1)
		cout<<"the paths are :\n";
	for (long long i = 0; i < extendedmethodcfg.size(); i += 1)
	{
		for (long long j = 0; j < extendedmethodcfg[0].size(); j += 1)
		{
			if(x==1)
			{
				if(extendedmethodcfg[i][j]==1)
					cout<<i<<" "<<j<<"\n";
			}
			else
				cout<<extendedmethodcfg[i][j]<<" ";
		}
		if(x!=1)
			cout<<"\n";
	}
}
vector<cfg> cfgs;
void generatecfgs()
{
	for(auto a:classes)
	{
		for(auto b:a.methodlist)
		{
			cfg x(b.instlist[0].no,b.instlist[b.instlist.size()-1].no,b.name,a.name,b);
			cfgs.push_back(x);
		}
	}
}
void printcfgs()
{
	for(auto a:cfgs)
		a.print();
}
void init(string path)
{
	string ext(".java");
	DIR* dirp = opendir(path.c_str());
	struct dirent * dp;
	while ((dp = readdir(dirp)) != NULL) 
	{
		string a(dp->d_name);
		//cout<<a<<"\n";
		if(a.find(ext)!=string::npos)
		{
			string x=path+"/"+a;
			cout<<x<<"\n";
			intermediate(x);
		}
	}
	prepro();
	closedir(dirp);
	mapmethods();
	mapinstructions();
	generatemecfg();
	generatecfgs();
	generateextendedmfg();
	//mapclasses();
	
}

