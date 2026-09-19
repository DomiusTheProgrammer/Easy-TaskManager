#include "include/taskManager.h"
#include "include/task.h"

#include <vector>
#include <print>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include <filesystem>

using std::string;

namespace
{
     std::filesystem::path saveFilePath()
     {
          if (std::filesystem::exists("save.dat") ||
              !std::filesystem::exists("05_todoManager"))
          {
               return "save.dat";
          }

          return "05_todoManager/save.dat";
     }
}

#pragma region constructor
TaskManager::TaskManager(Task task) : tasks{task} {}
#pragma endregion

#pragma region functions

bool TaskManager::checkID(const string &id) const
{
     for (const Task &task : tasks)
     {
          if (task.getID() == id)
          {
               std::println("This ID is already used!");
               return false;
          }
     }

     return true;
}

void TaskManager::deleteTask(const string &id)
{
     for (auto it = tasks.begin(); it != tasks.end(); ++it)
     {
          if (it->getID() == id)
          {
               const string removedId = it->getID();
               tasks.erase(it);
               std::println("The element {} got successful deleted!", removedId);
               return;
          }
     }

     std::println("No Object with this ID was found!");
}

void TaskManager::addTask(const Task &task)
{
     tasks.push_back(task);
}

void TaskManager::showTasks()
{
     for (Task &task : tasks)
     {
          std::println("ID: \t\t{}", task.getID());
          std::println("Title: \t\t{}", task.getTitle());
          std::println("Description: \t{}", task.getDescription());
          std::println("Priority: \t{}", task.getPriority());
          std::println("");
     }
}

void TaskManager::openTasksFromFile()
{
     std::ifstream ifile{saveFilePath()};
     if (!ifile)
     {
          return;
     }

     tasks.clear();

     string id;
     string title;
     string description;
     string priority;

     while (std::getline(ifile, id))
     {
          if (!std::getline(ifile, title) ||
              !std::getline(ifile, description) ||
              !std::getline(ifile, priority))
          {
               break;
          }
          tasks.emplace_back(id, title, description, Task::parsePriority(priority));
     }
}

void TaskManager::saveTasksInFile()
{
     std::ofstream ofile{saveFilePath()};
     if (!ofile)
     {
          std::println("Tasks could not be saved.");
          return;
     }

     for (const Task &task : tasks)
     {
          ofile << task.getID() << '\n'
                << task.getTitle() << '\n'
                << task.getDescription() << '\n'
                << task.getPriority() << '\n';
     }
}

void TaskManager::findTask(const string &id) const
{
     for (const Task &task : tasks)
     {
          if (task.getID() == id)
          {
               std::println("We have found your Task!");
               std::println("");
               std::println("ID: {}", task.getID());
               std::println("Description: {}", task.getDescription());
               return;
          }
     }

     std::println("This ID didn't match anything in your list!");
}

void TaskManager::editTask(const string &id)
{
     for (Task &task : tasks)
     {
          if (task.getID() == id)
          {
               string description;
               string priority;
               char inputChar;

               std::println("Do you want to edit your Task! (Y/N)");
               std::cin >> inputChar;
               inputChar = static_cast<char>(std::toupper(static_cast<unsigned char>(inputChar)));
               switch (inputChar)
               {
               case 'Y':
                    std::println("Enter your new description!");
                    std::getline(std::cin >> std::ws, description);
                    task.setDescription(description);

                    std::println("Enter your new priority (1: Low, 2: Moderate, 3: High)!");
                    std::cin >> priority;
                    task.setPriority(Task::parsePriority(priority));

                    std::println("Task succesfully changed and saved!");
                    saveTasksInFile();
                    break;
               case 'N':
                    break;
               default:
                    break;
               }

               return;
          }
     }

     std::println("No task with this ID was found!");
}

int TaskManager::exitConsole()
{
     return EXIT_SUCCESS;
}

#pragma endregion
