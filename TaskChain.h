#include<vector>
#include "Task.h"
#include "Helper.h"
#include <iostream>

#pragma once
class TaskChain
{
private:
	std::vector<Task> tasks;
	long long int hyperperiod;


public:
	TaskChain();

	void setHyperperiod(long long int t_hyperperiod);

	std::vector<Task> getTasks();
	long long int getHyperperiod();


	void addTask(Task t_task);
	long long int calculateHyperperiod();

	bool isInChain(long long int taskID);

	friend std::ostream& operator<<(std::ostream& out, const TaskChain& taskChain);

};

