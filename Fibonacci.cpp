/*
This is the source code of a program used to calculate any Fibonacci numbers up to the 92nd number (93rd if you consider zero the first number in the Fibonacci sequence).
There are three algorithms for the same task: recursion by brute force, recursion with memorisation, and tabulation.
*/

#include<iostream>

long long Fib(int n);
long long FibMem(long long *array, int n);

int main()
{	
	while(1)
	{
		/*First, indicate the Fibonacci number of interest.
		Note that the index starts from zero.*/
		int n;
		while(1)
		{
			std::cout<<"Please indicate the Fibonacci number you want to calculate: the subscript in Fn."<<"\n";
			std::cin>>n;
			while(std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout<<"Invalid input."<<"\n"<<"Please indicate the Fibonacci number you want to calculate: the subscript in Fn."<<"\n";
				std::cin>>n;
			}
			if(n>=0)
			{
				break;
			}
			else
			{
				std::cout<<"Invalid input."<<"\n";
			}
		}
		
		//Then, select an algorithm to calculate the Fibonacci number of interest.
		int method;
		while(1)
		{
			std::cout<<"Please select an option: recursion (type and enter 0), memorisation (type and enter 1), and tabulation (type and enter 2)."<<"\n";
			std::cin>>method;
			while(std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout<<"Invalid input."<<"\n"<<"Please select an option: recursion (type and enter 0), memorisation (type and enter 1), and tabulation (type and enter 2)."<<"\n";
				std::cin>>method;
			}
			if(method==0 || method==1 || method==2)
			{
				break;
			}
			else
			{
				std::cout<<"Invalid input."<<"\n";
			}
		}
		
		if(method == 0)
		{
			//This calculates the result by recursion.
			std::cout<<"The answer is "<<Fib(n)<<"."<<"\n";
		}
		else if(method == 1)
		{
			//Create an array to store the solutions to subproblems.
			long long arrayMem[n+1];
			//The first two elements do not require calculation at all because we know they are 0 and 1 respectively.
			arrayMem[0]=0;
			arrayMem[1]=1;
			//The other elements of the array are initially unknown. This is indicated by -1.
			for(int i=2; i<n+1; i++)
			{
				arrayMem[i]=-1;
			}
			//This calculates the result by recursion with memorisation.
			std::cout<<"The answer is "<<FibMem(arrayMem, n)<<"."<<"\n";
		}
		else if(method == 2)
		{
			//Create an array to store the solutions to subproblems.
			long long arrayMem[n+1];
			//The first two elements do not require calculation at all because we know they are 0 and 1 respectively.
			arrayMem[0]=0;
			arrayMem[1]=1;
			/*Starting from the base cases, iteratively construct solutions to successively bigger problems.
			Note that each step requires the preceding two solutions only and that the recursive function is not called.
			*/
			for(int i=2; i<n+1; i++)
			{
				arrayMem[i] = arrayMem[i-2] + arrayMem[i-1];
			}
			std::cout<<"The answer is "<<arrayMem[n]<<"."<<"\n";
		}
		char exit;
		std::cout<<"Do you want to continue? (type and enter Y or N)"<<"\n";
		std::cin>>exit;
		while(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout<<"Invalid input."<<"\n"<<"Do you want to continue? (type and enter Y or N)"<<"\n";
			std::cin>>exit;
		}
		if(exit == 'Y')
		{
			continue;
		}
		else if(exit == 'N')
		{
			break;
		}
		else
		{
			std::cout<<"Invalid input."<<"\n";
			break;			
		}
	}
	std::cout<<"See you next time.";
}

//The simple recursive function used to generate the Fibonacci sequence.
long long Fib(int n)
{
	long long Fibn;
	if(n==0)
	{
		Fibn = 0;
		return Fibn;
	}
	else if(n==1)
	{
		Fibn = 1;
		return Fibn;
	}
	else
	{
		Fibn = Fib(n-2) + Fib(n-1);
		return Fibn;
	}
}

//Recursive function used to generate the Fibonacci sequence with memorisation.
long long FibMem(long long *arrayMem, int n)
{
	/*Before using the recursive function, check whether the subproblem has been solved before.
	If so, just return the stored solution.*/
	if(arrayMem[n] != -1)
	{
		return arrayMem[n];
	}
	else
	{
		//If the subproblem is new, solve it by applying the recursive function and store the solution for future use.	
		long long Fibn;
		Fibn = FibMem(arrayMem, n-2) + FibMem(arrayMem, n-1);
		arrayMem[n] = Fibn;
		return Fibn;
	}
}
