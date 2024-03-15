#ifndef EISENHOWER_TASK_H
#define EISENHOWER_TASK_H

#include <string>
//#include "List.h"
#include "TextFileHandler.h"
#include "BinaryFileHandler.h"

using namespace std;
/*Punto 1*/
//Size : 6 bytes + sizeOf(string) = ??? bytes
struct Task {

    string description;
    bool isUrgent;
    bool isImportant;
    int estimatedTime;

};

/*Punto 2*/
Task getTaskFromLine(string &line, char delimiter = ';') {
    Task task;
    
    //parse the line and create a task
    List<string> tokens = split(line, delimiter);
    
    task.description = tokens.get(0);
    task.isUrgent = tokens.get(1) == "1";
    task.isImportant = tokens.get(2) == "1";
    task.estimatedTime = stoi(tokens.get(3));

    //remember to free the memory of tokens
    tokens.clear();

    return task;
}

List<Task> getTasksFromLines(List<string>& lines, char delimiter = ';') {
    List<Task> tasks;

    for (int i = 0; i < lines.size; i++) {
        string line = lines.get(i);
        tasks.add(getTaskFromLine(line, delimiter));
    }

    return tasks;
}

List<Task> readTasksFromTextFile(string& path) {

    TextFileHandler fileHandler(path);
    List<string> lines = fileHandler.readLines();
     
    return getTasksFromLines(lines);
}

/*Punto 5 - parte 1*/
string getLineReportFromTask(Task& task) {
    string line = task.description + " : " + to_string(task.estimatedTime) + " minutes";
    return line;
}

List<string> getLinesReportFromTasks(List<Task>& tasks) {
    List<string> lines;

    for (int i = 0; i < tasks.size; i++) {
        Task task = tasks.get(i);
        lines.add(getLineReportFromTask(task));
    }

    return lines;
}

List<Task> sortTasksByMinutes(List<Task>& tasks) {
    List<Task> sortedTasks = tasks.copy();
    for (int i = 0; i < sortedTasks.size; i++) {
        for (int j = 0; j < sortedTasks.size - 1; j++) {
            if (sortedTasks.get(j).estimatedTime < sortedTasks.get(j + 1).estimatedTime) {
                Task temp = sortedTasks.get(j);
                sortedTasks.set(j, sortedTasks.get(j + 1));
                sortedTasks.set(j + 1, temp);
            }
        }
    }
    return sortedTasks;
}

/*Punto 4 parte 1*/
List<Task> removeDeleteQuadrantTasks(List<Task>& tasks) {
    List<Task> newTasks;

    for (int i = 0; i < tasks.size; i++) {
        Task task = tasks.get(i);
        if (task.isUrgent || task.isImportant) {
            newTasks.add(task);
        }
    }

    return newTasks;
}








#endif