#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <time.h>
#include <limits>

constexpr int size1 = 6;
constexpr int size2 = 2;
void fitness_function(int chromosomes[][size1], float fitness[][size2], int n_chromosomes, int n_genes);
void selection(int chromosomes_offspring[][size1], int chromosomes[][size1], float fitness[][size2], int n_chromosomes, int n_genes);
void crossover(int chromosomes_offspring[][size1], int n_chromosomes, int n_genes);
void mutation(int chromosomes_offspring[][size1], int n_chromosomes, int n_genes, float P_mutation);

int main()
{
	/*Provide the parameters.*/
	srand(time(0)); //Seed the random number generator.
	const int n_iterations = 1000000; //How many generations do you want per run?
	const int n_chromosomes = 200; //How many chromosomes do you want per generation?
	const int n_genes = 6; //How many genes (bits) do  you want per chromosome? Remember to update constexpr int size1 to match this number too.
	float P_mutation = 0.1; //What is the probability of mutation per gene (bit)?
	
	/*Step 1: Create the initial generation of chromosomes randomly.*/
	int chromosomes[n_chromosomes][n_genes];
	float fitness[n_chromosomes][2];
	for(int i=0;i<n_chromosomes;i++)
	{
		for(int j=0;j<n_genes;j++)
		{
			float dummy = (float)std::rand()/(float)RAND_MAX;
			if(dummy < 0.5)
			{
				chromosomes[i][j] = 1;
			}
			else
			{
				chromosomes[i][j] = 0;
			}
		}
	}
	
	/*Simulate evolution here.*/
	for (int i=0;i<n_iterations;i++)
	{
		std::cout<<"Iteration "<<i+1<<"."<<"\n";
		
		/*Step 2: Assess the fitness of each chromosome, find the best
		chromosome in this generation (maximum fitness value), and convert
		each fitness value to a selection probability.*/
		fitness_function(chromosomes, fitness, n_chromosomes, n_genes);
		
		/*Step 3: Select the chromosomes that will reproduce.*/		
		int chromosomes_offspring[n_chromosomes][n_genes];
		selection(chromosomes_offspring, chromosomes, fitness, n_chromosomes, n_genes);
		
		/*Step 4: Let the selected chromosomes cross over.*/
		crossover(chromosomes_offspring, n_chromosomes, n_genes);
		
		/*Step 5: After crossover, mutate the genes in the offspring randomly.*/
		mutation(chromosomes_offspring, n_chromosomes, n_genes, P_mutation);
		
		/*Step 1: Finalise the new generation of chromosomes.*/
		memcpy(chromosomes, chromosomes_offspring, sizeof(chromosomes));
	}
	
	/*Print the final results.*/
	std::cout<<"The run is over. Here are the final results."<<"\n";
	fitness_function(chromosomes, fitness, n_chromosomes, n_genes);
	
	return 0;
}

void fitness_function(int chromosomes[][size1], float fitness[][size2], int n_chromosomes, int n_genes)
{
	/*Decode each chromosome and use the result (dummy) to calculate its fitness value.*/
	for(int i=0;i<n_chromosomes;i++)
	{	
		int dummy=0;
		
		for(int j=0;j<n_genes;j++)
		{
			dummy = dummy + chromosomes[i][j]*pow(2, n_genes-1-j);
		}
		
		fitness[i][0] = -pow(dummy, 2)/10+3*dummy;
	}
	
	/*Find out the total fitness, the maximum fitness, and the fittest chromosome.*/
	float total_fitness = 0;
	float max_fitness = std::numeric_limits<float>::lowest();
	int best;
	for(int i=0;i<n_chromosomes;i++)
	{
		total_fitness = total_fitness + fitness[i][0];
		if(fitness[i][0]>max_fitness)
		{
			max_fitness = fitness[i][0];
			best = i;
		}
	}
	
	/*Summarise the results.*/
	std::cout<<"Maximum fitness in this generation: "<<max_fitness<<"."<<"\n";
	std::cout<<"Best chromosome in this generation: ";
	int dummy=0;
	for(int i=0;i<n_genes;i++)
	{
		dummy = dummy + chromosomes[best][i]*pow(2, n_genes-1-i);
		std::cout<<chromosomes[best][i];
	}
	std::cout<<'.'<<"\n";
	std::cout<<"After decoding the best chromosome in this generation, the answer is "<<dummy<<"."<<"\n";
	
	/*Turn each fitness value into a selection probability.*/
	for(int i=0;i<n_chromosomes;i++)
	{
		fitness[i][1] = fitness[i][0]/total_fitness;
	}	
	
	/*Turn the selection probabilities into cumulative probabilities.*/
	for(int i=1;i<n_chromosomes;i++)
	{
		fitness[i][1] = fitness[i][1]+fitness[i-1][1];
	}
}

void selection(int chromosomes_offspring[][size1], int chromosomes[][size1], float fitness[][size2], int n_chromosomes, int n_genes)
{
	/*There are n_chromosomes spots available.*/
	for(int i=0;i<n_chromosomes;i++)
	{
		float dummy = (float)std::rand()/(float)RAND_MAX;
		
		/*Select a chromosome for each spot.*/
		int index;
		for(int j=0;j<n_chromosomes;j++)
		{
			if (dummy < fitness[j][1])
			{
				index = j;
				break;
			}
		}
		
		for(int j=0;j<n_genes;j++)
		{
			chromosomes_offspring[i][j] = chromosomes[index][j];
		}			
	}
}

void crossover(int chromosomes_offspring[][size1], int n_chromosomes, int n_genes)
{
	/*Pair up the selected chromosomes.*/
	for(int i=0;i<n_chromosomes/2;i++)
	{
		int dummy1 = 1+2*i;
		int dummy2 = std::rand()%n_genes; //Find the crossover point.
		for(int j=dummy2;j<n_genes;j++)
		{
			int dummy3 = chromosomes_offspring[dummy1-1][j];
			int dummy4 = chromosomes_offspring[dummy1][j];
			chromosomes_offspring[dummy1-1][j] = dummy4;
			chromosomes_offspring[dummy1][j] = dummy3;						
		}
	}
}

void mutation(int chromosomes_offspring[][size1], int n_chromosomes, int n_genes, float P_mutation)
{
	/*Try to mutate each gene in every chromosome.*/
	for(int i=0;i<n_chromosomes;i++)
	{
		
		for(int j=0;j<n_genes;j++)
		{
			float dummy = (float)std::rand()/(float)RAND_MAX;
			if(dummy < P_mutation)	
			{
				/*In order to mutate a gene, just turn 1 to 0 or 0 to 1.*/
				if(chromosomes_offspring[i][j]==1)
				{
					chromosomes_offspring[i][j] = 0;
				}
				else
				{
					chromosomes_offspring[i][j] = 1;				
				}
			}				
		}			
	}	
}
