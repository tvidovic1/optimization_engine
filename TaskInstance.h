#include "Task.h"

#pragma once
class TaskInstance
{
private:

	Task task; // The task that the instance is of
	long long int absolute_release_time; // The time at which the task instance becomes ready to execute
	long long int absolute_deadline; // The time by which the task instance should finish its execution
	long long int number_of_instance; // Which instance of the task in one hyperperiod

public:

	// CONSTRUCTOR

	TaskInstance(Task t_task, long long int t_absolute_release_time, long long int t_number_of_instance);

	// CONSTRUCTOR


	// SETTERS

	void setTask(Task t_task);

	void setAbsoluteReleaseTime(long long int t_absolute_release_time);
	
	void setAbsoluteDeadline(long long int t_absolute_deadline);

	void setNumberOfInstance(long long int t_number_of_instance);

	// SETTERS


	// GETTERS

	Task getTask();

	long long int getAbsoluteReleaseTime();

	long long int getAbsoluteDeadline();

	long long int getNumberOfInstance();

	// GETTERS


	// METHODS
	// METHODS

};



