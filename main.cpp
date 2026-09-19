#include "include/task.h"
#include "include/taskManager.h"

#include <string>
#include <print>
#include <cstdlib>
#include <iostream>
#include <limits>

#pragma region functions

void printMenu()
{
     std::println("=============================================================================");
     std::println("Enter your choice with the corresponding number");
     std::println("1. Create task.");
     std::println("2. Delete task.");
     std::println("3. Display tasks.");
     std::println("4. Find Task.");
     std::println("5. Edit Task.");
     std::println("6. Save.");
     std::println("7. Exit.");
     std::println("=============================================================================");
}

void createTask(TaskManager &manager, Task &task)
{
     std::string input;
     int prioValue;

     std::println("What is the name of your task?");
     std::cin.ignore();
     std::getline(std::cin, input);
     task.setTitle(input);

     do
     {
          std::println("Enter the ID of your object! (An ID must consist of 8 characters!)");
          std::cin >> input;
          while (input.length() != 8)
          {
               std::println("The ID must be exactly 8 characters long! Please try again.");
               std::cin >> input;
          }
     } while (!manager.checkID(input));

     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     task.setID(input);

     do
     {
          std::println("Describe your task!");
          std::getline(std::cin, input);
          if (input.empty())
          {
               std::println("Please enter a description!");
          }
     } while (input.empty());
     task.setDescription(input);

     do
     {
          std::println("How important is your task? - 1: Low, 2: Moderate, 3: High");
          std::cin >> prioValue;
          if (std::cin.fail())
          {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               prioValue = 0;
          }
     } while (prioValue < Gering || prioValue > Wichtig);

     task.setPriority(static_cast<Priority>(prioValue));
     manager.addTask(task);
}

void deleteTask(TaskManager &manager)
{
     std::string input;

     std::println("Enter the ID of the object to be deleted!");
     std::cin >> input;
     if (std::cin.fail())
     {
          std::cerr << "Unknown Error occured - Program will be terminated!";
          return;
     }
     manager.deleteTask(input);
}

void saveTask(TaskManager &manager)
{
     manager.saveTasksInFile();
     std::println("Tasks are saved.");
}

void editTask(TaskManager &manager, const string &id)
{
     manager.editTask(id);
}

#pragma endregion

int main()
{
     TaskManager manager;
     Task task;
     bool running = true;
     unsigned int value;
     string input;

     manager.openTasksFromFile();

     std::println("=============================================================================");
     std::println("Welcome");

     while (running)
     {
          printMenu();
          std::cin >> value;
          if (std::cin.fail())
          {
               std::cerr << "UNKNOWN ERROR. - Program will be terminated!\n";
               std::println("");
               return 0;
          }
          std::println("=============================================================================");

          switch (value)
          {
          case 1:
               createTask(manager, task);
               break;
          case 2:
               deleteTask(manager);
               break;
          case 3:
               manager.showTasks();
               break;
          case 4:
               std::println("Enter your ID");
               std::cin >> input;
               manager.findTask(input);
               break;
          case 5:
               std::println("Enter your ID");
               std::cin >> input;
               editTask(manager, input);
               break;
          case 6:
               saveTask(manager);
               break;
          case 7:
               std::println("Programm successfully closed!");
               std::println("");
               running = false;
               break;
          default:
               std::println("Wrong decisions!");
               break;
          }
     }
     return manager.exitConsole();
}