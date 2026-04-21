#include <iostream>
using namespace std;


struct Customer {
    int userID;
    char name[100];
    char cnic[20];
    char contact[20];
    char date[15];
    char time[10];
    char destination[100];
    int ticketNumber;
    char type[10];

    Customer* next;
    Customer* allNext;
};

Customer* vipFront = NULL;
Customer* vipRear  = NULL;
Customer* regFront = NULL;
Customer* regRear  = NULL;


Customer* allHead = NULL;
Customer* allTail = NULL;
int totalCustomers = 0;


Customer* recentCustomer = NULL;
int ticketCounter = 1;


void copyString(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void printBorder() {
    for (int i = 0; i < 60; i++)
        cout << "=";
    cout << endl;
}


void printHeader(const char title[]) {
    clearScreen();
    cout << endl;
    printBorder();
    cout << "  " << title << endl;
    printBorder();
    cout << endl;
}


void pause() {
    cout << "\n  Press ENTER to return to menu...";
    cin.ignore();
    cin.get();
}


void displayWelcome() {
    clearScreen();
    cout << "\n\n\n";
    printBorder();
    cout << "\n            TICKET QUEUE SIMULATION SYSTEM\n";
    cout << "\n               DSA Final Project - 2025\n\n";
    printBorder();
    cout << "\n\n  Press ENTER to continue...";
    cin.get();
}


void displayCustomer(Customer* c) {
    cout << "\n";
    cout << "  Type        : " << c->type << endl;
    cout << "  User ID     : " << c->userID << endl;
    cout << "  Name        : " << c->name << endl;
    cout << "  CNIC        : " << c->cnic << endl;
    cout << "  Contact     : " << c->contact << endl;
    cout << "  Travel Date : " << c->date << endl;
    cout << "  Travel Time : " << c->time << endl;
    cout << "  Destination : " << c->destination << endl;

    if (c->ticketNumber > 0)
        cout << "  Ticket No.  : #" << c->ticketNumber << endl;
}


Customer* inputCustomer(bool isVIP) {
    Customer* c = new Customer;
    c->next = NULL;
    c->allNext = NULL;
    c->ticketNumber = 0;

    if (isVIP) {
        copyString(c->type, "VIP");
        printHeader("VIP CUSTOMER REGISTRATION");
    } else {
        copyString(c->type, "REGULAR");
        printHeader("REGULAR CUSTOMER REGISTRATION");
    }

    cout << "  Enter User ID: ";
    cin >> c->userID;
    cin.ignore();

    cout << "  Enter Full Name: ";
    cin.getline(c->name, 100);

    cout << "  Enter CNIC (13 digits): ";
    cin.getline(c->cnic, 20);

    cout << "  Enter Contact Number: ";
    cin.getline(c->contact, 20);

    cout << "  Enter Travel Date (DD-MM-YYYY): ";
    cin.getline(c->date, 15);

    cout << "  Enter Travel Time (HH:MM): ";
    cin.getline(c->time, 10);

    cout << "  Enter Destination: ";
    cin.getline(c->destination, 100);

    return c;
}


void enqueue(bool isVIP) {
    Customer* c = inputCustomer(isVIP);


    if (isVIP) {
        if (vipRear == NULL)
            vipFront = vipRear = c;
        else {
            vipRear->next = c;
            vipRear = c;
        }
    } else {
        if (regRear == NULL)
            regFront = regRear = c;
        else {
            regRear->next = c;
            regRear = c;
        }
    }


    if (allTail == NULL)
        allHead = allTail = c;
    else {
        allTail->allNext = c;
        allTail = c;
    }

    recentCustomer = c;
    totalCustomers++;

    cout << "\n\n";
    printBorder();
    cout << "                   SAVED SUCCESSFULLY\n";
    displayCustomer(c);
    printBorder();
    pause();
}


void dequeue(bool isVIP) {
    printHeader(isVIP ? "SERVE VIP CUSTOMER" : "SERVE REGULAR CUSTOMER");

    Customer* temp = NULL;

    if (isVIP) {
        if (vipFront == NULL) {
            cout << "  [INFO] VIP Queue is empty!\n";
            pause();
            return;
        }
        temp = vipFront;
        vipFront = vipFront->next;
        if (vipFront == NULL) vipRear = NULL;
    } else {
        if (regFront == NULL) {
            cout << "  [INFO] Regular Queue is empty!\n";
            pause();
            return;
        }
        temp = regFront;
        regFront = regFront->next;
        if (regFront == NULL) regRear = NULL;
    }

    temp->ticketNumber = ticketCounter++;
    cout << "  Customer Served:\n";
    displayCustomer(temp);
    pause();
}


void displayCurrentCustomer() {
    printHeader("CURRENT CUSTOMER INFORMATION");

    if (recentCustomer == NULL)
        cout << "  [INFO] No customers registered yet!\n";
    else
        displayCustomer(recentCustomer);

    pause();
}


void displayAllCustomers() {
    printHeader("ALL CUSTOMERS OF THE DAY");

    if (allHead == NULL) {
        cout << "  [INFO] No customers registered today!\n";
    } else {
        cout << "  Total Customers Registered: " << totalCustomers << "\n\n";
        Customer* temp = allHead;
        int count = 1;

        while (temp != NULL) {
            cout << "  Customer #" << count << endl;
            displayCustomer(temp);
            temp = temp->allNext;
            count++;

            if (temp != NULL) {
                for (int i = 0; i < 60; i++) cout << "-";
                cout << endl;
            }
        }
    }
    pause();
}


void displayMenu() {
    printHeader("MAIN MENU");
    cout << "  1. VIP Customer Registration\n";
    cout << "  2. Regular Customer Registration\n";
    cout << "  3. Serve VIP Customer (Dequeue)\n";
    cout << "  4. Serve Regular Customer (Dequeue)\n";
    cout << "  5. Display Current Customer\n";
    cout << "  6. Display All Customers of the Day\n";
    cout << "  7. Exit System\n\n";
    cout << "  Enter your choice: ";
}


int main() {
    int choice;
    displayWelcome();

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: enqueue(true);  break;
            case 2: enqueue(false); break;
            case 3: dequeue(true);  break;
            case 4: dequeue(false); break;
            case 5: displayCurrentCustomer(); break;
            case 6: displayAllCustomers(); break;
            case 7:
                printHeader("EXIT SYSTEM");
                cout << "\n      Thank you for using Ticket Queue System!\n\n";
                printBorder();
                return 0;
            default:
                cout << "\n  [ERROR] Invalid choice!\n";
                pause();
        }
    }
}
