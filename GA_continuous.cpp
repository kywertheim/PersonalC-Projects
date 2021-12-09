#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits>

void fitness_function(float chromosomes[][2], float* fitness, int n_chromosomes);
void selection(float chromosomes_offspring[][2], float chromosomes[][2], float* fitness, int n_chromosomes);
void crossover(float chromosomes_offspring[][2], int n_chromosomes);
void mutation(float chromosomes_offspring[][2], int n_chromosomes, float P_mutation);

int main()
{
	/*Provide the parameters.*/
	srand(time(0)); //Seed the random number generator.
	const int n_iterations = 200; //How many generations do you want per run?
	const int n_chromosomes = 12; //How many chromosomes do you want per generation?
	float P_mutation = 0.2; //What is the probability of mutation per gene (bit)?
	
	/*Step 1: Create the initial generation of chromosomes randomly.*/
	float chromosomes[n_chromosomes][2];
	float fitness[n_chromosomes];
	for(int i=0;i<n_chromosomes;i++)
	{
		for(int j=0;j<2;j++)
		{
			float dummy = 10*(float)std::rand()/(float)RAND_MAX;
			chromosomes[i][j] = dummy;
		}
	}
	
	/*Simulate evolution here.*/
	for (int i=0;i<n_iterations;i++)
	{
		std::cout<<"Iteration "<<i+1<<"."<<"\n";
		
		/*Step 2: Assess the fitness of each chromosome and find the best
		chromosome in this generation (maximum fitness value).*/
		fitness_function(chromosomes, fitness, n_chromosomes);
		
		/*Step 3: Select the chromosomes that will reproduce.*/		
		float chromosomes_offspring[n_chromosomes][2];
		selection(chromosomes_offspring, chromosomes, fitness, n_chromosomes);
		
		/*Step 4: Let the selected chromosomes cross over.*/
		crossover(chromosomes_offspring, n_chromosomes);
		
		/*Step 5: After crossover, mutate the genes in the offspring randomly.*/
		mutation(chromosomes_offspring, n_chromosomes, P_mutation);
		
		/*Step 1: Finalise the new generation of chromosomes.*/
		memcpy(chromosomes, chromosomes_offspring, sizeof(chromosomes));
	}
	
	/*Print the final results.*/
	std::cout<<"The run is over. Here are the final results."<<"\n";
	fitness_function(chromosomes, fitness, n_chromosomes);
	
	return 0;
}

void fitness_function(float chromosomes[][2], float* fitness, int n_chromosomes)
{
	/*Calculate each chromosome's fitness value.*/
	for(int i=0;i<n_chromosomes;i++)
	{	
		fitness[i] = -1*(chromosomes[i][0]*sin(4*chromosomes[i][0])+1.1*chromosomes[i][1]*sin(2*chromosomes[i][1]));
	}
	
	/*Find out the maximum fitness and the fittest chromosome.*/
	float max_fitness = std::numeric_limits<float>::lowest();
	int best;
	for(int i=0;i<n_chromosomes;i++)
	{
		if(fitness[i]>max_fitness)
		{
			max_fitness = fitness[i];
			best = i;
		}
	}
	
	/*Summarise the results.*/
	std::cout<<"Maximum fitness in this generation: "<<max_fitness<<"."<<"\n";
	std::cout<<"Best chromosome in this generation: "<<chromosomes[best][0]<<" and "<<chromosomes[best][1]<<'.'<<"\n";
	
}

void selection(float chromosomes_offspring[][2], float chromosomes[][2], float* fitness, int n_chromosomes)
{
	/*Sort the chromosomes by fitness.*/
	float max_fitness[n_chromosomes];
	float best[n_chromosomes];	
	for(int i=0;i<n_chromosomes;i++)
	{
		max_fitness[i]=std::numeric_limits<float>::lowest();
		/*The first spot is for the chromosome with the maximum fitness value.*/
		if(i==0)
		{
			for(int j=0;j<n_chromosomes;j++)
			{
				if(fitness[j]>max_fitness[i])
				{
					max_fitness[i] = fitness[j];
					best[i] = j;
				}
			}			
		}
		/*Each remaining spot is for the chromosome with the fitness value less than
		that of the chromosome above it but more than those of the other chromosomes
		to be selected. Be wary of cases wherein two or more chromosomes share the
		same fitness value.*/
		else
		{
			for(int j=0;j<n_chromosomes;j++)
			{
				if(fitness[j]>max_fitness[i] && fitness[j]<max_fitness[i-1])
				{
					max_fitness[i] = fitness[j];
					best[i] = j;
				}
				else if(fitness[j]>max_fitness[i] && fitness[j]==max_fitness[i-1])
				{
					int dummy = 1;
					for(int k=0;k<i;k++)
					{
						if(j==best[k])
						{
							dummy = 0;
						}
					}
					if(dummy==1)
					{
						max_fitness[i] = fitness[j];
                                        	best[i] = j;
					}
				}
			}		
		}
	}
	
	/*Based on the chromosome's rank, calculate the probability of selection.
	If the chromosome is in the top half, calculate the probability.
	If it is in the bottom half, the probability is zero.*/
	float P_selection[n_chromosomes];
	int denominator = 0;
	for(int i=0;i<n_chromosomes/2;i++)
	{
		denominator = denominator + i + 1;
	}
	for(int i=0;i<n_chromosomes;i++)
	{
		if(i<n_chromosomes/2)
		{
			int rank = i+1;
			int chrindex = best[i];
			P_selection[chrindex] = (float)(n_chromosomes/2-rank+1)/(float)denominator;
		}
		else
		{
			int chrindex = best[i];
			P_selection[chrindex] = 0;
		}
	}
	
	/*Turn the selection probabilities into cumulative probabilities.*/	
	float P_cumulative[n_chromosomes];
	P_cumulative[0] = P_selection[0];
	for(int i=1;i<n_chromosomes;i++)
	{
		P_cumulative[i] = P_selection[i]+P_cumulative[i-1];
	}	

	/*There are n_chromosomes/2 spots available.
	Fill them up using the selection and culmulative probabilities.*/
	for(int i=0;i<n_chromosomes/2;i++)
	{
		float dummy = (float)std::rand()/(float)RAND_MAX;
		
		/*Select a chromosome (its index) for each spot.*/
		int index;
		for(int j=0;j<n_chromosomes;j++)
		{
			if (dummy < P_cumulative[j] && P_selection[j] > 0)
			{
				index = j;
				break;
			}
		}
		
		chromosomes_offspring[i][0] = chromosomes[index][0];			
		chromosomes_offspring[i][1] = chromosomes[index][1];	
	}

}

void crossover(float chromosomes_offspring[][2], int n_chromosomes)
{
	/*Pair up the selected chromosomes.*/
	for(int i=0;i<n_chromosomes/4;i++)
	{
		int dummy1 = 1+2*i;
		float dummy2 = (float)std::rand()/(float)RAND_MAX; //Find the crossover point.
		if(dummy2<0.5)
		{
			float beta = (float)std::rand()/(float)RAND_MAX;		
			chromosomes_offspring[dummy1-1+n_chromosomes/2][0] = (1-beta)*chromosomes_offspring[dummy1-1][0] + beta*chromosomes_offspring[dummy1][0];
			chromosomes_offspring[dummy1-1+n_chromosomes/2][1] = chromosomes_offspring[dummy1-1][1];
			chromosomes_offspring[dummy1+n_chromosomes/2][0] = beta*chromosomes_offspring[dummy1-1][0] + (1-beta)*chromosomes_offspring[dummy1][0];
			chromosomes_offspring[dummy1+n_chromosomes/2][1] = chromosomes_offspring[dummy1][1];
		}
		else
		{
			float beta = (float)std::rand()/(float)RAND_MAX;				
			chromosomes_offspring[dummy1-1+n_chromosomes/2][1] = (1-beta)*chromosomes_offspring[dummy1-1][1] + beta*chromosomes_offspring[dummy1][1];
			chromosomes_offspring[dummy1-1+n_chromosomes/2][0] = chromosomes_offspring[dummy1-1][0];
			chromosomes_offspring[dummy1+n_chromosomes/2][1] = beta*chromosomes_offspring[dummy1-1][1] + (1-beta)*chromosomes_offspring[dummy1][1];
			chromosomes_offspring[dummy1+n_chromosomes/2][0] = chromosomes_offspring[dummy1][0];
		}
	}
}

void mutation(float chromosomes_offspring[][2], int n_chromosomes, float P_mutation)
{
	/*Try to mutate each gene in every chromosome.*/
	for(int i=0;i<n_chromosomes;i++)
	{
		
		for(int j=0;j<2;j++)
		{
			float dummy = (float)std::rand()/(float)RAND_MAX;
			if(dummy < P_mutation)	
			{
				/*In order to mutate a gene, generate a new number between 0 and 10.*/
				float dummy = 10*(float)std::rand()/(float)RAND_MAX;
				chromosomes_offspring[i][j] = dummy;
			}				
		}			
	}	
}
