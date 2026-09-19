#pragma once

#include <string>
#include <iostream>

using std::string;

#pragma region Priority
enum Priority
{
     Gering = 1,
     Moderat = 2,
     Wichtig = 3
};
#pragma endregion

class Task
{
private:
     string id;
     string title;
     string description;
     Priority priority = Gering;

public:
     #pragma region functions

     //operator overload
     friend std::istream &operator>>(std::istream &in, Task &task);
     friend std::ostream &operator<<(std::ostream &out, Task &task);
     //parse Priority from String to enum
     static Priority parsePriority(const string &priorityText);

     #pragma endregion

     #pragma region constructor
     
     //constructor
     Task() = default;
     Task(string id, string title, string description, Priority priority);

     #pragma endregion

     #pragma region Getter/Setter
     //Getter and Setter
     void setTitle(string title);
     string getTitle() const;
     void setID(string id);
     string getID() const;
     void setDescription(string desc);
     string getDescription() const;
     void setPriority(Priority priority);
     string getPriority() const;

     #pragma endregion
};