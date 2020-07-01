#include "rapidxml-1.13/rapidxml.hpp"
#include "Task.h"
#include "TaskSet.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include<random>
#include <ctime>


#pragma once

#define NUMBER_OF_CORES 2

// Distribution of Read/Write label sizes
#define labelSizes std::vector<std::vector<int>> { {1}, {2}, {4}, {5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16}, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}, {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63}, {64}}

// Number of bytes that can be accessed for the duration of one signe clock cycle
#define NUMBER_OF_BYTES_PER_ONE_CLOCK_CYCLE 1/10


std::vector<TaskSet> readInput(std::vector<const char *> inputCorePaths);