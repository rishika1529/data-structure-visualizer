#include <iostream>
#include <vector>
using namespace std;

// ----------- STACK (Plates as Rectangles) -----------
class Stack {
    vector<int> st;
public:
    void push(int val) {
        st.push_back(val);
        cout << "\n[STACK] Added Plate " << val << "\n";
        display();
    }
    void pop() {
        if(st.empty()) { cout << "\n[STACK] No plates left!\n"; return; }
        cout << "\n[STACK] Removed Plate " << st.back() << "\n";
        st.pop_back();
        display();
    }
    void display() {
        cout << "\nStack of Plates:\n\n";
        if(st.empty()) {
            cout << "[ EMPTY STACK ]\n";
            return;
        }
        for(int i = st.size()-1; i >= 0; i--) {
            cout << "  +---------+\n";
            cout << "  |  " << st[i];
            if(st[i] < 10) cout << " "; // For alignment
            cout << "    |\n";
            cout << "  +---------+\n";
        }
        cout << endl;
    }
};

// ----------- QUEUE (People in a Line with simple chars) -----------
class Queue {
    vector<int> q;
public:
    void enqueue(int val) {
        q.push_back(val);
        cout << "\n[QUEUE] Person " << val << " joined the line.\n";
        display();
    }
    void dequeue() {
        if(q.empty()) { cout << "\n[QUEUE] No one in line!\n"; return; }
        cout << "\n[QUEUE] Person " << q.front() << " left the line.\n";
        q.erase(q.begin());
        display();
    }
    void display() {
        cout << "\nQueue of People:\n\n";
        if(q.empty()) {
            cout << "[ EMPTY QUEUE ]\n";
            return;
        }
        for(size_t i = 0; i < q.size(); i++) {
            cout << "[P" << q[i] << "] ";
        }
        cout << "\n(Front -> Back)\n\n";
    }
};

// ----------- LINKED LIST (Boxes with Arrows) -----------
struct Node {
    int data;
    Node* next;
    Node(int val): data(val), next(NULL) {}
};

class LinkedList {
    Node* head;
public:
    LinkedList(): head(NULL) {}
    void insert(int val) {
        Node* newNode = new Node(val);
        if(!head) head = newNode;
        else {
            Node* temp = head;
            while(temp->next) temp = temp->next;
            temp->next = newNode;
        }
        cout << "\n[LINKED LIST] Inserted " << val << "\n";
        display();
    }
    void remove() {
        if(!head) { cout << "\n[LINKED LIST] Empty!\n"; return; }
        Node* temp = head;
        head = head->next;
        cout << "\n[LINKED LIST] Removed " << temp->data << "\n";
        delete temp;
        display();
    }
    void display() {
        cout << "\nLinked List Visualization:\n\n";
        if(!head) {
            cout << "[ EMPTY LIST ]\n";
            return;
        }
        Node* temp = head;
        while(temp) {
            cout << "[ " << temp->data << " ]";
            if(temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << " -> NULL\n\n";
    }
};

// ----------- MAIN MENU -----------
int main() {
    Stack s;
    Queue q;
    LinkedList l;
    int choice, val;
    while(true) {
        cout << "\n--- Data Structure Visualizer ---\n";
        cout << "1. Push Plate (Stack)\n2. Pop Plate (Stack)\n";
        cout << "3. Add Person (Queue)\n4. Remove Person (Queue)\n";
        cout << "5. Insert Node (Linked List)\n6. Remove Node (Linked List)\n";
        cout << "7. Exit\nChoice: ";
        cin >> choice;
        switch(choice) {
            case 1: cout << "Enter Plate number: "; cin >> val; s.push(val); break;
            case 2: s.pop(); break;
            case 3: cout << "Enter Person number: "; cin >> val; q.enqueue(val); break;
            case 4: q.dequeue(); break;
            case 5: cout << "Enter Node value: "; cin >> val; l.insert(val); break;
            case 6: l.remove(); break;
            case 7: return 0;
            default: cout << "Invalid!\n";
        }
    }
}

