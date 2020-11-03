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
	int no;
	string methodname;
	string classname;
	map<int,inst> instructions;
	method meth;
	vector<pair<int,int>> adj;
	int complexity;
	vector<vector<int>>basisset;
	void calculatecomplexity()
	{
		complexity=adj.size()-instructions.size()+2;
	}
	cfg()
	{
	}
	vector<vector<int>> basissetconst(vector<int> cur,int i,int end)
	{
		vector<vector<int>> res;
		if(i!=end)
		{
			cur.push_back(i);
			vector<int>next;
			for(auto a:adj)
			{
				if(i==a.first)
					next.push_back(a.second);
			}
			for(auto a:next)
			{
				if(find(cur.begin(), cur.end(),a)==cur.end())
				{
					vector<vector<int>> x=basissetconst(cur,a,end);
					for(auto b:x)
					{
						res.push_back(b);
					}
				}
			}
		
			
		}
		else
		{
			cur.push_back(i);
			res.push_back(cur);
		}
		return res;
	}
	void findbasisset()
	{
		int start=instructions.begin()->first;
		int end=instructions.rbegin()->first;
		int i=start;
		vector<int>cur;
		//cur.push_back(i);
		basisset=basissetconst(cur,i,end);
	}
	void print()	
	{
		cout<<"The class name is "<<classname<<" \nThe Method name is "<<methodname<<"\nThe Cyclomatic Complexity is "<<complexity<<"\n";
		for(auto a:instructions)
		{
			cout<<a.first<<" "<<a.second.instruction<<"\n";
		}
		cout<<"The adjancency matrix is \n";
		for(auto a:adj)
		{
			cout<<"["<<a.first<<" "<<a.second<<"] ";
		}
//		cout<<"\nthe basis set is:\n";
//		for(auto a:basisset){for(auto i:a) cout<<i<<" ";cout<<"\n"; }cout<<"\n";
		cout<<"\n\n";
	}
	cfg(int start,int end,string n,string x,method y)
	{
		meth=y;
		methodname=n;
		classname=x;
		no=y.no;
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
		findbasisset();
//		print();
	}
};
class ecfg
{
	public:
//	string methodname;
//	string classname;
	map<int,cfg> cfgs;
//	method meth;
	vector<pair<int,int>> adj;
	int ecomplexity;
	int extracalls;
	vector<vector<int>>basisset;
	void store()
	{
		ecomplexity=calculateecomplexity();
	}
	int search(int x,vector<pair<int,int>> y)
	{
		for(auto a:y)
		{
			if(a.first==x)
				return a.second;
		}
		return -1;
	}
	vector<vector<int>> basisiset(int a,vector<pair<int,int>> calls)
	{
		cout<<"called for "<<a<<"\n";
		/*
		if(a!=7&&a!=0)
		{
			cout<<"hell"<<a;
			
			exit(0);
		}
		*/
		vector<vector<int>>res;
		for(auto b:cfgs[a].basisset)
		{
			cout<<"current basis set is\n";
			for(auto i:b) cout<<i<<" ";cout<<"\n";
			vector<vector<int>>re;
			vector<int>st;
			st.push_back(b[0]);
			re.push_back(st);
			for (long long i = 1; i < b.size(); i += 1)
			{
				for (auto it = re.begin(); it != re.end(); it += 1)
				{
					it->push_back(b[i]);
				}
				
				int s=search(b[i],calls);
				if(s!=-1)
				{
					cout<<"called for s "<<b[i]<<" s is "<<s<<"\n";
					vector<vector<int>>bre=basisiset(s,calls);
					vector<vector<int>> newre;
					for(auto r:re)
					{
						for(auto br:bre)
						{
							vector<int> rz=r;
							for(auto a:br)
								rz.push_back(a);
							newre.push_back(rz);
						}
					}
					re=newre;
					cout<<"ran on s"<<s<<"\n";
					for(auto a:re){for(auto i:a) cout<<i<<" ";cout<<"\n"; }cout<<"\n";
				}
				
			}
			for(auto x:re)
				res.push_back(x);
			cout<<"res is \n";
			for(auto a:res){for(auto i:a) cout<<i<<" ";cout<<"\n"; }cout<<"\n";
		}
		return res;
	}
	void findbasisset()
	{
		vector<pair<int,int>>calls;
		for(auto a:cfgs)
		{
			for(auto b:a.second.instructions)
			{
				if(b.second.type==3)
				{
					calls.push_back(make_pair(b.second.no,b.second.meno));
				}
			}
		}
		int m=-1;
		
		for(auto a:cfgs)
		{
			if(a.second.meth.name=="main")
				m=a.second.no;
		}
		if(m==-1)
		{
			cout<<"error";
			exit(0);
		}
		cout<<"calls are";
		for(auto i:calls) cout<<"["<<i.first<<" "<<i.second<<"] ";cout<<"\n";
		vector<vector<int>> mai=basisiset(m,calls);
		for(auto a:mai){for(auto i:a) cout<<i<<" ";cout<<"\n"; }cout<<"\n";;	
	}
	int calculateecomplexity()
	{
		extracalls=0;
		cfg m;
		vector<int>explored;
		for(auto a:cfgs)
		{
			if(a.second.meth.name=="main")
				m=a.second;
		}
		return cale(m,explored)+extracalls;
	}
	int cale(cfg x,vector<int> explored)
	{
		int value=x.complexity;
		vector<int>called;
		for(auto a:adj)
		{
			if(a.first==x.no)
			{
				called.push_back(a.second);
			}
		}
		if(called.size()>0)
		{
			int prevalue=0;
			for(auto a:called)
			{
				int thisvalue=0;
				if(a==x.no)
				{
					thisvalue=2;
					if(thisvalue>prevalue)
					{
						prevalue=thisvalue;
						continue;
					}
				}
				else
				{
					if(find(explored.begin(),explored.end(),a)!=explored.end())
					{
						extracalls++;
						continue;
					}
					else
					{
						explored.push_back(a);
						thisvalue=cale(cfgs[a],explored);
						if(thisvalue>prevalue)
							prevalue=thisvalue;
					}
				}
			}
			value+=prevalue;
		}
		return value;
	}
	void print()	
	{
		
		for(auto a:cfgs)
		{
			cout<<"The CFG no is "<<a.first<<" \n";
			a.second.print();
		}
		cout<<"Extended Cyclomatic Complexity is "<<ecomplexity<<"\n";
		cout<<"The Extended Control flow graph edges are\n";
		for(auto a:adj)
		{
			cout<<"["<<a.first<<" "<<a.second<<"] ";
		}
		cout<<"\n\n\n";
	}
	ecfg()
	{
		//int no=0;
		for(auto a:classes)
		{
			for(auto b:a.methodlist)
			{
				cfg x(b.instlist[0].no,b.instlist[b.instlist.size()-1].no,b.name,a.name,b);
				cfgs[x.no]=x;
			}
		}
		for(auto a:cfgs)
		{
			for(auto b:a.second.instructions)
			{
				if(b.second.type==3)
				{
					adj.push_back(make_pair(a.first,b.second.meno));
				}
			}
		}
		store();
//		findbasisset();
	}
};
#include<sys/types.h>
#include<dirent.h>

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
//			cout<<x<<"\n";
			intermediate(x);
		}
	}
	prepro();
	closedir(dirp);
	mapmethods();
	mapinstructions();
	generatemecfg();
	//mapclasses();
	
}


