#include "Model.h"


void initializeEnviroment(void)
{
	environment = IloEnv();
}

char* createIntervalVariableName(int taskID, int numberOfInstance, char phase)
{
    // The default name of interval variable: tau taskID instanceNumber phaseIdentifier
    char defaultIntervalVariableName[14] = "tau 000 000 X";

    char intervalVariableName[14];
    strcpy_s(intervalVariableName, defaultIntervalVariableName);

    // Set taskID
    intervalVariableName[4] = getFirstDigit(taskID) + '0';
    intervalVariableName[5] = getSecondDigit(taskID) + '0';
    intervalVariableName[6] = getThirdDigit(taskID) + '0';

    // Set instanceNumber
    intervalVariableName[8] = getFirstDigit(numberOfInstance) + '0';
    intervalVariableName[9] = getSecondDigit(numberOfInstance) + '0';
    intervalVariableName[10] = getThirdDigit(numberOfInstance) + '0';

    // Set phase identifier
    intervalVariableName[12] = phase;


    return intervalVariableName;
}

double createAndSolveModel(std::vector<TaskSet> taskSets, std::vector<TaskChain> taskChains, int numberOfSolutions, std::string logFile, int & status,int maximumInterCoreDelay, bool minimizeResponseTimes)
{
    
    long long int hyperPeriod = 0;

    // The common hyperperiod needs to be considered
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

    // Show application being scheduled


    for (int i = 0; i < taskSets.size(); i++)
    {
        std::cout << "Tasks on core " << i << ": "<< std::endl;

        for (int j = 0; j < taskSets.at(i).getTasks().size(); j++)
        {
            std::cout << taskSets.at(i).getTasks().at(j);
        }
    }

    std::cout << "Total hyperperiod: " << hyperPeriod/1000000000 << std::endl;
     
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
    
    //std::cout << "Na coru 0: " << numberInstancesCore[0] << " Na coru 1: " << numberInstancesCore[1] << std::endl;
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

    IloIntVarArray helper(environment);


    //IloIntervalVarArray phasesOfInstancesOnAllCores(environment, (numberInstancesCore.at(0) + numberInstancesCore.at(1)) * NUMBER_OF_PHASES);


    // The variable that keeps track of the number of interval variables
    IloInt numberOfIntervalVar = 0;

    IloIntVarArray consumerProducerPairVariablesForConsumerGlobal(environment);


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
                if (j == 0)
                {
                    //std::cout << "OVO STO SAD HOCU: " << currentInstance.getTask().getPeriod() * currentInstance.getNumberOfInstance() << std::endl;
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

                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];

                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);


                    std::cout << "R: " << phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] << std::endl;
                    //ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];


                    // Add the read instance to decision variables

                    //phasesOfInstancesOnAllCores.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);
                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);
                    numberOfIntervalVar++;
                    numberOfReadAndWriteIntervalVar++;

                    



                }

                else if (j == 1)
                {

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

                    // Constraints ordering interval variables that correspond to READ and EXECUTE phases
                    // Nonpreemptive scheduler, all phases of instance must be executed in order
                    std::cout << "E: " << phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] << std::endl;


                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

   

                    //phasesOfInstancesOnAllCores.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);
                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);


                    numberOfIntervalVar++;
                }

                else
                {

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

                    // Constraints ordering interval variables that correspond to EXECUTE and WRITE phases
                    // Nonpreemptive scheduler, all phases of instance must be executed in order
                    //model.add(IloStartAtEnd(environment, phasesOfInstancesOnCore.at(core)[numberOfIntervalVar], phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1], 0));

                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    if (minimizeResponseTimes)
                    {
                        responseTimeDecisionVariables.add(IloEndOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]) - currentInstance.getAbsoluteReleaseTime());

                        model.add(responseTimeDecisionVariables[responseTimeDecisionVariables.getSize() - 1] >= 0);
                        model.add(responseTimeDecisionVariables[responseTimeDecisionVariables.getSize() - 1] <= currentInstance.getTask().getPeriod());
                    }


                    std::cout << "W: " << phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] << std::endl;

                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];

                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    numberOfReadAndWriteIntervalVar++;

                    //phasesOfInstancesOnAllCores.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);


                    numberOfIntervalVar++;
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

            std::cout << "Entire instance: " << instanceVariable;
            // The instance starts when the corresponding Read Phase starts
            model.add(IloStartOf(instanceVariable) == IloStartOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3]));
            // The instance ends when the corresponding Write Phase ends
            model.add(IloEndOf(instanceVariable) == IloEndOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]));



            instancesOnCore.at(core).add(instanceVariable);

            bool isInAnyChain = false;
            for (int chain = 0; chain < taskChains.size(); chain++)
            {
                if (taskChains.at(chain).isInChain(currentInstance.getTask().getTaskId()))
                {
                    isInAnyChain = true;
                    break;
                }
            }

            if (i != numberInstancesCore.at(core) - 1)
            {


                if (taskSets.at(core).getInstances().at(i + 1).getTask().getTaskId() != currentInstance.getTask().getTaskId())
                {
                   
                    
                    if (isInAnyChain)
                    {
                        IloIntervalVar extraInstance(environment);

                        char name[20] = "extraInstanceTau000";

                        name[16] = getFirstDigit(currentInstance.getTask().getTaskId()) + '0';
                        name[17] = getSecondDigit(currentInstance.getTask().getTaskId()) + '0';
                        name[18] = getThirdDigit(currentInstance.getTask().getTaskId()) + '0';

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

                        std::cout << "Extra Instance: " << extraInstance << std::endl;
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


                    char name[20] = "extraInstanceTau000";

                    name[16] = getFirstDigit(currentInstance.getTask().getTaskId()) + '0';
                    name[17] = getSecondDigit(currentInstance.getTask().getTaskId()) + '0';
                    name[18] = getThirdDigit(currentInstance.getTask().getTaskId()) + '0';

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
                    std::cout << "Extra Instance: " << extraInstance << std::endl;

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
        model.add(IloNoOverlap(environment, phasesOfInstancesOnCore.at(i)));

    }
    
    // To avoid crossbar-switch contetion, interval variables that correspond to READ and WRITE phases on all cores should not overlap
    model.add(IloNoOverlap(environment, ReadAndWriteInstaces));

    // Generate new int decision variables zi for task chains and create constraints for them

    IloExpr objectiveFunction(environment);

    std::cout << "CREATING INT DEICISON VARIABLES FOR TASK CHAINS..." << std::endl << std::endl;

    for (int chain = 0; chain < taskChains.size(); chain++)
    {
        // Chain Hyperperiod
        long long int chainHyperPeriod = taskChains.at(chain).getHyperperiod();

        //std::cout << "chain: " << chain << " chain hyper period: " << chainHyperPeriod << std::endl << std::endl;


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

            //std::cout << "producerCoreAssignedTo: " << producerCoreAssignedTo << std::endl;

            //std::cout << "producerCoreAssignedTo: " << consumerCoreAssignedTo << std::endl;

            // Get all instances on producer's core
            std::vector<TaskInstance> instancesOnProducersCore = taskSets.at(producerCoreAssignedTo).getInstances();

            // Get all instances on consumer's core
            std::vector<TaskInstance> instancesOnConsumersCore = taskSets.at(consumerCoreAssignedTo).getInstances();



            for (int consumerInstanceIndex = 0; consumerInstanceIndex < instancesOnConsumersCore.size(); consumerInstanceIndex++) // Loop through all the instances on the consumer's core
            {
                bool firstTime = true;

                //Select only instances of the consumer
                //std::cout << "consumerInstanceIndex: " << consumerInstanceIndex << std::endl;
                TaskInstance currentInstanceOnConsumersCore = instancesOnConsumersCore.at(consumerInstanceIndex);

                if (currentInstanceOnConsumersCore.getTask().getTaskId() == consumerTaskId)
                {


                    // The right Instance of consumer is selected

                    long long int startOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod;
                    long long int endOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod + consumerTaskPeriod;

                    //std::cout << "Consumer: " << consumerTaskId << " [" << startOfConsumer << ", " << endOfConsumer << "]" << std::endl << std::endl;


                    // Create vector that holds all producer consumer communicating pairs for the current consumer

                    IloExprArray consumerProducerPairVariablesForConsumer(environment);

                    // Create vector that holds helper variables



                    // Check if the interval of consumer overlaps with the interval of first instance of producer
                             
                    for (int producerInstanceIndex = 0; producerInstanceIndex < instancesOnProducersCore.size(); producerInstanceIndex++) // Loop through all the instances on the producer's core
                    {

                        //Select only instances of the producer
                        TaskInstance currentInstanceOnProducersCore = instancesOnProducersCore.at(producerInstanceIndex);
                        if (currentInstanceOnProducersCore.getTask().getTaskId() == producerTaskId)
                        {

                            // The right instance of producer is seletcted

                            // TODO: check if this condition is fine
                            //std::cout << "PRVI PUT: " << "a: " << 0 << " b: " << producerTaskPeriod << " c: " << startOfConsumer << " d: " << endOfConsumer << std::endl;

                            if (consumerCoreAssignedTo != producerCoreAssignedTo)
                            {
                                if (intervalsOverlap(0, producerTaskPeriod - producerExecutionTime, startOfConsumer + consumerExecutionTime, endOfConsumer) && firstTime)
                                {
                                    // The communication between the producer from the previous hyperperiod has been added already
                                    firstTime = false;

                                    //IloIntVar producerConsumerPairFirst(environment, -hyperPeriod, hyperPeriod);

                                    int lastProducerInstanceIndex = producerInstanceIndex;
                                    while (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() * instancesOnProducersCore.at(lastProducerInstanceIndex).getTask().getPeriod() != taskSets.at(0).getHyperperiod())
                                    {
                                        lastProducerInstanceIndex++;
                                    }

                                    long long int startOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod;
                                    long long int endOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                    // If the intervals overlap add an extra constraint for the producer instance in the previous hyperperiod
                                    // TODO: chehck 10_4
                                    //model.add(producerConsumerPairFirst == ( IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - ( IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * lastProducerInstanceIndex + 2]) - taskSets.at(0).getHyperperiod() ) ) );

                                    //std::cout << "consumerProducer" << consumerProducerPairVariablesForConsumer.getSize() << " = " << std::endl << std::endl;

                                    //std::cout << "Producer: " << producerTaskId << " [" << startOfLastProducer - taskSets.at(0).getHyperperiod() << ", " << endOfLastProducer - taskSets.at(0).getHyperperiod() << "]" << std::endl << std::endl;


                                    /*consumerProducerPairVariablesForConsumer.add((IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - (IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * lastProducerInstanceIndex + 2]) - taskSets.at(0).getHyperperiod())));
                                    model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] <= endOfConsumer - startOfLastProducer + taskSets.at(0).getHyperperiod() - producerExecutionTime);
                                    model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] >= 0);
                                    */
                                    int indexOfProducerTaskOnCore = 0;

                                    for (int k = 0; k < taskSets.at(producerCoreAssignedTo).getTasks().size(); k++)
                                    {
                                        if (taskSets.at(producerCoreAssignedTo).getTasks().at(k).getTaskId() == producerTaskId)
                                        {
                                            indexOfProducerTaskOnCore = k;
                                        }
                                    }

                                    //std::cout << "start of last producer: " << startOfLastProducer;
                                    /*
                                    IloIntVar consumerProducerPairVariable(environment, 0, (long long int)(endOfConsumer - consumerExecutionTime) - (startOfLastProducer + producerExecutionTime) + hyperPeriod);

                                    char name[32] = "producer000_-000consumer000_000";

                                    name[8] = getFirstDigit(producerTaskId) + '0';
                                    name[9] = getSecondDigit(producerTaskId) + '0';
                                    name[10] = getThirdDigit(producerTaskId) + '0';

                                    name[13] = getFirstDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';
                                    name[14] = getSecondDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';
                                    name[15] = getThirdDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';

                                    name[24] = getFirstDigit(consumerTaskId) + '0';
                                    name[25] = getSecondDigit(consumerTaskId) + '0';
                                    name[26] = getThirdDigit(consumerTaskId) + '0';

                                    name[28] = getFirstDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';
                                    name[29] = getSecondDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';
                                    name[30] = getThirdDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';

                                    consumerProducerPairVariable.setName(name);
                                    */

                                    int indexOfExtraInstance = 0;

                                    for (int indexOfExtraWriteInstance = 0; indexOfExtraWriteInstance < extraWriteInstances.at(producerCoreAssignedTo).getSize(); indexOfExtraWriteInstance++)
                                    {

                                        char name[20] = "extraInstanceTau000";

                                        name[16] = getFirstDigit(producerTaskId) + '0';
                                        name[17] = getSecondDigit(producerTaskId) + '0';
                                        name[18] = getThirdDigit(producerTaskId) + '0';
                                        if (name == extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraWriteInstance].getName())
                                        {
                                            indexOfExtraInstance = indexOfExtraWriteInstance;
                                        }
                                    }

                                    IloExpr zi(environment);

                                    zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - (IloEndOf(extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraInstance]));

                                    model.add(zi);

                                    consumerProducerPairVariablesForConsumer.add(zi);

                                    //consumerProducerPairVariablesForConsumer.add(consumerProducerPairVariable);
                                   
                                    //std::cout << "CONSUMERPRODUCER" << (IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - (IloEndOf(extraWriteInstances.at(producerCoreAssignedTo)[indexOfProducerTaskOnCore]))) << std::endl;
                                    //consumerProducerPairVariablesForConsumerGlobal.add(consumerProducerPairVariable);


                                    //model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] <= (endOfConsumer - consumerExecutionTime) - (startOfLastProducer + producerExecutionTime - hyperPeriod) );
                                    //model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] >= 0);

                                    std::cout << zi << std::endl;

                                }

                                // New interval variable for communicating pairs-

                                //IloIntVar producerConsumerPair(environment, -hyperPeriod, hyperPeriod);

                               // Check if the instance of the producer can communicate with the instance of the consumer

                                long long int startOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod;
                                long long int endOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                if (canCommunicate(currentInstanceOnProducersCore, currentInstanceOnConsumersCore))
                                {
                                    long long int lowerBound = startOfConsumer - endOfProducer;
                                    //if (lowerBound > 0) lowerBound = 0;

                                    /*
                                    IloIntVar consumerProducerPairVariable(environment, lowerBound, endOfConsumer - startOfProducer - producerExecutionTime - consumerExecutionTime);

                                    char name[31] = "producer000_000consumer000_000";

                                    name[8] = getFirstDigit(producerTaskId) + '0';
                                    name[9] = getSecondDigit(producerTaskId) + '0';
                                    name[10] = getThirdDigit(producerTaskId) + '0';

                                    name[12] = getFirstDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';
                                    name[13] = getSecondDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';
                                    name[14] = getThirdDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';

                                    name[23] = getFirstDigit(consumerTaskId) + '0';
                                    name[24] = getSecondDigit(consumerTaskId) + '0';
                                    name[25] = getThirdDigit(consumerTaskId) + '0';

                                    name[27] = getFirstDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';
                                    name[28] = getSecondDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';
                                    name[29] = getThirdDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';

                                    consumerProducerPairVariable.setName(name);
                                    */

                                    IloExpr zi(environment);

                                    zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * producerInstanceIndex + 2]);

                                    model.add(zi);

                                    consumerProducerPairVariablesForConsumer.add(zi);

                                    //consumerProducerPairVariablesForConsumerGlobal.add(consumerProducerPairVariable);

                                    //consumerProducerPairVariablesForConsumer.add((IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * producerInstanceIndex + 2])));
                                    //model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] <= endOfConsumer - startOfProducer - producerExecutionTime - consumerExecutionTime);
                                    //model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] >= startOfConsumer  - endOfProducer);

                                    //std::cout << "Producer-Consumer Pair" << producerConsumerPair << std::endl << std::endl;

                                    std::cout << zi << std::endl;
                                }

                                /*
                                //If producer comes before consumer
                                if (startOfProducer <= startOfConsumer)
                                {
                                    std::cout << "a: " << startOfProducer + producerTaskPeriod - producerExecutionTime - consumerExecutionTime << " b: " << endOfProducer + producerTaskPeriod - producerExecutionTime - consumerExecutionTime << " c: " << startOfConsumer << " d: " << endOfConsumer << std::endl;
                                    if (intervalsOverlap(startOfProducer - producerExecutionTime - consumerExecutionTime, endOfProducer + producerTaskPeriod - producerExecutionTime - consumerExecutionTime, startOfConsumer, endOfConsumer))
                                    {


                                        // If the intervals overlap the producer/consumer pair can communicate and Zi constraint is introduced
                                        //model.add(producerConsumerPair == ( IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * producerInstanceIndex + 2]) ) );
                                        //std::cout << "consumerProducer" << consumerProducerPairVariablesForConsumer.getSize() << " = " << std::endl << std::endl;

                                        //std::cout << "Producer: " << producerTaskId << " [" << startOfProducer << ", " << endOfProducer << "]" << std::endl << std::endl;

                                        long long int lowerBound = startOfConsumer - endOfProducer;
                                        //if (lowerBound > 0) lowerBound = 0;

                                        IloIntVar consumerProducerPairVariable(environment, lowerBound, endOfConsumer - startOfProducer - producerExecutionTime - consumerExecutionTime);

                                        char name[31] = "producer000_000consumer000_000";

                                        name[8] = getFirstDigit(producerTaskId) + '0';
                                        name[9] = getSecondDigit(producerTaskId) + '0';
                                        name[10] = getThirdDigit(producerTaskId) + '0';

                                        name[12] = getFirstDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';
                                        name[13] = getSecondDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';
                                        name[14] = getThirdDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';

                                        name[23] = getFirstDigit(consumerTaskId) + '0';
                                        name[24] = getSecondDigit(consumerTaskId) + '0';
                                        name[25] = getThirdDigit(consumerTaskId) + '0';

                                        name[27] = getFirstDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';
                                        name[28] = getSecondDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';
                                        name[29] = getThirdDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';

                                        consumerProducerPairVariable.setName(name);

                                        model.add(consumerProducerPairVariable == (IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * producerInstanceIndex + 2])));
                                        consumerProducerPairVariablesForConsumer.add(consumerProducerPairVariable);
                                        consumerProducerPairVariablesForConsumerGlobal.add(consumerProducerPairVariable);

                                        //consumerProducerPairVariablesForConsumer.add((IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * producerInstanceIndex + 2])));
                                        //model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] <= endOfConsumer - startOfProducer - producerExecutionTime - consumerExecutionTime);
                                        //model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] >= startOfConsumer  - endOfProducer);

                                        //std::cout << "Producer-Consumer Pair" << producerConsumerPair << std::endl << std::endl;

                                        std::cout << consumerProducerPairVariable << std::endl;

                                    }
                                }
                                else // If producer starts after consumer
                                {
                                    if (intervalsOverlap(startOfProducer + producerExecutionTime, endOfProducer, startOfConsumer, endOfConsumer - consumerExecutionTime))
                                    {

                                        // If the intervals overlap the producer/consumer pair can communicate and Zi constraint is introduced
                                        //model.add(producerConsumerPair == ( IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * producerInstanceIndex + 2]) ) );
                                        //std::cout << "consumerProducer" << consumerProducerPairVariablesForConsumer.getSize() << " = " << std::endl << std::endl;

                                        //std::cout << "Producer: " << producerTaskId << " [" << startOfProducer << ", " << endOfProducer << "]" << std::endl << std::endl;

                                        long long int lowerBound = startOfConsumer - endOfProducer;
                                        //if (lowerBound > 0) lowerBound = 0;
                                        IloIntVar consumerProducerPairVariable(environment, lowerBound, endOfConsumer - startOfProducer - producerExecutionTime - consumerExecutionTime);

                                        char name[31] = "producer000_000consumer000_000";
                                        name[8] = getFirstDigit(producerTaskId) + '0';
                                        name[9] = getSecondDigit(producerTaskId) + '0';
                                        name[10] = getThirdDigit(producerTaskId) + '0';

                                        name[12] = getFirstDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';
                                        name[13] = getSecondDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';
                                        name[14] = getThirdDigit(currentInstanceOnProducersCore.getNumberOfInstance()) + '0';

                                        name[23] = getFirstDigit(consumerTaskId) + '0';
                                        name[24] = getSecondDigit(consumerTaskId) + '0';
                                        name[25] = getThirdDigit(consumerTaskId) + '0';

                                        name[27] = getFirstDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';
                                        name[28] = getSecondDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';
                                        name[29] = getThirdDigit(currentInstanceOnConsumersCore.getNumberOfInstance()) + '0';

                                        consumerProducerPairVariable.setName(name);

                                        model.add(consumerProducerPairVariable == (IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * producerInstanceIndex + 2])));
                                        consumerProducerPairVariablesForConsumer.add(consumerProducerPairVariable);
                                        consumerProducerPairVariablesForConsumerGlobal.add(consumerProducerPairVariable);


                                        //consumerProducerPairVariablesForConsumer.add((IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[NUMBER_OF_PHASES * producerInstanceIndex + 2])));
                                        //model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] <= endOfConsumer - startOfProducer - producerExecutionTime - consumerExecutionTime);
                                        //model.add(consumerProducerPairVariablesForConsumer[consumerProducerPairVariablesForConsumer.getSize() - 1] >= startOfConsumer - endOfProducer);

                                        std::cout << consumerProducerPairVariable << std::endl;

                                        //std::cout << "Producer-Consumer Pair" << producerConsumerPair << std::endl << std::endl;


                                    }

                                   
                                }

                                */
                            }
                            
                            
                        }
                        
                    }
                    
                   IloExpr MinusOne(environment);
                   MinusOne += -1;
                   //model.add(MinusOne == -1);
                   consumerProducerPairVariablesForConsumer.add(MinusOne);

                   //std::cout << "IMA IH: " << consumerProducerPairVariablesForConsumer.getSize() << std::endl;

                    for (int consumerProducerPairIndex = 0; consumerProducerPairIndex < consumerProducerPairVariablesForConsumer.getSize() - 1; consumerProducerPairIndex++)
                    {
                        IloIntVar helperVar(environment, 0, chainHyperPeriod * 4);

                        model.add(helperVar <= (IloAbs(consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) + consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) );
                        //model.add(helperVar >= 0);

                      
                        /*
                        char name[38] = "helper_producer000_000consumer000_000";

                        for (int k = 7; k < 38; k++)
                        {
                            name[k] = consumerProducerPairVariablesForConsumer[consumerProducerPairIndex].getName()[k - 7];
                        }

                        helperVar.setName(name);
                        */
 
                        
                        std::cout << helperVar << std::endl;


                        //std::cout << " ULAZIMO ZA: " << consumerProducerPairVariablesForConsumer[consumerProducerPairIndex];
                        
                        // Helper variable that is equal to zero if producer and consumer are communicating, otherwise it is equal to 1
                        
                        //model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex] < 0, helperVar == 0));

                        //model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int)1] < 0, helper.add((IloAbs(consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) + consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) / 2)));

                        model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int)1] < 0, helperVar == (IloAbs(consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) + consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]) ));
                        model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int)1] >= 0, helperVar == 0));
                        
                        
                        /*if(consumerProducerPairIndex == consumerProducerPairVariablesForConsumer.getSize() - 2)
                        {
                            model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int)1] > 0, helperVar == consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int)1]));
                        }*/

                        /*
                        // Check if first is smallest or not
                        if (consumerProducerPairIndex == 0)
                        {
                            std::cout << "FIRST NTIIIIIII ZAA" << std::endl;

                            model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex] >= 0 && consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int) 1] < 0, helperVar == consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]));
                            //model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex] >= 0 && consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int) 1] >= 0, helperVar == 0));

                        }

                        // Check if last is smallest
                        if (consumerProducerPairIndex == consumerProducerPairVariablesForConsumer.getSize() - 1 )
                        {
                            std::cout << "LAST NTIIIIIII ZAA" << std::endl;
                            model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex] >= 0, helperVar == consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]));
                        }

                        // Check for middle ones
                        if (consumerProducerPairIndex > 1 && consumerProducerPairIndex < consumerProducerPairVariablesForConsumer.getSize() - 1)
                        {
     
                            std::cout << "MIDDLE NTIIIIIII ZAA" << std::endl;

                            model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex] >= 0 && consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int) 1] < 0, helperVar == consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]));

                            //model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex] >= 0 && consumerProducerPairVariablesForConsumer[consumerProducerPairIndex - (int) 1] >= 0 && consumerProducerPairVariablesForConsumer[consumerProducerPairIndex + (int) 1] >= 0, helperVar == 0));
                        }
                        */

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

        if (maximumInterCoreDelay != -1)
        {

            model.add(objectiveFunction >= 0);

            //model.add(objectiveFunction <= maximumInterCoreDelay);

            IloObjective objective = IloMinimize(environment, objectiveFunction);

            std::cout << objective.getExpr() << std::endl;

            model.add(objective);

        }
        else
        {
            
            if (minimizeResponseTimes)
            {

                //model.add(objectiveFunction >= 560);

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


        IloSearchPhaseArray arrayOfPhases(environment);

        IloSearchPhase phase1(environment, allPhasesOfInstances);

        IloSearchPhase phase2(environment, instancesOnCore.at(0));

        IloSearchPhase phase3(environment, instancesOnCore.at(1));

        IloSearchPhase phase4(environment, helper);

        //arrayOfPhases.add(phase4);
        arrayOfPhases.add(phase3);
        arrayOfPhases.add(phase3);


        //cp.setSearchPhases(arrayOfPhases);

        cp.setParameter(IloCP::SearchType, IloCP::Auto);

        //cp.setParameter(IloCP::RestartFailLimit, 300);
        //cp.setParameter(IloCP::RestartGrowthFactor, 1.5);

        //cp.setParameter(IloCP::FailureDirectedSearch, IloCP::On);


        cp.setParameter(IloCP::Presolve, IloCP::On);

        //cp.setParameter(IloCP::RelativeOptimalityTolerance, 0.000001);

        cp.setParameter(IloCP::TimeLimit, 10);

        cp.setParameter(IloCP::LogVerbosity, IloCP::Verbose);




       
        //Find numberOfSolutions solutions
        //cp.setParameter(IloCP::SolutionLimit, numberOfSolutions);

        
        // begin search

        std::ofstream LogFile(logFile);
        cp.setOut(LogFile);

        //cp.solve();

        //cp.out() << cp.solve();

        //cp.startNewSearch();

       
       //numberOfConstraints = cp.getInfo(IloCP::NumberOfConstraints);

        
        

        //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        
        //print all solutions
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point end;
        
        //while (cp.next()) 
        //{

        if (cp.solve())
        {
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

                cp.out() << consumerProducerPairVariablesForConsumerGlobal[i].getName() << ": " << cp.getValue(consumerProducerPairVariablesForConsumerGlobal[i]) << std::endl;

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

            cp.end();

        return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}
