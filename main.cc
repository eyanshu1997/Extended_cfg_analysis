#include<bits/stdc++.h>
using namespace std;
#include "values.cc"
#include "parser.cc"
#include "classes.cc"
#include "intermediate.cc"
#include "methodcfg.cc"

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		cout<<"error in args"<<"\n";
		exit(0);
	}
	
	string	a(argv[1]);
//	cout<<a<<"\n";
	init(a);
	ecfg fin;
	fin.print();	
//	printcfgs();
//	for(auto a:instructionmap)
//	{
//		cout<<a.first<<" ";
//		(a.second).cprint();
//	}
//	printinst();
//	printmecfg(1);	
//	
//	printextendedmfg(1);

	//methodmap[1].print();
//	printall();
//	for(auto a:classes)
//		a.printin();
}
