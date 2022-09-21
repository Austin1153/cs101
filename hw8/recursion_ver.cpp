#include <iostream>

using namespace std;

class storage {
    public:
        int data;
        char ope;
        storage* next;
        void insert(char op, int val) {
            data = val;
            ope = op;
        }
        bool checkdata() {
            if (data && ope) 
                return true;
            else
                return false;
        }
};

class LinkedList {
    private:
        storage* head;
    public:
        LinkedList() {
            head = NULL;
        }
        void append(char opt ,int value) {
            if (!head) {
                head = (storage*)calloc(1, sizeof(storage));
                head->insert(opt, value);
            } else {
                append(opt, value, head);
            }
        }
        void append(char opt ,int value, storage* locNode) {
            if (!locNode->checkdata()) {
                locNode->insert(opt, value);
            } else if (!locNode->next) {
                locNode->next = (storage*)calloc(1, sizeof(storage));
                append(opt, value, locNode->next);
            } else {
                append(opt, value, locNode->next);
            }
        }
        void free_all_node(storage* locNode) {
            if (!locNode) {
                locNode = head;
            }
            cout << locNode->ope << "  " << locNode->data << endl;
            if (locNode->next) {
                free_all_node(locNode->next);
            }
            free(locNode);
        }
};

int main() {
    int n, data_in;
    char opt_in;
    LinkedList LL;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> opt_in >> data_in;
        LL.append(opt_in, data_in);
    }
    cout << "----------" << endl;
    LL.free_all_node(NULL);
    cout << "all freed" <<endl;

    return 0;
}
