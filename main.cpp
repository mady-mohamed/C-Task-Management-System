#include <iostream>
#include <list>
#include <map>
using namespace std;

// Forward declarations
class Employee;
class Manager;

class Task {
    private:
        long id;
        string description;
        int priority;
        Employee* assignee;
        Manager* assigner;
    public:
        Task(long taskId, string taskDescription, int taskPriority, Employee* taskAssignee, Manager* taskAssigner) {
            id = taskId;
            description = taskDescription;
            priority = taskPriority;
            assignee = taskAssignee;
            assigner = taskAssigner;
        }
};

class Employee {
    private:
        int id;
        string title;
        string name;
        list<Task> assignedTasks;
    public:
        Employee(int employeeId, string employeeTitle, string employeeName) {
            id = employeeId;
            title = employeeTitle;
            name = employeeName;
        }

        void displayInfo() {
            cout << "Employee ID: " << id << ", Name: " << name << ", Title: " << title << endl;
        }
};

class Manager : public Employee {
    private:
        list<Task> tasksAssigned;
    public:
        Manager(int employeeId, string employeeTitle, string employeeName) : Employee(employeeId, employeeTitle, employeeName) {}
};

int main() {
    bool running = true;
    map<int, Employee> employees; // Map to store employees with their ID as the key

    while (running) {
        cout << "Welcome to the Task Management System! 1. Add Employee 2. Create Task 3. Assign Task 4. Update Task Status 5. View Tasks 6. Exit Choose an option: ";
        int option;
        cin >> option;

        int employeeId;
        string employeeName, employeeTitle;

        switch (option) {
            case 1:
                // Add Employee logic
                cout << "Add Employee..." << endl;
                cout << "Enter Employee ID: ";
                cin >> employeeId;
                cout << "Enter Name: ";
                cin >> employeeName;
                cout << "Enter Title: ";
                cin >> employeeTitle;
                employees[employeeId] = Employee(employeeId, employeeTitle, employeeName);
                cout << "Employee added successfully." << endl;
                break;
            case 2:
                // Create Task logic
                cout << "Creating Task..." << endl;
                break;
            case 3:
                // Assign Task logic
                cout << "Assigning Task..." << endl;
                break;
            case 4:
                // Update Task Status logic
                cout << "Updating Task Status..." << endl;
                break;
            case 5:
                // View All Tasks logic
                cout << "Viewing Tasks..." << endl;
                break;
            case 6:
                // Exit
                cout << "Exiting..." << endl;
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    return 0;
}