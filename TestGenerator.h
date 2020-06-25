#include <vector>
#include "Task.h"
#include "TaskSet.h"
#include "TaskChain.h"
#include <iostream>
#include <algorithm>
#include<random>
#include <ctime>

#pragma once

// Clock frequency
#define CLOCK_FREQUENCY 300000000

// Number of clock cylces per one byte

#define NUMBER_OF_CYCLES_PER_BYE = 10

// Number of bytes that can be accessed for the duration of one signe clock cycle
#define NUMBER_OF_BYTES_PER_ONE_CLOCK_CYCLE 1/10

// Percentage of READ bytes
#define READ_PERCENTAGE 0.9

// Percentage of WRITE bytes
#define WRITE_PERCENTAGE 0.6

// The minimum number of tasks in a test case
#define MINIMUM_NUMBER_OF_TASKS 3

// Possible activation patterns for chains of tasks and their probabilities
#define activationPatterns std::vector<int> {1, 2, 3}
#define activationPatternsProbabilities std::vector<double> {0.7, 0.2, 0.1}

// Possible numbers of tasks per each of the activation patterns and their probabilities
#define numberOfTasksPerActivationPattern std::vector<int> {2, 3, 4, 5}
#define numberOfTasksPerActivationPatternProbabilites std::vector<double> {0.3, 0.4, 0.2, 0.1}

// Possible periods of tasks and their probabilities
#define tasksPeriods std::vector<int> {1, 2, 5, 10, 20, 50, 100, 200}
#define tasksPeriodsProbabilities std::vector<double> {0.03, 0.02, 0.02, 0.25, 0.25, 0.03, 0.20, 0.01}

// Matrix that holds allowed periods for the consuming activation patterns. For example if the period of
// the producing activation pattern is equal to 1 then the allowed periods of the consuming activation 
// patterns are {1, 10, 20, 100}

//#define allowedConsumerPeriods std::vector<std::vector<int>> {{1, 10, 20, 100}, {2, 10, 20, 100}, {2, 5, 10, 20, 50, 100}, {1, 2, 5, 10, 20, 50, 100, 200}, {1, 2, 5, 10, 20, 50, 100, 200}, {5, 10, 20, 50, 100}, {2, 5, 10, 20, 50, 100, 200}, {10, 20, 100, 200}}

#define isPeriodOfConsumingActivationPatternAllowed std::vector<std::vector<bool>> {{1, 0, 0, 1, 1, 0, 1, 0}, {0, 1, 0, 1, 1, 0, 1, 0}, {0, 1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 1, 1, 1, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 1, 0, 1, 1}}

// Distribution of Read/Write label sizes
#define labelSizes std::vector<std::vector<int>> { {1}, {2}, {4}, {5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16}, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}, {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63}, {64}}

// Distribution of label sizes
#define labelSizesProbabilities std::vector<double> {0.35, 0.49, 0.13, 0.008, 0.013, 0.005, 0.002, 0.002}

// A function that randomly generates Test Case 
std::vector<TaskSet> generateTestCase(int numberOfChains, std::vector<TaskChain>& chains, int numberOfTaskInstances, double totalUtilizationForCore0, double totalUtilizationForCore1, double percentageOfSystemConectedness, int numberOfCommunicatingProducerConsumerInstances = -1);

// A function that checks if exactly n task instances is created
bool correctAmountOfTaskInstances(std::vector<TaskSet> taskSets, int n);

// A function that checks the logical validity of a set of task chains
bool chainsValid(std::vector<TaskChain> chains);

// A function that checks if exactly n instances can communicate in the created application
bool correctAmountOfCommunicatingInstances(std::vector<TaskSet> taskSets, std::vector<TaskChain> chains, int n);
