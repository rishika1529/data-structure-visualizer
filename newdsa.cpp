#include <iostream>
#include <vector>
#include <queue>
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

// ----------- GENERIC TREE (Each node can have multiple children) -----------
class GenericTreeNode {
public:
    int data;
    vector<GenericTreeNode*> children;
    GenericTreeNode(int val): data(val) {}
};

class GenericTree {
    GenericTreeNode* root;
public:
    GenericTree(): root(NULL) {}

    GenericTreeNode* findNode(GenericTreeNode* node, int val) {
        if(!node) return NULL;
        if(node->data == val) return node;
        for(auto child : node->children) {
            GenericTreeNode* found = findNode(child, val);
            if(found) return found;
        }
        return NULL;
    }

    void insert(int parentVal, int childVal) {
        if(!root) {
            root = new GenericTreeNode(parentVal);
            GenericTreeNode* child = new GenericTreeNode(childVal);
            root->children.push_back(child);
            cout << "\n[GENERIC TREE] Created root " << parentVal << " and added child " << childVal << "\n";
            display();
            return;
        }
        GenericTreeNode* parentNode = findNode(root, parentVal);
        if(!parentNode) {
            cout << "\n[GENERIC TREE] Parent " << parentVal << " not found!\n";
            return;
        }
        GenericTreeNode* childNode = new GenericTreeNode(childVal);
        parentNode->children.push_back(childNode);
        cout << "\n[GENERIC TREE] Added node " << childVal << " to parent " << parentVal << "\n";
        display();
    }

    void display(GenericTreeNode* node, int depth=0) {
        if(!node) return;
        for(int i=0; i<depth; i++) cout << "  ";
        cout << node->data << "\n";
        for(auto child : node->children) display(child, depth+1);
    }

    void display() {
        cout << "\nGeneric Tree Visualization:\n\n";
        if(!root) {
            cout << "[ EMPTY GENERIC TREE ]\n";
            return;
        }
        display(root);
        cout << endl;
    }
};

// ----------- BINARY SEARCH TREE (BST) -----------
class BSTNode {
public:
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val): data(val), left(NULL), right(NULL) {}
};

class BST {
    BSTNode* root;

    BSTNode* insertNode(BSTNode* node, int val) {
        if(!node) return new BSTNode(val);
        if(val < node->data)
            node->left = insertNode(node->left, val);
        else if(val > node->data)
            node->right = insertNode(node->right, val);
        // ignore duplicates
        return node;
    }

    BSTNode* findMin(BSTNode* node) {
        while(node && node->left) node = node->left;
        return node;
    }

    BSTNode* removeNode(BSTNode* node, int val) {
        if(!node) return NULL;
        if(val < node->data)
            node->left = removeNode(node->left, val);
        else if(val > node->data)
            node->right = removeNode(node->right, val);
        else {
            // node found
            if(!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if(!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // two children
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeNode(node->right, temp->data);
        }
        return node;
    }

    void displayInorder(BSTNode* node) {
        if(!node) return;
        displayInorder(node->left);
        cout << node->data << " ";
        displayInorder(node->right);
    }

public:
    BST(): root(NULL) {}

    void insert(int val) {
        root = insertNode(root, val);
        cout << "\n[BST] Inserted " << val << "\n";
        display();
    }

    void remove(int val) {
        root = removeNode(root, val);
        cout << "\n[BST] Removed " << val << "\n";
        display();
    }

    void display() {
        cout << "\nBST Inorder Traversal:\n";
        if(!root) {
            cout << "[ EMPTY BST ]\n";
            return;
        }
        displayInorder(root);
        cout << "\n\n";
    }
};

// ----------- MAIN MENU -----------
int main() {
    Stack s;
    Queue q;
    LinkedList l;
    GenericTree gt;
    BST bst;

    int choice, val, parentVal;

    while(true) {
        cout << "\n--- Data Structure Visualizer ---\n";
        cout << "1. Push Plate (Stack)\n2. Pop Plate (Stack)\n";
        cout << "3. Add Person (Queue)\n4. Remove Person (Queue)\n";
        cout << "5. Insert Node (Linked List)\n6. Remove Node (Linked List)\n";
        cout << "7. Add Child Node (Generic Tree)\n8. Display Generic Tree\n";
        cout << "9. Insert Node (BST)\n10. Remove Node (BST)\n11. Exit\nChoice: ";
        cin >> choice;

        switch(choice) {
            case 1: cout << "Enter Plate number: "; cin >> val; s.push(val); break;
            case 2: s.pop(); break;
            case 3: cout << "Enter Person number: "; cin >> val; q.enqueue(val); break;
            case 4: q.dequeue(); break;
            case 5: cout << "Enter Node value: "; cin >> val; l.insert(val); break;
            case 6: l.remove(); break;
            case 7: 
                cout << "Enter Parent node value (or root if empty): "; cin >> parentVal;
                cout << "Enter Child node value: "; cin >> val;
                gt.insert(parentVal, val); 
                break;
            case 8:
                gt.display();
                break;
            case 9:
                cout << "Enter value to insert in BST: "; cin >> val;
                bst.insert(val);
                break;
            case 10:
                cout << "Enter value to remove from BST: "; cin >> val;
                bst.remove(val);
                break;
            case 11:
                cout << "Exiting...\n"; return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

