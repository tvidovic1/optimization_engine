/* The class describing a single task in the system. A task is represented by its:
- longest possible access to memory while reading
- longest possible execution part of task
- longest possible access to memory while writing
NOTE: The first three parameters represent the task in the form of the Phased Exectuion Model described in the Thesis
- period (the length of a period of the task)
- deadline (the point at which the task has to finish its execution to be considered scheduled succesfully, considered to be equal to its period)
- the execution core to which the task was assigned to pre-runtime

Several *instances* of each task are created in a single hyperperiod.
@SEE: TaskInstance class*/

#include <vector>
#include <iostream>

#pragma once
class Task
{
private:
	long long int task_id; // The ID of the task
	long long int worst_case_read; // Longest possible access to memory while reading
	long long int worst_case_execute; // Longest possible execution part of task
	long long int worst_case_write; // Longest possible access to memory while writing
	long long int period; // Period (the length of a period of the task)
	long long int deadline; // Deadline (deadline = period)
	long long int core_assigned_to; // The execution core to which the task was assigned to pre-runtime
	std::vector<Task> successors;
	bool is_producer; // Is this task a producer in a task chain?
	bool is_consumer; // Is this task a consumer in a task chain ?


public:

	// CONSTRUCTORS

	Task();

	Task(long long int t_task_id, long long int t_worst_case_read, long long int t_worst_case_execute, long long int worst_case_write, long long int t_period, long long int t_core_assigned_to);

	//CONSTRUCTORS


	// SETTERS

	void setTaskId(long long int t_task_id);

	void setWorstCaseRead(long long int t_worst_case_read);

	void setWorstCaseExecute(long long int t_worst_case_execute);

	void setWorstCaseWrite(long long int worst_case_write);

	void setPeriod(long long int t_period);

	void setDeadline(long long int t_deadline);

	void setCoreAssignedTo(long long int t_core_assigned_to);

	void setSuccessors(std::vector<Task> t_successors);


	// SETTERS


	// GETTERS

	const long long int getTaskId();

	long long int getWorstCaseRead();

	long long int getWorstCaseExecute();

	long long int getWorstCaseWrite();

	long long int getPeriod() const;

	long long int getDeadline();

	long long int getCoreAssignedTo();

	std::vector<Task> getSuccessors();

	// GETTERS


	// METHODS

	// A method that returns the worst case execution time of a task
	long long int getWorstCaseExecutionTime();

	void addSuccessor(Task successor);

	// METHODS

	// OPERATORS

	friend std::ostream& operator<<(std::ostream& out, const Task& task);


};

