class inst
{
	public:
	int type; //0 is start #######1 for simple    ########2 for loop or if     ###########3 for function call ########5 for initalization ###6 for if #######7 for else  #### 8 is end
	string instruction;
	vector<inst> instlist;
	string datatyp,varname;
	string me;
	string cl;
	int meno;
	bool linked=false;
	int no=-1;
	inst()
	{
	}
	bool operator==(const inst& p) const
	{ 
		return instruction == p.instruction&&type==p.type&&no==p.no; 
	}
	inst(string in)
	{
		//no=instructioncount++;
		type=1;
		instruction=in;
	}
	inst(string a,vector<inst> x,int y)
	{
		//no=instructioncount++;
		type=y;
		instruction=a;
		instlist=x;
	}
	inst(string a,string b,string c)
	{
		//no=instructioncount++;
		type=3;
		instruction=a;
		linked=true;
		cl=trim(b);
		me=trim(c);
		
	}
	inst(string a,int x)
	{
		//no=instructioncount++;
		type=x;
		instruction=a;
	}
	inst(string a,string b,string c,int x)
	{
		instruction=a;
		varname=trim(c);
		datatyp=trim(b);
		//linked=true;
		type=5;
	}

	void process(cla *b);
	void cprint()
	{
		cout<<no<<" "<<instruction<<"\n";
//		cout<<no<<" "<<type<<" "<<instruction<<"\n";
//		if(type==5)
//		{
//			cout<<"varname is "<<varname<<"\n";
//			cout<<"datatype is"<<datatyp<<"\n";
//		}
//		if(linked==true)
//		{
//			cout<<"class is "<<cl<<"\n";
//			cout<<"method no is"<<meno<<"\n";
//			cout<<"method is "<<me<<"\n";
//		}
	}
	void print()
	{
		cout<<"instrcution count is "<<no<<"\ntype "<<type<<"\n";
		if(type==1)
			cout<<"["<<instruction<<"]\n\n";
		else if(type==2)
		{
			cout<<"[\n if statement    "<<instruction<<"\n";
			cout<<" no of instructions are "<<instlist.size()<<"\n";
			for (long long i = 0; i < instlist.size(); i += 1)
			{
				cout<<"instsurtcion " <<i<<"\n";
				instlist[i].print();
			}
			cout<<"\n]\n\n";
		}
		else
		{
			if(type==5)
			{
				cout<<"\n["<<instruction<<"\n";
				cout<<"varname is "<<varname<<"\n";
				cout<<"datatype is"<<datatyp<<"\n";
				cout<<"type is "<<type<<"]\n\n";
			}
			else
			{
				cout<<"\n["<<instruction<<"\n";
				cout<<"class is "<<cl<<"\n";
				cout<<"method no is"<<meno<<"\n";
				cout<<"method is "<<me<<"]\n\n";
			}
		}
		
	}
};
class method
{
	public:
	int no;
	string name;
	string n;
	vector<inst> instlist;
	bool operator==(const method& p) const
	{ 
		return name == p.name&&n==p.n&&no==p.no; 
	} 
	method()
	{
	}
	method(string na,int meno)
	{
		no=meno;
		n=na;
		int s=na.find("(");
		if(s!=string::npos)
		{
			name=trim(na.substr(0,s));
		}
		else
			name=na;
	}
	method(string na,vector<inst> a,int meno)
	{
		no=meno;
		n=na;
		instlist=a;
		int s=na.find("(");
		if(s!=string::npos)
		{
			name=trim(na.substr(0,s));
		}
		else
			name=na;
	}
	void print()
	{
		cout<<"method name is "<<name<<" no is "<<no<<"\n";
		cout<<"instructions are \n";
		for(auto a:instlist)
			a.print();
		cout<<"\n\n";
	}
	void add(inst a)
	{
		instlist.push_back(a);
	}
	void process(cla *b)
	{
		
		for(auto it= instlist.begin();it!=instlist.end();it++)
		{
			(it)->process(b);
		}
		
	}
};
class variables
{
	public:
	string class_name;
	string name;
	variables(string a,string b)
	{
		class_name=a;
		name=b;
	}
	void print()
	{
		cout<<"data type "<<class_name<<" name "<<name<<"\n";
	}
};


class cla
{
	public:
	string name;
	vector<variables> vars;
	vector<method> methodlist;
	cla(string n)
	{
		name=n;
	}
	void add(method m)
	{
		methodlist.push_back(m);
	}
	void add(variables v)
	{
		vars.push_back(v);
	}
	void print()
	{
		cout<<"name of class "<<name <<"\n";
		cout<<"no of variables is "<<vars.size()<<"\n";
		for(auto a:vars)
		{
			a.print();
		}
		cout<<"no of methods "<<methodlist.size()<<"\n";
		for(auto a :methodlist)
			a.print();
	
	}
	void process()
	{
		for(auto it=methodlist.begin();it!=methodlist.end();it++)
			(it)->process(this);
	}
	int contains(string x)
	{
		for(auto a:methodlist)
		{
			//cout<<"checking "<<x<<" "<<a.name<<"\n";
			if(a.name==x)
				return a.no;
		}
		return -1;
	}
};
void inst::process(cla *b)
{
	// a.function() or function()
	for(auto it= instlist.begin();it!=instlist.end();it++)
	{
		(it)->process(b);
	}
	if(type==4)
	{
		//cout<<"called for instruction "<<instruction<<"\n";
		int s=instruction.find("(");
		if(s!=string::npos)
		{
			string x=instruction.substr(0,s);
			x=trim(x);
			//cout<<"(found"<<x<<"\n";
			int y=x.rfind(" ");
			x=x.substr(y+1,x.size());
			int z=x.find(".");
			if(z==string::npos)
			{
				//cout<<". not found "<<x<<"\n";
				int s=b->contains(trim(x));
				if(s>0)
				{
					//cout<<"res "<<x<<" "<<b->name<<"\n\n\n";
					type=3;
					meno=s;
					me=x;
					cl=b->name;
				}
				else
				{
					//cout<<"1 instruction\n\n\n";
					//instruction="unidentified "+instruction;
					type=1;
				}
			}
			else
			{
				string na=x.substr(0,z);
				x=x.substr(z+1,x.size());
				//cout<<na<<" . found "<<x<<"\n";
				bool set=true;
				for(auto v:vars)
				{
					if(na==v.name)
					for(auto a:classes)
					{
						if(trim(a.name)==trim(v.class_name))
						{
							int s=a.contains(trim(x));
							if(s>0)
							{
								//cout<<"res "<<x<<" "<<a.name<<"\n\n\n";
								type=3;
								me=x;
								meno=s;
								cl=a.name;
								set=false;
							}
						}
					}
				}
				if(set==true)
				{
					//cout<<"1..2 instruction\n\n\n";
					type=1;
					//instruction="unidentified "+instruction;
				}
			}
		}
		else
		{
			//cout<<"1..3 instruction\n\n\n";
			type=1;
			instruction=instruction;
		}
	}
}

class cfg
{
	unordered_map<int,string> instructions;
	vector<vector<int>> adj;
	void print()	
	{
		for(auto a:instructions)
		{
			cout<<a.first<<" "<<a.second<<"\n";
		}
		for(auto a:adj)
		{	for(auto b:a)
				cout<<b<<" ";
			cout<<"\n";
		}
		cout<<"\n";
			
	}
};
