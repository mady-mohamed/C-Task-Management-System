#include <iostream>
#include <list>
#include <map>
#include <sqlite3.h>
#include <sstream>
using namespace std;

#include "Database.h"
#include "Employee.h"
#include "Task.h"
#include "Manager.h"
#include "TaskManager.h"

// Forward declarations
class Employee;
class Manager;
class Task;

int main() {
    Database db("task_management_system.db");
    bool running = true;
    map<int, Employee> employees; // Map to store employees with their ID as the key
    map<int, Manager> managers;
    map<int, Task> tasks;

    while (running) {
        cout << "Welcome to the Task Management System! \n"
             << "1. Add Employee \n"
             << "2. Show Employees \n"
             << "3. Assign Manager\n"
             << "4. Show Managers \n"
             << "5. Create Task \n"
             << "6. Update Task Status \n"
             << "7. View Tasks \n"
             << "8. Exit \n"
             << "Choose an option:" << endl;
        int option, taskOption;
        cin >> option;

        int employeeId = 0;
        string employeeName;
        string employeeTitle;
        int taskId = 0;
        string taskDescription;
        int taskPriority = 0;
        int taskAssignerId = 0;
        int taskAssigneeId = 0;
        Task newTask;
        int managerId;
        TaskManager taskMng;
        switch (option) {
            case 1: {
                // Add Employee logic
                cout << "Add Employee..." << endl;
                cout << "Enter Employee ID: ";
                cin >> employeeId;
                cout << "Enter Name: ";
                cin >> employeeName;
                cout << "Enter Title: ";
                cin >> employeeTitle;
                cout << "Adding Employee" << endl;
                employees[employeeId] = Employee(employeeId, employeeTitle, employeeName);
                cout << "Employee added successfully" << endl;
                employees[employeeId].displayInfo();
                break;
            }
            case 2: {
                // Show Employees Logic
                cout << "Showing Employees..." << endl;
                for (const auto& [key, value] : employees) {
                    value.displayInfo();
                }
                break;
            }
            case 3: {
                // Assign Manager Logic
                cout << "Assign Manager..." << endl;
                cout << "Enter Manager Employee ID: " << endl;
                cin >> managerId;
                if (employees.find(managerId) != employees.end()) {
                    Employee emp = employees[managerId];
                    managers[managerId] = Manager(emp.getEmployeeId(), emp.getEmployeeTitle(), emp.getEmployeeTitle());
                } else {
                    cout << "Employee ID not found." << endl;
                }
                break;
            }
            case 4: {
                // Show Manager Logic
                cout << "Showing Manager..." << endl;
                for (const auto& [key, value] : managers) {
                    value.displayInfo();
                }
                break;
            }
            case 5: {
                // Create Task logic
                cout << "Create Task..." << endl;
                cout << "Enter Task ID: " << endl;
                cin >> taskId;
                cout << "Enter Task Description: " << endl;
                cin >> taskDescription;
                cout << "Enter Task Priority: " << endl;
                cin >> taskPriority;
                cout << "Enter Task Assigner ID: " << endl;
                cin >> taskAssignerId;
                Manager* taskAssigner = &managers[taskAssignerId];
                cout << "Enter Task Assignee ID: " << endl;
                cin >> taskAssigneeId;
                Employee* taskAssignee = &employees[taskAssigneeId];
                newTask = Task(taskId, taskDescription, taskPriority, taskAssignee, taskAssigner);
                taskMng.addTask(newTask);
                Task* taskRef = taskMng.getTask(taskId);
                taskAssignee->assignTask(taskRef);
                taskMng.getTask(taskId)->printTask();
                break;
            }
            case 6: {
                // Update Task Status logic
                cout << "Updating Task Status..." << endl;
                cout << "Enter Task ID: " << endl;
                cin >> taskId;
                cout << "Modify: \n1. Description\n2. Priority \n3. Assigner\n4. Assignee\n";
                cin >> taskOption;
                switch (taskOption){
                    case 1:{
                        cout << "Enter new description: " << endl;
                        cin >> taskDescription;
                        taskMng.getTask(taskId)->setTaskDescription(taskDescription);
                        break;
                    }
                    case 2:{
                        cout << "Enter new priority (1 low, 2 medium, 3 high): " << endl;
                        cin >> taskPriority;
                        taskMng.getTask(taskId)->setTaskPriority(taskPriority);
                        break;
                    }
                    case 3:{
                        cout << "Enter new Assigner Manager ID: " << endl;
                        cin >> taskAssignerId;
                        Manager* taskAssigner = &managers[taskAssignerId];
                        taskMng.getTask(taskId)->setAssigner(taskAssigner);
                        break;
                    }
                    case 4:{
                        cout << "Enter new Assigned Employee ID: " << endl;
                        cin >> taskAssignerId;
                        Employee* taskAssignedEmployee = &employees[taskAssignerId];
                        taskMng.getTask(taskId)->setAssignee(taskAssignedEmployee);
                        break;
                    }
                    default:{
                        cout << "Invalid option. Please try again." << endl;
                        break;
                    }
                }
                break;
            }
            case 7: {
                // View All Tasks logic
                cout << "Viewing Tasks..." << endl;
                taskMng.viewTasks();
                break;
            }
            case 8: {
                // Exit
                cout << "Exiting..." << endl;
                running = false;
                break;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}