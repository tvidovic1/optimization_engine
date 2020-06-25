#include "TaskSet.h"
#include "Helper.h"
#include "iostream"

//CONSTRUCTOR

TaskSet::TaskSet(long long int t_core)
{
	setCore(t_core);

	setHyperperiod(HYPERPERIOD_OF_EMPTY_TASK_SET);
}

//CONSTRUCTOR


// SETTERS

void TaskSet::setCore(long long int t_core)
{
	core = t_core;
	return;
}

void TaskSet::setHyperperiod(long long int t_hyperperiod)
{
	hyperperiod = t_hyperperiod;
}

// SETTERS


// GETTERS

std::vector<Task> TaskSet::getTasks() { return tasks; };

long long int TaskSet::getCore() { return core; }

long long int TaskSet::getHyperperiod() { return hyperperiod;  }

std::vector<TaskInstance> TaskSet::getInstances() 
{
	std::vector<TaskInstance> instances;

	for (long long int i = 0; i < tasks.size(); i++)
	{

		for (long long int j = 1; j <= this->getHyperperiod()/tasks.at(i).getPeriod(); j++)
		{
			instances.push_back(TaskInstance(tasks.at(i), (j-1)*tasks.at(i).getPeriod(), j));
		}
	}

	return instances;
}

// GETTERS


// METHODS

void TaskSet::addTask(Task t_task)
{

	if (t_task.getCoreAssignedTo() != core) throw std::invalid_argument("Invalid core!");

	//Check if task already added
	for (long long int i = 0; i < tasks.size(); i++)
	{

		if (tasks.at(i).getTaskId() == t_task.getTaskId() ) return;
	}

	tasks.push_back(t_task);

	setHyperperiod(calculateHyperperiod()); // Recalculate the hyperperiod to account for the new task
}

void TaskSet::removeTask(Task t_task)
{

	// Find appropriate task
	for (long long int i = 0; i < tasks.size(); i++)
	{
		if (tasks.at(i).getTaskId() == t_task.getTaskId() )
		{
			tasks.erase(tasks.begin() + i);
		}
	}

	setHyperperiod(calculateHyperperiod());
}

long long int TaskSet::calculateHyperperiod()
{

	if (tasks.size() == 1) return tasks.at(0).getPeriod(); //If only one task

	std::vector<long long int> periods; // vector holding the periods of all the tasks in set (without duplicate periods)

	for (long long int i = 0; i < tasks.size(); i++)
	{
		long long int period = tasks.at(i).getPeriod();
		bool isNewPeriodValue = true;

		for (long long int j = 0; j < periods.size(); j++)
		{
			//Remove double periods for faster hyperperiod calculation
			if (periods.at(j) == period) isNewPeriodValue = false;
		}

		if (isNewPeriodValue || true) periods.push_back(period);
	}
	return findLeastCommonMultiple(periods);

}

// METHODS