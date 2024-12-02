#include <iostream>
#include "Employee.h"
#include "Manager.h"
using namespace std;

#ifndef TASK_H
#define TASK_H

class Task {
    private:
        long id;
        string description;
        int priority;
        Employee* assignee;
        Manager* assigner;
    public:
        Task() : id(0), description(""), priority(0) {} // Default constructor

        Task(long taskId, string taskDescription, int taskPriority, Employee* taskAssignee, Manager* taskAssigner) {
            id = taskId;
            description = taskDescription;
            priority = taskPriority;
            assignee = taskAssignee;
            assigner = taskAssigner;
        }

        void setTaskDescription(string taskDescription) {
            description = taskDescription;
        }
        void setTaskPriority(int taskPriority) {
            priority = taskPriority;
        }

        void setAssigner(Manager* taskAssigner){
            assigner = taskAssigner;
        }
        void setAssignee(Employee* taskAssignee) {
            assignee = taskAssignee;
        }
        void displayInfo() const {
            cout << "Task ID: " << id << ", Description: " << description << ", Priority: " << priority;
            if (assignee) {
                cout << ", Assignee: ";
                assignee->displayInfo();
            } else {
                cout << ", Assignee: None";
            }
            if (assigner) {
                cout << ", Assigner: ";
                assigner->displayInfo();
            } else {
                cout << ", Assigner: None";
            }
            cout << endl;
        }
};

#endif