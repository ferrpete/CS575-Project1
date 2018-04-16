// Program to calculate the volume between two Bezier surfaces.

#include <stdio.h>
#include <fstream>
#include <omp.h>
#include "Project1.h"

#define XMIN	 0.
#define XMAX	 3.
#define YMIN	 0.
#define YMAX	 3.

#define NUMTRIES 5

int main( int argc, char *argv[ ] )
{
	
#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
#endif

	printf( "Number of nodes: %d\n", NUMNODES );
	
	double fullTileArea = ( (( XMAX - XMIN)/(double)(NUMNODES-1) ) *
						   (( YMAX - YMIN)/(double)(NUMNODES-1) ) );
	
	omp_set_num_threads( NUMT );
	
	fprintf( stderr, "Using %d threads\n", NUMT );
	
	double maxMegaHeights = 0.;
	double sumMegaHeights = 0.;
	double sum = 0;
	
	for( int t = 0; t < NUMTRIES; t++ )
	{
	
		sum = 0;
		double myPartialSum = 0;
		
		double time0 = omp_get_wtime( );
		
		#pragma omp parallel for reduction(+:sum),private(myPartialSum)
		for( int i = 0; i < NUMNODES*NUMNODES; i++ )
		{
			
			int iu = i % NUMNODES;
			int iv = i / NUMNODES;
			
			double height = Height( iu, iv );
			double weight = Weight( iu, iv );
			
			myPartialSum = weight * fullTileArea * height;
			sum = sum + myPartialSum;
			
		}
		
		double time1 = omp_get_wtime( );
		double megaHeights = (double)NUMNODES*NUMNODES/(time1-time0)/1000000.;
		sumMegaHeights += megaHeights;
		if( megaHeights > maxMegaHeights )
			maxMegaHeights = megaHeights;
	
	}
	
	double avgMegaHeights = sumMegaHeights/(double)NUMTRIES;
	printf( " Peak Performance = %8.2lf MegaHeights/Sec\n", maxMegaHeights );
	printf( "Average Performance = %8.2lf MegaHeights/Sec\n", avgMegaHeights );
	printf( "The area of the Bezier surface is %8.10lf\n.", sum );
	
	std::ofstream dataFile("TrapezoidalRuleData.txt", std::ofstream::out | std::ofstream::app);
	dataFile << NUMT << ", " << NUMNODES << ", " << maxMegaHeights << ", " << avgMegaHeights << "\n";
	
	return 0;
	
}
