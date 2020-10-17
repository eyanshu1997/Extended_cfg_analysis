class inst
{
	public:
	string instruction;
	vector<inst> instlist;
};
class method
{
	public:
	string name;
	vector<inst> instlist;	
};
class cla
{
	public:
	string name;
	vector<pair<string,string>> vars;
	vector<method> methodlist;
};

