#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Task; // Forward declaration

class Employee {
    protected:
        int id;
        string title;
        string name;
        list<Task*> assignedTasks; // Use pointer to Task
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
        }
};

#endif