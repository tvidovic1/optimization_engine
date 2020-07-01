#include "Parser.h"
#include "Task.h"
#include "TaskSet.h"



std::vector<TaskSet> readInput(std::vector< const char*> inputCorePaths)
{

	
	const char* channelName = "Channel";
	const char* eventName = "Event";

	// a vector that keeps the generated task sets

	std::vector<TaskSet> taskSets;
	// a vector of all the names of the tasks
	
	std::vector<char*> namesOfTasks;

	// a vector of the corresponding task ids

	std::vector<int> idOfTasks;

	for (int core = 0; core < NUMBER_OF_CORES; core++)
	{
		TaskSet newTaskSet(core);

		rapidxml::xml_document<> * doc = new rapidxml::xml_document<>();
		rapidxml::xml_node<>* root_node;

		// Read the xml file into a vector

		std::ifstream theFile(inputCorePaths.at(core));
		std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		// Parse the buffer using the xml file parsing library into doc 
		(*doc).parse<0>(&buffer[0]);

		// get the root node

		root_node = doc->first_node("document");

		rapidxml::xml_node<>* node = root_node->first_node("Channel");

		std::string nodeName;

		int currentTaskId = 1;

		do
		{

			std::cout << "Node Name: " << node->name() << " Node type: " << node->type() << std::endl;
			std::cout << "Name: " << node->first_attribute("Name")->value() << " IndexTable: " << node->first_attribute("IndexTable")->value() << std::endl;

			// read next task

			namesOfTasks.push_back(node->first_attribute("Name")->value());

			// save corresponding task id and increase counter

			idOfTasks.push_back(currentTaskId);
			currentTaskId++;

			// get indextable of task

			int indexTable = std::stoi(node->first_attribute("IndexTable")->value());

			// find the event of the corresponding task

			rapidxml::xml_node<>* eventNode = root_node->first_node("Event");

			while (eventNode->next_sibling() != nullptr)
			{
				if (std::stoi(eventNode->first_attribute("IndexTable")->value()) == indexTable)
				{
					// preoper task found, calculate total WCET
					int upper = std::stoi(eventNode->next_sibling()->first_attribute("Timestamp")->value());
					if (upper < 1000)
					{
						upper *= 1000;
					}

					int lower = std::stoi(eventNode->first_attribute("Timestamp")->value());

					if (lower < 1000)
					{
						lower *= 1000;
					}
					int totalWCET = upper - lower;

					std::cout << "NAME: " << nodeName << " WCET: " << totalWCET << std::endl;

					// TODO: fix label size and periods

					int readLabelSize = 8;

					int writeLabelSize = 8;

					int WCRT = 2000;

					int WCWT = 2000;

					int WCET = totalWCET - WCRT - WCWT;

					int period = 100000000;

					Task newTask(currentTaskId, WCRT, WCET, WCWT, period, core);


					newTaskSet.addTask(newTask);


					break;
				}

				eventNode = eventNode->next_sibling();
			}

			node = node->next_sibling();

			nodeName = node->name() + '\0';
		} while (nodeName == channelName);

		taskSets.push_back(newTaskSet);

		delete doc;


	}

	
	return taskSets;
	
}