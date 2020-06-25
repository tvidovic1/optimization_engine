/*
A file containing all the helper functions used throught project
*/

#include <vector>
#include <set>
#include "TaskInstance.h"
#include "Task.h"

#pragma once

/* A function that returns index of the desiried element of a vector
returns -1 if value does not exist in vector values */
int findIndex(std::vector<int> values, int value);

// A function that finds the GCD of the two inputs using the standard recursive algorithm
long long int findGreatestCommonDivisor(long long int a, long long int b);

// A function to find the GCD of an array of inputs
long long int findGreatestCommonDivisorOfVector(std::vector<long long int> inputs);

// A function that finds the LCM of the n inputs in the vector relying on GCD
long long int findLeastCommonMultiple(std::vector<long long int> inputs);

// A function that returns the left most digit of a 4 digit number (0 if non-enxistent)
int getFirstDigit(int number);

// A function that returns the second left most digit of a 4 digit number (0 if non-enxistent)
int getSecondDigit(int number);

// A function that returns the third left most digit of a 4 digit number
int getThirdDigit(int number);


// A function that returns the third left most digit of a 4 digit number
int getFourthDigit(int number);

// A function that returns true if intervals [a1, a2] and [b1, b2] overlap
bool intervalsOverlap(long long int a1, long long int a2, long long int b1, long long int b2);

// Check if instance b can communicate with instance a
bool follows(TaskInstance a, TaskInstance b);

// A function that prints vector of ints
void showVectorInt(std::vector<int> vec);

// A function that prints vector of doubles
void showVector(std::vector<double > vec);

// A function that prints matrix of doubles
void showMatrix(std::vector<std::vector<double> > vec);

// A function that replicates the matrix mat rows times horzontally and columns times vertically
std::vector<std::vector<double> > repmat(std::vector<std::vector<double> > mat, int rows, int columns);

// A function that returns vector of n uniformly random number whose sum is equal to u (using randFixedSum algorithm)
std::vector<std::vector<double>> generateTaskUtilization(double n, double u);

// A function that selects an element from a vector based on Roullete Wheel Selection algorithm
int roulleteWheelSelecetion(std::vector<double> probabilities);

// A function to check if two sets intersect
bool setsIntersect(std::set<int> a, std::set<int> b);

// A function to check if two task instances can potentially communicate
bool canCommunicate(TaskInstance producer, TaskInstance consumer);




