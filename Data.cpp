#include "Data.h"
#include <iostream>

std::vector<TaskSet>  TestCase1(std::vector<TaskChain>& chains)
{
    Task task1(1, 1, 1, 1, 12, 1);
    Task task2(2, 1, 1, 1, 6, 1);
    Task task3(3, 1, 1, 1, 12, 1);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);
    taskSet0.addTask(task3);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;
}

std::vector<TaskSet>  TestCase2(std::vector<TaskChain>& chains)
{

    Task task1(1, 1, 1, 1, 12, 1);
    Task task2(2, 1, 1, 1, 12, 1);
    Task task3(3, 1, 1, 1, 12, 1);
    //Task task4(4, 1, 1, 1, 12, 1);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);


    TaskSet taskSet0(1);

    TaskSet taskSet1(2);

    taskSet0.addTask(task1);
    taskSet0.addTask(task2);
    taskSet0.addTask(task3);
    //taskSet0.addTask(task4);


    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;

}

std::vector<TaskSet>  TestCase3(std::vector<TaskChain>& chains)
{

    Task task1(1, 2, 2, 2, 42, 1);
    Task task2(2, 2, 2, 2, 42, 1);
    Task task3(3, 2, 2, 2, 42, 1);

    Task task4(4, 2, 2, 2, 42, 2);
    Task task5(5, 4, 6, 4, 42, 2);
    Task task6(6, 2, 2, 2, 42, 2);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task5);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);

    taskSet0.addTask(task1);
    taskSet0.addTask(task2);
    taskSet0.addTask(task3);

    taskSet1.addTask(task4);
    taskSet1.addTask(task5);
    taskSet1.addTask(task6);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;

}

std::vector<TaskSet>  TestCase4(std::vector<TaskChain>& chains)
{
    Task task1(1, 1, 1, 1, 6, 1);
    Task task2(2, 1, 1, 1, 12, 1);
    Task task3(3, 1, 1, 1, 24, 1);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);

    chains.push_back(taskChain1);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);


    taskSet0.addTask(task1);
    taskSet0.addTask(task2);
    taskSet0.addTask(task3);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);


    return taskSets;
}

std::vector<TaskSet>  TestCase5(std::vector<TaskChain>& chains)
{
    Task task1(1, 1, 1, 1, 12, 1);
    Task task2(2, 1, 1, 1, 12, 2);
    Task task3(3, 1, 1, 1, 12, 2);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);


    taskSet0.addTask(task1);
    taskSet1.addTask(task2);
    taskSet1.addTask(task3);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);


    return taskSets;
}

std::vector<TaskSet>  TestCase6_1(std::vector<TaskChain>& chains)
{

    Task task1(1, 1, 2, 1, 10, 1);
    Task task2(2, 2, 6, 2, 40, 1);
    Task task3(3, 1, 3, 1, 20, 1);

    Task task4(4, 2, 3, 1, 20, 2);
    Task task5(5, 2, 8, 2, 40, 2);


    TaskSet taskSet0(1);

    TaskSet taskSet1(2);

    taskSet0.addTask(task1);
    taskSet0.addTask(task2);
    taskSet0.addTask(task3);

    taskSet1.addTask(task4);
    taskSet1.addTask(task5);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;

}

std::vector<TaskSet>  TestCase6_2(std::vector<TaskChain>& chains)
{

    Task task1(1, 2, 3, 1, 12, 1);
    Task task2(2, 1, 4, 1, 36, 1);
    Task task3(3, 2, 2, 2, 24, 1);

    Task task4(4, 1, 1, 1, 12, 2);
    Task task5(5, 1, 3, 1, 24, 2);
    Task task6(6, 1, 2, 1, 24, 2);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);

    taskSet0.addTask(task1);
    taskSet0.addTask(task2);
    taskSet0.addTask(task3);

    taskSet1.addTask(task4);
    taskSet1.addTask(task5);
    taskSet1.addTask(task6);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;

}

std::vector<TaskSet>  TestCase6_3(std::vector<TaskChain>& chains)
{


    Task task1(1, 2, 12, 2, 48, 1);
    Task task2(2, 1, 2, 1, 48, 1);
    Task task3(3, 1, 1, 1, 12, 1);

    Task task4(4, 3, 20, 2, 96, 2);
    Task task5(5, 1, 1, 1, 24, 2);
    Task task6(6, 2, 4, 2, 48, 2);
    Task task7(7, 2, 2, 2, 48, 2);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);

    taskSet0.addTask(task1);
    taskSet0.addTask(task2);
    taskSet0.addTask(task3);

    taskSet1.addTask(task4);
    taskSet1.addTask(task5);
    taskSet1.addTask(task6);
    taskSet1.addTask(task7);


    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;

}

std::vector<TaskSet>  TestCase7(std::vector<TaskChain>& chains)
{
    Task task1(1, 1, 0, 1, 6, 1);
    Task task2(2, 1, 0, 1, 12, 1);
    Task task3(3, 1, 0, 1, 6, 1);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);
    taskSet0.addTask(task3);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;
}

std::vector<TaskSet>  TestCase8(std::vector<TaskChain>& chains)
{
    Task task1(1, 1, 0, 1, 5, 1);
    Task task2(2, 1, 1, 1, 8, 1);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);

    chains.push_back(taskChain1);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;
}

std::vector<TaskSet>  TestCase10_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 3, 1, 12, 1);
    Task task2(2, 1, 2, 1, 12, 2);
    Task task3(3, 1, 1, 1, 12, 1);
    
    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task3);

    TaskSet taskSet1(2);

    taskSet1.addTask(task2);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase10_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 16, 1);
    Task task2(2, 1, 1, 1, 16, 1);
    Task task3(3, 1, 2, 1, 16, 2);
    Task task4(4, 1, 1, 1, 16, 2);
    Task task5(5, 1, 1, 1, 16, 1);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task5);

    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase10_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 16, 1);
    Task task2(2, 1, 1, 1, 16, 2);
    Task task3(3, 1, 1, 1, 16, 1);
    Task task4(4, 1, 1, 1, 16, 2);
    Task task5(5, 1, 1, 1, 16, 1);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task3);

    taskSet0.addTask(task5);

    TaskSet taskSet1(2);

    taskSet1.addTask(task2);

    taskSet1.addTask(task4);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase10_4(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 3, 2, 20, 2);
    Task task2(2, 2, 1, 2, 20, 1);
    Task task3(3, 1, 5, 1, 20, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task2);

    TaskSet taskSet1(2);

    taskSet1.addTask(task1);

    taskSet1.addTask(task3);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase10_5(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 3, 1, 100, 1);
    Task task2(2, 2, 2, 1, 100, 1);
    Task task3(3, 1, 2, 1, 100, 2);
    Task task4(4, 1, 1, 1, 100, 1);
    Task task5(5, 1, 5, 2, 100, 2);
    Task task6(6, 1, 2, 1, 100, 2);
    Task task7(7, 1, 2, 2, 100, 2);
    Task task8(8, 1, 1, 1, 100, 1);
    Task task9(9, 1, 2, 1, 100, 2);
    Task task10(10, 1, 2, 1, 100, 1);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);
    taskChain1.addTask(task6);
    taskChain1.addTask(task7);
    taskChain1.addTask(task8);
    taskChain1.addTask(task9);
    taskChain1.addTask(task10);
   

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);
    taskSet0.addTask(task2);
    taskSet0.addTask(task4);
    taskSet0.addTask(task8);
    taskSet0.addTask(task10);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task5);

    taskSet1.addTask(task6);

    taskSet1.addTask(task7);

    taskSet1.addTask(task9);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase11_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 24, 1);
    Task task2(2, 1, 1, 1, 12, 1);
    Task task3(3, 1, 1, 1, 6, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase11_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 100, 1);
    Task task2(2, 1, 1, 1, 50, 1);
    Task task3(3, 1, 1, 1, 20, 1);
    Task task4(4, 1, 0, 1, 10, 2);
    Task task5(5, 1, 0, 1, 5, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase11_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 6, 1);
    Task task2(2, 1, 0, 1, 9, 1);
    Task task3(3, 1, 2, 1, 36, 2);
    Task task4(4, 1, 1, 1, 18, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

   

    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase12_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 8, 1);
    Task task2(2, 1, 0, 1, 7, 2);
    Task task3(3, 1, 0, 1, 6, 1);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task2);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase12_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 3, 2, 13, 1);
    Task task2(2, 1, 2, 1, 15, 2);
    Task task3(3, 1, 3, 1, 17, 2);
    Task task4(4, 1, 2, 1, 19, 2);
    Task task5(5, 1, 1, 1, 21, 1);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task5);
    

    TaskSet taskSet1(2);

    taskSet1.addTask(task2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase12_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 11, 1);
    Task task2(2, 1, 2, 1, 13, 1);
    Task task3(3, 1, 1, 2, 17, 2);
    Task task4(4, 1, 0, 1, 19, 1);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task4);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}



std::vector<TaskSet>  TestCase13_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 3, 1);
    Task task2(2, 1, 0, 1, 24, 1);
    Task task3(3, 1, 0, 1, 12, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase13_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 3, 1);
    Task task2(2, 1, 0, 1, 24, 1);
    Task task3(3, 1, 0, 1, 12, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase13_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 5, 1);
    Task task2(2, 1, 0, 1, 10, 1);
    Task task3(3, 1, 1, 1, 20, 2);
    Task task4(4, 1, 1, 1, 50, 2);
    Task task5(5, 1, 1, 1, 100, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);
    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);
    taskSet1.addTask(task4);
    taskSet1.addTask(task5);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase13_4(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 2, 1, 36, 2);
    Task task2(2, 1, 1, 1, 18, 1);
    Task task3(3, 1, 0, 1, 6, 1);
    Task task4(4, 1, 0, 1, 9, 2);
 


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task2);
    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task1);
    taskSet1.addTask(task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase13_5(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 7, 1);
    Task task2(2, 1, 0, 1, 14, 1);
    Task task3(3, 1, 0, 1, 28, 1);
    Task task4(4, 1, 0, 1, 28, 2);
    Task task5(5, 1, 1, 1, 56, 2);
    Task task6(6, 1, 1, 1, 14, 2);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task4);
    taskChain1.addTask(task6);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);
    taskSet0.addTask(task2);
    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task4);
    taskSet1.addTask(task5);
    taskSet0.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}



std::vector<TaskSet>  TestCase14_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 5, 2, 21, 1);
    Task task2(2, 2, 6, 1, 23, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    TaskSet taskSet1(2);

    taskSet1.addTask(task2);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase14_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 2, 1, 19, 1);
    Task task2(2, 2, 3, 1, 21, 1);
    Task task3(3, 2, 3, 2, 23, 2);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase14_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 7, 1);
    Task task2(2, 1, 0, 1, 9, 1);
    Task task3(3, 1, 0, 1, 11, 2);
    Task task4(4, 1, 0, 1, 13, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase15_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 6, 1);
    Task task2(2, 1, 0, 1, 7, 2);
    Task task3(3, 1, 0, 1, 8, 1);

    

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task2);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase15_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 3, 2, 21, 1);
    Task task2(2, 1, 2, 1, 19, 2);
    Task task3(3, 1, 3, 1, 17, 2);
    Task task4(4, 1, 2, 1, 15, 2);
    Task task5(5, 1, 1, 1, 13, 1);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task5);


    TaskSet taskSet1(2);

    taskSet1.addTask(task2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase15_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 19, 1);
    Task task2(2, 1, 2, 1, 17, 1);
    Task task3(3, 1, 1, 2, 13, 2);
    Task task4(4, 1, 0, 1, 11, 1);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task4);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase16_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 7, 1);
    Task task2(2, 1, 0, 1, 6, 2);
    Task task3(3, 1, 0, 1, 8, 1);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task2);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase16_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 19, 1);
    Task task2(2, 1, 2, 1, 17, 2);
    Task task3(3, 1, 1, 1, 19, 1);
    Task task4(4, 1, 0, 1, 11, 1);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task3);

    taskSet0.addTask(task4);


    TaskSet taskSet1(2);

    taskSet1.addTask(task2);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase17_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 80, 1);
    Task task2(2, 1, 0, 1, 20, 1);
    Task task3(3, 1, 0, 1, 20, 1);
    Task task4(4, 1, 0, 1, 40, 2);
    Task task5(5, 1, 0, 1, 10, 2);
    Task task6(6, 1, 0, 1, 40, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);
    

    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task5);
    taskChain2.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);

    taskSet1.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase17_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 7, 1);
    Task task2(2, 1, 1, 1, 28, 1);
    Task task3(3, 1, 1, 1, 14, 2);
    Task task4(4, 1, 0, 1, 28, 2);
    Task task5(5, 1, 0, 1, 56, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase17_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 100, 1);
    Task task2(2, 1, 0, 1, 100, 1);
    Task task3(3, 1, 0, 1, 50, 1);
    Task task4(4, 1, 1, 1, 200, 1);
    Task task5(5, 1, 0, 1, 25, 1);
    Task task6(6, 1, 1, 1, 50, 1);
    Task task7(7, 1, 0, 1, 20, 1);

    Task task8(8, 1, 2, 1, 50, 2);
    Task task9(9, 0, 1, 1, 20, 2);
    Task task10(10, 1, 1, 1, 200, 2);
    Task task11(11, 1, 0, 1, 25, 2);
    Task task12(12, 1, 1, 1, 100, 2);
    Task task13(13, 1, 2, 1, 200, 2);
    Task task14(14, 1, 0, 1, 50, 2);
    Task task15(15, 1, 1, 1, 100, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task10);
    taskChain1.addTask(task5);

    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task8);
    taskChain2.addTask(task9);
    taskChain2.addTask(task4);


    TaskChain taskChain3;
    taskChain3.addTask(task15);
    taskChain3.addTask(task7);
    taskChain3.addTask(task14);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);

    taskSet0.addTask(task4);

    taskSet0.addTask(task5);

    taskSet0.addTask(task6);

    taskSet0.addTask(task7);


    TaskSet taskSet1(2);

    taskSet1.addTask(task8);

    taskSet1.addTask(task9);

    taskSet1.addTask(task10);

    taskSet1.addTask(task11);

    taskSet1.addTask(task12);

    taskSet1.addTask(task13);

    taskSet1.addTask(task14);

    taskSet1.addTask(task15);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase18_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 7, 1);
    Task task2(2, 1, 0, 1, 8, 1);
    Task task3(3, 1, 0, 1, 9, 1);

    Task task4(4, 0, 1, 0, 7, 2);
    Task task5(5, 1, 0, 1, 8, 2);
    Task task6(6, 1, 0, 1, 9, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task5);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);
    taskChain2.addTask(task6);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);

    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);

    taskSet1.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase19_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 7, 1);
    Task task2(2, 1, 0, 1, 8, 1);
    Task task3(3, 1, 0, 1, 9, 1);

    Task task4(4, 0, 1, 0, 7, 2);
    Task task5(5, 1, 0, 1, 8, 2);
    Task task6(6, 1, 0, 1, 9, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task3);
    taskChain1.addTask(task5);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task6);
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);

    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);

    taskSet1.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase19_2(std::vector<TaskChain>& chains)
{

    // Declare Tasks

    Task task1(1, 0, 1, 0, 8, 1);
    Task task2(2, 1, 0, 1, 7, 1);

    Task task3(3, 0, 1, 0, 6, 2);
    Task task4(4, 1, 0, 1, 9, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);
    taskChain2.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task3);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;

}

std::vector<TaskSet>  TestCase20_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 7, 1);
    Task task2(2, 1, 0, 1, 8, 1);
    Task task3(3, 1, 0, 1, 9, 1);

    Task task4(4, 0, 1, 0, 7, 2);
    Task task5(5, 1, 0, 1, 8, 2);
    Task task6(6, 1, 0, 1, 9, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task6);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task5);
    taskChain2.addTask(task3);
    taskChain2.addTask(task4);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);

    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);

    taskSet1.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase20_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 6, 1);
    Task task2(2, 1, 0, 1, 8, 1);

    Task task3(3, 0, 1, 0, 7, 2);
    Task task4(4, 1, 0, 1, 9, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task3);
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);
    taskChain2.addTask(task1);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase21_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 80, 1);
    Task task2(2, 1, 0, 1, 20, 1);
    Task task3(3, 1, 0, 1, 10, 1);
    Task task4(4, 1, 0, 1, 40, 2);
    Task task5(5, 1, 0, 1, 20, 2);
    Task task6(6, 1, 0, 1, 40, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task5);
    taskChain2.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task4);
    taskSet1.addTask(task5);
    taskSet1.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase21_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 7, 1);
    Task task2(2, 1, 1, 1, 56, 1);
    Task task3(3, 1, 1, 1, 14, 2);
    Task task4(4, 1, 0, 1, 28, 2);
    Task task5(5, 1, 0, 1, 56, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);
    taskChain2.addTask(task1);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase21_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 100, 1);
    Task task2(2, 1, 0, 1, 100, 1);
    Task task3(3, 1, 0, 1, 50, 1);
    Task task4(4, 1, 1, 1, 200, 1);
    Task task5(5, 1, 0, 1, 25, 1);
    Task task6(6, 1, 1, 1, 50, 1);
    Task task7(7, 1, 0, 1, 20, 1);

    Task task8(8, 1, 2, 1, 50, 2);
    Task task9(9, 0, 1, 1, 20, 2);
    Task task10(10, 1, 1, 1, 200, 2);
    Task task11(11, 1, 0, 1, 25, 2);
    Task task12(12, 1, 1, 1, 100, 2);
    Task task13(13, 1, 2, 1, 200, 2);
    Task task14(14, 1, 0, 1, 50, 2);
    Task task15(15, 1, 1, 1, 100, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);
    taskChain1.addTask(task11);
    taskChain1.addTask(task7);

    TaskChain taskChain2;
    taskChain2.addTask(task10);
    taskChain2.addTask(task15);
    taskChain2.addTask(task6);
    taskChain2.addTask(task9);


    TaskChain taskChain3;
    taskChain3.addTask(task14);
    taskChain3.addTask(task5);
    taskChain3.addTask(task9);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);

    taskSet0.addTask(task4);

    taskSet0.addTask(task5);

    taskSet0.addTask(task6);

    taskSet0.addTask(task7);


    TaskSet taskSet1(2);

    taskSet1.addTask(task8);

    taskSet1.addTask(task9);

    taskSet1.addTask(task10);

    taskSet1.addTask(task11);

    taskSet1.addTask(task12);

    taskSet1.addTask(task13);

    taskSet1.addTask(task14);

    taskSet1.addTask(task15);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase22_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 80, 1);
    Task task2(2, 1, 0, 1, 20, 1);
    Task task3(3, 1, 0, 1, 10, 1);
    Task task4(4, 1, 0, 1, 40, 2);
    Task task5(5, 1, 0, 1, 20, 2);
    Task task6(6, 1, 0, 1, 40, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task4);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task5);
    taskChain2.addTask(task1);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);

    taskSet1.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase22_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 7, 1);
    Task task2(2, 1, 1, 1, 56, 1);
    Task task3(3, 1, 1, 1, 14, 2);
    Task task4(4, 1, 0, 1, 28, 2);
    Task task5(5, 1, 0, 1, 56, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase22_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 100, 1);
    Task task2(2, 1, 0, 1, 100, 1);
    Task task3(3, 1, 0, 1, 50, 1);
    Task task4(4, 1, 1, 1, 200, 1);
    Task task5(5, 1, 0, 1, 25, 1);
    Task task6(6, 1, 1, 1, 50, 1);
    Task task7(7, 1, 0, 1, 20, 1);

    Task task8(8, 1, 2, 1, 50, 2);
    Task task9(9, 0, 1, 1, 20, 2);
    Task task10(10, 1, 1, 1, 200, 2);
    Task task11(11, 1, 0, 1, 25, 2);
    Task task12(12, 1, 1, 1, 100, 2);
    Task task13(13, 1, 2, 1, 200, 2);
    Task task14(14, 1, 0, 1, 50, 2);
    Task task15(15, 1, 1, 1, 100, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task7);
    taskChain1.addTask(task11);
    taskChain1.addTask(task3);
    taskChain1.addTask(task1);

    TaskChain taskChain2;
    taskChain2.addTask(task9);
    taskChain2.addTask(task6);
    taskChain2.addTask(task15);
    taskChain2.addTask(task10);


    TaskChain taskChain3;
    taskChain3.addTask(task9);
    taskChain3.addTask(task5);
    taskChain3.addTask(task14);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);

    taskSet0.addTask(task4);

    taskSet0.addTask(task5);

    taskSet0.addTask(task6);

    taskSet0.addTask(task7);


    TaskSet taskSet1(2);

    taskSet1.addTask(task8);

    taskSet1.addTask(task9);

    taskSet1.addTask(task10);

    taskSet1.addTask(task11);

    taskSet1.addTask(task12);

    taskSet1.addTask(task13);

    taskSet1.addTask(task14);

    taskSet1.addTask(task15);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase23_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 6, 1);
    Task task2(2, 1, 0, 1, 7, 1);

    Task task3(3, 0, 1, 0, 8, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);




    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase23_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 6, 1);
    Task task2(2, 0, 0, 1, 7, 1);

    Task task3(3, 0, 1, 0, 8, 2);
    Task task4(4, 1, 0, 1, 9, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task4);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase23_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 6, 1);
    Task task2(2, 1, 0, 1, 7, 1);
    Task task3(3, 1, 0, 1, 8, 1);

    Task task4(4, 0, 1, 0, 9, 2);
    Task task5(5, 1, 0, 1, 10, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);

    TaskChain taskChain3;
    taskChain3.addTask(task3);
    taskChain3.addTask(task5);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);


    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task5);

    taskSet1.addTask(task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase24_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 7, 1);
    Task task2(2, 1, 0, 1, 8, 1);

    Task task3(3, 0, 1, 0, 6, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);




    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase24_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 6, 1);
    Task task2(2, 0, 0, 1, 7, 1);

    Task task3(3, 0, 1, 0, 8, 2);
    Task task4(4, 1, 0, 1, 9, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task1);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase24_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 6, 1);
    Task task2(2, 1, 0, 1, 7, 1);

    Task task3(3, 1, 0, 1, 8, 2);
    Task task4(4, 0, 1, 0, 9, 2);
    Task task5(5, 1, 0, 1, 10, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task4);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);

    TaskChain taskChain3;
    taskChain3.addTask(task5);
    taskChain3.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);


    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);



    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task5);

    taskSet1.addTask(task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase25_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 6, 1);
    Task task2(2, 0, 1, 0, 7, 1);

    Task task3(3, 1, 0, 1, 7, 2);
    Task task4(4, 1, 0, 1, 8, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase25_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 6, 1);
    Task task2(2, 0, 1, 0, 7, 1);
    Task task3(3, 0, 1, 0, 7, 1);

    Task task4(4, 1, 0, 1, 7, 2);
    Task task5(5, 1, 0, 1, 7, 2);
    Task task6(6, 0, 1, 0, 6, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task5);

    TaskChain taskChain3;
    taskChain3.addTask(task5);
    taskChain3.addTask(task6);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);

    taskSet1.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase26_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 40, 1);
    Task task2(2, 1, 0, 1, 20, 1);
    Task task3(3, 1, 0, 1, 20, 1);
    Task task4(4, 1, 0, 1, 40, 2);
    Task task5(5, 1, 0, 1, 20, 2);
    Task task6(6, 1, 0, 1, 40, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task5);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task6);
    taskChain2.addTask(task1);
    taskChain2.addTask(task4);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);


    TaskSet taskSet1(2);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);

    taskSet1.addTask(task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase26_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 1, 56, 1);
    Task task2(2, 1, 1, 1, 56, 1);
    Task task3(3, 1, 1, 1, 56, 2);
    Task task4(4, 1, 0, 1, 56, 2);
    Task task5(5, 1, 0, 1, 14, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);

    taskSet1.addTask(task4);

    taskSet1.addTask(task5);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase26_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 0, 1, 100, 1);
    Task task2(2, 1, 0, 1, 100, 1);
    Task task3(3, 1, 0, 1, 50, 1);
    Task task4(4, 1, 1, 1, 200, 1);
    Task task5(5, 1, 0, 1, 25, 1);
    Task task6(6, 1, 1, 1, 50, 1);
    Task task7(7, 1, 0, 1, 20, 1);

    Task task8(8, 1, 2, 1, 50, 2);
    Task task9(9, 0, 1, 1, 20, 2);
    Task task10(10, 1, 1, 1, 200, 2);
    Task task11(11, 1, 0, 1, 25, 2);
    Task task12(12, 1, 1, 1, 100, 2);
    Task task13(13, 1, 2, 1, 200, 2);
    Task task14(14, 1, 0, 1, 50, 2);
    Task task15(15, 1, 1, 1, 100, 2);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task15);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task6);
    taskChain2.addTask(task14);
    taskChain2.addTask(task8);


    TaskChain taskChain3;
    taskChain3.addTask(task13);
    taskChain3.addTask(task12);
    taskChain3.addTask(task4);
    taskChain3.addTask(task10);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);

    taskSet0.addTask(task3);

    taskSet0.addTask(task4);

    taskSet0.addTask(task5);

    taskSet0.addTask(task6);

    taskSet0.addTask(task7);


    TaskSet taskSet1(2);

    taskSet1.addTask(task8);

    taskSet1.addTask(task9);

    taskSet1.addTask(task10);

    taskSet1.addTask(task11);

    taskSet1.addTask(task12);

    taskSet1.addTask(task13);

    taskSet1.addTask(task14);

    taskSet1.addTask(task15);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase27_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 5, 2, 23, 1);
    Task task2(2, 2, 6, 1, 21, 2);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    TaskSet taskSet1(2);

    taskSet1.addTask(task2);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase27_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 2, 1, 19, 1);
    Task task2(2, 2, 3, 1, 21, 1);
    Task task3(3, 2, 3, 2, 23, 2);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task3);
    taskChain1.addTask(task2);
    taskChain1.addTask(task1);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase28_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 2, 1, 19, 1);
    Task task2(2, 2, 3, 1, 21, 1);
    Task task3(3, 2, 3, 2, 23, 2);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);

    taskSet0.addTask(task2);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase28_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 0, 6, 1);

    Task task3(3, 0, 1, 0, 8, 2);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(1);

    taskSet0.addTask(task1);


    TaskSet taskSet1(2);

    taskSet1.addTask(task3);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

// Industrial Test-Case (Engine Managment System)

std::vector<TaskSet>  TestCaseIndustrial(std::vector<TaskChain>& chains)
{
    Task task1(1, 908, 573000, 25, 1000000000, 1);
    Task task2(2, 958, 2461000, 195, 1000000000, 2);
    Task task3(3, 908, 86000, 28, 50000000, 1);

    Task task4(4, 908, 169000, 55, 50000000, 2);
    Task task5(5, 908, 482000, 55, 50000000, 1);
    Task task6(6, 55, 144000, 28, 100000000, 1);

    Task task7(7, 990, 2892000, 55, 100000000, 2);
    Task task8(8, 1013, 2957000, 83, 100000000, 1);
    Task task9(9, 990, 2892000, 55, 100000000, 2);

    Task task10(10, 1013, 2957000, 83, 100000000, 1);
    Task task11(11, 1148, 3188000, 28, 100000000, 2);
    Task task12(12, 1060, 2269000, 25, 1000000000, 1);
    
    Task task13(13, 988, 677000, 28, 100000000, 1);
    Task task14(14, 965, 19641000, 390, 200000000, 2);
    Task task15(15, 833, 843000, 240, 200000000, 1);

    Task task16(16, 908, 118000, 0, 1000000000, 1);
    Task task17(17, 28, 274000, 28, 1000000000, 1);
    Task task18(18, 985, 1651000, 195, 1000000000, 2);

    TaskChain taskChain1;
    taskChain1.addTask(task5);
    taskChain1.addTask(task6);
    taskChain1.addTask(task7);
    taskChain1.addTask(task8);
    chains.push_back(taskChain1);

    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task9);
    taskChain2.addTask(task11);
    taskChain2.addTask(task13);
    taskChain2.addTask(task18);

    chains.push_back(taskChain2);


    TaskChain taskChain3;
    taskChain3.addTask(task4);
    taskChain3.addTask(task7);
    taskChain3.addTask(task8);

    chains.push_back(taskChain3);

    TaskSet taskSet0(1);

    TaskSet taskSet1(2);


    taskSet0.addTask(task1);
    taskSet0.addTask(task3);
    taskSet0.addTask(task5);
    taskSet0.addTask(task6);
    taskSet0.addTask(task8);
    taskSet0.addTask(task10);
    taskSet0.addTask(task12);
    taskSet0.addTask(task13);
    taskSet0.addTask(task15);
    taskSet0.addTask(task16);
    taskSet0.addTask(task17);

    taskSet1.addTask(task2);
    taskSet1.addTask(task4);
    taskSet1.addTask(task7);
    taskSet1.addTask(task9);
    taskSet1.addTask(task14);
    taskSet1.addTask(task18);
    taskSet1.addTask(task11);



    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);


    return taskSets;
}