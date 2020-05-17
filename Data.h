#include "TaskSet.h"
#include "TaskChain.h"
#include <vector>

#pragma once

// TEMPLATE:

/* Test cases with following characteristics:
	- Types of Tasks:
	- Harmonic or Non Harmonic:
	- Semi Circular or Circular:
	- One Core or Multi-Core:
	- One-Chain or Multiple Chains:
	- Over Sampling or Under Sampling:
*/

std::vector<TaskSet>  TestCase1(std::vector<TaskChain> & chains);

std::vector<TaskSet>  TestCase2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase3(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase4(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase5(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase6_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase6_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase6_3(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase7(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase8(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: One-Chain
	- Over Sampling or Under Sampling: Same Period
*/
std::vector<TaskSet>  TestCase10_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase10_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase10_3(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase10_4(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase10_5(std::vector<TaskChain>& chains);



/* Test cases with following characteristics:
	- Types of Tasks: Independent and Chains
	- Harmonic or Non Harmonic: Harmonic
	- Semi Circular or Circular: Semi Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: One-Chain
	- Over Sampling or Under Sampling: Under Sampling
*/


std::vector<TaskSet> TestCase11_1(std::vector<TaskChain>& chains);

std::vector<TaskSet> TestCase11_2(std::vector<TaskChain>& chains);

std::vector<TaskSet> TestCase11_3(std::vector<TaskChain>& chains);


/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: One-Chain
	- Over Sampling or Under Sampling: Over Sampling
*/

std::vector<TaskSet>  TestCase12_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase12_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase12_3(std::vector<TaskChain>& chains);


/* Test cases with following characteristics:
	- Types of Tasks: Both
	- Harmonic or Non Harmonic: Harmonic
	- Semi Circular or Circular: Semi Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: One-Chain
	- Over Sampling or Under Sampling: Over Sampling
*/

std::vector<TaskSet>  TestCase13_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase13_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase13_3(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase13_4(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase13_5(std::vector<TaskChain>& chains);


/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Semi-Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: One-Chain
	- Over Sampling or Under Sampling: Over Sampling
*/

std::vector<TaskSet>  TestCase14_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase14_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase14_3(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: One-Chain
	- Over Sampling or Under Sampling: Under Sampling
*/

std::vector<TaskSet>  TestCase15_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase15_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase15_3(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: One-Chain
	- Over Sampling or Under Sampling: Both
*/

std::vector<TaskSet>  TestCase16_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase16_2(std::vector<TaskChain>& chains);


/* Test cases with following characteristics:
	- Types of Tasks: Both
	- Harmonic or Non Harmonic: Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Both
*/

std::vector<TaskSet>  TestCase17_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase17_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase17_3(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Over Sampling
*/

std::vector<TaskSet>  TestCase18_1(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Under Sampling
*/

std::vector<TaskSet>  TestCase19_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase19_2(std::vector<TaskChain>& chains);


/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Both
*/
std::vector<TaskSet>  TestCase20_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase20_2(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Both
	- Harmonic or Non Harmonic: Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Under Sampling
*/

std::vector<TaskSet>  TestCase21_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase21_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase21_3(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Both
	- Harmonic or Non Harmonic: Harmonic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Over Sampling
*/

std::vector<TaskSet>  TestCase22_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase22_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase22_3(std::vector<TaskChain>& chains);


/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Semi-Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Over sampling
*/

std::vector<TaskSet>  TestCase23_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase23_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase23_3(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Semi-Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Under sampling
*/

std::vector<TaskSet>  TestCase24_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase24_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase24_3(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Semi-Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Both
*/

std::vector<TaskSet>  TestCase25_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase25_2(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Both
	- Harmonic or Non Harmonic:Harmo nic
	- Semi Circular or Circular: Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Multiple Chains
	- Over Sampling or Under Sampling: Same Period
*/

std::vector<TaskSet>  TestCase26_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase26_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase26_3(std::vector<TaskChain>& chains);


/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Semi-Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Single Chain
	- Over Sampling or Under Sampling: Under-Sampling
*/

std::vector<TaskSet>  TestCase27_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase27_2(std::vector<TaskChain>& chains);

/* Test cases with following characteristics:
	- Types of Tasks: Only Chains
	- Harmonic or Non Harmonic: Non-Harmonic
	- Semi Circular or Circular: Semi-Circular
	- One Core or Multi-Core: Multi-Core
	- One-Chain or Multiple Chains: Single Chain
	- Over Sampling or Under Sampling: Both
*/

std::vector<TaskSet>  TestCase28_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase28_2(std::vector<TaskChain>& chains);



// Industrial test Case

std::vector<TaskSet>  TestCaseIndustrial(std::vector<TaskChain>& chains);