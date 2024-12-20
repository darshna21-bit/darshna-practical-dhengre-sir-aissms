#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Appointment {
    string name;
    int start;
    int end;
    Appointment* next;
};

class AppointmentSchedule {
private:
    Appointment* head;
    int minDuration;
    int maxDuration;

    bool isOverlap(int start, int end) {
        Appointment* temp = head;
        while (temp) {
            if (!(end <= temp->start || start >= temp->end)) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

public:
    AppointmentSchedule(int minDur, int maxDur) : head(nullptr), minDuration(minDur), maxDuration(maxDur) {}

    ~AppointmentSchedule() {
        while (head) {
            Appointment* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void displayFreeSlots(int dayStart, int dayEnd) {
        Appointment* temp = head;
        int lastEnd = dayStart;

        cout << "Free slots:\n";
        while (temp) {
            if (temp->start > lastEnd) {
                cout << "From " << setw(2) << setfill('0') << lastEnd
                     << " to " << setw(2) << setfill('0') << temp->start << "\n";
            }
            lastEnd = temp->end;
            temp = temp->next;
        }
        if (lastEnd < dayEnd) {
            cout << "From " << setw(2) << setfill('0') << lastEnd
                 << " to " << setw(2) << setfill('0') << dayEnd << "\n";
        }
    }

    void bookAppointment(string name, int start, int end) {
        if (end - start < minDuration || end - start > maxDuration) {
            cout << "Appointment duration is out of bounds.\n";
            return;
        }

        if (isOverlap(start, end)) {
            cout << "Appointment overlaps with an existing one.\n";
            return;
        }

        Appointment* newApp = new Appointment{name, start, end, nullptr};

        if (!head || head->start > end) {
            newApp->next = head;
            head = newApp;
        } else {
            Appointment* temp = head;
            while (temp->next && temp->next->start < start) {
                temp = temp->next;
            }
            newApp->next = temp->next;
            temp->next = newApp;
        }
        cout << "Appointment booked successfully.\n";
    }

    void cancelAppointment(int start, int end) {
        if (!head) {
            cout << "No appointments to cancel.\n";
            return;
        }

        Appointment* temp = head;
        Appointment* prev = nullptr;

        while (temp) {
            if (temp->start == start && temp->end == end) {
                if (prev) {
                    prev->next = temp->next;
                } else {
                    head = temp->next;
                }
                delete temp;
                cout << "Appointment canceled successfully.\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "No matching appointment found.\n";
    }

    void sortAppointments() {
        if (!head || !head->next) return;

        Appointment* sorted = nullptr;

        while (head) {
            Appointment* current = head;
            head = head->next;

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
    int dayStart = 9;
    int dayEnd = 17;
    int minDuration = 1;
    int maxDuration = 2;

    AppointmentSchedule schedule(minDuration, maxDuration);
    int choice;

    do {
        displayMenu();
        cin >> choice;

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
    } while (choice != 5);

    return 0;
}

