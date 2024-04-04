#ifndef stack_hpp
#define stack_hpp

#include <iostream>
using namespace std;

template <class T>
class stack {
    private:
        struct node {
            T info;
            node* next;
            node(T i, node* n) : info(i), next(n) { }
            node() : next(nullptr) { }
        };
        node *head, *z;
        int count;
    public:
        stack() {
            head = new node;
            z = new node;
            head->next = z;
            z->next = z;
            count = 0;
        }
        stack(const stack& st) {
            node d; node* t = &d;
            head = new node;
            z = new node;
            head->next = z;
            z->next = z;
            count = 0;
            for (node* it = st.head->next; it != st.z; it = it->next) {
                t->next = new node(it->info, nullptr);
                t = t->next;
                count++;
            }
            t->next = z;
            head->next = d.next;
        }
        ~stack() {
            while (head != z) {
                node* x = head;
                head = head->next;
                delete x;
            }
            delete z;
        }
        int size() const { return count; }
        bool empty() const { return head->next == z; }
        void push(T info) { head->next = new node(info, head->next); }
        T pop() { 
            T ret = head->next->info;
            node* t = head->next;
            head->next = head->next->next;
            delete t;
            return ret;
        }
        T top() {
            return head->next->info;
        }
};

#endif