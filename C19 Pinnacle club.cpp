#include <iostream>
#include <string>
using namespace std;

struct Node {
    int prn;          
    string name;      
    Node* next;       
};
class PinnacleClub {
private:
    Node* head;  // Pointer to the first member (President) of the club
public:
    // Constructor to initialize the club with no members
    PinnacleClub() : head(nullptr) {}
    // Function to add a new member to the club
    void addMember(int prn, string name, string position) {
        // Create a new node for the new member
        Node* newNode = new Node{prn, name, nullptr};

        // Adding President: Ensure no other President exists
        if (position == "president") {
            if (head) {
                cout << "A president already exists. Cannot add another president.\n";
                delete newNode;
                return;
            }
            // Set the new node as the first node (President)
            newNode->next = head;
            head = newNode;
        }
        // Adding Secretary: Ensure a President exists before adding a Secretary
        else if (position == "secretary") {
            if (!head) {
                cout << "Add a president first!\n";
                delete newNode;
                return;
            }
            // Traverse to the end of the list to add Secretary
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        // Adding a regular member: Ensure President and Secretary exist first
        else {
            if (!head || !head->next) {
                cout << "A president and secretary must be present before adding members.\n";
                delete newNode;
                return;
            }
            // Traverse to the second-last node to add the new member
            Node* temp = head;
            while (temp->next && temp->next->next) {
                temp = temp->next;
            }
            // Insert the new member at the end of the list
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Function to delete a member from the club
    void deleteMember(int prn) {
        if (!head) {
            cout << "The club has no members.\n";
            return;
        }

        // If the member to delete is the first (President)
        if (head->prn == prn) {
            Node* temp = head;
            head = head->next;
            delete temp;  // Free memory
            return;
        }

        // Traverse the list to find the member to delete
        Node* temp = head;
        while (temp->next && temp->next->prn != prn) {
            temp = temp->next;
        }

        // If member is found, delete the member
        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;  // Free memory
        } else {
            cout << "Member not found.\n";
        }
    }

    // Function to compute the total number of members in the club
    int totalMembers() {
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;  // Increment count for each member in the list
            temp = temp->next;
        }
        return count;
    }

    // Function to display the list of members
    void displayMembers() {
        if (!head) {
            cout << "The club has no members.\n";
            return;
        }
        Node* temp = head;
        cout << "President: \n";
        cout << "PRN: " << temp->prn << ", Name: " << temp->name << "\n";
        temp = temp->next;
        // Display regular members
        while (temp && temp->next) {
            cout << "Member: \n";
            cout << "PRN: " << temp->prn << ", Name: " << temp->name << "\n";
            temp = temp->next;
        }
        // Display Secretary (last member in the list)
        if (temp) {
            cout << "Secretary: \n";
            cout << "PRN: " << temp->prn << ", Name: " << temp->name << "\n";
        }
    }

    // Function to concatenate two linked lists
    void concatenate(PinnacleClub& other) {
        if (!head) {
            head = other.head;  // If the current list is empty, just point to the other list
        } else {
            Node* temp = head;
            // Traverse to the end of the current list
            while (temp->next) {
                temp = temp->next;
            }
            // Link the end of the current list to the start of the other list
            temp->next = other.head;
        }
        other.head = nullptr;  // Set the other list to null to avoid duplicating the members
    }

    // Destructor to delete all members and free memory when the club object is destroyed
    ~PinnacleClub() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;  // Free memory for each member
        }
    }
};

int main() {
    PinnacleClub divisionA, divisionB;  
    int choice, division, prn, numMembers;
    string name, position;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Members\n";
        cout << "2. Delete Member\n";
        cout << "3. Display Members\n";
        cout << "4. Compute Total Members\n";
        cout << "5. Concatenate Divisions\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:  // Add a new member
                cout << "Enter division (1 for A, 2 for B): ";
                cin >> division;
                cout << "How many members do you want to add? ";
                cin >> numMembers;
                for (int i = 0; i < numMembers; i++) {
                    cout << "Enter PRN: ";
                    cin >> prn;
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Position (president/member/secretary): ";
                    cin >> position;
                    if (division == 1) {
                        divisionA.addMember(prn, name, position);
                    } else if (division == 2) {
                        divisionB.addMember(prn, name, position);
                    } else {
                        cout << "Invalid division.\n";
                    }
                }
                break;

            case 2:  // Delete a member
                cout << "Enter division (1 for A, 2 for B): ";
                cin >> division;
                cout << "Enter PRN to delete: ";
                cin >> prn;
                if (division == 1) {
                    divisionA.deleteMember(prn);
                } else if (division == 2) {
                    divisionB.deleteMember(prn);
                } else {
                    cout << "Invalid division.\n";
                }
                break;

            case 3:  // Display all members
                cout << "Enter division (1 for A, 2 for B): ";
                cin >> division;
                if (division == 1) {
                    divisionA.displayMembers();
                } else if (division == 2) {
                    divisionB.displayMembers();
                } else {
                    cout << "Invalid division.\n";
                }
                break;

            case 4:  // Compute total members
                cout << "Enter division (1 for A, 2 for B): ";
                cin >> division;
                if (division == 1) {
                    cout << "Total Members in Division A: " << divisionA.totalMembers() << "\n";
                } else if (division == 2) {
                    cout << "Total Members in Division B: " << divisionB.totalMembers() << "\n";
                } else {
                    cout << "Invalid division.\n";
                }
                break;

            case 5:  // Concatenate two divisions
                divisionA.concatenate(divisionB);
                cout << "Divisions concatenated. All members are now in Division A.\n";
                break;

            case 6:  // Exit the program
                cout << "Exiting...\n";
                break;

            default:  // Invalid choice
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);  // Repeat until the user chooses to exit

    return 0;
}

