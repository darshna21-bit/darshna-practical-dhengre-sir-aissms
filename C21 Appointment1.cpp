#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Structure to represent an appointment
struct Appointment {
    string name;      // Name of the appointment holder
    int start;        // Start time of the appointment
    int end;          // End time of the appointment
    Appointment* next; // Pointer to the next appointment in the linked list
};

// Class to manage the appointment schedule
class AppointmentSchedule {
private:
    Appointment* head; // Pointer to the start of the linked list of appointments
    int minDuration;   // Minimum allowed duration for an appointment
    int maxDuration;   // Maximum allowed duration for an appointment

    // Helper function to check if a new appointment overlaps with existing ones
    bool isOverlap(int start, int end) {
        Appointment* temp = head;
        while (temp) {
            // Check if the new appointment's time range overlaps with any existing ones
            if (!(end <= temp->start || start >= temp->end)) {
                return true; // Overlap found
            }
            temp = temp->next;
        }
        return false; // No overlap
    }

public:
    // Constructor to initialize the schedule with given duration limits
    AppointmentSchedule(int minDur, int maxDur) : head(nullptr), minDuration(minDur), maxDuration(maxDur) {}

    // Destructor to free allocated memory
    ~AppointmentSchedule() {
        while (head) {
            Appointment* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to display free time slots between appointments
    void displayFreeSlots(int dayStart, int dayEnd) {
        Appointment* temp = head;
        int lastEnd = dayStart; // Tracks the end of the last scheduled appointment

        cout << "Free slots:\n";
        while (temp) {
            // If there's a gap between the last appointment and the current one, display it
            if (temp->start > lastEnd) {
                cout << "From " << setw(2) << setfill('0') << lastEnd
                     << " to " << setw(2) << setfill('0') << temp->start << "\n";
            }
            lastEnd = temp->end; // Update the last end time
            temp = temp->next;
        }
        // Display any free time after the last appointment until the end of the day
        if (lastEnd < dayEnd) {
            cout << "From " << setw(2) << setfill('0') << lastEnd
                 << " to " << setw(2) << setfill('0') << dayEnd << "\n";
        }
    }

    // Function to book a new appointment
    void bookAppointment(string name, int start, int end) {
        // Check if the appointment duration is within allowed limits
        if (end - start < minDuration || end - start > maxDuration) {
            cout << "Appointment duration is out of bounds.\n";
            return;
        }

        // Check for overlaps with existing appointments
        if (isOverlap(start, end)) {
            cout << "Appointment overlaps with an existing one.\n";
            return;
        }

        // Create a new appointment
        Appointment* newApp = new Appointment{name, start, end, nullptr};

        // Insert the new appointment into the sorted linked list
        if (!head || head->start > end) {
            newApp->next = head; // Insert at the beginning
            head = newApp;
        } else {
            Appointment* temp = head;
            // Traverse to the correct position in the sorted list
            while (temp->next && temp->next->start < start) {
                temp = temp->next;
            }
            newApp->next = temp->next; // Insert the new appointment
            temp->next = newApp;
        }
        cout << "Appointment booked successfully.\n";
    }

    // Function to cancel an existing appointment
    void cancelAppointment(int start, int end) {
        if (!head) {
            cout << "No appointments to cancel.\n";
            return;
        }

        Appointment* temp = head;
        Appointment* prev = nullptr;

        // Find the appointment matching the given time range
        while (temp) {
            if (temp->start == start && temp->end == end) {
                if (prev) {
                    prev->next = temp->next; // Remove from the list
                } else {
                    head = temp->next; // Update head if it's the first node
                }
                delete temp; // Free memory
                cout << "Appointment canceled successfully.\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "No matching appointment found.\n";
    }

    // Function to sort the appointments based on start time
    void sortAppointments() {
        if (!head || !head->next) return; // No need to sort if 0 or 1 appointments

        Appointment* sorted = nullptr;

        while (head) {
            Appointment* current = head;
            head = head->next;

            // Insert the current appointment into the sorted list
            if (!sorted || current->start < sorted->start) {
                current->next = sorted;
                sorted = current;
            } else {
                Appointment* temp = sorted;
                while (temp->next && temp->next->start < current->start) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
        }
        head = sorted;
        cout << "Appointments sorted successfully.\n";
        displayAppointments();
    }

    // Function to display all scheduled appointments
    void displayAppointments() {
        if (!head) {
            cout << "No appointments to display.\n";
            return;
        }
        cout << "Appointments:\n";
        Appointment* temp = head;
        while (temp) {
            cout << "Name: " << temp->name << ", Start: " << temp->start << ", End: " << temp->end << "\n";
            temp = temp->next;
        }
    }
};

// Function to display the main menu
void displayMenu() {
    cout << "\nAppointment Scheduler\n";
    cout << "1. Display Free Slots\n";
    cout << "2. Book Appointment\n";
    cout << "3. Cancel Appointment\n";
    cout << "4. Sort Appointments\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int dayStart = 9; // Start of the working day
    int dayEnd = 17;  // End of the working day
    int minDuration = 1; // Minimum allowed appointment duration
    int maxDuration = 2; // Maximum allowed appointment duration

    AppointmentSchedule schedule(minDuration, maxDuration); // Initialize the schedule
    int choice;

    do {
        displayMenu(); // Show menu options
        cin >> choice; // Take user input

        switch (choice) {
            case 1: {
                schedule.displayFreeSlots(dayStart, dayEnd);
                break;
            }
            case 2: {
                string name;
                int start, end;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter start time and end time (24-hour format): ";
                cin >> start >> end;
                schedule.bookAppointment(name, start, end);
                break;
            }
            case 3: {
                int start, end;
                cout << "Enter start time and end time of appointment to cancel: ";
                cin >> start >> end;
                schedule.cancelAppointment(start, end);
                break;
            }
            case 4: {
                schedule.sortAppointments();
                break;
            }
            case 5: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 5); // Repeat until user chooses to exit

    return 0;
}

