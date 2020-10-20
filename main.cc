#include<bits/stdc++.h>
using namespace std;
#include "values.cc"
#include "parser.cc"
#include "classes.cc"
#include "intermediate.cc"

int main()
{
	intermediate();
	for(auto a:classes)
	{
		a.print();
	}
	

}
