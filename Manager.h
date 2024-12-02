#include <iostream>
#include "employee.h"
using namespace std;

#ifndef MANAGER_H
#define MANAGER_H

class Manager : public Employee {
    public:
        Manager() : Employee(), employeeId(0), employeeTitle(""), employeeName("") {}
        Manager(int employeeId, string employeeTitle, string employeeName)
            : Employee(employeeId, employeeTitle, employeeName) {}

        void displayInfo() const {
                cout << "Manager Employee ID: " << id << ", Name: " << name << ", Title: " << title << endl;
                for (auto i = assignedTasks.begin(); i != assignedTasks.end(); ++i){
                    i->displayInfo();
                }
            }

        void assignEmployeeTask(const Task& task){
            assignerTasks.push_back(task);
        }

        void deAssignEmployeeTask(const Task& task){
            assignerTasks.remove(task);
        }

    private:
        int employeeId;
        string employeeTitle;
        string employeeName;
        list<Task> assignerTasks;
};

#endif