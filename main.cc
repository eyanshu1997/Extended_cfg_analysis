#include<bits/stdc++.h>
using namespace std;
#include "values.cc"
#include "parser.cc"
#include "classes.cc"
#include "intermediate.cc"
void generatecfg()
{
	
}
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
		for (auto itm = it->methodlist.begin(); itm != it->methodlist.end(); itm += 1)
		{
			for (auto iti = itm->instlist.begin(); iti != itm->instlist.end(); iti += 1)
			{
				reprint(iti);
			}
		}
	}
}
int main()
{
	intermediate();
	printinst();
}
