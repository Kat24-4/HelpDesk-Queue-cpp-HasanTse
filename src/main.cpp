// Mini Project 03 - Help Desk Ticketing System
// Nashita Hasan, Katherine Tse
// EECE 7205 - Fundamentals of Computer Engineering


// Build (from inside the "Mini Project 03" folder):
//   g++ -std=c++17 -Wall -o MiniProject03_HasanTse MiniProject03_HasanTse.cpp
// Run:
//   ./MiniProject03_HasanTse          (interactive menu)
//   ./MiniProject03_HasanTse test     (scripted test of every feature, uses tickets.csv)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// ===================== Feature 1: Classes =====================

class Ticket {
public:
    int ID;
    string Name;
    string Category;
    int Minutes;
    Ticket* NextTicket;

    Ticket(int id, string name, string cat, int min)
        : ID(id), Name(name), Category(cat), Minutes(min), NextTicket(nullptr) {}
};

class Action {
public:
    Ticket* ticket;
    string action;          // "Add", "Serve", or "Cancel"
    Action* NextAction;

    Action(Ticket* t, string a) : ticket(t), action(a), NextAction(nullptr) {}
};

class ActionStack {
private:
    Action* Top;
    int Count;

public:
    ActionStack() : Top(nullptr), Count(0) {}

    ~ActionStack() {
        while (Top != nullptr) {
            Action* temp = Top;
            Top = Top->NextAction;
            delete temp;
        }
    }

    // Feature 6: push an action
    void AddAction(Ticket* ticket, string action) {
        Action* newAction = new Action(ticket, action);
        newAction->NextAction = Top;
        Top = newAction;
        Count++;
    }

    // Feature 6: pop an action (caller owns the returned Action)
    Action* PopAction() {
        if (Top == nullptr) return nullptr;
        Action* topAction = Top;
        Top = Top->NextAction;
        topAction->NextAction = nullptr;
        Count--;
        return topAction;
    }

    // Used by the TicketQueue destructor to free tickets that only the stack still references
    void CollectTickets(set<Ticket*>& out) const {
        for (Action* a = Top; a != nullptr; a = a->NextAction) out.insert(a->ticket);
    }
};

class TicketQueue {
private:
    Ticket* Front;
    Ticket* Rear;
    int Count;
    int nextID;
    ActionStack Actions;

    static string Trim(const string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == string::npos) return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

public:
    TicketQueue() : Front(nullptr), Rear(nullptr), Count(0), nextID(0) {}

    ~TicketQueue() {
        // Served/cancelled tickets live only in the action stack (so Undo can restore them),
        // so gather every ticket from both places and delete each exactly once.
        set<Ticket*> all;
        for (Ticket* t = Front; t != nullptr; t = t->NextTicket) all.insert(t);
        Actions.CollectTickets(all);
        for (Ticket* t : all) delete t;
    }

    int GetCount() const { return Count; }

    // ===================== Feature 2: Add and Serve =====================

    void Add(string name, string cat, int min) {
        Ticket* newTicket = new Ticket(nextID, name, cat, min);
        nextID++;
        if (Front == nullptr) {
            Front = newTicket;
        } else {
            Rear->NextTicket = newTicket;
        }
        Rear = newTicket;
        Count++;
        cout << "New Ticket Added! Ticket ID: " << newTicket->ID << endl;
        Actions.AddAction(newTicket, "Add");
    }

    void Serve() {
        if (Front == nullptr) {
            cout << "There are no tickets! The Queue is empty." << endl;
            return;
        }
        Ticket* currTicket = Front;
        Front = currTicket->NextTicket;
        if (Front == nullptr) Rear = nullptr;
        currTicket->NextTicket = nullptr;
        Count--;
        cout << "Ticket: " << currTicket->ID << " was served in " << currTicket->Minutes
             << " minutes. Requestor: " << currTicket->Name
             << ", Category: " << currTicket->Category << endl;
        Actions.AddAction(currTicket, "Serve");
    }

    // ===================== Feature 3: Print =====================

    void Print() const {
        if (Front == nullptr) {
            cout << "There are no tickets! The Queue is empty." << endl;
            return;
        }
        int totalMinutes = 0;
        // ==For Two Agents==
        // int agent1Min = 0;
        // int agent2Min = 0;
        // int currAgent = 1; 
        for (Ticket* currTicket = Front; currTicket != nullptr; currTicket = currTicket->NextTicket) {

            cout << "Ticket " << currTicket->ID << " - Requestor: " << currTicket->Name
                 << ", Category: " << currTicket->Category
                 << ", Task Time: " << currTicket->Minutes
                 << ", Wait Time: " << totalMinutes << endl; 
            totalMinutes += currTicket->Minutes;
            
            // == For Two Agents ==
            // if (currAgent == 1) {
            //     cout << ", Wait Time (Agent 1): " << agent1Min << endl;
            //     agent1Min += currTicket->Minutes;
            //     currAgent = 2;
            // } else {
            //     cout << ", Wait Time (Agent 2): " << agent2Min << endl;
            //     agent2Min += currTicket->Minutes;
            //     currAgent = 1;
            // }
        }
        cout << "Total Waiting Minutes: " << totalMinutes << endl;

        // == For Two Agents ==
        // cout << "Total Waiting Minutes Agent 1: " << agent1Min << endl;
        // cout << "Total Waiting Minutes Agent 2: " << agent2Min << endl;
    }

    // ===================== Feature 4: Search by ID or Name =====================

    void Search(int id) const {
        if (Front == nullptr) {
            cout << "There are no tickets! The Queue is empty." << endl;
            return;
        }
        int totalMinutes = 0;
        int position = 1;
        for (Ticket* currTicket = Front; currTicket != nullptr; currTicket = currTicket->NextTicket) {
            if (currTicket->ID == id) {
                cout << "Ticket " << currTicket->ID << endl;
                cout << "Ticket position in line: " << position << endl;
                cout << "Estimated wait time: " << totalMinutes << " minutes." << endl;
                return;
            }
            totalMinutes += currTicket->Minutes;
            position++;
        }
        cout << "Ticket was not found in the queue." << endl;
    }

    void Search(const string& name) const {
        if (Front == nullptr) {
            cout << "There are no tickets! The Queue is empty." << endl;
            return;
        }
        int totalMinutes = 0;
        int position = 1;
        for (Ticket* currTicket = Front; currTicket != nullptr; currTicket = currTicket->NextTicket) {
            if (currTicket->Name == name) {
                cout << "Ticket for " << currTicket->Name << endl;
                cout << "Position in line: " << position << endl;
                cout << "Estimated wait time: " << totalMinutes << " minutes." << endl;
                return;
            }
            totalMinutes += currTicket->Minutes;
            position++;
        }
        cout << "Ticket was not found in the queue." << endl;
    }

    // ===================== Feature 5: Cancel =====================

    void Cancel(int id) {
        if (Front == nullptr) {
            cout << "There are no tickets! The Queue is empty." << endl;
            return;
        }
        Ticket* currTicket = Front;
        Ticket* prevTicket = nullptr;
        while (currTicket != nullptr) {
            if (currTicket->ID == id) {
                if (currTicket == Front) {
                    Front = currTicket->NextTicket;
                    if (Front == nullptr) Rear = nullptr;
                } else if (currTicket == Rear) {
                    prevTicket->NextTicket = nullptr;
                    Rear = prevTicket;
                } else {
                    prevTicket->NextTicket = currTicket->NextTicket;
                }
                currTicket->NextTicket = nullptr;
                Count--;
                cout << "Ticket " << id << " cancelled." << endl;
                Actions.AddAction(currTicket, "Cancel");
                return;
            }
            prevTicket = currTicket;
            currTicket = currTicket->NextTicket;
        }
        cout << "Ticket was not found in the queue." << endl;
    }

    // ===================== Feature 6: Undo =====================

    void Undo() {
        Action* currAction = Actions.PopAction();
        if (currAction == nullptr) {
            cout << "Nothing to undo." << endl;
            return;
        }
        Ticket* t = currAction->ticket;

        if (currAction->action == "Add") {
            // The added ticket is always the Rear at this point (later actions were undone first)
            if (Front == t) {
                Front = nullptr;
                Rear = nullptr;
            } else {
                Ticket* currTicket = Front;
                while (currTicket->NextTicket != t) currTicket = currTicket->NextTicket;
                Rear = currTicket;
                currTicket->NextTicket = nullptr;
            }
            Count--;
            delete t;
            cout << "Add Undone." << endl;
        } else if (currAction->action == "Serve") {
            t->NextTicket = Front;
            Front = t;
            if (Rear == nullptr) Rear = t;
            Count++;
            cout << "Serve Undone." << endl;
        } else if (currAction->action == "Cancel") {
            if (Front == nullptr) {
                t->NextTicket = nullptr;
                Front = t;
                Rear = t;
            } else {
                // Reinsert in ID order (IDs increase in arrival order)
                Ticket* currTicket = Front;
                Ticket* prevTicket = nullptr;
                while (currTicket != nullptr && currTicket->ID < t->ID) {
                    prevTicket = currTicket;
                    currTicket = currTicket->NextTicket;
                }
                if (prevTicket == nullptr) {
                    t->NextTicket = Front;
                    Front = t;
                } else {
                    t->NextTicket = currTicket;
                    prevTicket->NextTicket = t;
                    if (currTicket == nullptr) Rear = t;
                }
            }
            Count++;
            cout << "Cancel Undone." << endl;
        } else {
            cout << "Invalid Action" << endl;
        }
        delete currAction;
    }

    // ===================== Feature 7: Load and Save =====================

    void Load(const string& file) {
        ifstream loadFile(file);
        if (!loadFile.is_open()) {
            cout << "Could Not Open File." << endl;
            return;
        }
        string line, word;
        int lineNum = 0;
        while (getline(loadFile, line)) {
            lineNum++;
            if (Trim(line).empty()) continue;
            vector<string> row;
            stringstream stringStream(line);
            while (getline(stringStream, word, ',')) row.push_back(Trim(word));
            if (row.size() < 3) {
                cout << "Skipping malformed line " << lineNum << ": " << line << endl;
                continue;
            }
            try {
                int minutes = stoi(row[2]);
                Add(row[0], row[1], minutes);
            } catch (const exception&) {
                cout << "Skipping line " << lineNum << " (minutes is not a number): " << line << endl;
            }
        }
        loadFile.close();
        cout << "Tickets from file added to queue!" << endl;
    }

    void Save(const string& file) const {
        ofstream saveFile(file);
        if (!saveFile.is_open()) {
            cout << "Could Not Open File." << endl;
            return;
        }
        for (Ticket* currTicket = Front; currTicket != nullptr; currTicket = currTicket->NextTicket) {
            saveFile << currTicket->Name << "," << currTicket->Category << ","
                     << currTicket->Minutes << "\n";
        }
        saveFile.close();
        cout << "Saved tickets in queue!" << endl;
    }
};

// ===================== Scripted test =====================

void header(const string& title) { cout << "\n===== " << title << " =====" << endl; }

void runTests() {
    TicketQueue q;

    header("Empty queue edge cases");
    q.Print();
    q.Serve();
    q.Search(0);
    q.Cancel(0);
    q.Undo();

    header("Load tickets.csv");
    q.Load("data/tickets.csv");
    q.Print();

    header("Serve two tickets");
    q.Serve();
    q.Serve();
    q.Print();

    header("Search by ID (5) and by name (Henry Nguyen), plus a miss");
    q.Search(5);
    q.Search(string("Henry Nguyen"));
    q.Search(99);

    header("Cancel front (2), middle (6), rear (9)");
    q.Cancel(2);
    q.Cancel(6);
    q.Cancel(9);
    q.Print();

    header("Undo the three cancels (should restore 9, 6, 2 in ID order)");
    q.Undo();
    q.Undo();
    q.Undo();
    q.Print();

    header("Undo the two serves (0 and 1 return to the front)");
    q.Undo();
    q.Undo();
    q.Print();

    header("Add a ticket, then undo the add");
    q.Add("Kevin Brooks", "Network", 22);
    q.Print();
    q.Undo();
    q.Print();

    header("Save to saved_tickets.csv and reload into a new queue");
    q.Save("saved_tickets.csv");
    TicketQueue q2;
    q2.Load("saved_tickets.csv");
    q2.Print();
    cout << "Original count: " << q.GetCount() << ", reloaded count: " << q2.GetCount() << endl;

    header("Undo everything in the reloaded queue until empty");
    while (q2.GetCount() > 0) q2.Undo();
    q2.Print();
    q2.Undo();
}

// ===================== Interactive menu =====================

void runMenu() {
    TicketQueue q;
    int choice = -1;
    while (choice != 0) {
        cout << "\n--- Help Desk Menu ---\n"
             << "1. Add ticket\n2. Serve ticket\n3. Print queue\n"
             << "4. Search by ID\n5. Search by name\n6. Cancel ticket\n"
             << "7. Undo\n8. Load from file\n9. Save to file\n0. Exit\n"
             << "Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        string name, cat, file;
        int num;
        switch (choice) {
            case 1:
                cout << "Requestor name: "; getline(cin, name);
                cout << "Category: "; getline(cin, cat);
                cout << "Minutes: ";
                if (cin >> num) q.Add(name, cat, num);
                else { cout << "Invalid minutes." << endl; cin.clear(); }
                cin.ignore(10000, '\n');
                break;
            case 2: q.Serve(); break;
            case 3: q.Print(); break;
            case 4:
                cout << "Ticket ID: ";
                if (cin >> num) q.Search(num); else cin.clear();
                cin.ignore(10000, '\n');
                break;
            case 5:
                cout << "Requestor name: "; getline(cin, name);
                q.Search(name);
                break;
            case 6:
                cout << "Ticket ID: ";
                if (cin >> num) q.Cancel(num); else cin.clear();
                cin.ignore(10000, '\n');
                break;
            case 7: q.Undo(); break;
            case 8:
                cout << "File name: "; getline(cin, file);
                q.Load(file);
                break;
            case 9:
                cout << "File name: "; getline(cin, file);
                q.Save(file);
                break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "test") runTests();
    else runMenu();
    return 0;
}
