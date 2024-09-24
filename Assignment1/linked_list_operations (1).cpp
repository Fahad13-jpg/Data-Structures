#include <iostream>
#include <string>

using namespace std;

// Structure to represent a task node in the linked list
struct Node {
    int taskId;                 // Stores the ID of the task
    string taskDescription;     // Stores the description of the task
    int priority;               // Stores the priority of the task
    Node* next;                 // Pointer to the next node (task) in the list
};

// TaskManagementSystem class handles the task list using a singly linked list
class TaskManagementSystem {
private:
    Node* head;  // Pointer to the first task in the list (head of the linked list)

public:
    // Constructor to initialize the head pointer to nullptr (empty list)
    TaskManagementSystem() {
        head = nullptr;
    }

    // Destructor to delete all tasks from memory when the program ends
    ~TaskManagementSystem() {
        while (head != nullptr) {  // Loop through the list and delete each node
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to add a new task based on its priority
    void addTask(int taskId, string taskDescription, int priority) {
        Node* newNode = new Node;  // Create a new node for the task
        newNode->taskId = taskId;
        newNode->taskDescription = taskDescription;
        newNode->priority = priority;
        newNode->next = nullptr;

        // If the list is empty or the new task has a higher priority, add it at the front
        if (head == nullptr || priority > head->priority) {
            newNode->next = head;  // Point the new node to the current head
            head = newNode;        // Update the head to the new node
        } else {
            // Traverse the list to find the correct position based on priority
            Node* current = head;
            while (current->next != nullptr && current->next->priority >= priority) {
                current = current->next;
            }
            // Insert the new node at the found position
            newNode->next = current->next;
            current->next = newNode;
        }
        cout << "Task added successfully!\n";
    }

    // Function to remove the task with the highest priority (from the start of the list)
    void removeHighestPriorityTask() {
        if (head != nullptr) {
            Node* temp = head;   // Save the current head node to delete
            head = head->next;   // Move the head to the next node
            delete temp;         // Delete the old head node
            cout << "Highest priority task removed successfully!\n";
        } else {
            cout << "No tasks available to remove.\n";  // Message when list is empty
        }
    }

    // Function to remove a specific task by its ID
    void removeTaskById(int taskId) {
        if (head == nullptr) {   // If the list is empty
            cout << "No tasks available to remove.\n";
            return;
        }

        Node* current = head;
        Node* previous = nullptr;

        // Traverse the list to find the task with the matching ID
        while (current != nullptr && current->taskId != taskId) {
            previous = current;  // Keep track of the previous node
            current = current->next;  // Move to the next node
        }

        // If the task is found
        if (current != nullptr) {
            if (previous == nullptr) {
                head = current->next;  // Remove the head task if it's the one to be deleted
            } else {
                previous->next = current->next;  // Link the previous node to the next node
            }
            delete current;  // Delete the task
            cout << "Task with ID " << taskId << " removed successfully!\n";
        } else {
            cout << "Task with ID " << taskId << " not found.\n";  // If task ID not found
        }
    }

    // Function to display all tasks in the list
    void viewTasks() {
        if (head == nullptr) {   // If the list is empty
            cout << "No tasks available.\n";
            return;
        }

        Node* current = head;  // Start from the head of the list
        // Loop through the list and print details of each task
        while (current != nullptr) {
            cout << "Task ID: " << current->taskId 
                 << ", Description: " << current->taskDescription
                 << ", Priority: " << current->priority << endl;
            current = current->next;  // Move to the next task in the list
        }
    }
};

// Function to display the menu options for the user
void displayMenu() {
    cout << "\nTask Management System Menu:\n";
    cout << "1. Add a new task\n";
    cout << "2. View all tasks\n";
    cout << "3. Remove the highest priority task\n";
    cout << "4. Remove a task by ID\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    TaskManagementSystem taskSystem;  // Create an instance of TaskManagementSystem
    int choice;  // Variable to store user input

    // Infinite loop to continuously show the menu until the user exits
    while (true) {
        displayMenu();  // Show menu options
        cin >> choice;  // Get user's choice

        switch (choice) {
            case 1: {  // Add a new task
                int taskId, priority;
                string taskDescription;

                cout << "Enter task ID: ";
                cin >> taskId;
                cin.ignore();  // Clear newline character from the input buffer
                cout << "Enter task description: ";
                getline(cin, taskDescription);  // Read the task description
                cout << "Enter task priority: ";
                cin >> priority;

                taskSystem.addTask(taskId, taskDescription, priority);  // Add the task to the list
                break;
            }
            case 2:
                taskSystem.viewTasks();  // View all tasks
                break;
            case 3:
                taskSystem.removeHighestPriorityTask();  // Remove the highest priority task
                break;
            case 4: {  // Remove a specific task by its ID
                int taskId;
                cout << "Enter task ID to remove: ";
                cin >> taskId;
                taskSystem.removeTaskById(taskId);  // Remove the task by ID
                break;
            }
            case 5:  // Exit the program
                cout << "Exiting the system...\n";
                return 0;
            default:  // Invalid input case
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
