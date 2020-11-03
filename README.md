# Extended_cfg_analysis
Abstract
Control flow graphs and cyclomatic complexity are integral in determining the basis paths in procedural systems and no of the independent paths in a system for use in basis set testing. The basic features of object-oriented software such as inheritance, encapsulation, and polymorphism make it difficult to apply those approaches of testing to them. Basis path testing which is a form of white-box testing is a very commonly used technique that ensures that every path of a program is executed at least once.
For basis set testing the major challenge is the calculation of cyclomatic complexity in object-oriented programs. My work implements a model named Extended Control Flow Graph for code-based analysis of object-oriented software. It is a layered control flow graph where nodes refer to methods rather than statements. my work implements the calculation of Extended Cyclomatic complexity and basis paths for an object-oriented program given as input. the proof of the model, as well as other details, are mentioned in the reference paper. I have implemented the model as a proof of concept of a system that could easily determine the basis set for testing in the case of object-oriented programs.

Tables of contents

Chapter 1 Introduction
1.1 Introduction to Control Flow Graph

	A control flow graph in computer science is a representation using graph notation, of all paths that might be traversed through a program during its execution.
	In a control flow graph, the node represents a  basic block of execution, which is in sequential order of execution, without any scope of change of order of execution. Directed edges determine the change of flow of execution from one block of execution to the start of another block. in addition to these blocks in most representations, there are specially designated blocks: the entry blocks, through which control enters, and an exit block from where all the control flow leaves.


FIG 1.1 EXAMPLE OF CONTROL FLOW GRAPH

1.2 Cyclomatic Complexity of a CFG

	Cyclomatic complexity is a metric that was developed by [4] and is used to indicate the complexity of a program. It is a measure of the maximum no of linearly independent paths through a program in execution.
 	Cyclomatic complexity is computed using the control flow graph of the program: the nodes of the graph correspond to indivisible groups of commands of a program, and a directed edge connects two nodes if the second command might be executed immediately after the first command. Cyclomatic complexity may also be applied to individual functions, modules, methods, or classes within a program. The cyclomatic complexity of a section of source code is the number of linearly independent paths within it—where "linearly independent" means that each path has at least one edge that is not in one of the other paths. For instance, if the source code contained no control flow statements (conditionals or decision points), the complexity would be 1, since there would be only a single path through the code. If the code had one single-condition IF statement, there would be two paths through the code: one where the IF statement evaluates to TRUE and another one where it evaluates to FALSE, so the complexity would be 2. Two nested single-condition IFs, or one IF with two conditions, would produce a complexity of 3. [5]  
There are many ways to calculate the cyclomatic complexity of a program but the mostly used is: 
CC= E-N+2
where CC is cyclomatic complexity, N is the number of nodes, and E is the number of Edges.

1.3 Use of Control flow graph in software testing

	Cyclomatic Complexity is useful in determining the number of test cases that are necessary to achieve test coverage of a particular module[4]. it is useful since it determines the upper bound for the number of paths through the program in execution. The control flow also tells us about the basis path set. The basis path set is a set of all the paths from the start node to the end node which are all the paths that a program can take up during the execution. The testing of the basis path set ensures that the program is tested for all situations that a program can take up during the execution.

Chapter 2 How to approach a solution

Approaching the solution involves understanding the below stated model and implementing in all its completeness to develop a proof of concept of a system that would take an object oriented system as an input and output the extended cyclomatic complexity, extended control flow graph, as well as the basis set of the program.

2.1 Concept of extended Control flow graph

	Extended Control Flow Graph is(ECFG) is a new model proposed by S. Bhattacharya and A. Kanjilal in a paper [1][3]. It is analogous to CFG for an object-oriented system. It is Layered Cfg where each node is itself a method Cfg and each edge is a method call. Everything else is similar in case of a normal CFG. Thus every node may further be referring to another graph. 
Essentially ECFG has two layers
• The topmost layer represents the methods of individual classes.
• The next layer represents the CFGs of these methods.

Following are the features of ECFG:
1. The graph is similar to CFG consisting of nodes and edges between nodes except at the topmost level where some nodes may be disconnected. It is a series of graphs arranged in layers.
2. Nodes in CFG refer to statement(s) whereas in ECFG, nodes refer to methods.
3. Every method has associated graphs (CFG) and cyclomatic complexity values. methods, not found in the required class may be a part of its parent class.
4. Object declaration is similar to variable declaration of procedural languages but is not a sequence statement since it refers to constructor method.
5. Edges between nodes are formed whenever any method calls another method. There may be different ways in which nodes are connected.

Fig 2.2 EXAMPLE OF ECFG

2.2 Concept of extended Extended Cyclomatic Complexity

In an ECFG, the methods (or CFGs) may be connected in one of the six possible ways.
E-CC, the composite complexity of the two or more graphs taken together is distinct in each case. The physical significance of CC i.e. the number of independent paths is maintained while calculating E-CC as well.
The various cases and the E-CC value is as follows and their corresponding proofs are present in the referred paper[1]

Case 1: When two or more graphs are connected in series, i.e. the methods execute in sequence one after the other. If V(G1),V(G2)......V(Gn) are complexities of individual graphs then the E-CC is the largest among them all.
E − CC = V (Gx) if V (Gx) > V (G1), V (G2).....V (Gn) and 1 < x < n 

Case 2: When two or more graphs are embedded within a graph i.e. a method calls another method which in turn calls another and so on. If V(G1), V(G2) ...... V(Gn) are complexities of each individual graphs and they are embedded within each other i.e. G1 embeds G2, G2 embeds G3 and so on, then the E- CC is given as follows :
E − CC = V (G1) + V (G2) + V (G3) + ...............V (Gn)(n − 1)
where n-1 graphs (2 to n) are embedded within G1.The same holds true even if there is no nested embedding i.e. G1 embeds G2,G3... Gn.

Case 3: If a graph embeds another graph more than once, e.g G1 embeds G2 thrice,then G2 is taken to be embedded only once since once tested it need not be tested again.
Composite complexity E-CC will be the same as in Case 2 where all the complexity values refer to unique graphs - G1, G2 ........... Gn.

Case 4: When many graphs embed the same graph i.e. more than one method calls the same method. Here also the repeated graph is considered only once but the point of entry should be tested in every context.
E − CC = (V (G1) + V (G2) − 1) + V (G3) + ...... + V (Gn) + (n − 2)
where V(G1) : complexity of G(1) that is embedded multiple times and V(G2) ...V(Gn) are complexity values for graphs which embed G1 and n-2 : no. of graphs embedding G1 except one.

Case 5: When one graph is recursively repeated i.e. a method is recursively called.
E − CC = V (G1) + 2
where V(G1) is the complexity of the method in recursion.
Case 6: When recursion involves more than one method. This is a combination of case 1,2,3. Composite complexity
E − CC = V (G 0 ) + 2
where G 0 is more than one method connected as per case 1 or 2.

Chapter 3 Design for the solution

3.1 Overview

My proposed work is to automate the Construction of the proposed model ie ECFG [1][3] for java programs. I have chosen java since it is a completely object oriented language and that would provide consistency. I would also implement the Calculation of Extended Cyclomatic Complexity and generation of the Basis path set for object oriented java programs using the proposed model.The various steps involved are:
Implementation of a way to parse a java class into intermediate form.
storing of intermediate form to the respective defined class objects.
construct CFG for a given method.
 Traversing the CFG to find Call Nodes and connect Edges between Nodes of ECFG (remember in ECFG methods are the nodes).
Implement the calculation of E-CC by using six defined cases.

3.2 Implementation of a way to parse the class.

	I had to face various problems for parsing the programs. I couldn't use ASM Api for java compiled classes as there wasn't much available support for that in the C++ language of my use. there were various things that were needed to be taken care of for the parsing of classes:
Inheritance caused called methods not being in the clases that the parser expected.
nested if else,while as well as if statements needed to be handled to understand the level of depth of brackets the statement was in.
polymorphism caused the methods to have the same name but different arguments to resolve the functions call i had to check the arguments .

The brief discussion of my implemented methods are as follows:
trim- this function was used to trim the strings for tailing and starting spaces.
hanleelse, handlebr, handlemod-all these functions are helper functions for the parser function they all perform some function to handle brackets else if or loops etc understanding the depth of the statement in the program.
parser- this function is used to read a file and parse it to an intermediate form for next functions to parse. This function also removes some information that is not required.

3.3 Storing of intermediate form to the respective defined class objects.

There are few classes that are used to store the program into a form that is easily workable. the classes are defined below:

inst class-it is used to store. it contains all the information for an individual instruction in case of if and loop statements the instruction inside the if clocks are stored in a vector of instruction inside the instruction class. the various data objects in this class are as follows:
type- defines the type of the instruction. 0 is start, 1 for simple, 2 for loop, 3 for function call, 5 for initialization, 6 for if, 7 for else, 8 is end.
instruction- contains the actual string form of instruction.
data type- contains the data type in case of initialization statement.
varname- contains  the data type in case of initialization statement.
me- contains method name in case of method call
cl-contains class name in case of method call
meno- contains method number in case of method call
no- instruction number.
instlist- vector of instructions contained within in case of loop ,if or else.
method class- it is used to store an individual method. the various data types in this class is:
no- method number.
name- name of the method.
instlist- the vector of instruction class contained in the method.
variables class- it is used to store any variable used that is initialized.
class_name- denotes the class name of the variable.
name- name of the variable.
cla class-it is used to store an individual class.its data types are as follows:
fname-the full declaration of class including the extends throws keywords etc.
name-the actual name of the class.
no- the class number..
vars- the variables declared in the class.
methodist- vector of method class representing each method present in the class.
inherit- list of class no that the class inherits.

The actual storing of the intermediate parsing output returned by the parser function to the reprepective class objects defined above is done by a lot of functions. The functions are:

findcl-it takes the intermediate parsed output as input and finds the next class in the code.it also finds the code block of the class enclosed in brackets. For each class found by this function it is processed to find the variable declaration of the class and its contained methods.for each declaration method that is found, its followed code block is passed to getinst function.
getinst- this function takes a list of strings as input and outputs a vector of inst class objects for each instruction. if there is a if, else, or aloop instruction the code blocked enclosed by these instructions is further passed to getinst function to return the enclosed set of instructions.

There are a number of other supporting functions that perform various other functions that are called by the above two functions to get the work done. there are various other functionalities that are being performed for different types of functions. the inherited classes methods are copied into the class that inherits them. function call instructions are mapped to the respective functions.

3.4 Construction of CFG for method. 

	The construction of CFG involves parsing each class for its underlying methods and then storing them into the CFg class. The cfg class is used to store a cfg for respective methods.the various datatypes of this class and its functions are:
no-number of method.
methodname- name of the method.
classname- name of the class the method is a part of.
meth- method class object of whichthe cfg is.
instructions- a map of instruction to corresponding instruction object in the method.
adj-a 2-Dimensional array of integer where 1 denotes there is directed edge from i to j. and zero that an end is not present. i and j represent the array indices and the intersection number i biegn the source and j being the destination.
basisset- it is a 2-d vector which stores all the paths from start to end in a method.
complexity- it stores the complexity of the graph.
calculatecompexity- it calculates the complexity of the cfg using the formula E-N+2 as described inthye previous sections.
basissetconst- it is used to construct the basis set by traversing all the paths from start to end. The seize of this vector is equal to the cyclomatic complexity.
cfg()-constructor function for the cfg class it fill the adj matrix defined above using the defined procedure for creating a cfg.the cfg in various situations are:
			
Fig 3.1 CFG for “if else”		Fig 3.2 CFG for “while”.			Fig 3.3 CFG for “for”

3.5 Construction of ECFG

	The ECFG is stored in the class ecfg it contains the following data types:
cfgs- it is a map of the number of methods with corresponding cfg objects.
adj- it is a 2-Dimensional array that is 1 if there is a directed edge from i to j and 0 is there does not exists a edge where i  denotes the source method no and j denotes the destination method no.
the formation process of extended cfg is as follows:
it starts from the main method’s cfg.
for each function call in this method it adds a directed edge from the current function to the called function.
for all called functions in the current function the steps 2-3 are done again.
the resultant adj matrix is stored in the object of ecfg class. 

3.6 Calculation of Extended Cyclomatic complexity

	The extended Cyclomatic Complexity of the ECFG is calculated by following the rules
as discussed previously in section 2.2 by traversing the ECFG by following algorithm.
	
	
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

This algorithm works as the extended cyclomatic complexity is defined in the research paper [1] and [3].

Chapter 4 Results

4.1	Example 1
	This is simple program we check for all types of cases of connectivity.

Input code


import java.util.scanner;

public class atm
{
	private int balance;
	int getbalance()
	{
		return balance;
		
	}
	void withdraw(int account)
	{
		if(balance<1000)
			System.out.println("insufficient funds");
		else
		{ 
			if(balance-amount<1000)
				System.out.println("balance should not be less than 1000");
			else
				deductbalance(amount);
		}
	}
	void deposit(int amount)
	{
		addbalance(amount);
	}
	void deductbalance(int amount)
	{
		int bal;
		bal=getbalance();
		bal-=amount;
		setbalance(bal);
	}
	void addbalance(int amount)
	{
		int bal=getBalance();
		bal+=amount;
		setbalance(amount);
	}
	void setbalance(int amount)
	{
		balance=amount;
	}
	public static void main(String[] args)
	{
		int choice=0;
		Atm a= new ATM();
		while(choice!=1)
		{
			System.out.println("enter your choice");
			System.out.println("1. check balance");
			System.out.println("2. withdraw amount");
			System.out.println("3. deposit money");
			System.out.println("enter -1 to exit");
			Scanner s=new Scanner(System.in);
			choice=s.nextInt();
			if(choice<=3&&choice>=1)
			{
				
				if(choice==1)
					System.out.println(a.getBalance);
				else
					if(choice==2)
					{
						System.out.println("enter the amount");
						int amount=s.nextInt();
						a.withdrwa(amount);
					}
					else
						if(choice==3)
						{
							System.out.println("enter teh amount");
							int am=s.nextInt();
							a.deposit(am);
						}
			}
				
		}
	}
}

Output


The CFG no is 0 
The class name is atm 
The Method name is getbalance
The Cyclomatic Complexity is 1
0 start 
1 return balance
2 end 
The adjancency matrix is 
[0 1] [1 2] 

The CFG no is 1 
The class name is atm 
The Method name is withdraw
The Cyclomatic Complexity is 3
3 start 
4 if(balance<1000)
5 System.out.println("insufficient funds")
6 else
7 if(balance-amount<1000)
8 System.out.println("balance should not be less than 1000")
9 else
10 deductbalance(amount)
11 end 
The adjancency matrix is 
[3 4] [4 5] [4 6] [5 11] [6 7] [7 8] [7 9] [8 11] [9 10] [10 11] 

The CFG no is 2 
The class name is atm 
The Method name is deposit
The Cyclomatic Complexity is 1
12 start 
13 addbalance(amount)
14 end 
The adjancency matrix is 
[12 13] [13 14] 

The CFG no is 3 
The class name is atm 
The Method name is deductbalance
The Cyclomatic Complexity is 1
15 start 
16 int bal
17 bal=getbalance()
18 bal-=amount
19 setbalance(bal)
20 end 
The adjancency matrix is 
[15 16] [16 17] [17 18] [18 19] [19 20] 

The CFG no is 4 
The class name is atm 
The Method name is addbalance
The Cyclomatic Complexity is 1
21 start 
22 int bal=getBalance()
23 bal+=amount
24 setbalance(amount)
25 end 
The adjancency matrix is 
[21 22] [22 23] [23 24] [24 25] 

The CFG no is 5 
The class name is atm 
The Method name is setbalance
The Cyclomatic Complexity is 1
26 start 
27 balance=amount
28 end 
The adjancency matrix is 
[26 27] [27 28] 

The CFG no is 6 
The class name is atm 
The Method name is main
The Cyclomatic Complexity is 6
29 start 
30 int choice=0
31 Atm a= new ATM()
32 while(choice!=1)
33 System.out.println("enter your choice")
34 System.out.println("1. check balance")
35 System.out.println("2. withdraw amount")
36 System.out.println("3. deposit money")
37 System.out.println("enter -1 to exit")
38 Scanner s=new Scanner(System.in)
39 choice=s.nextInt()
40 if(choice<=3&&choice>=1)
41 if(choice==1)
42 System.out.println(a.getBalance)
43 else
44 if(choice==2)
45 System.out.println("enter the amount")
46 int amount=s.nextInt()
47 a.withdrwa(amount)
48 else
49 if(choice==3)
50 System.out.println("enter teh amount")
51 int am=s.nextInt()
52 a.deposit(am)
53 end 
The adjancency matrix is 
[29 30] [30 31] [31 32] [32 33] [32 53] [33 34] [34 35] [35 36] [36 37] [37 38] [38 39] [39 40] [40 32] [40 41] [41 42] [41 43] [42 32] [43 44] [44 45] [44 48] [45 46] [46 47] [47 32] [48 49] [49 32] [49 50] [50 51] [51 52] [52 32] 

Extended Cyclomatic Complexity is 6
The Extended Control flow graph edges are 
[2 4] [3 5] [4 5] 

	The above output shows the snapshot of the output of my program as it is shown the program analysis each class and its method and properly finds the cfg of those methods and then finds the extended Control flow graph and also the Extended Cyclomatic complexity of the graph.

Conclusion

	In this project we implemented a graph based methodology for analysis of OO systems focusing on the structure of program code and arrives at an analogous model to CFG for testing of OO systems. Cyclomatic Complexity metric identifies the minimum number of paths required for testing. We propose to use the E-CC metric and derive test paths for OO systems similar to McCabe’s basis set which would be essential for test vector generation

References
[1] Swapan Bhattacharya and Ananya Kanjilal. Code Based Analysis For ObjectOriented Systems. J. Comput. Sci. Technol., 21(6):965–972, 2006.
[2] E. J. Weyuker. Evaluating software complexity measures. IEEE Transactions on Software Engineering, 14(9):1357–1365, April.
[3] Swapan Bhattacharya and Ananya Kanjilal. Static Analysis of Object Oriented Systems Using Extended Control Flow Graph. IEEE,proceedings of TENCON 2004. 2004 IEEE Region 10 Conference, pages 310–313, 2004.
[4] Thomas J. McCabe. A complexity measure. IEEE Transactions on Software Engineering, 2(4):308–320, December 1976
[5] https://en.wikipedia.org/wiki/Cyclomatic_complexity.
[4] Williams B. S. A survey on Code Coverage as a Stopping Criterion for Unit Testing. Dept. of Computer Science, North Carolina State University Technical Report TR- 2008-22, 2008.
