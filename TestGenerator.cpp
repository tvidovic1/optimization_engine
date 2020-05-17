#include "TestGenerator.h"

bool chainsValid(std::vector<TaskChain> chains)
{
	int chainIndex = 0;
	int taskIndex = 0;

	for (int i = 0; i < chains.size(); i++)
	{
		chainIndex = i;
		for (int j = 0; j < chains.at(i).getTasks().size(); j++)
		{
			taskIndex = j;
			int taskId = chains.at(i).getTasks().at(taskIndex).getTaskId();
			std::set<int> taskPredecessors;
			std::set<int> taskSuccessors;

			for (int k = 0; k < chains.size(); k++)
			{
				for (int l = 0; l < chains.at(k).getTasks().size(); l++)
				{
					if (chains.at(k).getTasks().at(l).getTaskId() == taskId) // add all predecessors and successors to set
					{
						//add all predecessors
						for (int predecessors = 0; predecessors < l; predecessors++)
						{
							taskPredecessors.insert(chains.at(k).getTasks().at(predecessors).getTaskId());
						}
						//add all successors
						for (int successors = l + 1; successors < chains.at(k).getTasks().size(); successors++)
						{
							taskSuccessors.insert(chains.at(k).getTasks().at(successors).getTaskId());
						}
					}
				}
			}

			if (setsIntersect(taskPredecessors, taskSuccessors))
			{
				return false;
			}
		}
	}
	return true;
}

bool correctAmountOfCommunicatingInstances(std::vector<TaskSet> taskSets, std::vector<TaskChain> chains, int n)
{

	if (n < 0) return true;


	int numberOfInstances = 0;

	std::vector<std::vector<TaskInstance>> instancesOnCore;

	// The common hyperperiod needs to be considered
	long long int hyperPeriod;
	if (taskSets.at(0).getHyperperiod() != 0 && taskSets.at(1).getHyperperiod() != 0)
	{
		std::vector<long long int> hyperperiodsOfTaskSets;
		hyperperiodsOfTaskSets.push_back(taskSets.at(0).getHyperperiod() / 1000000);
		hyperperiodsOfTaskSets.push_back(taskSets.at(1).getHyperperiod() / 1000000);
		hyperPeriod = findLeastCommonMultiple(hyperperiodsOfTaskSets) * 1000000;
		//std::cout << "hyper: " << hyperPeriod << std::endl;
		taskSets.at(0).setHyperperiod(hyperPeriod);
		taskSets.at(1).setHyperperiod(hyperPeriod);
	}


	for (int i = 0; i < 2; i++)
	{
		instancesOnCore.push_back(std::vector<TaskInstance>());
		instancesOnCore.at(i) = taskSets.at(i).getInstances();
	}


	// Loop through all the chains

	for (int chain = 0; chain < chains.size(); chain++)
	{
		// loop through all of the consumers in the chain
		for (int consumerIndex = 1; consumerIndex < chains.at(chain).getTasks().size(); consumerIndex++)
		{
			long long int consumerTaskId = chains.at(chain).getTasks().at(consumerIndex).getTaskId();
			long long int consumerCoreAssignedTo = chains.at(chain).getTasks().at(consumerIndex).getCoreAssignedTo() - 1;

			long long int producerIndex = consumerIndex - 1;
			long long int producerTaskId = chains.at(chain).getTasks().at(producerIndex).getTaskId();
			long long int producerCoreAssignedTo = chains.at(chain).getTasks().at(producerIndex).getCoreAssignedTo() - 1;

			//std::cout << "TU SMO" << std::endl;


			//loop through all instances on consumers core
			for (int consumerInstanceIndex = 0; consumerInstanceIndex < instancesOnCore.at(consumerCoreAssignedTo).size(); consumerInstanceIndex++)
			{
				bool firstTime = true;
				TaskInstance currentConsumerInstance = instancesOnCore.at(consumerCoreAssignedTo).at(consumerInstanceIndex);

				// if it is an instance of the correct consumer
				if (currentConsumerInstance.getTask().getTaskId() == consumerTaskId)
				{
					//loop through all instances on producers core
					for (int producerInstanceIndex = 0; producerInstanceIndex < instancesOnCore.at(producerCoreAssignedTo).size(); producerInstanceIndex++)
					{
						TaskInstance currentProducerInstance = instancesOnCore.at(producerCoreAssignedTo).at(producerInstanceIndex);

						//std::cout << "CONSUMER " << currentConsumerInstance.getTask().getTaskId() << " PRODUCER " << currentProducerInstance.getTask().getTaskId() << std::endl;
						// if it is an instance of the correct producer

						if (currentProducerInstance.getTask().getTaskId() == producerTaskId)
						{
						     //if the two instances can communicate increase count
							if (canCommunicate(currentConsumerInstance, currentProducerInstance) && producerCoreAssignedTo != consumerCoreAssignedTo)
							{
								std::cout << currentConsumerInstance.getTask().getTaskId() << currentConsumerInstance.getNumberOfInstance() << "AND" << currentProducerInstance.getTask().getTaskId() << currentProducerInstance.getNumberOfInstance() << std::endl;
								numberOfInstances++;
							}

							if (intervalsOverlap(0, currentProducerInstance.getTask().getPeriod() - currentProducerInstance.getTask().getWorstCaseExecutionTime(), currentConsumerInstance.getAbsoluteReleaseTime() + currentConsumerInstance.getTask().getWorstCaseExecutionTime(), currentConsumerInstance.getAbsoluteDeadline()) && producerCoreAssignedTo != consumerCoreAssignedTo && firstTime)
							{
								std::cout << currentConsumerInstance.getTask().getTaskId() << currentConsumerInstance.getNumberOfInstance() << "AND" << currentProducerInstance.getTask().getTaskId() << currentProducerInstance.getNumberOfInstance() << std::endl;
								firstTime = false;

								numberOfInstances++;

							}
						}
					}

				}
			}

		}
	}

	std::cout << "numberOfInstances: " << numberOfInstances << std::endl;
	return numberOfInstances == n;
}


std::vector<TaskSet> generateTestCase(int numberOfChains, std::vector<TaskChain>& chains, double totalUtilizationForCore0, double totalUtilizationForCore1, double percentageOfSystemConectedness, int numberOfCommunicatingProducerConsumerInstances)
{
	std::vector<TaskSet> taskSets;

	do
	{

		taskSets.clear();

		// Vector that holds numbers of tasks per activation pattern for each of the chains
		std::vector<std::vector<int>> numberOfTasksPerActivationPatternPerChain;

		// Vector that holds periods of tasks per activation pattern for each of the chain
		std::vector<std::vector<int>> periodsOfTasksPerActivationPatternPerChain;

	
		for (int chain = 0; chain < numberOfChains; chain++)
		{
			// For each of the chains (there are numberOfChains chains) randomly generate possible activation pattern

			// Index of randomly generated number of activation pattern for current chain
			int indexOfActivationPattern = roulleteWheelSelecetion(activationPatternsProbabilities);

			std::vector<int> numbersOfTasksForCurrentChain;
			numberOfTasksPerActivationPatternPerChain.push_back(numbersOfTasksForCurrentChain);

			std::vector<int> periodsOfTasksForCurrentChain;
			periodsOfTasksPerActivationPatternPerChain.push_back(periodsOfTasksForCurrentChain);

			// For each of the activation patterns generate random corresponding number of tasks and periods of tasks
			for (int activationPattern = 0; activationPattern < activationPatterns[indexOfActivationPattern]; activationPattern++)
			{

				numberOfTasksPerActivationPatternPerChain.at(chain).push_back(numberOfTasksPerActivationPattern.at(roulleteWheelSelecetion(numberOfTasksPerActivationPatternProbabilites)));

				// If there is only one activation pattern or the current activation pattern is the first one, then a period for that activation pattern can be chosen from all possible tasks' periods
				// else periods can only be chosen according to the matrix allowedConsumerPeriods

				if (activationPatterns[indexOfActivationPattern] == 1 || activationPattern == 0)
				{
					periodsOfTasksPerActivationPatternPerChain.at(chain).push_back(tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities)));
				}

				else
				{
					// Period of producing activation pattern
					int periodOfProducingActivationPattern = periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern - 1);
				
					// Find index of the period of producing activation pattern in order to find allowed period of consuming activation pattern
					int indexOfPeriodOfProducingActivationPattern = findIndex(tasksPeriods, periodOfProducingActivationPattern);
				
					int periodOfConsumingActivationPatternPeriod;

					int indexOfPeriodOfConsumingActivationPattern;
				
					// Randomly generate periods of consuming activation pattern until the allowed period of consming activation pattern is obtained
					do 
					{
						// Randomly generate a potential period of consuming activation pattern
						periodOfConsumingActivationPatternPeriod = tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities));

						//std::cout << activationPattern << periodOfConsumingActivationPatternPeriod << std::endl;

						// Find index of the potential consuming activation pattern
						indexOfPeriodOfConsumingActivationPattern = findIndex(tasksPeriods, periodOfConsumingActivationPatternPeriod);

					} while (isPeriodOfConsumingActivationPatternAllowed[indexOfPeriodOfProducingActivationPattern][indexOfPeriodOfConsumingActivationPattern] == false);
					
					periodsOfTasksPerActivationPatternPerChain.at(chain).push_back(tasksPeriods.at(indexOfPeriodOfConsumingActivationPattern));
				}
			}
		}

		// Vector that holds periods of all tasks (tasks in chains + independent tasks)
		std::vector<int> periodsOfTasks;

		for (int chain = 0; chain < numberOfChains; chain++)
		{
			for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
			{
				for (int task = 0; task < numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern); task++)
				{
					periodsOfTasks.push_back(periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern));
				}
			}
		}

	

		// TEST1
		for (int i = 0; i < numberOfChains; i++)
		{
			//std::cout << "Chain: " << i + 1 << "Total Number of Activation Patterns: " << numberOfTasksPerActivationPatternPerChain.at(i).size() << std::endl;

			//std::cout << numberOfTasksPerActivationPatternPerChain.size() << std::endl;
			//std::cout << periodsOfTasksPerActivationPatternPerChain.size() << std::endl;

			for (int j = 0; j < numberOfTasksPerActivationPatternPerChain.at(i).size(); j++)
			{
				//std::cout << "Activation Pattern: " << j + 1 << " Number of Tasks " << numberOfTasksPerActivationPatternPerChain.at(i).at(j)<< " Tasks' Period: " << periodsOfTasksPerActivationPatternPerChain.at(i).at(j) <<std::endl;
			}
		}
	

		//showVectorInt(periodsOfTasks);
		//std::cout << std::endl;

	
		// A variable that holds the total number of tasks in chains
		int numberOfTasksInChains = 0;

		// Calculate total number of tasks in chains
		for (int chain = 0; chain < numberOfChains; chain++)
		{
			for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
			{
				numberOfTasksInChains += numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern);
			}
		}

		//Randomly generate the total number of tasks (task in chains + independent tasks) 
		std::random_device rd;

		std::mt19937 gen(rd());

		

		std::uniform_int_distribution<> distribution(0, numberOfTasksInChains);
		
		//int totalNumberOfTasks = std::max(8, numberOfTasksInChains + distribution(gen));

		//std::cout << totalNumberOfTasks;

		// Calculate the total number of independent task 
		//int numberOfIndependentTasks = totalNumberOfTasks - numberOfTasksInChains;

		//std::cout << numberOfIndependentTasks << std::endl;
		


		int numberOfIndependentTasks = std::ceil(numberOfTasksInChains * (1 - percentageOfSystemConectedness) / percentageOfSystemConectedness);

		int totalNumberOfTasks = numberOfIndependentTasks + numberOfTasksInChains;

		if (totalNumberOfTasks < 3) totalNumberOfTasks = 3;
		//std::cout << numberOfTasksInChains << " " << numberOfIndependentTasks << std::endl;
			 
	
		// Randomly generate periods for independent tasks 

		for (int independentTask = 0; independentTask < numberOfIndependentTasks; independentTask++)
		{
			periodsOfTasks.push_back(tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities)));
		}

		//std::cout << "TU SMO";

		//showVectorInt(periodsOfTasks);
		//std::cout << std::endl;

		// Randolmy caculate the number of tasks that will be placed on each of the cores

		// Vector that holds IDs of all of the tasks
		std::vector<int> allTasksIDs;

		for (int taskID = 0; taskID < totalNumberOfTasks; taskID++)
		{
			allTasksIDs.push_back(taskID + 1);
		}

		// Shuffle the vector of IDs 
		std::random_shuffle(allTasksIDs.begin(), allTasksIDs.end());

		/*for (int taskId = 0; taskId < totalNumberOfTasks; taskId++)
		{
			std::cout << allTasksIds[taskId] << " ";
		}*/

		// Split up vector of IDs by randomly generating the point of split up, keeping in mind that minimum number of tasks on one core must be at least equal to 3 (intuitive reasoning)
		// Core 0 will have splitUpPoint tasks and Core 1 will have totalNumberOfTasks - splitUpPoint tasks
		std::uniform_int_distribution<> distributionForSplitUpOfTasks(1, totalNumberOfTasks - 1);

		int splitUpPoint = distributionForSplitUpOfTasks(gen);

		// Vector that holds the information of which task is assigned to which core
		std::vector<int> coreAssignedTo;

		for (int taskID = 0; taskID < totalNumberOfTasks; taskID++)
		{
			if (taskID < splitUpPoint)
			{
				coreAssignedTo.push_back(1);
			}
			else
			{
				coreAssignedTo.push_back(2);
			}
		}

		//showVectorInt(allTasksIDs);
		//std::cout << std::endl;

		//showVectorInt(coreAssignedTo);
		//std::cout << std::endl;

		// Sort tasks' IDs ascendingly and cores that are assigned to them acordingly

		for (int taskID = 0; taskID < allTasksIDs.size() - 1; taskID++)
		{
			for (int taskIDHelp = 0; taskIDHelp < allTasksIDs.size() - taskID - 1; taskIDHelp++)
			{
				if (allTasksIDs[taskIDHelp] > allTasksIDs[taskIDHelp + 1])
				{
					int tempID = allTasksIDs[taskIDHelp];
					int tempCore = coreAssignedTo[taskIDHelp];

					allTasksIDs[taskIDHelp] = allTasksIDs[taskIDHelp + 1];
					coreAssignedTo[taskIDHelp] = coreAssignedTo[taskIDHelp + 1];

					allTasksIDs[taskIDHelp + 1] = tempID;
					coreAssignedTo[taskIDHelp + 1] = tempCore;

				}
			}
		}

		//showVectorInt(allTasksIDs);
		//std::cout << std::endl;

		//showVectorInt(coreAssignedTo);
		//std::cout << std::endl;

		// Generate utilizations for each of the tasks for each of the cores and put it into vectors utilizationsForCore0 and utilizationForCore1 respectively

		//showVectorInt(allTasksIDs);
		//std::cout << std::endl;

		//showVectorInt(coreAssignedTo);
		//std::cout << std::endl << splitUpPoint <<std::endl;

		std::vector<std::vector<double>> utilizationsForCore0 = generateTaskUtilization(double(splitUpPoint), totalUtilizationForCore0);

		std::vector<std::vector<double>> utilizationsForCore1 = generateTaskUtilization(double(totalNumberOfTasks - splitUpPoint), totalUtilizationForCore1);

		std::vector<double> utilizationsOfTasks(utilizationsForCore0.at(0).size() + utilizationsForCore1.at(0).size(), 0.0);

		int utilization = 0;

		for (int task = 0; task < totalNumberOfTasks; task++)
		{
			if (coreAssignedTo.at(task) == 1)
			{
				utilizationsOfTasks.at(task) = utilizationsForCore0.at(0).at(utilization);
				utilization++;
			}
		}

		utilization = 0;

		for (int task = 0; task < totalNumberOfTasks; task++)
		{
			if (coreAssignedTo.at(task) == 2)
			{
				utilizationsOfTasks.at(task) = utilizationsForCore1.at(0).at(utilization);
				utilization++;
			}
		}

		/*
		showMatrix(utilizationsForCore0);
		std::cout << std::endl;

		showMatrix(utilizationsForCore1);
		std::cout << std::endl;

		showVectorInt(coreAssignedTo);
		std::cout << std::endl;

		showVector(utilizationsOfTasks);
		std::cout << std::endl;
		*/

		// Calculate WCET for each of the tasks according to formula: WCET = T/U;

		std::vector<long long int> worstCaseExecutionTime;

		//std::cout << "TU SMO";


		for (int task = 0; task < totalNumberOfTasks; task++)
		{
			// Multipy worst case exection time by 1000000000 in order to get picoseconds
			worstCaseExecutionTime.push_back(1000000000 * (double)periodsOfTasks.at(task)  * utilizationsOfTasks.at(task));
		}

		// Calculate duration of the read phase
		std::vector<long long int> worstCaseRead;

		for (int task = 0; task < totalNumberOfTasks; task++)
		{
			// Multipy worst case exection time by 1000000000000 in order to get picoseconds
			int generatedIndex = roulleteWheelSelecetion(labelSizesProbabilities);
			std::uniform_int_distribution<> labelDistribution(0, labelSizes.at(generatedIndex).size() - 1);

			int whichLabel = labelDistribution(gen);
			worstCaseRead.push_back(1000000000000 * READ_PERCENTAGE * (double) (labelSizes.at(generatedIndex).at(whichLabel)) / (double) (CLOCK_FREQUENCY * NUMBER_OF_BYTES_PER_ONE_CLOCK_CYCLE));
		}

		// Calculate duration of the write phase
		std::vector<long long int> worstCaseWrite;

		for (int task = 0; task < totalNumberOfTasks; task++)
		{
			// Multipy worst case exection time by 1000000000000 in order to get picoseconds
			int generatedIndex = roulleteWheelSelecetion(labelSizesProbabilities);
			std::uniform_int_distribution<> labelDistribution(0, labelSizes.at(generatedIndex).size() - 1);

			int whichLabel = labelDistribution(gen);
			worstCaseWrite.push_back(1000000000000 * WRITE_PERCENTAGE * (double)(labelSizes.at(generatedIndex).at(whichLabel)) / (double)(CLOCK_FREQUENCY * NUMBER_OF_BYTES_PER_ONE_CLOCK_CYCLE));
		}

		// Calculate duration of the execute phase
		std::vector<long long int> worstCaseExecute;

		for (int task = 0; task < totalNumberOfTasks; task++)
		{
			// worstCaseExecutionTime - worstCaseRead - worstCaseWrite
			if (worstCaseExecutionTime.at(task) - worstCaseRead.at(task) - worstCaseWrite.at(task) < 0)
			{
				worstCaseExecute.push_back(0);
			}
			else
			{
				worstCaseExecute.push_back(worstCaseExecutionTime.at(task) - worstCaseRead.at(task) - worstCaseWrite.at(task));
			}
		}

		// Create task sets for each of the cores

		TaskSet taskSet0(1);

		TaskSet taskSet1(2);



		/*
		showVectorInt(allTasksIDs);
		std::cout << std::endl;

		showVectorInt(worstCaseRead);
		std::cout << std::endl;

		showVectorInt(worstCaseExecute);
		std::cout << std::endl;

		showVectorInt(worstCaseWrite);
		std::cout << std::endl;

		showVectorInt(periodsOfTasks);
		std::cout << std::endl;

		showVectorInt(coreAssignedTo);
		std::cout << std::endl;

		*/
		std::vector <Task> tasks;

		for (int task = 0; task < totalNumberOfTasks; task++)
		{
			Task newTask = Task(allTasksIDs[task], worstCaseRead[task], worstCaseExecute[task], worstCaseWrite[task], (long long int) periodsOfTasks[task] * 1000000000, coreAssignedTo[task]);

			//std::cout << newTask;

			tasks.push_back(newTask);

			if (coreAssignedTo[task] == 1)
			{
			
				taskSet0.addTask(newTask);
			}

			else
			{
				taskSet1.addTask(newTask);
			}

		}

		taskSets.push_back(taskSet0);
		taskSets.push_back(taskSet1);

		// Populate the chains
		do {

			chains.clear();

			for (int chain = 0; chain < numberOfChains; chain++)
			{
				TaskChain newChain;

				for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
				{
					for (int numberOfTasks = 0; numberOfTasks < numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern); numberOfTasks++)
					{
						int randomTaskID;

						do
						{
							std::uniform_int_distribution<> distribution(0, totalNumberOfTasks - 1);

							randomTaskID = distribution(gen);

							//std::cout << "pattern: " << (long long int) periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern) * 1000000000 << "task:"  << tasks.at(randomTaskID) << "is in chain: " << newChain.isInChain(randomTaskID);

						} while (tasks.at(randomTaskID).getPeriod() != (long long int) periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern) * 1000000000 || newChain.isInChain(randomTaskID + 1));

						newChain.addTask(tasks.at(randomTaskID));
					}
				}

				chains.push_back(newChain);

				//std::cout << newChain;
			}
		} while (!chainsValid(chains));
	

		for (int i = 0; i < chains.size(); i++)
		{
			//std::cout << chains.at(i) << std::endl;
		}

	
	}while(!correctAmountOfCommunicatingInstances(taskSets, chains, numberOfCommunicatingProducerConsumerInstances) );

	return taskSets;
}
