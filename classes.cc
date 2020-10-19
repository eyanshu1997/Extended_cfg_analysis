class inst
{
	public:
	int type; //1 for simple    2 for loop or if     3 for function call
	string instruction;
	vector<inst> instlist;
	string me;
	string cl;
	inst(string in)
	{
		type=1;
		instruction=in;
	}
	inst(string a,vector<inst> x)
	{
		type=2;
		instruction=a;
		instlist=x;
	}
	inst(string a,string b,string c)
	{
		type=3;
		instruction=a;
		cl=b;
		me=c;
		
	}
	inst(string a,int x)
	{
		type=3;
		instruction=a;
	}
	void process(cla *b);
	void print()
	{
		cout<<"type "<<type<<"\n";
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
			cout<<"\n["<<instruction<<"\n";
			cout<<"class is "<<cl<<"\n";
			cout<<"method is "<<me<<"]\n\n";
		}
		
	}
};
class method
{
	public:
	string name;
	string n;
	vector<inst> instlist;
	method(string na)
	{
		n=na;
		int s=na.find("(");
		if(s!=string::npos)
		{
			name=trim(na.substr(0,s));
		}
		else
			name=na;
	}
	method(string na,vector<inst> a)
	{
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
		cout<<"method name is "<<name<<"\n";
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
		
		for(auto a:instlist)
		{
			a.process(b);
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
		cout<<"no of methods "<<methodlist.size()<<"\n";
		for(auto a :methodlist)
			a.print();
		cout<<"no of variables is "<<vars.size()<<"\n";
		for(auto a:vars)
		{
			a.print();
		}
	}
	void process()
	{
		for(auto a:methodlist)
			a.process(this);
	}
	bool contains(string x)
	{
		for(auto a:methodlist)
		{
			//cout<<"checking "<<x<<" "<<a.name<<"\n";
			if(a.name==x)
				return true;
		}
		return false;
	}
};
void inst::process(cla *b)
{
	// a.function() or function()
	for(auto a:instlist)
	{
		a.process(b);
	}
	if(type==3)
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
				if(b->contains(trim(x))==true)
				{
					cout<<"res "<<x<<" "<<b->name<<"\n\n\n";
					type=3;
					me=x;
					cl=b->name;
				}
				else
				{
					//cout<<"1 instruction\n\n\n";
					instruction="unidentified "+instruction;
					type=1;
				}
			}
			else
			{
				string na=x.substr(0,z);
				x=x.substr(z+1,x.size());
				//cout<<na<<" . found "<<x<<"\n";
				bool set=true;
				for(auto a:classes)
				{
					if(trim(a.name)==trim(na))
					{
						if(a.contains(trim(x)))
						{
							cout<<"res "<<x<<" "<<a.name<<"\n\n\n";
							type=3;
							me=x;
							cl=a.name;
							set=false;
						}
					}
				}
				if(set==true)
				{
					//cout<<"1..2 instruction\n\n\n";
					type=1;
					instruction="unidentified "+instruction;
				}
			}
		}
		else
		{
			//cout<<"1..3 instruction\n\n\n";
			type=1;
			instruction="unidentified "+instruction;
		}
	}
}

