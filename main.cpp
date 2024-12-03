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

map<int, Employee> employees; // Map to store employees with their ID as the key
map<int, Manager> managers;

void initializeMaps(Database& database) {
    // Query to get all employees
    string queryEmployees = "SELECT EmployeeID, Name, Title FROM Employees;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database.getDb(), queryEmployees.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int employeeId = sqlite3_column_int(stmt, 0);
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            employees[employeeId] = Employee(employeeId, title, name);
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Failed to query employees: " << sqlite3_errmsg(database.getDb()) << endl;
    }

    // Query to get all managers
    string queryManagers = "SELECT ManagerID, ManagerID FROM Managers;";
    if (sqlite3_prepare_v2(database.getDb(), queryManagers.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int managerId = sqlite3_column_int(stmt, 0);
            int employeeId = sqlite3_column_int(stmt, 1);
            managers[managerId] = Manager(managerId, employees[employeeId].getEmployeeTitle(), employees[employeeId].getEmployeeName());
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Failed to query managers: " << sqlite3_errmsg(database.getDb()) << endl;
    }
}

int main() {
    Database db("task_management_system.db");
    initializeMaps(db);
    bool running = true;

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
                // Write Employee to database
                string insertEmployeeQuery = "INSERT INTO Employees (EmployeeID, Name, Title) VALUES (" + to_string(employeeId) + ", '" + employeeName + "', '" + employeeTitle + "');";
                if (db.executeQuery(insertEmployeeQuery)) {
                    cout << "Employee written to database successfully" << endl;
                } else {
                    cout << "Failed to write employee to database" << endl;
                }
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
                    Employee& emp = employees[managerId];
                    managers[managerId] = Manager(emp.getEmployeeId(), emp.getEmployeeTitle(), emp.getEmployeeName());
                    string insertEmployeeQuery = "INSERT INTO Managers (ManagerID) VALUES (" + to_string(managerId) + ");";
                    if (db.executeQuery(insertEmployeeQuery)) {
                        cout << "Manager written to database successfully" << endl;
                    } else {
                        cout << "Failed to write Manager to database" << endl;
                    }
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
                string insertTaskQuery = "INSERT INTO Tasks (TaskID, Description, Priority, AssignerID, AssigneeID) VALUES ('" 
                         + to_string(taskId) + "', '" + taskDescription + "', '" 
                         + to_string(taskPriority) + "', '" + to_string(taskAssignerId) + "', '" 
                         + to_string(taskAssigneeId) + "');";  
                if (db.executeQuery(insertTaskQuery)) {
                        cout << "Task written to database successfully" << endl;
                    } else {
                        cout << "Failed to write Task to database" << endl;
                    }
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

                        // Update Task Description in database
                        string updateDescriptionQuery = "UPDATE Tasks SET Description = '" + taskDescription + "' WHERE TaskID = " + to_string(taskId) + ";";
                        if (db.executeQuery(updateDescriptionQuery)) {
                            cout << "Task description updated in database successfully" << endl;
                        } else {
                            cout << "Failed to update task description in database" << endl;
                        }
                        break;
                    }
                    case 2:{
                        cout << "Enter new priority (1 low, 2 medium, 3 high): " << endl;
                        cin >> taskPriority;
                        taskMng.getTask(taskId)->setTaskPriority(taskPriority);

                        // Update Task Priority in database
                        string updatePriorityQuery = "UPDATE Tasks SET Priority = " + to_string(taskPriority) + " WHERE TaskID = " + to_string(taskId) + ";";
                        if (db.executeQuery(updatePriorityQuery)) {
                            cout << "Task priority updated in database successfully" << endl;
                        } else {
                            cout << "Failed to update task priority in database" << endl;
                        }
                        break;
                    }
                    case 3:{
                        cout << "Enter new Assigner Manager ID: " << endl;
                        cin >> taskAssignerId;
                        Manager* taskAssigner = &managers[taskAssignerId];
                        taskMng.getTask(taskId)->setAssigner(taskAssigner);

                        // Update Task Assigner in database
                        string updateAssignerQuery = "UPDATE Tasks SET AssignerID = " + to_string(taskAssignerId) + " WHERE TaskID = " + to_string(taskId) + ";";
                        if (db.executeQuery(updateAssignerQuery)) {
                            cout << "Task assigner updated in database successfully" << endl;
                        } else {
                            cout << "Failed to update task assigner in database" << endl;
                        }
                        break;
                    }
                    case 4:{
                        cout << "Enter new Assigned Employee ID: " << endl;
                        cin >> taskAssignerId;
                        Employee* taskAssignedEmployee = &employees[taskAssignerId];
                        taskMng.getTask(taskId)->setAssignee(taskAssignedEmployee);

                        // Update Task Assignee in database
                        string updateAssigneeQuery = "UPDATE Tasks SET AssigneeID = " + to_string(taskAssignerId) + " WHERE TaskID = " + to_string(taskId) + ";";
                        if (db.executeQuery(updateAssigneeQuery)) {
                            cout << "Task assignee updated in database successfully" << endl;
                        } else {
                            cout << "Failed to update task assignee in database" << endl;
                        }
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