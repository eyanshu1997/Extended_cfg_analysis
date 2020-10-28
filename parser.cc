

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
vector<string> handleelse(string line)
{
	line=trim(line);
	vector<string>x;
	int s=line.find("else");
	if(s==0&&line.size()>4)
	{
		string rem=trim(line.substr(s+4,line.size()-s-4));
		line=line.substr(0,4);
		x.push_back(rem);
		x.push_back(line);
	}
	else
		x.push_back(line);
	return x;
	
}
vector<string> handlemod(string line)
{
	vector<string>z;
	line=trim(line);
	int s=line.find(" ");
	string x=trim(line.substr(0,s));
	auto it=find(modifiers.begin(),modifiers.end(),x);
	while(it!=modifiers.end())
	{
		line=trim(line.substr(s+1,line.size()-s-1));
		s=line.find(" ");
		if(s!=string::npos)
			x=trim(line.substr(0,s));
		else
			x=trim(line);
		it=find(modifiers.begin(),modifiers.end(),x);
	}
	z.push_back(trim(line));
	return z; 
}
vector<string> handlebr(string line,string br)
{
	//cout<<line;
	line=trim(line);
	vector<string>lines;
	size_t fo;
	fo=line.rfind(br);
	if(br==";")
	{
		int st=line.find("for(");
		int se=line.find(")");
		if(st<fo<se)
		{
			lines.push_back(line);
			return lines;	
		}
	}
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
bool check(string a)
{
	for(auto b:modifiers)
		if(a.find(b+":")==0)
			return false;
	return true;
}
vector<string> rememp(vector<string> lines)
{
	vector<string> ne;
	for(auto a:lines)
	{
		a=trim(a);
		if(a!=""&&a!=";"&&a!=":")
			if(a.find("@")!=0)
				if(check(a))
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
		if(line.find("//")!=0)
		{
			vector<string> li=handlebr(line,"}");
			for(auto x:li)
			{
				vector<string> z=handlebr(x,"{");
				for(auto y:z)
				{
					vector<string> a=handlebr(y,";");
					for(auto b:a)
					{
						vector<string>c =handleelse(b);
						for(auto e:c)
						{
							vector<string>f=handlemod(e);
							for(auto d:f)
								lines.push_back(trim(d));
						}
					}
				}
			}
		}
	}
	lines=rememp(lines);
	return lines;
}


