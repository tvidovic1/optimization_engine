// Implemenation of the Task class

#include "Task.h"

// CONSTRUCTORS


//TODO: initialize properly
Task::Task() 
{
	return;
}

Task::Task(long long int t_task_id, long long int t_worst_case_read, long long int t_worst_case_execute, long long int worst_case_write, long long int t_period, long long int t_core_assigned_to)
{

	setTaskId(t_task_id);

	setWorstCaseRead(t_worst_case_read);

	setWorstCaseExecute(t_worst_case_execute);

	setWorstCaseWrite(worst_case_write);

	setPeriod(t_period);

	setDeadline(t_period);

	setCoreAssignedTo(t_core_assigned_to);

	return;
}

//CONSTRUCTORS


// SETTERS

void Task::setTaskId(long long int t_task_id)
{

	task_id = t_task_id;
}

void Task::setWorstCaseRead(long long int t_worst_case_read)
{
	worst_case_read = t_worst_case_read;

	return;
}

void Task::setWorstCaseExecute(long long int t_worst_case_execute)
{
	worst_case_execute = t_worst_case_execute;

	return;
}

void Task::setWorstCaseWrite(long long int t_worst_case_write)
{
	worst_case_write = t_worst_case_write;

	return;
}

void Task::setPeriod(long long int t_period)
{
	period = t_period;

	return;
}

void Task::setDeadline(long long int t_deadline)
{ 
	// TODO: Replace with error
	// In our model we assume that deadline is equal to period
	if (t_deadline != period) return;

	deadline = t_deadline;

	return;
}

void Task::setCoreAssignedTo(long long int t_core_assigned_to)
{
	core_assigned_to = t_core_assigned_to;

	return;
}

void Task::setSuccessors(std::vector<Task> t_successors)
{
	successors = t_successors;
	return;
}


// SETTERS


// GETTERS

const long long int Task::getTaskId() { return task_id; }

long long int Task::getWorstCaseRead() { return worst_case_read;  }

long long int Task::getWorstCaseExecute() { return worst_case_execute; }

long long int Task::getWorstCaseWrite() { return worst_case_write;  }

long long int Task::getPeriod() const { return period; }

long long int Task::getDeadline() { return deadline; }

long long int Task::getCoreAssignedTo() { return core_assigned_to; }

std::vector<Task> Task::getSuccessors() { return successors; }

// GETTERS


// METHODS

long long int Task::getWorstCaseExecutionTime()
{
	return getWorstCaseRead() + getWorstCaseExecute() + getWorstCaseWrite();
}

void Task::addSuccessor(Task successor)
{
	successors.push_back(successor);
}

// OPERATORS
std::ostream& operator<<(std::ostream& out, const Task& task)
{
	out << "tau " << task.task_id << ", WC Read: " << task.worst_case_read << ", WC Execute: " << task.worst_case_execute << ", WC Write: " <<task.worst_case_write << ", Period: " << task.period / 1000000000 << ", Core: " << task.core_assigned_to << ", Utilization: " <<  (double)((long long int)task.worst_case_read + (long long int)task.worst_case_execute + (long long int)task.worst_case_write)/ (long long int)task.period  <<std::endl;

	return out;
}