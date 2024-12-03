// TaskManager.h
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <list>
#include "Task.h"
using namespace std;

class Task;

class TaskManager {
public:
    void addTask(const Task& task){
        tasks.push_back(task);
    }
    void removeTask(int taskId) {
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->getId() == taskId) {
                tasks.erase(it);
                break;
            }
        }
    }
    void viewTasks() const{
        for (const auto& task : tasks){
            cout << "Task ID: " << task.getId() <<", Task Name: " << task.getDescription() << endl;
        }
    }
    Task* getTask(int taskId){
            for (auto& task : tasks) {
                if (task.getId() == taskId) {
                    return &task;
                }
            }
            return nullptr; // Return nullptr if task is not found
        };
private:
    list<Task> tasks;
};

#endif