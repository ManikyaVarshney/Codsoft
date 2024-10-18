#include <iostream>
#include <vector>
using namespace std;

// Struct to represent a task
struct Task {
    string description;
    bool isCompleted;
};

// Function to display the tasks
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }
    cout << "\nYour To-Do List:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].description;
        if (tasks[i].isCompleted) {
            cout << " [Completed]";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to add a task
void addTask(vector<Task>& tasks) {
    string description;
    cout << "Enter the description of the task: ";
    cin.ignore();  // To ignore any newline character left in the input buffer
    getline(cin, description);  // Get the full line of input
    tasks.push_back({description, false});  // Add task with default status "pending"
    cout << "Task added successfully!\n";
}

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to mark as completed.\n";
        return;
    }
    viewTasks(tasks);
    int taskNumber;
    cout << "Enter the task number to mark as completed: ";
    cin >> taskNumber;
    
    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!\n";
    } else {
        tasks[taskNumber - 1].isCompleted = true;
        cout << "Task marked as completed!\n";
    }
}

// Function to remove a task
void removeTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to remove.\n";
        return;
    }
    viewTasks(tasks);
    int taskNumber;
    cout << "Enter the task number to remove: ";
    cin >> taskNumber;
    
    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!\n";
    } else {
        tasks.erase(tasks.begin() + taskNumber - 1);
        cout << "Task removed successfully!\n";
    }
}

// Main function to manage the to-do list
int main() {
    vector<Task> tasks;
    int choice;
    bool exit = false;

    cout << "Welcome to the Simple To-Do List Manager!\n";

    while (!exit) {
        cout << "\nMenu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                exit = true;
                cout << "Exiting the To-Do List Manager. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    }

    return 0;
}
