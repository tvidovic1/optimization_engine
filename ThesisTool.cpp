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
    int numberOfTestCases = 1;
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

void testTasksInstancesconstraintsVsTaskChains()
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

    std::vector<std::vector<int>> numberOfTasks;
    std::vector<double> avgNumberOfTasksPerNumberOfChain;
    std::vector<std::vector<int>> numberOfInstances;
    std::vector<double> avgNumberOfInstancesPerNumberOfChain;
    std::vector<std::vector<int>> numberOfConstraints;
    std::vector<double> avgNumberOfConstraintsPerNumberOfChain;


    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfTasksPerNumberOfChain;

        numberOfTasks.push_back(numberOfTasksPerNumberOfChain);

    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfInstancesPerNumberOfChain;

        numberOfInstances.push_back(numberOfInstancesPerNumberOfChain);

    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfConstraintsPerNumberOfChain;

        numberOfConstraints.push_back(numberOfConstraintsPerNumberOfChain);

    }

    int numberOfTest = 1;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {

        for (int i = 0; i < numberOfTestCases; i++)
        {
            chains.clear();

            std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains[numberOfChain], chains, utilizationsForCores[0], utilizationsForCores[1], percentageOfConectedness, numberOfCommunicatingPairs);

            //std::cout << "TU SAM" << std::endl;

            int totalNumberOfTasksPerTestCase = mytaskSets.at(0).getTasks().size() + mytaskSets.at(1).getTasks().size();
            int totalNumberOfInstancesPerTestCase = mytaskSets.at(0).getInstances().size() + mytaskSets.at(1).getInstances().size();

            numberOfTasks.at(numberOfChain).push_back(totalNumberOfTasksPerTestCase);
            numberOfInstances.at(numberOfChain).push_back(totalNumberOfInstancesPerTestCase);

            std::string logFile1 = "LogFileTasksInstConstVsTaskChains";
            std::string logFile2 = std::to_string(numberOfTest);
            std::string logFile3 = ".txt";

            numberOfTest++;

            std::cout << logFile1 + logFile2 + logFile3;

            int totalNumberOfConstraints = 0;

            double executionTime = createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3, status, maximumInterCoreDelay);

            numberOfConstraints.at(numberOfChain).push_back(totalNumberOfConstraints);

        }



    }

    // Calculate average number of tasks

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        double sumOfNumberOfTasksPerNumberOfChain = 0.0;

        for (int numberOfTask = 0; numberOfTask < numberOfTasks.at(numberOfChain).size(); numberOfTask++)
        {
            sumOfNumberOfTasksPerNumberOfChain += numberOfTasks.at(numberOfChain).at(numberOfTask);
        }

        avgNumberOfTasksPerNumberOfChain.push_back(sumOfNumberOfTasksPerNumberOfChain / numberOfTestCases);
    }


    // Calculate average number of instances

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        double sumOfNumberOfInstancesPerNumberOfChain = 0.0;

        for (int numberOfInstance = 0; numberOfInstance < numberOfInstances.at(numberOfChain).size(); numberOfInstance++)
        {
            sumOfNumberOfInstancesPerNumberOfChain += numberOfInstances.at(numberOfChain).at(numberOfInstance);
        }

        avgNumberOfInstancesPerNumberOfChain.push_back(sumOfNumberOfInstancesPerNumberOfChain / numberOfTestCases);
    }

    // Calculate average number of constraints

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        double sumOfNumberOfConstraintsPerNumberOfChain = 0.0;

        for (int numberOfConstraint = 0; numberOfConstraint < numberOfConstraints.at(numberOfChain).size(); numberOfConstraint++)
        {
            sumOfNumberOfConstraintsPerNumberOfChain += numberOfConstraints.at(numberOfChain).at(numberOfConstraint);
        }

        avgNumberOfConstraintsPerNumberOfChain.push_back(sumOfNumberOfConstraintsPerNumberOfChain / numberOfTestCases);
    }

    // Print all number of tasks

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains (number of tasks): " << numberOfChains.at(numberOfChain) << std::endl;
        for (int numberOfTask = 0; numberOfTask < numberOfTasks.at(numberOfChain).size(); numberOfTask++)
        {
            //std::cout << "test " << numberOfTest << " time: " << executionTimes.at(utilizationPair).at(executionTime) << " ,";

            std::cout << numberOfTasks.at(numberOfChain).at(numberOfTask) << " ";

        }

        std::cout << std::endl;
    }

    // Print average number of tasks per number of chains

    std::cout << "AVERAGE NUMBER OF TASKS PER NUMBER OF CHAINS: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains (tasks average number):" << numberOfChains.at(numberOfChain) << std::endl;

        std::cout << avgNumberOfTasksPerNumberOfChain.at(numberOfChain) << std::endl;
    }

    // Print all number of task instances

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains (number of instances): " << numberOfChains.at(numberOfChain) << std::endl;
        for (int numberOfInstance = 0; numberOfInstance < numberOfInstances.at(numberOfChain).size(); numberOfInstance++)
        {
            //std::cout << "test " << numberOfTest << " time: " << executionTimes.at(utilizationPair).at(executionTime) << " ,";

            std::cout << numberOfInstances.at(numberOfChain).at(numberOfInstance) << " ";

        }

        std::cout << std::endl;
    }


    // Print average number of task instances per number of chains

    std::cout << "AVERAGE NUMBER OF TASK INSTANCES PER NUMBER OF CHAINS: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains (task instances average number):" << numberOfChains.at(numberOfChain) << std::endl;

        std::cout << avgNumberOfInstancesPerNumberOfChain.at(numberOfChain) << std::endl;
    }

    // Print all number of constraints

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains (number of constraints): " << numberOfChains.at(numberOfChain) << std::endl;
        for (int numberOfConstraint = 0; numberOfConstraint < numberOfConstraints.at(numberOfChain).size(); numberOfConstraint++)
        {
            //std::cout << "test " << numberOfTest << " time: " << executionTimes.at(utilizationPair).at(executionTime) << " ,";

            std::cout << numberOfConstraints.at(numberOfChain).at(numberOfConstraint) << " ";

        }

        std::cout << std::endl;
    }


    // Print average number of task instances per number of chains

    std::cout << "AVERAGE NUMBER OF CONSTRAINTS PER NUMBER OF CHAINS: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "Number of chains (constraints average number):" << numberOfChains.at(numberOfChain) << std::endl;

        std::cout << avgNumberOfConstraintsPerNumberOfChain.at(numberOfChain) << std::endl;
    }

    return;

}

void testConstraintsVsCommunicatingPairs()
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

            std::string logFile1 = "LogFileTasksInstConstVsTaskChains";
            std::string logFile2 = std::to_string(numberOfTest);
            std::string logFile3 = ".txt";

            numberOfTest++;

            std::cout << logFile1 + logFile2 + logFile3;

            int totalNumberOfConstraints = 0;

            double executionTime = createAndSolveModel(mytaskSets, chains, numberOfSolutions, logFile1 + logFile2 + logFile3, status, maximumInterCoreDelay);

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




int main(int, const char* []) {


    //int numberOfSolutions = 1;

    //Initialize the cplex environment
    initializeEnviroment();

    testSolvingTimeVsNumberOfCommunicatingPairs();

    // try
    // {

         //std::vector<TaskChain> taskChains;
         //taskChains.clear();
         
         //std::vector<TaskSet> taskSets = TestCase17_3(taskChains);

    //int maximumInterCoreDelay = -1;

    //createAndSolveModel(taskSets, taskChains, numberOfSolutions, "IndustrialResponseTime.txt" ,maximumInterCoreDelay, false);

    //std::vector<std::vector<double>> utilizations = generateTaskUtilization(10, 0.9);

    //std::vector<double> activationPatternsProbabilities = { 0.1, 0.2, 0.7 };

    //std::vector<int> activationPatterns = { 1, 2, 3 };

    //int index = roulleteWheelSelecetion(activationPatternsProbabilities);

    //std::cout << "Activation pattern is: " << activationPatterns[index] << " with probability: " << activationPatternsProbabilities[index];

    /*
    int numberOfChains = 3;
    std::vector<TaskChain> chains;

    chains.clear();

    std::vector<TaskSet> mytaskSets = generateTestCase(numberOfChains, chains, 0.5, 0.5, 0.6, 30);

    createAndSolveModel(mytaskSets, chains, numberOfSolutions, "RANDOM.txt", maximumInterCoreDelay);
    */

    


    /*
    
    // 2. Experiment part I, utilizations for cores are fixed, but number of chains is variable, calculate number of constraints, number of tasks and number of instances 

/*
   

    // 2. Experiment part 2, utilizations for cores are fixed but the number of chains is variable, solving time and number of tighten scheldues is calculated

/*
    

    */

    //}catch (IloException & ex) {

        //environment.out() << "Error: " << ex << std::endl;

    //}
    //environment.end();

    
	return 0;
}

