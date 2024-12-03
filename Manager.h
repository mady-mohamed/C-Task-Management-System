#include <iostream>
#include <list>
#include "employee.h"
using namespace std;

#ifndef MANAGER_H
#define MANAGER_H

class Manager : public Employee {
    private:
        int employeeId;
        string employeeTitle;
        string employeeName;
        list<Task*> assignerTasks;
    public:
        Manager() : Employee(), employeeId(0), employeeTitle(""), employeeName("") {}
        Manager(int employeeId, string employeeTitle, string employeeName)
            : Employee(employeeId, employeeTitle, employeeName) {}

        void assignEmployeeTask(Task* task){
            assignerTasks.push_back(task);
        }

        void deAssignEmployeeTask(Task* task){
            assignerTasks.remove(task);
        }

        void displayInfo() const {
                cout << "Manager Employee ID: " << id << ", Name: " << name << ", Title: " << title << endl;
                for (auto i = assignerTasks.begin(); i != assignerTasks.end(); ++i){
                (*i)->displayInfo();
                }
            }

    
};

#endif