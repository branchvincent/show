/****************************************************************************
*																			*
*	File:		runSim.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file executes the simulation for the specified number	* 
*				of minutes and the specified number of runs. Then, it 		*
*				outputs the results to the specified file.					*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;
using namespace cnsts;

// Function prototypes

void setTrafficLevels(vector<float>& traffic);
void outputStats(Simulation& sim, string outputFile);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

//  Notes:
//  - Not using RAND_RUN
//  - OUTPUT_ON used once
//  - sim.run(NUM_REPS):  NUM_REPS has already set stat size
//  - call runs replications

int main() 
{
//	Set folder path

//  string outputFile = "/Users/Branch/Desktop/DES/DES/Output/runData.csv";
		
//	Initialize variables

//  Run sim and output data
    
    Simulation sim; //(END_TIME, traffic);
	sim.run();
    outputStats(sim, OUTPUT_FILE);

	return 0;
}

/****************************************************************************
*																			*
*	Function:	setTrafficLevels											*
*																			*
*	Purpose:	To set the traffic levels for the simulation				*
*																			*
****************************************************************************/

//void setTrafficLevels(vector<float>& traffic)
//{
////	Set random traffic, if applicable
//
//    srand((unsigned int) time(0));
//	float levels[] = {0.5, 1, 2};
//	
//	if (RAND_RUN_ON)
//		for (int i = 0; i < traffic.size(); i++)
//			traffic[i] = levels[rand() % 3];
//	
////	Otherwise, set specific traffic
//
//	else
//		for (int i = 0; i < traffic.size(); i++)
//			traffic[i] = levels[i % 3];
//	
//	return;
//}

/****************************************************************************
*																			*
*	Function:	outputStats                                                 *
*																			*
*	Purpose:	To output the statistical data from the simulation			*
*																			*
****************************************************************************/

void outputStats(Simulation& sim, string outputFile)
{
//  Check for output
    
    if (OUTPUT_ON)
    {
    //  Open file
        
        ofstream fout(outputFile);
        if (!fout)
        {
            cerr << "Error: Cannot open file. Exiting..." << endl;
            exit(1);
        }
        
    //  Output stats
        
        fout << sim << endl;
    }
            
    return;
}