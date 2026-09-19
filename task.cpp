#include "include/task.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

#pragma region overload functions

std::istream &operator>>(std::istream &in, Task &task)
{
    in >> task.id >> task.title >> task.description;
    std::string priorityText;
    in >> priorityText;
    task.priority = Task::parsePriority(priorityText);
    return in;
}

std::ostream &operator<<(std::ostream &out, Task &task)
{
    out << task.id << ' ' << task.title << ' ' << task.description << ' ' << task.priority << ";\n";
    return out;
}

#pragma endregion

#pragma region constructor
// constructor
Task::Task(string id, string title, string description, Priority priority)
    : id(id), title(title), description(description), priority(priority) {}

#pragma endregion 

#pragma region Getter/Setter

void Task::setTitle(string title)
{
    this->title = title;
}

string Task::getTitle() const
{
    return title;
}

void Task::setID(string id)
{
    this->id = id;
}

string Task::getID() const
{
    return id;
}

void Task::setDescription(string description)
{
    this->description = description;
}

string Task::getDescription() const
{
    return description;
}

void Task::setPriority(Priority priority)
{
    this->priority = priority;
}

string Task::getPriority() const
{
    switch (priority)
    {
    case Gering:
        return "Gering";
        break;
    case Moderat:
        return "Moderat";
        break;
    case Wichtig:
        return "Wichtig";
        break;
    default:
        return "Unknown";
        break;
    }
}

Priority Task::parsePriority(const string &priorityText)
{
    if (priorityText.empty())
    {
        return Gering;
    }

    std::string normalized = priorityText;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), [](unsigned char c)
                { return static_cast<char>(std::tolower(c)); });

    if (normalized == "1" || normalized == "gering" || normalized == "low")
    {
        return Gering;
    }
    if (normalized == "2" || normalized == "moderat" || normalized == "medium")
    {
        return Moderat;
    }
    if (normalized == "3" || normalized == "wichtig" || normalized == "important" || normalized == "high")
    {
        return Wichtig;
    }

    return Gering;
}

#pragma endregion