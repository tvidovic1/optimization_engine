#include <ilcp/cp.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "Task.h"
#include "TaskInstance.h"
#include "TaskSet.h"
#include "Helper.h"
#include "Model.h"
#include "TaskChain.h"
#include "Data.h"
#include "TestGenerator.h"

int counter = 1;

// TEST 1: Complexity of the optimization engine with respect to the number of task instances

void testConstraintsVsTaskInstances()
{
    std::vector<int> numberOfTaskInstances = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000 };
    std::vector<int> numberOfChains = { 1, 2, 3, 4, 5 };
    std::vector<double> utilizationsForCores = { 0.5, 0.5 };
    int numberOfCommunicatingPairs = 32;
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 2;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    int timeLimit = 1;
    std::vector<TaskChain> chains;

    std::vector<std::vector<std::vector<int>>> numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains;
    std::vector<std::vector<double>> avgNumberOfConstraintsPerNumberOfTaskInstancesPerChain;

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<std::vector<int>> numberOfConstraintsPerNumberOfTaskInstance;
        numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains.push_back(numberOfConstraintsPerNumberOfTaskInstance);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        for (int j = 0; j < numberOfTaskInstances.size(); j++)
        {
            std::vector<int> numberOfConstraints;
            numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains.at(i).push_back(numberOfConstraints);
        }  
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> avgNumberOfConstraintsPerNumberOfTaskInstance;

        avgNumberOfConstraintsPerNumberOfTaskInstancesPerChain.push_back(avgNumberOfConstraintsPerNumberOfTaskInstance);
    }

    int numberOfTest;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        numberOfTest = 1;

        for (int numberOfTaskInstance = 0; numberOfTaskInstance < numberOfTaskInstances.size(); numberOfTaskInstance)
        {
            for (int i = 0; i < numberOfTestCases; i++)
            {
                chains.clear();

                std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains[numberOfChain], chains, numberOfTaskInstances[numberOfTaskInstance], utilizationsForCores[0], utilizationsForCores[1], percentageOfConectedness, numberOfCommunicatingPairs);

                std::string logFile1 = "LogFileConstVsInstancesChain";
                std::string logFile2 = std::to_string(numberOfChain);
                std::string logFile3 = std::to_string(numberOfTest);
                std::string logFile4 = ".txt";

                numberOfTest++;

                //std::cout << logFile1 + logFile2 + logFile3 + logFile4;

                int totalNumberOfConstraints = 0;

                createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3 + logFile4, status, totalNumberOfConstraints, timeLimit, maximumInterCoreDelay);

                numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains.at(numberOfChain).at(numberOfTaskInstance).push_back(totalNumberOfConstraints);

            }
        }
    }


    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {

        for (int numberOfInstance = 0; numberOfInstance < numberOfTaskInstances.size(); numberOfInstance++)
        {
            double sum = 0.0;

            for (int test = 0; test < numberOfTestCases; test++)
            {
                sum += numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains.at(numberOfChain).at(numberOfInstance).at(test);
            }

            avgNumberOfConstraintsPerNumberOfTaskInstancesPerChain.at(numberOfChain).push_back(sum / numberOfTestCases);
        }
    }

    // Print average number of contraints per number of task instances per number of chains

    std::cout << "AVERAGE NUMBER OF CONSTRAINTS PER NUMBER: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "CHAIN: " << numberOfChain << std::endl;

        for (int numberOfInstance = 0; numberOfInstance < numberOfTaskInstances.size(); numberOfInstance)
        {
            std::cout << "Number of task instances " << numberOfTaskInstances.at(numberOfInstance) << ": ";
            std::cout << avgNumberOfConstraintsPerNumberOfTaskInstancesPerChain.at(numberOfChain).at(numberOfInstance) << std::endl;
        }
             
    }

    counter++;

    return;

}

// TEST 2: Complexity of the optimization engine with respect to the number of communicating producer-consumer pairs

void testConstraintsVsCommunicatingPairs()
{
    int numberOfTaskInstances = 500;
    std::vector<int> numberOfChains = { 1, 2, 3, 4, 5 };
    std::vector<double> utilizationsForCores = { 0.5, 0.5 };
    std::vector<int> numberOfCommunicatingPairs = {0, 2, 4, 8, 16, 32, 64, 128};
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 100;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    int timeLimit = 600;
    std::vector<TaskChain> chains;

    std::vector<std::vector<std::vector<int>>> numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains;
    std::vector<std::vector<double>> avgNumberOfConstraintsPerNumberOfCommunicatingPairsPerChain;

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<std::vector<int>> numberOfConstraintsPerNumberOfTaskInstance;
        numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains.push_back(numberOfConstraintsPerNumberOfTaskInstance);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        for (int j = 0; j < numberOfCommunicatingPairs.size(); j++)
        {
            std::vector<int> numberOfConstraints;
            numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains.at(i).push_back(numberOfConstraints);
        }
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> avgNumberOfConstraintsPerNumberOfTaskInstance;

        avgNumberOfConstraintsPerNumberOfCommunicatingPairsPerChain.push_back(avgNumberOfConstraintsPerNumberOfTaskInstance);
    }

    int numberOfTest;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        numberOfTest = 1;

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair)
        {
            for (int i = 0; i < numberOfTestCases; i++)
            {
                chains.clear();

                std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains[numberOfChain], chains, numberOfTaskInstances, utilizationsForCores[0], utilizationsForCores[1], percentageOfConectedness, numberOfCommunicatingPairs[numberOfCommunicatingPair]);

                std::string logFile1 = "LogFileConstVsPairsChain";
                std::string logFile2 = std::to_string(numberOfChain);
                std::string logFile3 = std::to_string(numberOfTest);
                std::string logFile4 = ".txt";

                numberOfTest++;

                //std::cout << logFile1 + logFile2 + logFile3 + logFile4;

                int totalNumberOfConstraints = 0;

                createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3 + logFile4, status, totalNumberOfConstraints, timeLimit, maximumInterCoreDelay);

                numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains.at(numberOfChain).at(numberOfCommunicatingPair).push_back(totalNumberOfConstraints);

            }
        }
    }


    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair++)
        {
            double sum = 0.0;

            for (int test = 0; test < numberOfTestCases; test++)
            {
                sum += numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains.at(numberOfChain).at(numberOfCommunicatingPair).at(test);
            }

            avgNumberOfConstraintsPerNumberOfCommunicatingPairsPerChain.at(numberOfChain).push_back(sum / numberOfTestCases);
        }
    }

    // Print average number of contraints per number of task instances per number of chains

    std::cout << "AVERAGE NUMBER OF CONSTRAINTS PER NUMBER: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "CHAIN: " << numberOfChain << std::endl;

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair)
        {
            std::cout << "Number of communicating producer-consumer pairs " << numberOfCommunicatingPairs.at(numberOfCommunicatingPair) << ": ";
            std::cout << avgNumberOfConstraintsPerNumberOfCommunicatingPairsPerChain.at(numberOfChain).at(numberOfCommunicatingPair) << std::endl;
        }

    }

    return;

}

// TEST 3: Solving time with respect to the variable number of task instances

void testSolvingTimeVsTaskInstances()
{
    std::vector<int> numberOfTaskInstances = { 100, 150, 200, 250, 300 , 350, 400, 450 };
    std::vector<int> numberOfChains = { 2, 3, 4};
    std::vector<double> utilizationsForCores = { 0.5, 0.5 };
    int numberOfCommunicatingPairs = 16;
    double percentageOfConectedness = 0.4;
    int numberOfTestCases = 1;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    int timeLimit = 1;
    std::vector<TaskChain> chains;

    std::vector<std::vector<std::vector<int>>> solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains;
    std::vector<std::vector<double>> avgSolvingTimePerNumberOfCommunicatingPairsPerChain;

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<std::vector<int>> numberOfConstraintsPerNumberOfTaskInstance;
        solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains.push_back(numberOfConstraintsPerNumberOfTaskInstance);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        for (int j = 0; j < numberOfTaskInstances.size(); j++)
        {
            std::vector<int> numberOfConstraints;
            solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains.at(i).push_back(numberOfConstraints);
        }
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> avgNumberOfConstraintsPerNumberOfTaskInstance;

        avgSolvingTimePerNumberOfCommunicatingPairsPerChain.push_back(avgNumberOfConstraintsPerNumberOfTaskInstance);
    }

    int numberOfTest;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        numberOfTest = 1;

        for (int numberOfInstance = 0; numberOfInstance < numberOfTaskInstances.size(); numberOfInstance++)
        {
            for (int i = 0; i < numberOfTestCases; i++)
            {
                chains.clear();

                std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains[numberOfChain], chains, numberOfTaskInstances[numberOfInstance], utilizationsForCores[0], utilizationsForCores[1], percentageOfConectedness, numberOfCommunicatingPairs);

                std::string logFile1 = "LogFileSolvingTimeVsInstancesChain";
                std::string logFile2 = std::to_string(numberOfChain);
                std::string logFile3 = std::to_string(numberOfTest);
                std::string logFile4 = ".txt";

                numberOfTest++;

                //std::cout << logFile1 + logFile2 + logFile3 + logFile4;

                int totalNumberOfConstraints;

                double solvingTime = createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3 + logFile4, status, totalNumberOfConstraints, timeLimit, maximumInterCoreDelay);

                solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains.at(numberOfChain).at(numberOfInstance).push_back(solvingTime);

                std::cout << "TEST" << counter << std::endl;
                counter++;

            }
        }
    }


    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {

        for (int numberOfInstance = 0; numberOfInstance < numberOfTaskInstances.size(); numberOfInstance++)
        {
            double sum = 0.0;

            for (int test = 0; test < numberOfTestCases; test++)
            {
                sum += solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains.at(numberOfChain).at(numberOfInstance).at(test);
            }

            avgSolvingTimePerNumberOfCommunicatingPairsPerChain.at(numberOfChain).push_back(sum / numberOfTestCases);
        }
    }

    // Print average number of contraints per number of task instances per number of chains

    std::cout << "AVERAGE NUMBER OF CONSTRAINTS PER NUMBER: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "CHAIN: " << numberOfChain << std::endl;

        for (int numberOfInstance = 0; numberOfInstance < numberOfTaskInstances.size(); numberOfInstance++)
        {
            std::cout << "Number of task instances " << numberOfTaskInstances.at(numberOfInstance) << ": ";
            std::cout << avgSolvingTimePerNumberOfCommunicatingPairsPerChain.at(numberOfChain).at(numberOfInstance) << std::endl;
        }

    }

    return;

}


// TEST 4: Solving time with respect to the variable number of communicating producer-consumer pairs

void testSolvingTimeVsCommunicatingPairs()
{
    int numberOfTaskInstances = 300;
    std::vector<int> numberOfChains = { 2, 3};
    std::vector<double> utilizationsForCores = { 0.5, 0.5 };
    std::vector<int> numberOfCommunicatingPairs = { 0, 2, 4, 8, 16, 32, 64, 128 };
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 2;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    int timeLimit = 1;
    std::vector<TaskChain> chains;

    std::vector<std::vector<std::vector<int>>> solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains;
    std::vector<std::vector<double>> avgSolvingTimePerNumberOfCommunicatingPairsPerChain;

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<std::vector<int>> numberOfConstraintsPerNumberOfTaskInstance;
        solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains.push_back(numberOfConstraintsPerNumberOfTaskInstance);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        for (int j = 0; j < numberOfCommunicatingPairs.size(); j++)
        {
            std::vector<int> numberOfConstraints;
            solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains.at(i).push_back(numberOfConstraints);
        }
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> avgNumberOfConstraintsPerNumberOfTaskInstance;

        avgSolvingTimePerNumberOfCommunicatingPairsPerChain.push_back(avgNumberOfConstraintsPerNumberOfTaskInstance);
    }

    int numberOfTest;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        numberOfTest = 1;

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair++)
        {
            for (int i = 0; i < numberOfTestCases; i++)
            {
                chains.clear();

                std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains[numberOfChain], chains, numberOfTaskInstances, utilizationsForCores[0], utilizationsForCores[1], percentageOfConectedness, numberOfCommunicatingPairs[numberOfCommunicatingPair]);

                std::string logFile1 = "LogFileSolvingTimeVsPairsChain";
                std::string logFile2 = std::to_string(numberOfChain);
                std::string logFile3 = std::to_string(numberOfTest);
                std::string logFile4 = ".txt";

                numberOfTest++;

                //std::cout << logFile1 + logFile2 + logFile3 + logFile4;

                int totalNumberOfConstraints;

                double solvingTime = createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3 + logFile4, status, totalNumberOfConstraints, timeLimit, maximumInterCoreDelay);

                solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains.at(numberOfChain).at(numberOfCommunicatingPair).push_back(solvingTime);

            }
        }
    }


    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair++)
        {
            double sum = 0.0;

            for (int test = 0; test < numberOfTestCases; test++)
            {
                sum += solvingTimePerNumberOfCommunicatingPairsPerNumberOfChains.at(numberOfChain).at(numberOfCommunicatingPair).at(test);
            }

            avgSolvingTimePerNumberOfCommunicatingPairsPerChain.at(numberOfChain).push_back(sum / numberOfTestCases);
        }
    }

    // Print average number of contraints per number of task instances per number of chains

    std::cout << "AVERAGE NUMBER OF CONSTRAINTS PER NUMBER: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "CHAIN: " << numberOfChain << std::endl;

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair++)
        {
            std::cout << "Number of communicating producer-consumer pairs " << numberOfCommunicatingPairs.at(numberOfCommunicatingPair) << ": ";
            std::cout << avgSolvingTimePerNumberOfCommunicatingPairsPerChain.at(numberOfChain).at(numberOfCommunicatingPair) << std::endl;
        }

    }

    return;

}


// TEST 5: Schedulability ratio with respect to the variable utilizations 

void testSchedulabilityRatioVsUtilizations()
{
    int numberOfTaskInstances = 120;
    std::vector<int> numberOfChains = { 2, 3, 4};
    std::vector<std::vector<double>> utilizationsForCores = { {0.2, 0.2}, {0.2, 0.4}, { 0.2, 0.6 }, { 0.2, 0.8 }, { 0.4, 0.4 }, { 0.4, 0.6 }, { 0.4, 0.8 }, { 0.6, 0.6 }, { 0.6, 0.8 }, { 0.8, 0.8 } };
    int numberOfCommunicatingPairs = 8;
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 100;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    int timeLimit = 600;
    std::vector<TaskChain> chains;


    std::vector<std::vector<int>> numberOfOptimizedPerUtilizationsPerChain;
    std::vector<std::vector<int>> numberOfTightenedPerUtilizationsPerChain;
    std::vector<std::vector<int>> numberOfInfeasiblePerUtilizationsPerChain;
    std::vector<std::vector<double>> schedulabilityRatioPerUtilizationsPerChain;

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfOptimizedPerUtilizations;
        numberOfOptimizedPerUtilizationsPerChain.push_back(numberOfOptimizedPerUtilizations);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfTightenedPerUtilizations;
        numberOfTightenedPerUtilizationsPerChain.push_back(numberOfTightenedPerUtilizations);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfInfeasiblePerUtilizations;
        numberOfInfeasiblePerUtilizationsPerChain.push_back(numberOfInfeasiblePerUtilizations);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> schedulabilityRatioPerChain;
        schedulabilityRatioPerUtilizationsPerChain.push_back(schedulabilityRatioPerChain);
    }


    int numberOfTest;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        numberOfTest = 1;

        for (int utilizationPair = 0; utilizationPair < utilizationsForCores.size(); utilizationPair++)
        {
            int numberOfOptimizedSchedulesPerUtilizationPair = 0;
            int numberOfTightenedSchedulesPerUtilizationPair = 0;
            int numberOfInfeasibleSchedulesPerUtilizationPair = 0;

            for (int i = 0; i < numberOfTestCases; i++)
            {
                chains.clear();

                std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains[numberOfChain], chains, numberOfTaskInstances, utilizationsForCores.at(utilizationPair).at(0), utilizationsForCores.at(utilizationPair).at(1), percentageOfConectedness, numberOfCommunicatingPairs);

                std::string logFile1 = "LogFileSchedulabilityRatioVsUtilizationsChain";
                std::string logFile2 = std::to_string(numberOfChain);
                std::string logFile3 = std::to_string(numberOfTest);
                std::string logFile4 = ".txt";

                std::cout << "TEST: " << numberOfTest << std::endl;
                numberOfTest++;

                //std::cout << logFile1 + logFile2 + logFile3 + logFile4;

                int totalNumberOfConstraints;

                createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3 + logFile4, status, totalNumberOfConstraints, timeLimit, maximumInterCoreDelay);

                if (status == 0)
                {
                    numberOfOptimizedSchedulesPerUtilizationPair++;
                }
                else if (status == 1)
                {
                    numberOfTightenedSchedulesPerUtilizationPair++;
                }
                else
                {
                    numberOfInfeasibleSchedulesPerUtilizationPair++;
                }

            }

            numberOfOptimizedPerUtilizationsPerChain.at(numberOfChain).push_back(numberOfOptimizedSchedulesPerUtilizationPair);
            numberOfTightenedPerUtilizationsPerChain.at(numberOfChain).push_back(numberOfTightenedSchedulesPerUtilizationPair);
            numberOfInfeasiblePerUtilizationsPerChain.at(numberOfChain).push_back(numberOfInfeasibleSchedulesPerUtilizationPair);
        }
    }

   
    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        for (int utilizationPair = 0; utilizationPair < utilizationsForCores.size(); utilizationPair++)
        {
            schedulabilityRatioPerUtilizationsPerChain.at(numberOfChain).push_back((numberOfTestCases - numberOfInfeasiblePerUtilizationsPerChain.at(numberOfChain).at(utilizationPair)) / numberOfTestCases);
        }
    }

    std::cout << "SCHEDULABILITY RATIOS: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "CHAIN: " << numberOfChain << std::endl;

        for (int utilizationPair = 0; utilizationPair < utilizationsForCores.size(); utilizationPair++)
        {
            std::cout << "Utilization Pair " << utilizationsForCores.at(utilizationPair).at(0) << " " << utilizationsForCores.at(utilizationPair).at(0) << ": ";
            schedulabilityRatioPerUtilizationsPerChain.at(numberOfChain).push_back((numberOfTestCases - numberOfInfeasiblePerUtilizationsPerChain.at(numberOfChain).at(utilizationPair)) / numberOfTestCases);
            std::cout << schedulabilityRatioPerUtilizationsPerChain.at(numberOfChain).at(utilizationPair) << std::endl;
        }
    }

    return;

}




/*

void testConstraintsVsCommunicatingPairs()
{
    int numberOfChains = 2;
    std::vector<double> utilizationsForCores = { 0.5, 0.5 };
    std::vector<int> numberOfCommunicatingPairs = { 0, 2 };
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 50;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    std::vector<TaskChain> chains;

    std::vector<std::vector<int>> numberOfConstraints;
    std::vector<double> avgNumberOfConstraintsPerNumberOfChain;


    for (int i = 0; i < numberOfCommunicatingPairs.size(); i++)
    {
        std::vector<int> numberOfConstraintsPerNumberOfChain;

        numberOfConstraints.push_back(numberOfConstraintsPerNumberOfChain);

    }

    int numberOfTest = 1;

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {

        for (int i = 0; i < numberOfTestCases; i++)
        {
            chains.clear();

            std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains, chains, utilizationsForCores[0], utilizationsForCores[1], percentageOfConectedness, numberOfCommunicatingPairs[communicatingPair]);

            std::string logFile1 = "LogFileTasksInstConstVsCommunicatingPairs";
            std::string logFile2 = std::to_string(numberOfTest);
            std::string logFile3 = ".txt";

            numberOfTest++;

            std::cout << logFile1 + logFile2 + logFile3;

            int totalNumberOfConstraints = 0;

            double executionTime = createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3, status, totalNumberOfConstraints, maximumInterCoreDelay);

            numberOfConstraints.at(communicatingPair).push_back(totalNumberOfConstraints);

        }

    }


    // Calculate average number of constraints

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        double sumOfNumberOfConstraintsPerNumberOfChain = 0.0;

        for (int numberOfConstraint = 0; numberOfConstraint < numberOfConstraints.at(communicatingPair).size(); numberOfConstraint++)
        {
            sumOfNumberOfConstraintsPerNumberOfChain += numberOfConstraints.at(communicatingPair).at(numberOfConstraint);
        }

        avgNumberOfConstraintsPerNumberOfChain.push_back(sumOfNumberOfConstraintsPerNumberOfChain / numberOfTestCases);
    }



    // Print all number of constraints

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        std::cout << "Number of communicating pairs: " << numberOfCommunicatingPairs.at(communicatingPair) << std::endl;
        for (int numberOfConstraint = 0; numberOfConstraint < numberOfConstraints.at(communicatingPair).size(); numberOfConstraint++)
        {
            //std::cout << "test " << numberOfTest << " time: " << executionTimes.at(utilizationPair).at(executionTime) << " ,";

            std::cout << numberOfConstraints.at(communicatingPair).at(numberOfConstraint) << " ";

        }

        std::cout << std::endl;
    }


    // Print average number of task instances per number of chains

    std::cout << "AVERAGE NUMBER OF CONSTRAINTS PER NUMBER OF CHAINS: " << std::endl;

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        std::cout << "Number of communicating pairs: " << numberOfCommunicatingPairs.at(communicatingPair) << std::endl;

        std::cout << avgNumberOfConstraintsPerNumberOfChain.at(communicatingPair) << std::endl;
    }


    return;
}

/*
void testSolvingTimeVsNumberOfChains()
{

    std::vector<int> numberOfChains = { 1, 2, 3, 4, 5 };
    std::vector<double> utilizationsForCores = { 0.5, 0.5 };
    int numberOfCommunicatingPairs = 20;
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 100;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    std::vector<TaskChain> chains;

    std::vector<std::vector<double>> executionTimes;
    std::vector<double> avgExecutionTimePerNumberOfChains;
    std::vector<int> numberOfOptimizedSchedules;
    std::vector<int> numberOfTightenedSchedules;
    std::vector<int> numberOfUnsolvedSchedules;
    
    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> executionTimesPerNumberOfChains;

        executionTimes.push_back(executionTimesPerNumberOfChains);
    }

    int numberOfTest = 1;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        int numberOfOptimizedSchedulesPerNumberOfChain = 0;

        int numberOfTightenedSchedulesPerNumberOfChain = 0;

        int numberOfUnsolvedSchedulesPerNumberOfChains = 0;
       
        for (int i = 0; i < numberOfTestCases; i++)
        {
            chains.clear();

            std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains[numberOfChain], chains, utilizationsForCores[0], utilizationsForCores[1], percentageOfConectedness, numberOfCommunicatingPairs);



            std::string logFile1 = "LogFileSolvingTimeVsNumberOfChains";
            std::string logFile2 = std::to_string(numberOfTest);
            std::string logFile3 = ".txt";

            numberOfTest++;

            executionTimes.at(numberOfChain).push_back(createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3, status, maximumInterCoreDelay));

            //std::cout << "TU Sam" << std::endl;
            if (status == 0)
            {
                numberOfOptimizedSchedulesPerNumberOfChain++;
            }
            else if (status == 1)
            {
                numberOfTightenedSchedulesPerNumberOfChain++;
            }
            else
            {
                numberOfUnsolvedSchedulesPerNumberOfChains++;
            }

        }
        numberOfOptimizedSchedules.push_back(numberOfOptimizedSchedulesPerNumberOfChain);
        numberOfTightenedSchedules.push_back(numberOfTightenedSchedulesPerNumberOfChain);
        numberOfUnsolvedSchedules.push_back(numberOfUnsolvedSchedulesPerNumberOfChains);

    }

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        double sumOfExecutionTimesPerNumberOfChain = 0.0;

        for (int executionTime = 0; executionTime < executionTimes.at(numberOfChain).size(); executionTime++)
        {
            sumOfExecutionTimesPerNumberOfChain += executionTimes.at(numberOfChain).at(executionTime);
        }

        avgExecutionTimePerNumberOfChains.push_back(sumOfExecutionTimesPerNumberOfChain / numberOfTestCases);
    }

    std::cout << "ALL EXECUTION TIMES: " << std::endl;

    numberOfTest = 1;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains: " << numberOfChains.at(numberOfChain) << std::endl;

        for (int executionTime = 0; executionTime < executionTimes.at(numberOfChain).size(); executionTime++)
        {
            //std::cout << "test " << numberOfTest << " time: " << executionTimes.at(utilizationPair).at(executionTime) << " ,";

            std::cout << executionTimes.at(numberOfChain).at(executionTime) << " ";

            numberOfTest++;
        }

        std::cout << std::endl;
        std::cout << std::endl;
    }

    std::cout << "AVERAGE EXECUTION TIME PER NUMBER OF CHAINS: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains: " << numberOfChains.at(numberOfChain) << std::endl;

        std::cout << avgExecutionTimePerNumberOfChains.at(numberOfChain) << std::endl;
    }

    std::cout << "NUMBER OF OPTIMIZED SCHEDULES: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains: " << numberOfChains.at(numberOfChain) << std::endl;

        std::cout << numberOfOptimizedSchedules.at(numberOfChain) << std::endl;
    }


    std::cout << "NUMBER OF TIGHTENED SCHEDULES: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains: " << numberOfChains.at(numberOfChain) << std::endl;

        std::cout << numberOfTightenedSchedules.at(numberOfChain) << std::endl;
    }


    std::cout << "NUMBER OF UNSOLVED SCHEDULES: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains: " << numberOfChains.at(numberOfChain) << std::endl;

        std::cout << numberOfUnsolvedSchedules.at(numberOfChain) << std::endl;
    }


    return;
}

void testSolvingTimeVsUtilizations()
{
    std::vector<std::vector<double>> pairsOfUtilizationForCores = { {0.2, 0.2}, {0.2, 0.4}, { 0.2, 0.6 }, { 0.2, 0.8 }, { 0.4, 0.4 }, { 0.4, 0.6 }, { 0.4, 0.8 }, { 0.6, 0.6 }, { 0.6, 0.8 }, { 0.8, 0.8 } };
    int numberOfChains = 2;
    int numberOfCommunicatingPairs = 20;
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 100;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    std::vector<TaskChain> chains;

    std::vector<std::vector<double>> executionTimes;
    std::vector<double> avgExecutionTimePerPairOfUtilization;

    std::vector<int> numberOfOptimizedSchedules;
    std::vector<int> numberOfTightenedSchedules;
    std::vector<int> numberOfUnsolvedSchedules;
    
    //std::cout << "TU SAM" << std::endl;

    for (int i = 0; i < pairsOfUtilizationForCores.size(); i++)
    {
        std::vector<double> executionTimesPerUtilizationPair;

        executionTimes.push_back(executionTimesPerUtilizationPair);
    }
     
    int numberOfTest = 1;

    for (int utilizationPair = 0; utilizationPair < pairsOfUtilizationForCores.size(); utilizationPair++)
    {
        int numberOfOptimizedSchedulesPerNumberOfChain = 0;

        int numberOfTightenedSchedulesPerNumberOfChain = 0;

        int numberOfUnsolvedSchedulesPerNumberOfChains = 0;

        for (int i = 0; i < numberOfTestCases; i++)
        {
            chains.clear();

            std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains, chains, pairsOfUtilizationForCores.at(utilizationPair).at(0), pairsOfUtilizationForCores.at(utilizationPair).at(1), percentageOfConectedness, numberOfCommunicatingPairs);

            //int totalNumberOfTasksPerTestCase = mytaskSets.at(0).getTasks().size() + mytaskSets.at(1).getTasks().size();
            //int totalNumberOfInstancesPerTestCase = mytaskSets.at(0).getInstances().size() + mytaskSets.at(1).getInstances().size();

            //numberOfTasks.at(utilizationPair).push_back(totalNumberOfTasksPerTestCase);
            //numberOfInstances.at(utilizationPair).push_back(totalNumberOfInstancesPerTestCase);

            std::string logFile1 = "LogFileSolvingTimeVsUtilizations";
            std::string logFile2 = std::to_string(numberOfTest);
            std::string logFile3 = ".txt";

            numberOfTest++;

            std::cout << logFile1 + logFile2 + logFile3;

            executionTimes.at(utilizationPair).push_back(createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3, status, maximumInterCoreDelay));

            //std::cout << "TU Sam" << std::endl;
            if (status == 0)
            {
                numberOfOptimizedSchedulesPerNumberOfChain++;
            }
            else if (status == 1)
            {
                numberOfTightenedSchedulesPerNumberOfChain++;
            }
            else
            {
                numberOfUnsolvedSchedulesPerNumberOfChains++;
            }

        }

        numberOfOptimizedSchedules.push_back(numberOfOptimizedSchedulesPerNumberOfChain);
        numberOfTightenedSchedules.push_back(numberOfTightenedSchedulesPerNumberOfChain);
        numberOfUnsolvedSchedules.push_back(numberOfUnsolvedSchedulesPerNumberOfChains);

    }
    
   
    for (int utilizationPair = 0; utilizationPair < pairsOfUtilizationForCores.size(); utilizationPair++)
    {
        double sumOfExecutionTimesPerUtilizationPair = 0.0;

        for (int executionTime = 0; executionTime < executionTimes.at(utilizationPair).size(); executionTime++)
        {
            sumOfExecutionTimesPerUtilizationPair += executionTimes.at(utilizationPair).at(executionTime);
        }

        avgExecutionTimePerPairOfUtilization.push_back(sumOfExecutionTimesPerUtilizationPair / numberOfTestCases);
    }

    std::cout << "ALL EXECUTION TIMES: " << std::endl;

    numberOfTest = 1;

    for (int utilizationPair = 0; utilizationPair < pairsOfUtilizationForCores.size(); utilizationPair++)
    {
        std::cout << "utilizationPair: (" << pairsOfUtilizationForCores.at(utilizationPair).at(0) << ", " << pairsOfUtilizationForCores.at(utilizationPair).at(1) << ")"  << std::endl;
        for (int executionTime = 0; executionTime < executionTimes.at(utilizationPair).size(); executionTime++)
        {
            //std::cout << "test " << numberOfTest << " time: " << executionTimes.at(utilizationPair).at(executionTime) << " ,";

            std::cout << executionTimes.at(utilizationPair).at(executionTime) << " ";

            numberOfTest++;
        }

        std::cout << std::endl;
    }

    std::cout << "AVERAGE EXECUTION TIME PER UTILIZATION PAIR: " << std::endl;

    for (int utilizationPair = 0; utilizationPair < pairsOfUtilizationForCores.size(); utilizationPair++)
    {
        std::cout << "utilizationPair: (" << pairsOfUtilizationForCores.at(utilizationPair).at(0) << ", " << pairsOfUtilizationForCores.at(utilizationPair).at(1) << ")" << std::endl;

        std::cout << avgExecutionTimePerPairOfUtilization.at(utilizationPair) << std::endl;
    }


    std::cout << "NUMBER OF OPTIMIZED SCHEDULES: " << std::endl;

    for (int utilizationPair = 0; utilizationPair < pairsOfUtilizationForCores.size(); utilizationPair++)
    {
        std::cout << "utilizationPair: (" << pairsOfUtilizationForCores.at(utilizationPair).at(0) << ", " << pairsOfUtilizationForCores.at(utilizationPair).at(1) << ")" << std::endl;

        std::cout << numberOfOptimizedSchedules.at(utilizationPair) << std::endl;
    }


    std::cout << "NUMBER OF TIGHTENED SCHEDULES: " << std::endl;

    for (int utilizationPair = 0; utilizationPair < pairsOfUtilizationForCores.size(); utilizationPair++)
    {
        std::cout << "utilizationPair: (" << pairsOfUtilizationForCores.at(utilizationPair).at(0) << ", " << pairsOfUtilizationForCores.at(utilizationPair).at(1) << ")" << std::endl;

        std::cout << numberOfTightenedSchedules.at(utilizationPair) << std::endl;
    }


    std::cout << "NUMBER OF UNSOLVED SCHEDULES: " << std::endl;

    for (int utilizationPair = 0; utilizationPair < pairsOfUtilizationForCores.size(); utilizationPair++)
    {
        std::cout << "utilizationPair: (" << pairsOfUtilizationForCores.at(utilizationPair).at(0) << ", " << pairsOfUtilizationForCores.at(utilizationPair).at(1) << ")" << std::endl;

        std::cout << numberOfUnsolvedSchedules.at(utilizationPair) << std::endl;
    }

    return;
}

void testSolvingTimeVsNumberOfCommunicatingPairs()
{

    int numberOfChains = 2;
    std::vector<double> utilizationsForCores = { 0.5, 0.5 };
    std::vector<int> numberOfCommunicatingPairs = {0, 2, 4, 8, 16, 32, 64, 128};
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 100;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    std::vector<TaskChain> chains;

    std::vector<std::vector<double>> executionTimes;
    std::vector<double> avgExecutionTimePerPairOfUtilization;

    std::vector<int> numberOfOptimizedSchedules;
    std::vector<int> numberOfTightenedSchedules;
    std::vector<int> numberOfUnsolvedSchedules;

    //std::cout << "TU SAM" << std::endl;

    for (int i = 0; i < numberOfCommunicatingPairs.size(); i++)
    {
        std::vector<double> executionTimesPerUtilizationPair;

        executionTimes.push_back(executionTimesPerUtilizationPair);
    }

    int numberOfTest = 1;

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        int numberOfOptimizedSchedulesPerNumberOfChain = 0;

        int numberOfTightenedSchedulesPerNumberOfChain = 0;

        int numberOfUnsolvedSchedulesPerNumberOfChains = 0;

        for (int i = 0; i < numberOfTestCases; i++)
        {
            chains.clear();

            std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains, chains, utilizationsForCores[0], utilizationsForCores[1], percentageOfConectedness, numberOfCommunicatingPairs[communicatingPair]);

            std::string logFile1 = "LogFileSolvingTimeVsCommunicatingPairs";
            std::string logFile2 = std::to_string(numberOfTest);
            std::string logFile3 = ".txt";

            numberOfTest++;

            std::cout << logFile1 + logFile2 + logFile3;

            executionTimes.at(communicatingPair).push_back(createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3, status, maximumInterCoreDelay));

            //std::cout << "TU Sam" << std::endl;
            if (status == 0)
            {
                numberOfOptimizedSchedulesPerNumberOfChain++;
            }
            else if (status == 1)
            {
                numberOfTightenedSchedulesPerNumberOfChain++;
            }
            else
            {
                numberOfUnsolvedSchedulesPerNumberOfChains++;
            }

        }

        numberOfOptimizedSchedules.push_back(numberOfOptimizedSchedulesPerNumberOfChain);
        numberOfTightenedSchedules.push_back(numberOfTightenedSchedulesPerNumberOfChain);
        numberOfUnsolvedSchedules.push_back(numberOfUnsolvedSchedulesPerNumberOfChains);

    }

    for (int communicatingPair = 0; communicatingPair <numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        double sumOfExecutionTimesPerUtilizationPair = 0.0;

        for (int executionTime = 0; executionTime < executionTimes.at(communicatingPair).size(); executionTime++)
        {
            sumOfExecutionTimesPerUtilizationPair += executionTimes.at(communicatingPair).at(executionTime);
        }

        avgExecutionTimePerPairOfUtilization.push_back(sumOfExecutionTimesPerUtilizationPair / numberOfTestCases);
    }

    std::cout << "ALL EXECUTION TIMES: " << std::endl;

    numberOfTest = 1;

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        std::cout << "Number of communicating pairs: "<<  numberOfCommunicatingPairs[communicatingPair] << std::endl;

        for (int executionTime = 0; executionTime < executionTimes.at(communicatingPair).size(); executionTime++)
        {

            std::cout << executionTimes.at(communicatingPair).at(executionTime) << " ";

            numberOfTest++;
        }

        std::cout << std::endl;
    }

    std::cout << "AVERAGE EXECUTION TIME PER UTILIZATION PAIR: " << std::endl;

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        std::cout << "Number of communicating pairs: " << numberOfCommunicatingPairs[communicatingPair] << std::endl;

        std::cout << avgExecutionTimePerPairOfUtilization.at(communicatingPair) << std::endl;
    }


    std::cout << "NUMBER OF OPTIMIZED SCHEDULES: " << std::endl;

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        std::cout << "Number of communicating pairs: " << numberOfCommunicatingPairs[communicatingPair] << std::endl;

        std::cout << numberOfOptimizedSchedules.at(communicatingPair) << std::endl;
    }


    std::cout << "NUMBER OF TIGHTENED SCHEDULES: " << std::endl;

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        std::cout << "Number of communicating pairs: " << numberOfCommunicatingPairs[communicatingPair] << std::endl;

        std::cout << numberOfTightenedSchedules.at(communicatingPair) << std::endl;
    }


    std::cout << "NUMBER OF UNSOLVED SCHEDULES: " << std::endl;

    for (int communicatingPair = 0; communicatingPair < numberOfCommunicatingPairs.size(); communicatingPair++)
    {
        std::cout << "Number of communicating pairs: " << numberOfCommunicatingPairs[communicatingPair] << std::endl;

        std::cout << numberOfUnsolvedSchedules.at(communicatingPair) << std::endl;
    }

    return;
}
*/




void testIndustrialTestCase()
{
    int numberOfSolutions = 1;

    std::vector<TaskChain> taskChains;

    taskChains.clear();

    int maximumInterCoreDelay = -1;

    int status = 0;

    std::vector<TaskSet> taskSets = TestCaseIndustrial(taskChains);

    createAndSolveModel(taskSets, taskChains, numberOfSolutions, "IndustrialResponseTime.txt", status, maximumInterCoreDelay, true);

}

int main(int, const char* []) {

    try
    {
        testSolvingTimeVsCommunicatingPairs();
    }
    catch (const std::exception & e)
    {
        std::cout << e.what();

    }
    
	return 0;
}

