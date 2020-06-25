#include "TaskChain.h"

TaskChain::TaskChain()
{
	tasks.clear();
	hyperperiod = HYPERPERIOD_OF_EMPTY_TASK_CHAIN; 
}

void TaskChain::setHyperperiod(long long int t_hyperperiod) { hyperperiod = t_hyperperiod; }

long long int TaskChain::getHyperperiod() { return hyperperiod; }

void TaskChain::addTask(Task t_task)
{
	tasks.push_back(t_task);
	setHyperperiod(calculateHyperperiod()); // after a task is added recalculate the hyperperiod
}

std::vector<Task> TaskChain::getTasks() { return tasks; }

long long int TaskChain::calculateHyperperiod()
{
	if (tasks.size() == 1) return tasks.at(0).getPeriod(); //If only one task

	std::vector<long long int> periods; // vector holding the periods of all the tasks in set (without duplicate periods)

	for (unsigned long long int i = 0; i < tasks.size(); i++)
	{
		long long int period = tasks.at(i).getPeriod();
		bool isNewPeriodValue = true;

		for (unsigned long long int j = 0; j < periods.size(); j++)
		{
			//Remove double periods for faster hyperperiod calculation
			if (periods.at(j) == period) isNewPeriodValue = false;
		}

		if (isNewPeriodValue || true) periods.push_back(period) ;
	}

	return findLeastCommonMultiple(periods);
}

bool TaskChain::isInChain(long long int taskID)
{

	for (long long int task = 0; task < this->getTasks().size(); task++)
	{
		if (this->getTasks().at(task).getTaskId() == taskID)
		{
			return true;
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, const TaskChain& taskChain)
{
	out << "Task Chain: " << std::endl;

	for (long long int task = 0; task < taskChain.tasks.size() - 1; task++)
	{
		out << taskChain.tasks.at(task) << "\t|" << std::endl << "\tV" << std::endl;
	}

	 out << taskChain.tasks.at(taskChain.tasks.size() - 1) << std::endl;

}

