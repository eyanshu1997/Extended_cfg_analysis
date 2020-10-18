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
	void print()
	{
		cout<<"type "<<type<<"\n";
		if(type==1)
			cout<<instruction<<"\n\n";
		else if(type==2)
		{
			cout<<"if statement    "<<instruction<<"\n";
			cout<<" no of instructions are "<<instlist.size()<<"\n";
			for (long long i = 0; i < instlist.size(); i += 1)
			{
				cout<<"instsurtcion " <<i<<"\n";
				instlist[i].print();
			}
			cout<<"\n\n";
		}
		else
		{
			cout<<instruction<<"\n";
			cout<<"class is "<<cl<<"\n";
			cout<<"method is "<<me<<"\n\n";
		}
		
	}
};
class method
{
	public:
	string name;
	vector<inst> instlist;
	method(string na)
	{
		name=na;
	}
	method(string na,vector<inst> a)
	{
		name=na;
		instlist=a;
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
};
class cla
{
	public:
	string name;
	vector<pair<string,string>> vars;
	vector<method> methodlist;
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
	
};


