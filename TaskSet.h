#include <iterator> 
#include <vector>
#include "Task.h"
#include "TaskInstance.h"

#define HYPERPERIOD_OF_EMPTY_TASK_SET 0

#pragma once
class TaskSet
{
private:
	std::vector<Task> tasks;
	long long int core;
	long long int hyperperiod;
	std::vector<TaskInstance> instances;


public:

	//CONSTRUCTOR

	TaskSet(long long int t_core);

	//CONSTRUCTOR


	// SETTERS

	void setCore(long long int t_core);
	void setHyperperiod(long long int t_hyperperiod);

	// SETTERS


	// GETTERS
	std::vector<Task> getTasks();
	long long int getCore();
	long long int getHyperperiod();
	std::vector<TaskInstance> getInstances();

	// GETTERS


	// METHODS

	void addTask(Task t_task);

	void removeTask(Task t_task);

	long long int calculateHyperperiod();

	// METHODS
};

