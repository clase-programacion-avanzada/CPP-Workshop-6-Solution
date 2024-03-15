#ifndef EISENHOWER_TASK_BINARY_H
#define EISENHOWER_TASK_BINARY_H

#include "Task.h"

/*Punto 3*/
//Remember you will need a taskBinary struct 
//to write and read from the binary file
//Size: 106 bytes
struct TaskBinary {
    char description[100];//100
    bool isUrgent;//1
    bool isImportant;//1
    int estimatedTime;//4
};

TaskBinary toBinaryTask(Task& task) {
    TaskBinary taskBinary;
    
    strcpy(taskBinary.description, task.description.c_str());
    taskBinary.isUrgent = task.isUrgent;
    taskBinary.isImportant = task.isImportant;
    taskBinary.estimatedTime = task.estimatedTime;

    return taskBinary;
}

Task toTask(TaskBinary& taskBinary) {
    Task task;
    task.description = taskBinary.description;
    task.isUrgent = taskBinary.isUrgent;
    task.isImportant = taskBinary.isImportant;
    task.estimatedTime = taskBinary.estimatedTime;

    return task;
}

List<TaskBinary> toTaskBinaryList(List<Task>& tasks) {
    List<TaskBinary> taskBinaries;

    for (int i = 0; i < tasks.size; i++) {
        Task task = tasks.get(i);
        taskBinaries.add(toBinaryTask(task));
    }

    return taskBinaries;
}

List<Task> toTaskList(List<TaskBinary>& taskBinaries) {
    List<Task> tasks;

    for (int i = 0; i < taskBinaries.size; i++) {
        TaskBinary taskBinary = taskBinaries.get(i);
        tasks.add(toTask(taskBinary));
    }

    return tasks;
}

int getFileSize(string fileName) {
    fstream file;

    file.open(fileName, ios::in | ios::binary);

    if (file.fail()) {
        return -1;
    }

    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

TaskBinary* readTasksUsingPointer(char* path) {

    int fileSize = getFileSize(path);

    if (fileSize == -1) {
        return nullptr;
    }

    fstream file;

    file.open(path, ios::in | ios::binary);

    if (file.fail()) {
        return nullptr;
    }

    TaskBinary* taskBinaries = new TaskBinary[fileSize / sizeof(TaskBinary)];

    file.read(reinterpret_cast<char *>(taskBinaries), fileSize);
    file.close();

    return taskBinaries;

}

List<Task> readTasksFromBinaryFile(string& path) {
    //BinaryFileHandler<TaskBinary> fileHandler(path);
    //List<TaskBinary> taskBinaries = fileHandler.readBinaryFile();
    
    List<TaskBinary> taskBinaries;

    fstream file;

    file.open(path, ios::in | ios::binary);

    if (file.fail()) {
        return List<Task>();
    }

    TaskBinary element;

    while(file.read(reinterpret_cast<char *>(&element), sizeof(TaskBinary))) {
        taskBinaries.add(element);
    }

    file.close();

    //Ya leímos los datos del archivo binario

    List<Task> tasks;

    for( int i = 0; i < taskBinaries.size; i++){
        
        TaskBinary taskBinary = taskBinaries.get(i);

        Task task;
        task.description = taskBinary.description;
        task.isUrgent = taskBinary.isUrgent;
        task.isImportant = taskBinary.isImportant;
        task.estimatedTime = taskBinary.estimatedTime;

        tasks.add(task);
    }

    return tasks;

}




bool writeTasksToBinaryFile(List<Task>& tasks, string& path) {
    //BinaryFileHandler<TaskBinary> fileHandler(path);
    List<TaskBinary> taskBinaries = toTaskBinaryList(tasks);


    fstream file;

    file.open(path, ios::out | ios::binary);

    if (file.fail()) {
        return false;
    }

    for (int i = 0; i < tasks.size; i++) {
        Task task = tasks.get(i);
        TaskBinary taskBinary;
    
        strcpy(taskBinary.description, task.description.c_str());
        taskBinary.isUrgent = task.isUrgent;
        taskBinary.isImportant = task.isImportant;
        taskBinary.estimatedTime = task.estimatedTime;

        file.write(reinterpret_cast<char *>(&taskBinary), sizeof(TaskBinary));
    }

    file.close();

    return true;


    //return fileHandler.writeBinaryFile(taskBinaries);
}





#endif