#pragma once
#include "task.h"

#include <vector>
#include <iostream>
#include <fstream>

using std::string;

class TaskManager
{
private:
     std::vector<Task> tasks;
public:
     TaskManager() = default;
     TaskManager(Task task);
     void deleteTask(const string &id);
     void addTask(const Task &task);
     bool checkID(const string &id) const;
     void findTask(const string &id) const;
     void editTask(const string &id);
     void showTasks();
     void openTasksFromFile();
     void saveTasksInFile();
     int exitConsole();
};