#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

using namespace std;

#include "Employee.h"
class Manager; // Forward declaration of Manager class
#include "Manager.h"

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

        int getId() const{
            return id;
        }

        string getDescription() const{
            return description;
        }

        void printTask() const {
            cout << "Task ID: " << id << endl;
            cout << "Description: " << description << endl;
            cout << "Priority: " << priority << endl;
            if (assignee) {
                cout << "Assignee: " << assignee->getEmployeeName() << endl;
            } else {
                cout << "Assignee: None" << endl;
            }
            if (assigner) {
                cout << "Assigner: " << assigner->getEmployeeName() << endl;
            } else {
                cout << "Assigner: None" << endl;
            }
        }
};

#endif