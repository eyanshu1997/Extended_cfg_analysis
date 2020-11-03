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

