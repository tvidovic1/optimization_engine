#include "TaskInstance.h"
#include "Task.h"


// CONSTRUCTOR

TaskInstance::TaskInstance(Task t_task, long long int t_absolute_release_time, long long int t_number_of_instance)
{
	setTask(t_task);
	
	setAbsoluteReleaseTime(t_absolute_release_time);

	setAbsoluteDeadline(t_number_of_instance*task.getPeriod());

	setNumberOfInstance(t_number_of_instance);
	
	return;
}

// CONSTRUCTOR

// SETTERS


void TaskInstance::setTask(Task t_task)
{
	task = t_task;

	return;
}

void TaskInstance::setAbsoluteReleaseTime(long long int t_absolute_release_time)
{
	absolute_release_time = t_absolute_release_time;

	return;
}

void TaskInstance::setAbsoluteDeadline(long long int t_absolute_deadline)
{
	absolute_deadline = t_absolute_deadline;

	return;
}

void TaskInstance::setNumberOfInstance(long long int t_number_of_instance)
{
	number_of_instance = t_number_of_instance;
	return;
}

// SETTERS


// GETTERS

Task TaskInstance::getTask() { return task; }

long long int TaskInstance::getAbsoluteReleaseTime() { return absolute_release_time; }

long long int TaskInstance::getAbsoluteDeadline() { return absolute_deadline; }

long long int TaskInstance::getNumberOfInstance() { return number_of_instance; }

// GETTERS


// METHODS



// METHODS
