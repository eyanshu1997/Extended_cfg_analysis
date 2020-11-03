package test;
public class test
{
	static void m1()
	{
		int a=1;
		int b=2;
		int c;
		if(a<b)
			c=a+b;
		else
			c=0;
	}
	static void m2()
	{
		m2();
	}
	static void m3()
	{
		m2();
		m4();
	}
	static void m4()
	{
		int a=0;
	}
	static void m5()
	{
		int a=1;
		int b=3;
		int c;
		if(a>b)
			c=a+b;
		else
		{
			if(a<b)
				c=b-a;
			else
				c=0;
		}
	}
	static void m6()
	{
		m6();
		m7();
	}
	static void m7()
	{
		int z=0;
		
	}
	static void main(string args[])
	{
		m1();
		m6();
		m5();
		m2();
		m3();
	}
}
