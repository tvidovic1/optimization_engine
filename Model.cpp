#include "Model.h"


void initializeEnviroment(void)
{
	environment = IloEnv();
}

char* createIntervalVariableName(int taskID, int numberOfInstance, char phase)
{
    // The default name of interval variable: tau taskID instanceNumber phaseIdentifier
    char defaultIntervalVariableName[16] = "tau 0000 0000 X";

    char intervalVariableName[16];
    strcpy_s(intervalVariableName, defaultIntervalVariableName);

    // Set taskID
    intervalVariableName[4] = getFirstDigit(taskID) + '0';
    intervalVariableName[5] = getSecondDigit(taskID) + '0';
    intervalVariableName[6] = getThirdDigit(taskID) + '0';
    intervalVariableName[7] = getFourthDigit(taskID) + '0';


    // Set instanceNumber
    intervalVariableName[9] = getFirstDigit(numberOfInstance) + '0';
    intervalVariableName[10] = getSecondDigit(numberOfInstance) + '0';
    intervalVariableName[11] = getThirdDigit(numberOfInstance) + '0';
    intervalVariableName[12] = getFourthDigit(numberOfInstance) + '0';


    // Set phase identifier
    intervalVariableName[14] = phase;


    return intervalVariableName;
}

double createAndSolveModel(std::vector<TaskSet> taskSets, std::vector<TaskChain> taskChains, int numberOfSolutions, std::string logFile, int & status, int & numberOfConstraints, int timeLimit, int maximumInterCoreDelay, bool minimizeResponseTimes)
{
    
    long long int hyperPeriod = 0;

    if (taskSets.at(0).getHyperperiod() != 0 && taskSets.at(1).getHyperperiod() != 0)
    {
        // The hyperperiods of individual task sets
        std::vector<long long int> hyperperiodsOfTaskSets;

        hyperperiodsOfTaskSets.push_back(taskSets.at(0).getHyperperiod());
        hyperperiodsOfTaskSets.push_back(taskSets.at(1).getHyperperiod());

        // The common hyperperiod needs to be considered
        hyperPeriod = findLeastCommonMultiple(hyperperiodsOfTaskSets);
        taskSets.at(0).setHyperperiod(hyperPeriod);
        taskSets.at(1).setHyperperiod(hyperPeriod);
    }

    // Show application being scheduled

    // Show tasks on both cores

    for (int i = 0; i < taskSets.size(); i++)
    {
        std::cout << "Tasks on core " << i << ": "<< std::endl;

        for (int j = 0; j < taskSets.at(i).getTasks().size(); j++)
        {
            std::cout << taskSets.at(i).getTasks().at(j);
        }
    }

    // Show Hyperperiod
    std::cout << std::endl << "Total hyperperiod: " << hyperPeriod << std::endl << std::endl;
     
    // Show Taskchains

    for ( int i = 0; i < taskChains.size(); i++)
    {
        std::cout << "Chain " << i << ": " << std::endl;
        
        std::cout << taskChains.at(i);

    }


    // The initialization of the model
    model = IloModel(environment);

    // The vector that holds the number of task instances for each of the cores
    std::vector<IloInt> numberInstancesCore;
    
    for (IloInt i = 0; i < NUMBER_OF_CORES; i++)
    {
      
        numberInstancesCore.push_back(taskSets.at(i).getInstances().size());
    }
    
    // The Array of interval variables holding interval variables representing all the phases of all the instances
    IloIntervalVarArray allPhasesOfInstances(environment);

    // The vector that holds arrays of interval variables for each of the phases of each of the task instances for each of the cores
    std::vector<IloIntervalVarArray> phasesOfInstancesOnCore;

    // The vector that holds arrays of interval variables for each of the phases of each of the task instances for each of the cores
    std::vector<IloIntervalVarArray> instancesOnCore;


    for (IloInt i = 0; i < NUMBER_OF_CORES; i++)
    {
        // The number of interval variables is equal to the number of task instances for each of the cores multiplied by the number of phases
        phasesOfInstancesOnCore.push_back(IloIntervalVarArray (environment, numberInstancesCore.at(i) * NUMBER_OF_PHASES));
    }

    for (IloInt i = 0; i < NUMBER_OF_CORES; i++)
    {
        // The number of interval variables is equal to the number of task instances for each of the cores multiplied by the number of phases
        instancesOnCore.push_back(IloIntervalVarArray(environment));
    }

    // The variable that holds the total number of interval variables for READ and WRITE phases for all cores
    IloInt totalNumberOfRWPhases = 0;
    
    for (IloInt i = 0; i < NUMBER_OF_CORES; i++)
    {
        // Only READ and WRITE phases are considered
        totalNumberOfRWPhases += numberInstancesCore.at(i) * (NUMBER_OF_PHASES-1);
    }

    // The array that holds interval variables for all READ and WRITE phases
    IloIntervalVarArray ReadAndWriteInstaces(environment, totalNumberOfRWPhases);

    // The variable that holds all helper H variables
    IloIntVarArray helper(environment);

    // The variable that keeps track of the number of interval variables
    IloInt numberOfIntervalVar = 0;

    // The array of Zi expressions
    IloExprArray consumerProducerPairVariablesForConsumerGlobal(environment);

    // The variable that keeps track of the number of interval variables for all READ and WRITE phases
    IloInt numberOfReadAndWriteIntervalVar = 0;

    //Variables used for minimizing response time
    IloExprArray responseTimeDecisionVariables(environment);

    // Array that holds interval variables for extra instances TODO
    std::vector<IloIntervalVarArray> extraWriteInstances;

    for (IloInt i = 0; i < NUMBER_OF_CORES; i++)
    {
        // The number of interval variables is equal to the number of task instances for each of the cores multiplied by the number of phases
        extraWriteInstances.push_back(IloIntervalVarArray(environment));

    }

    std::cout << "CREATING DEICISON INTERVAL VARIABLES FOR TASKS..." << std::endl << std::endl;
    for (IloInt core = 0; core < NUMBER_OF_CORES; core++)
    {
        for (IloInt i = 0; i < numberInstancesCore.at(core); i++)
        {
            TaskInstance currentInstance = taskSets.at(core).getInstances().at(i);


            for (IloInt j = 0; j < NUMBER_OF_PHASES; j++)
            {
                if (j == 0) // Create the interval variable representing the read phase
                {

                    // The start and end point is presented in detail in the master thesis

                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = IloIntervalVar(environment, 0, currentInstance.getTask().getPeriod() * currentInstance.getNumberOfInstance());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setName(createIntervalVariableName(currentInstance.getTask().getTaskId(), currentInstance.getNumberOfInstance(), 'R'));
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setPresent();
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setStartMin(currentInstance.getAbsoluteReleaseTime());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setStartMax(currentInstance.getAbsoluteDeadline() -  currentInstance.getTask().getWorstCaseExecutionTime());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setEndMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setEndMax(currentInstance.getAbsoluteDeadline() - (currentInstance.getTask().getWorstCaseExecute() + currentInstance.getTask().getWorstCaseWrite()));
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setLengthMin(currentInstance.getTask().getWorstCaseRead());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setLengthMax(currentInstance.getTask().getWorstCaseRead());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setSizeMin(currentInstance.getTask().getWorstCaseRead());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setSizeMax(currentInstance.getTask().getWorstCaseRead());

                    // add to appropriate arrays
                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];
                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);
                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);
                    numberOfIntervalVar++;
                    numberOfReadAndWriteIntervalVar++;

                    



                }

                else if (j == 1) // Create the interval variable representing the execute phase
                {
                    // The start and end point is presented in detail in the master thesis

                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = IloIntervalVar(environment, 0, currentInstance.getTask().getPeriod() * currentInstance.getNumberOfInstance());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setName(createIntervalVariableName(currentInstance.getTask().getTaskId(), currentInstance.getNumberOfInstance(), 'E'));
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setPresent();
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setStartMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setStartMax(currentInstance.getAbsoluteDeadline() - (currentInstance.getTask().getWorstCaseExecute() + currentInstance.getTask().getWorstCaseWrite()));
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setEndMin( currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + currentInstance.getTask().getWorstCaseExecute());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setEndMax( currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setLengthMin(currentInstance.getTask().getWorstCaseExecute());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setLengthMax(currentInstance.getTask().getWorstCaseExecute());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setSizeMin(currentInstance.getTask().getWorstCaseExecute());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setSizeMax(currentInstance.getTask().getWorstCaseExecute());

                    // add to appropriate arrays
                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);
                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);


                    numberOfIntervalVar++;
                }

                else // Create the interval variable representing the write phase
                {
                    // The start and end point is presented in detail in the master thesis

                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = IloIntervalVar(environment, 0, currentInstance.getTask().getPeriod() * currentInstance.getNumberOfInstance() );
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setName(createIntervalVariableName(currentInstance.getTask().getTaskId(), currentInstance.getNumberOfInstance(), 'W'));
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setPresent();
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setStartMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() +  taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setStartMax( currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setEndMin( currentInstance.getAbsoluteReleaseTime() +  currentInstance.getTask().getWorstCaseExecutionTime());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setEndMax(currentInstance.getAbsoluteDeadline());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setLengthMin(currentInstance.getTask().getWorstCaseWrite());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setLengthMax(currentInstance.getTask().getWorstCaseWrite());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setSizeMin(currentInstance.getTask().getWorstCaseWrite());
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].setSizeMax(currentInstance.getTask().getWorstCaseWrite());

                    // add to appropriate arrays
                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];

                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    numberOfReadAndWriteIntervalVar++;

                    numberOfIntervalVar++;

                    // If the response time minimization flag is set, create R variables
                    if (minimizeResponseTimes)
                    {
                        responseTimeDecisionVariables.add(IloEndOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]) - currentInstance.getAbsoluteReleaseTime());

                        model.add(responseTimeDecisionVariables[responseTimeDecisionVariables.getSize() - 1] >= 0);
                        model.add(responseTimeDecisionVariables[responseTimeDecisionVariables.getSize() - 1] <= currentInstance.getTask().getPeriod());
                    }

                }


            }

            // Execute phase must not start before read phase

            model.add(IloEndBeforeStart(environment, phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3], phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 2] ));


            // Write phase must not start before execute phase

            model.add(IloEndBeforeStart(environment, phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 2], phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]));

            
            // Add an interval variable representing the entire exectuion of currentInstance
            IloIntervalVar instanceVariable(environment);
            instanceVariable.setPresent();
            instanceVariable.setStartMin(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3].getStartMin());
            instanceVariable.setStartMax(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3].getStartMax());

            instanceVariable.setEndMin(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].getEndMin());
            instanceVariable.setEndMax(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].getEndMax());

            instanceVariable.setLengthMin(currentInstance.getTask().getWorstCaseExecutionTime());
            instanceVariable.setLengthMax(currentInstance.getTask().getPeriod());

            instanceVariable.setSizeMin(currentInstance.getTask().getWorstCaseExecutionTime());
            instanceVariable.setSizeMax(currentInstance.getTask().getPeriod());

            // The instance starts when the corresponding Read Phase starts
            model.add(IloStartOf(instanceVariable) == IloStartOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3]));

            // The instance ends when the corresponding Write Phase ends
            model.add(IloEndOf(instanceVariable) == IloEndOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]));

            // add to appropriate array
            instancesOnCore.at(core).add(instanceVariable);

            // check to see if the instance is part of a chain
            bool isInAnyChain = false;
            for (int chain = 0; chain < taskChains.size(); chain++)
            {
                if (taskChains.at(chain).isInChain(currentInstance.getTask().getTaskId()))
                {
                    isInAnyChain = true;
                    break;
                }
            }

            // Create the final instance of the same task in the previous hyperperiod
            // The first instance of a consumer task in this hyperperiod can potentially communicate with the final instance in the previous hyperperiod
            if (i != numberInstancesCore.at(core) - 1)
            {


                if (taskSets.at(core).getInstances().at(i + 1).getTask().getTaskId() != currentInstance.getTask().getTaskId())
                {
                   
                    
                    if (isInAnyChain)
                    {
                        IloIntervalVar extraInstance(environment);

                        char name[21] = "extraInstanceTau0000";

                        name[16] = getFirstDigit(currentInstance.getTask().getTaskId()) + '0';
                        name[17] = getSecondDigit(currentInstance.getTask().getTaskId()) + '0';
                        name[18] = getThirdDigit(currentInstance.getTask().getTaskId()) + '0';
                        name[19] = getFourthDigit(currentInstance.getTask().getTaskId()) + '0';

                        // The start and end point is presented in detail in the master thesis

                        extraInstance.setName(name);
                        extraInstance.setStartMin(-1 * taskSets.at(core).getHyperperiod());
                        extraInstance.setPresent();
                        extraInstance.setStartMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute() - taskSets.at(core).getHyperperiod());
                        extraInstance.setStartMax(currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite() - taskSets.at(core).getHyperperiod());
                        extraInstance.setEndMin((currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime()) - taskSets.at(core).getHyperperiod());
                        extraInstance.setEndMax(0);
                        extraInstance.setLengthMin(currentInstance.getTask().getWorstCaseWrite());
                        extraInstance.setLengthMax(currentInstance.getTask().getWorstCaseWrite());
                        extraInstance.setSizeMin(currentInstance.getTask().getWorstCaseWrite());
                        extraInstance.setSizeMax(currentInstance.getTask().getWorstCaseWrite());

                        // add to appropriate arrays
                        extraWriteInstances.at(core).add(extraInstance);

                        model.add(IloStartOf(extraInstance) == IloStartOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]) - taskSets.at(core).getHyperperiod());
                    }


                }
            }

            else
            {

                if (isInAnyChain)
                {
                    IloIntervalVar extraInstance(environment);


                    char name[21] = "extraInstanceTau0000";

                    name[16] = getFirstDigit(currentInstance.getTask().getTaskId()) + '0';
                    name[17] = getSecondDigit(currentInstance.getTask().getTaskId()) + '0';
                    name[18] = getThirdDigit(currentInstance.getTask().getTaskId()) + '0';
                    name[19] = getFourthDigit(currentInstance.getTask().getTaskId()) + '0';


                    // The start and end point is presented in detail in the master thesis

                    extraInstance.setName(name);
                    extraInstance.setStartMin(-1 * taskSets.at(core).getHyperperiod());
                    extraInstance.setPresent();
                    extraInstance.setStartMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute() - taskSets.at(core).getHyperperiod());
                    extraInstance.setStartMax(currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite() - taskSets.at(core).getHyperperiod());
                    extraInstance.setEndMin((currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime()) - taskSets.at(core).getHyperperiod());
                    extraInstance.setEndMax(0);
                    extraInstance.setLengthMin(currentInstance.getTask().getWorstCaseWrite());
                    extraInstance.setLengthMax(currentInstance.getTask().getWorstCaseWrite());
                    extraInstance.setSizeMin(currentInstance.getTask().getWorstCaseWrite());
                    extraInstance.setSizeMax(currentInstance.getTask().getWorstCaseWrite());

                    // add to appropriate arrays
                    extraWriteInstances.at(core).add(extraInstance);

                    model.add(IloStartOf(extraInstance) == IloStartOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]) - taskSets.at(core).getHyperperiod());
                }

            }

        }
        numberOfIntervalVar = 0;
    }

    // Interval variables that correspond to phases of tasks instances should not overlap on each of the cores individually
    for (IloInt i = 0; i < NUMBER_OF_CORES; i++)
    {
        model.add(IloNoOverlap(environment, instancesOnCore.at(i)));
    }
    
    // To avoid crossbar-switch contetion, interval variables that correspond to READ and WRITE phases on all cores should not overlap
    model.add(IloNoOverlap(environment, ReadAndWriteInstaces));

    // Generate new int decision variables zi for task chains and create constraints for them

    // Inititate objective function
    IloExpr objectiveFunction(environment);

    std::cout << "CREATING INT DEICISON VARIABLES FOR TASK CHAINS..." << std::endl << std::endl;

    for (int chain = 0; chain < taskChains.size(); chain++)
    {
        // Chain Hyperperiod
        long long int chainHyperPeriod = taskChains.at(chain).getHyperperiod();

        for (int consumerTaskIndex = 1; consumerTaskIndex < taskChains.at(chain).getTasks().size(); consumerTaskIndex++) // Loop through all of the tasks in the chain except for the first one (has no producers)
        {

            // the consumer
            int consumerTaskId = taskChains.at(chain).getTasks().at(consumerTaskIndex).getTaskId();
            long long int consumerTaskPeriod = taskChains.at(chain).getTasks().at(consumerTaskIndex).getPeriod();
            int consumerCoreAssignedTo = taskChains.at(chain).getTasks().at(consumerTaskIndex).getCoreAssignedTo() - 1;
            long long int consumerExecutionTime = taskChains.at(chain).getTasks().at(consumerTaskIndex).getWorstCaseExecutionTime();
        


            //the producer
            int producerTaskIndex = consumerTaskIndex - 1;
            int producerTaskId = taskChains.at(chain).getTasks().at(producerTaskIndex).getTaskId();
            long long int producerTaskPeriod = taskChains.at(chain).getTasks().at(producerTaskIndex).getPeriod();
            int producerCoreAssignedTo = taskChains.at(chain).getTasks().at(producerTaskIndex).getCoreAssignedTo() - 1;
            long long int producerExecutionTime = taskChains.at(chain).getTasks().at(producerTaskIndex).getWorstCaseExecutionTime();

            // Get all instances on producer's core
            std::vector<TaskInstance> instancesOnProducersCore = taskSets.at(producerCoreAssignedTo).getInstances();

            // Get all instances on consumer's core
            std::vector<TaskInstance> instancesOnConsumersCore = taskSets.at(consumerCoreAssignedTo).getInstances();

            for (int consumerInstanceIndex = 0; consumerInstanceIndex < instancesOnConsumersCore.size(); consumerInstanceIndex++) // Loop through all the instances on the consumer's core
            {
                bool firstTime = true;

                //Select only instances of the consumer
                TaskInstance currentInstanceOnConsumersCore = instancesOnConsumersCore.at(consumerInstanceIndex);

                if (currentInstanceOnConsumersCore.getTask().getTaskId() == consumerTaskId)
                {


                    // The right Instance of consumer is selected

                    long long int startOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod;
                    long long int endOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod + consumerTaskPeriod;

                    // Create vector that holds all producer consumer communicating pairs for the current consumer

                    IloExprArray consumerProducerPairVariablesForConsumer(environment);

                    // Check if the interval of consumer overlaps with the interval of first instance of producer
                             
                    for (int producerInstanceIndex = 0; producerInstanceIndex < instancesOnProducersCore.size(); producerInstanceIndex++) // Loop through all the instances on the producer's core
                    {

                        //Select only instances of the producer
                        TaskInstance currentInstanceOnProducersCore = instancesOnProducersCore.at(producerInstanceIndex);
                        if (currentInstanceOnProducersCore.getTask().getTaskId() == producerTaskId)
                        {

                            // The right instance of producer is seletcted

                            if (consumerCoreAssignedTo != producerCoreAssignedTo)
                            {
                                if (intervalsOverlap(0, producerTaskPeriod - producerExecutionTime, startOfConsumer + consumerExecutionTime, endOfConsumer) && firstTime)
                                {
                                    // The communication between the producer from the previous hyperperiod has been added already
                                    firstTime = false;

                                    int lastProducerInstanceIndex = producerInstanceIndex;
                                    while (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() * instancesOnProducersCore.at(lastProducerInstanceIndex).getTask().getPeriod() != taskSets.at(0).getHyperperiod())
                                    {
                                        lastProducerInstanceIndex++;
                                    }

                                    long long int startOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod;
                                    long long int endOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                    int indexOfProducerTaskOnCore = 0;

                                    for (int k = 0; k < taskSets.at(producerCoreAssignedTo).getTasks().size(); k++)
                                    {
                                        if (taskSets.at(producerCoreAssignedTo).getTasks().at(k).getTaskId() == producerTaskId)
                                        {
                                            indexOfProducerTaskOnCore = k;
                                        }
                                    }


                                    // For the extra instances in the previous hyperperiod:

                                    int indexOfExtraInstance = 0;

                                    for (int indexOfExtraWriteInstance = 0; indexOfExtraWriteInstance < extraWriteInstances.at(producerCoreAssignedTo).getSize(); indexOfExtraWriteInstance++)
                                    {

                                        // Create name for compariosn
                                        char name[21] = "extraInstanceTau0000";

                                        name[16] = getFirstDigit(producerTaskId) + '0';
                                        name[17] = getSecondDigit(producerTaskId) + '0';
                                        name[18] = getThirdDigit(producerTaskId) + '0';
                                        name[19] = getFourthDigit(producerTaskId) + '0';

                                        if (name == extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraWriteInstance].getName())
                                        {
                                            indexOfExtraInstance = indexOfExtraWriteInstance;
                                        }
                                    }

                                    // Create Zi constraints as described in the master thesis

                                    IloExpr zi(environment);

                                    zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex]) - (IloEndOf(extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraInstance]));

                                    model.add(zi);

                                    consumerProducerPairVariablesForConsumer.add(zi);

                                    consumerProducerPairVariablesForConsumerGlobal.add(zi);
                                

                                }

                               // Check if the instance of the producer can communicate with the instance of the consumer

                                long long int startOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod;
                                long long int endOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                if (canCommunicate(currentInstanceOnProducersCore, currentInstanceOnConsumersCore))
                                {
                                    long long int lowerBound = startOfConsumer - endOfProducer;
                                    
                                    // Create Zi constraints as described in the master thesis

                                    IloExpr zi(environment);

                                    zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * producerInstanceIndex + 2]);

                                    model.add(zi);

                                    consumerProducerPairVariablesForConsumer.add(zi);

                                    consumerProducerPairVariablesForConsumerGlobal.add(zi);

                                }

                            }
                            
                            
                        }
                        
                    }
                    
                    // Create additional MinusOne helper variable to help with selection
                   IloExpr MinusOne(environment);
                   MinusOne += -1;
                   consumerProducerPairVariablesForConsumer.add(MinusOne);

                    for (int consumerProducerPairIndex = 0; consumerProducerPairIndex < consumerProducerPairVariablesForConsumer.getSize() - 1; consumerProducerPairIndex++)
                    {
                        // Create helper H variable for appropriate Zi expression
                        IloIntVar helperVar(environment, 0, chainHyperPeriod * 4);

                        model.add(helperVar <= (IloAbs(consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) + consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) );
                        
                        std::cout << helperVar << std::endl;

                        // If the following Zi is negative, this is the smallest Zi value, set Hi = Zi
                        model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[(long long int) consumerProducerPairIndex + (long long int)1] < 0, helperVar == (IloAbs(consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) + consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) ));
                        // If the following Zi is positive, this is still not the smallest Zi value, set Hi = 0
                        model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[(long long int) consumerProducerPairIndex + (long long int)1] >= 0, helperVar == 0));

                        helper.add(helperVar);

                    }
                    
                }
    
            }
        }

    }

    std::cout << "Objective Function" << std::endl;

    objectiveFunction = IloSum(helper) / 2;

    std::cout << objectiveFunction << std::endl;

    // Multiobjective function

        // if a maximum inter core delay is set
        if (maximumInterCoreDelay != -1)
        {

            model.add(objectiveFunction <= maximumInterCoreDelay);

            IloObjective objective = IloMinimize(environment, objectiveFunction);

            std::cout << objective.getExpr() << std::endl;

            model.add(objective);

        }
        else
        {
            /* if the response tiems should be minimized as well
            a multi objective function is created
            first the sum of helper variables is minimized
            second among schedules with minimized helper variables
            response time variables are minimized as well */
            if (minimizeResponseTimes)
            {
                // The response times function for minimization
                IloExpr responseTimes = IloSum(responseTimeDecisionVariables);

                model.add(responseTimes >= 0);

                IloObjective responsePlusInterCore = IloMinimize(environment, IloStaticLex(environment, objectiveFunction, responseTimes));

                model.add(responsePlusInterCore);
            }
            else
            {
                model.add(objectiveFunction >= 0);

                IloObjective objective = IloMinimize(environment, objectiveFunction);

                model.add(objective);
            }

 
        }

        // Create the constraint programming problem
        IloCP cp(model);

        cp.setParameter(IloCP::SearchType, IloCP::Auto);

        // allow cp optimizer more time to infer about the next solution
        cp.setParameter(IloCP::DefaultInferenceLevel, IloCP::Extended);

        cp.setParameter(IloCP::Presolve, IloCP::On);

        cp.setParameter(IloCP::TimeLimit, timeLimit);

        cp.setParameter(IloCP::LogVerbosity, IloCP::Verbose);

        
        // Output in log file
        std::ofstream LogFile(logFile);
        cp.setOut(LogFile);

        // Log tasks on both cores

        for (int i = 0; i < taskSets.size(); i++)
        {
            cp.out() << "Tasks on core " << i << ": " << std::endl;

            for (int j = 0; j < taskSets.at(i).getTasks().size(); j++)
            {
                cp.out() << taskSets.at(i).getTasks().at(j);
            }
        }

        // Log Hyperperiod
        cp.out() << std::endl << "Total hyperperiod: " << hyperPeriod << std::endl << std::endl;

        // Log Taskchains

        for (int i = 0; i < taskChains.size(); i++)
        {
            cp.out() << "Chain " << i << ": " << std::endl;

            cp.out() << taskChains.at(i);

        }

        // Initialize time
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point end;

        if (cp.solve())
        {
            std::cout << cp.getTime() << std::endl;

            end = std::chrono::steady_clock::now();
            if (cp.getStatus() == IloAlgorithm::Optimal)
            {
                status = 0;
            } 
            else
            {
                status = 1;
            }
                
       
            for (IloInt core = 0; core < NUMBER_OF_CORES; core++)
            {
                bool first = true;

                for (IloInt i = 0; i < numberInstancesCore.at(core) * NUMBER_OF_PHASES; i++)
                {
                    if (first)
                    {
                        first = false;

                        cp.out() << "************ CORE " << core << " ************" << std::endl;
                    }

                    cp.out() << cp.domain(phasesOfInstancesOnCore.at(core)[i]) << std::endl;

                }

            }

            bool first = true;
            for (IloInt i = 0; i < consumerProducerPairVariablesForConsumerGlobal.getSize(); i++)
            {
                if (first)
                {
                    first = false;

                    cp.out() << "************ Z_i: " << " ************" << std::endl;
                }

                cp.out() << consumerProducerPairVariablesForConsumerGlobal[i] << ": " << cp.getValue(consumerProducerPairVariablesForConsumerGlobal[i]) << std::endl;

            }

            first = true;
            for (IloInt i = 0; i < responseTimeDecisionVariables.getSize(); i++)
            {
                if (first)
                {
                    first = false;

                    cp.out() << "************ responseTimes: " << " ************" << std::endl;
                }

                cp.out() << i << ": " << cp.getValue(responseTimeDecisionVariables[i]) << std::endl;

            }

            first = true;
            for (IloInt i = 0; i < helper.getSize(); i++)
            {
                if (first)
                {
                    first = false;

                    cp.out() << "************ helper: " << " ************" << std::endl;
                }

                cp.out() << i << ": " << cp.getValue(helper[i]) << std::endl;

            }

        }

        else
        {
            end = std::chrono::steady_clock::now();
            cp.out() << "Model has no solution." << std::endl;
                status = -1;
        }
            
            
        std::cout << "DONE!" << std::endl;

        numberOfConstraints = cp.getInfo(IloCP::NumberOfConstraints);

        cp.end();

        return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}
