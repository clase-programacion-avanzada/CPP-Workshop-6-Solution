#include "libs/List.h"


#include <iostream>
#include "./libs/Task.h"
#include "./libs/TextFileHandler.h"
#include "./libs/TaskBinary.h"

using namespace std;

void printMenu();
void writeReportFiles(List<Task>& tasks);
void printTasks(List<Task>& tasks);

int main() {
    
    
    int option = 0;
    string textFile = "tasks.txt";
    string binaryFile = "tasks.bin";
    List<Task> tasksFromTextFile;
    List<Task> tasksFromBinaryFile;
    List<Task> taskWithoutDeleteQuadrant;
    List<Task> sortedTasks;
    do {
        printMenu();

        cout << "Ingrese una opción: ";
        cin >> option;

       switch (option)
        {
            case 1:
                tasksFromTextFile = readTasksFromTextFile(textFile);
                break;
            case 2:
                if (tasksFromTextFile.size == 0) {
                    cout << "No hay tareas para escribir en el archivo binario" << endl;
                    break;
                }
                writeTasksToBinaryFile(tasksFromTextFile, binaryFile);
                break;
            case 3:
                tasksFromBinaryFile = readTasksFromBinaryFile(binaryFile);
                break;
            case 4:
                if (tasksFromBinaryFile.size == 0) {
                    cout << "No hay tareas para generar reportes" << endl;
                    break;
                }
                sortedTasks = sortTasksByMinutes(tasksFromBinaryFile);
                writeReportFiles(sortedTasks);
                break;
            case 5:
                if (tasksFromBinaryFile.size == 0) {
                    cout << "No hay tareas para borrar" << endl;
                    break;
                }
                taskWithoutDeleteQuadrant = removeDeleteQuadrantTasks(tasksFromBinaryFile);
                break;
            case 6:
                if (tasksFromBinaryFile.size == 0) {
                    cout << "No hay tareas para imprimir" << endl;
                    break;
                }
                
                printTasks(tasksFromBinaryFile);
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
                break;
        } 

    } while (option != 0);
    
    tasksFromTextFile.clear();
    tasksFromBinaryFile.clear();
    taskWithoutDeleteQuadrant.clear();
    sortedTasks.clear();

    return 0;
}
/*Punto 5 -parte 2*/
void writeReportFiles(List<Task>& tasks) {
    List<Task> doQuadrantTasks;
    List<Task> planifyQuadrantTasks;
    List<Task> eliminateQuadrantTasks;
    List<Task> delegateQuadrantTasks;

    for (int i = 0; i < tasks.size; i++) {
        Task task = tasks.get(i);
        if (task.isUrgent && task.isImportant) {
            doQuadrantTasks.add(task);
        } 
        if (!task.isUrgent && task.isImportant) {
            planifyQuadrantTasks.add(task);
        }
        if (task.isUrgent && !task.isImportant) {
            delegateQuadrantTasks.add(task);
        }
        if (!task.isUrgent && !task.isImportant) {
            eliminateQuadrantTasks.add(task);
        }
    }

    TextFileHandler fileHandler("doQuadrantTasks.txt");

    fileHandler.writeLines(getLinesReportFromTasks(doQuadrantTasks));

    fileHandler.fileName = "delegateQuadrantTasks.txt";
    fileHandler.writeLines(getLinesReportFromTasks(delegateQuadrantTasks));

    fileHandler.fileName = "eliminateQuadrantTasks.txt";
    fileHandler.writeLines(getLinesReportFromTasks(eliminateQuadrantTasks));

    fileHandler.fileName = "delegateQuadrantTasks.txt";
    fileHandler.writeLines(getLinesReportFromTasks(delegateQuadrantTasks));

    doQuadrantTasks.clear();
    planifyQuadrantTasks.clear();
    eliminateQuadrantTasks.clear();
    delegateQuadrantTasks.clear();
    

}


void printMenu() {
    cout << "1. Leer archivo de texto con las tareas." << endl;
    cout << "2. Escribir lista generada en un archivo binario." << endl;
    cout << "3. Leer el archivo binario y actualizar la lista de tareas." << endl;
    cout << "4. Generar reportes." << endl;
    cout << "5. Borrar tareas del cuadrante eliminar." << endl;
    cout << "6. Imprimir lista de tareas sin el cuadrante eliminar." << endl;
    cout << "0. Salir" << endl;
}

void printTasks(List<Task>& tasks) {
    for (int i = 0; i < tasks.size; i++) {
        Task task = tasks.get(i);
        cout << task.description 
        << (task.isUrgent ? " Urgente" : " No urgente")
        << (task.isImportant ? " Importante" : " No importante")
        << " " << task.estimatedTime << " minutos" << endl;

    }
}


