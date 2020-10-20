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
int inbrc(vector<string>lines,int cc)
{
	int br=1;
	if(lines[cc]!="{")
	{
		cout<<"error in braket\n";
		exit(0);
	}
	for(int i=cc+1;i<lines.size();i++)
	{
		if(lines[i]=="{")
			br++;
		if(lines[i]=="}")
			br--;
		if(br==0)
			return i;
	}
	return cc;
}
int inif(vector<string>lines,int cc)
{
	int s=cc;
	//cout<<"line no "<<s<<"\n";
	if(cc<lines.size())
		if(lines[s].find("{")!=string::npos)
		{
			int c=inbrc(lines,s);
			return c;	
		}
		else
		{
			if(lines[s].find("if")==0)
			{
				
				int c=inif(lines,s+1);
				//cout<<"last line is "<<c<<" "<<lines[c]<<"\n";
				if(c+1<lines.size()&&lines[c+1]=="else")
				{
					return inif(lines,c+2);
				}
				return c;
			}
			else
			{
				bool set=true;
				for(auto a:loop)
				{
					if(lines[s].find(a)!=string::npos)
					{
						set=false;
						int c=inif(lines,s+1);
						return c;
					}
				}
				if(set==true)
				{
					return s;
				}
			}
		}
	return s;
}
void print_vars()
{
	for(auto a:vars)
	{
		cout<<"class "<<a.class_name<<" name "<<a.name<<"\n"; 
	}
}
bool checkinit(string line)
{
	int s=line.find(" ");
	string ac=line.substr(0,s);
	//cout<<"checking ["<<ac<<"]\n";
	auto it=find(data_types.begin(),data_types.end(),ac);
	if(it==data_types.end())
		return false;
	return true;
}
vector<inst> get_inst(vector<string> in_ml)
{
	int cc=0;
	vector<inst> ins;
	while(cc<in_ml.size())
	{
		if(in_ml[cc].find("System.out.print")==string::npos)
			if(checkinit(in_ml[cc]))
			{
				//cout<<"initialization statement "<<in_ml[cc]<<"\n";
				int s=in_ml[cc].find(" ");
				string cl=in_ml[cc].substr(0,s);
				string tmp=in_ml[cc].substr(s+1,in_ml[cc].size()-s-1);
				s=tmp.find(" ");
				tmp=tmp.substr(0,s);
				s=tmp.find("=");
				if(s!=string::npos)
					tmp=tmp.substr(0,s);
				tmp=trim(tmp);
				variables z(cl,tmp);
				vars.push_back(z);
				ins.push_back(inst(in_ml[cc],cl,tmp,5));
				cc++;
			}
			else
			{
				bool set=false;
				for(auto a:loop)
				{
					if(cc<in_ml.size())
					if(in_ml[cc].find(a)==0)
					{
						set=true;
						if(in_ml[cc]=="{")
						{
							//if{
							int x=inbrc(in_ml,cc+1);
							vector<string> li(in_ml.begin()+cc+1,in_ml.begin()+x);
							vector<inst> z=get_inst(li);
							ins.push_back(inst(in_ml[cc],z));
							cc=x+1;
						}
						else
						{
							int x=inif(in_ml,cc+1);
							if(x==cc+1)
							{
								//if() a=c;
								vector<inst> ab;
								ab.push_back(inst(in_ml[cc+1]));
								ins.push_back(inst(in_ml[cc],ab));
								cc=cc+2;
							}
							else
							{
								//if() if()
								vector<string> li(in_ml.begin()+cc+1,in_ml.begin()+x+1);
								vector<inst> l=get_inst(li);
								ins.push_back(inst(in_ml[cc],l));
								cc=x+1;
							}
						}
					}
				}
				if(set==false)
				{
					bool s=false;
					for(auto a:cond)
					{
						if(cc<in_ml.size())
						if(in_ml[cc].find(a)==0)
						{
							s=true;
							if(in_ml[cc+1]=="{")
							{
								//if{
								int x=inbrc(in_ml,cc+1);
								vector<string> li(in_ml.begin()+cc+2,in_ml.begin()+x);
								vector<inst> z=get_inst(li);
								ins.push_back(inst(in_ml[cc],z));
								cc=x+1;
							}
							else
							{
								int x=inif(in_ml,cc+1);
								if(x==cc+1)
								{
									//if() a=c;
									vector<inst> ab;
									ab.push_back(inst(in_ml[cc+1]));
									ins.push_back(inst(in_ml[cc],ab));
									cc=cc+2;
								}
								else
								{
									//if() if()
									vector<string> li(in_ml.begin()+cc+1,in_ml.begin()+x+1);
									vector<inst> l=get_inst(li);
									ins.push_back(inst(in_ml[cc],l));
									cc=x+1;
								}
							}
						}
					}
					if(s==false)
					{
						ins.push_back(inst(in_ml[cc],4));
						cc++;
					}
				}
			}
		else
		{
			//x.push_back("print statement "+in_ml[cc]);
			ins.push_back(inst(in_ml[cc]));
			cc++;
		}
	}
	return ins;
}
method promethod(vector<string> in_ml,string na)
{
	//vector<string> x;
	vector<inst> a=get_inst(in_ml);
	int x=methodcount++;
	method me(na,a,x);
	//methodmap[x]=me;
	return me;
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
		//cout<<na<<"\n";
		cla clas(na);
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
				//cout<<"constructor\n";
				vector<string>ml(in_class.begin()+cc+1,in_class.end());
				//print_lines(ml);
				vector<string> in_ml=inbr(ml);
				method me=promethod(in_ml,na);
				clas.add(me);
				//print_lines(in_ml);
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
						int s=re.find(",");
						if(s==string::npos)
						{
							//cout<<"initialization statement "<<ac<<" "<<re<<"\n";
							variables z(ac,re);
							vars.push_back(z);
							clas.add(z);
						}
						else
						{
							//int a,b;
							//cout<<"ac "<<ac<<"\n";
							while(s!=string::npos)
							{
								string var=trim(re.substr(0,s));
								variables z(ac,var);
								vars.push_back(z);
								clas.add(z);
								re=trim(re.substr(s+1,re.size()-s-1));
								s=re.find(",");
							}
							variables z(ac,re);
							vars.push_back(z);
							clas.add(z);
							
						}
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
						//cout<<"method name "<<na<<"\n";
						vector<string>ml(in_class.begin()+cc+1,in_class.end());
						vector<string> in_ml=inbr(ml);
						//print_lines(in_ml);
						//cout<<"\n\n\n";
						method me=promethod(in_ml,na);
//						me.print();
						clas.add(me);
						cc=cc+in_ml.size()+3;
					}
					
				}
			}
		}

		pc=pc+in_class.size()+3;
		//cout<<"pc is"<<pc<<"\n";
		tmp.push_back(clas);
	}
	return tmp;
}
void assignno(vector<inst>::iterator x)
{
	x->no=instructioncount++;
	for (auto it = x->instlist.begin(); it != x->instlist.end(); it += 1)
	{
		assignno(it);
	}
}
void intermediate()
{
		//string line="class node{";
	//vector<string> lines=handlebr(trim(line),"{");
	vector<string> lines=parse("test/Test.java");

//	vector<string> lines=parse("a.txt");
//	vector<inst> a=get_inst(lines);
//	method me("a",a);
//	me.print();

//	cout<<inif(lines,0);
//	print_lines(lines);
//	cout<<"no of lines is"<<lines.size()<<"\n";



	vector<cla> res=findcl(lines);
	classes=res;
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
	//print_vars();
//	vector<string> x;
//	for(int i=2;i<lines.size();i++)
//		x.push_back(lines[i]);
//	print_lines(x);
//	x=inbr(x);
//	print_lines(x);

	//return res;
}
