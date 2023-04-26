// measures the average diversity among all populations
// implemented as described in:
// Mattiussi et al. (2004) - Measures of Diversity for Populations and Distances Between Individuals with Highly Reorganizable Genomes
// Wineberg, M. and Oppacher, F. (2003a). Distance between populations
#include "./libs/types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <math.h>
#define NO_RECORDING
#include "./libs/funcoes_cec_2015/cec15_test_func.h"
#include "./libs/statistics.h"
#include "./libs/types.h"
#include "./libs/utils.h"
#include "./libs/crossover.h"
#include "./libs/log.h"
#include <dirent.h>
#include <string.h>

double euclidian(individuo firstIndividuo, individuo secondIndividuo, int dimension){
	double distance = 0;
	for(int i = 0; i < dimension; i++)
	{
		distance +=  pow(firstIndividuo.chromosome[i] - secondIndividuo.chromosome[i],2);
	}
	distance = sqrt(distance);
	return distance;
}

void densityPopulation(populacao *populations,int island_size) {
	double average = 0;
	double sd = 0;
	double *sum = (double *) calloc(island_size, sizeof(double));
	double sumIndividual;
	int nIndividuals = populations[0].size;
	double multiplier = 2/(nIndividuals - 1);
	// for all populations
	for (int i = 0; i < island_size; i++) {
		// for all individuals from population i
		for (int j = 0; j < nIndividuals - 1; j++) {
			// against all individuals from the same population
			for (int k = j+1; k < nIndividuals; k++) {
				// sums with the norm-2 of individual j and k
				sum[i] += euclidian(populations[i].individuos[j], populations[i].individuos[k], 10);
			}
		}
	}

	for (int i = 0; i < island_size; i++) {
		average += sum[i];
	}

	average /= island_size;

	for (int i = 0; i < island_size; i++) {
		sd += (sum[i]-average)*(sum[i]-average);
	}
	sd /= island_size;
	sd = sqrt(sd);

	//cout << average << ";" << sd << ";";
	printf("\nDensityPopulation\n");
	printf("%lf;%lf;\n", average, sd);
}

// implements the same diversity metric of the density population
// extends it to the entire "world"
void densityWorld(populacao *populations,int island_size) {
	double total;
	double sum[island_size][island_size];
	int nIndividuals = populations[0].size;

	// for all populations
	for (int i = 0; i < island_size; i++) {
		// in comparison with all other populations
		for (int j = i; j < island_size; j++) {
			// for all individuals from population i
			for (int k = 0; k < nIndividuals-1; k++) {
				// against all individuals from the same population
				for (int l = j+1; l < nIndividuals; l++) {
					// sums with the norm-2 of individual j and k
					sum[i][j] += euclidian(populations[i].individuos[k], populations[j].individuos[l], 10);
				}
			}
		}
	}

	for (int i = 0; i < island_size; i++) {
		for (int j = i; j < island_size; j++) {
			total += sum[i][j];
		}
	}
    printf("\nDensityWord\n");
    printf("%lf;\n",total);
	/*
	//cout << total << ";" << endl;
	
	// TODO: incompleto. Pensar numa maneira de comparar este número com o outro
	// pensamento: não é necessário comparar este número com o outro, só comparar
	// de uma execução com outra. Então, é somar tudo e retornar
	// verificar se esta ideia acima está correta
	*/
}
