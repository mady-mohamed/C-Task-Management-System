#include <iostream>
#include <list>
#include "Task.h"
using namespace std;

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Task;

class Employee {
    protected:
        int id;
        string title;
        string name;
        list<Task*> assignedTasks;
    public:
        Employee() : id(0), title(""), name("") {} // Default constructor

        Employee(int employeeId, string employeeTitle, string employeeName) {
            id = employeeId;
            title = employeeTitle;
            name = employeeName;
        }

        int getEmployeeId() {
            return id;
        }

        string getEmployeeTitle() {
            return title;
        }

        string getEmployeeName() {
            return name;
        }

        void assignTask(Task* task){
            assignedTasks.push_back(task);
        }

        void deAssignTask(Task* task){
            assignedTasks.remove(task);
        }

        void displayInfo() const {
            cout << "Employee ID: " << id << ", Name: " << name << ", Title: " << title << endl;
            cout << "Assigned Tasks: " << endl;
            for (auto i = assignedTasks.begin(); i != assignedTasks.end(); ++i) {
                (*i)->displayInfo();
            }
        }
};

#endif