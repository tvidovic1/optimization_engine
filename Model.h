#include <ilcp/cp.h>
#include <string>
#include <cstring>
#include <vector>
#include "Task.h"
#include "TaskInstance.h"
#include "TaskSet.h"
#include "Helper.h"
#include "TaskChain.h"
#include <chrono>
#include <sstream>
#include <fstream>
#include <string>


#pragma once

// Each of the tasks has three phases: READ, EXECUTE and WRITE
#define NUMBER_OF_PHASES 3

// There are two cores 
#define NUMBER_OF_CORES 2

// The global CPLEX enviroment variable
static IloEnv environment;

// The global CPLEX model variable
static IloModel model;

// The function for the initialitaion of the enviroment
void initializeEnviroment(void);

// The function that creates the name of interval variable
char* createIntervalVariableName(int taskID, int numberOfInstance, char phase);

// The function that creates CPLEX model based on task sets
double createAndSolveModel(std::vector<TaskSet> taskSets, std::vector<TaskChain> taskChains, int numberOfSolutions, std::string logFile, int & status,int maximumInterCoreDelay = -1, bool minimizeResponseTimes = false);






