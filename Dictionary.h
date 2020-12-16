#pragma once
#include "libs.h"
#include "error.h"
#include "Wear.h"
#include "file.h"
#include "Product.h"
class Dictionary {
public:
    static int size;
    class Node {
    public:
        Node* next;
        Node* prev;
        Product item;
        Wear key;
        Node(Product info) {
            this->item = info;
            next = nullptr;
            prev = nullptr;
        }
        Node() {
            next = nullptr;
            prev = nullptr;

        }
//        Node& operator[](int index) {
//            Node* temp = head;
//            int count = 0;
//            while (count != index) {
//                count++;
//                temp = temp->next;
//            }
//            return temp;
//        }
        Node& operator=(Node it) {
            next = it.next;
            prev = it.prev;
            item = it.item;
            key.name = it.key.name;
            key.cost = it.key.cost;
            key.id = it.key.id;
            return *this;
        }
    };
    class Iterator {
    private:
        Node* temp;
    public:
        Iterator() {
            temp = nullptr;
        }
        Iterator(Node* the_node) {
            temp = the_node;
        }
        Iterator& operator++() {
            try {
                if (size == 0) {
                    throw 3;
                }
            }
            catch (int i) {
                Exception ex(i);
                ex.Print();
            }
            temp = temp->next;
            return *this;
        }
        Iterator& operator--() {
            try {
                if (size == 0) {
                    throw 3;
                }
            }
            catch (int i) {
                Exception ex(i);
                ex.Print();
            }
            temp = temp->prev;
            return *this;
        }
        Iterator& operator=(Iterator it) {
            temp = it.temp;
            return *this;
        }
        bool operator == (const Iterator& it) const
        {
            return (temp == it.temp);
        }
        bool operator!=(const Iterator& it) const
        {
            return !(it == *this);
        }
        Product& operator*() {
            return temp->item;
        }
        Iterator& operator+(int info) {
            int i = 0;
            while (i < info) {
                temp = temp->next;
                i++;
            }
            return *this;
        }
    };
private:
    Node* head;
    Node* tail;
    Iterator* head_iterator;
    Iterator* tail_iterator;
public:
    Dictionary() {
        head = nullptr;
        tail = nullptr;
        head_iterator = nullptr;
        tail_iterator = nullptr;
    }
    int Size() {
        return size;
    }
    void push(Product info) {
        Node* temp = new Node(info);
        temp->next = nullptr;
        if (head == nullptr) {
            temp->prev = nullptr;
            tail = temp;
            head = temp;
            head_iterator = new Iterator(head);
        }
        else {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
            tail_iterator = new Iterator(tail);
        }
        size++;
    }
    void print() {
        try {
            if (size == 0) {
                throw 3;//empty
            }
        }
        catch (int i) {
            Exception ex(i);
            ex.Print();
            return;
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->item << " " << temp->key << endl;
            temp = temp->next;
        }
    }


    void find(int id) {
        try {
            if (size == 0) {
                throw 3;
            }
        }
        catch (int i) {
            Exception ex(i);
            ex.Print();
            return;
        }
        Node* temp = head;
        int fl = 0;
        while (temp != nullptr) {
            if (temp->key.id == id) {
                cout << "FIND: " << temp->item << "   key: " << temp->key;
                fl = 1;
            }
            temp = temp->next;
        }
        if (fl == 0) {
            cout << "There isn't such object in the list";
        }
    }
    Node*& operator[](int index) {
        try {
            if (size == 0) {
                throw 3;
            }
        }
        catch (int i) {
            Exception ex(i);
            ex.Print();
        }
        Node* temp = head;
        int count = 0;
        while (count != index) {
            count++;
            temp = temp->next;
        }
        return temp;
    }
    Iterator& begin() {
        try {
            if (size == 0) {
                throw 3;
            }
        }
        catch (int i) {
            Exception ex(i);
            ex.Print();
        }
        return *head_iterator;
    }

    Iterator& end() {
        try {
            if (size == 0) {
                throw 3;
            }
        }
        catch (int i) {
            Exception ex(i);
            ex.Print();

        }
        return *tail_iterator;
    }
    Product remove_front()
    {

        try {
            if (size == 0) {
                throw 3;
            }
        }
        catch (int i) {
            Exception ex(i);
            ex.Print();
        }
        Node* node_to_remove = head;
        Product return_val = node_to_remove->item;
        head = node_to_remove->next;
        head->prev = 0;
        head_iterator = new Iterator(head);

        delete node_to_remove;
        size--;
        return return_val;

    }
    void paste_sort(Dictionary& list) {
        try {
            if (size == 0) {
                throw 3;
            }
        }
        catch (int i) {
            Exception ex(i);
            ex.Print();
            return;
        }
        class Node* temp = new Node();
        int item;
        for (int counter = 1; counter < list.Size(); counter++)
        {
            temp = list[counter];
            item = counter - 1;
            while (item >= 0 && list[item]->key.id < temp->key.id)
            {
                list[item + 1] = list[item];
                list[item] = temp;
                item--;
            }
        }
    }
    void find2(Dictionary &list){
        string date;
        double price;
        cout<<"Vvedite date:"<<endl;
        cin>>date;
        cout<<date;
        cout<<"Vvedite price:"<< endl;
        cin>>price;
        try {
            if (size == 0) {
                throw 3;
            }
        }
        catch (int i) {
            Exception ex(i);
            ex.Print();
            return;
        }
        Iterator i1=list.end();
        int fl = 1,i=0;
        for (int j = 0; j < list.Size(); j++) {
            fl=0;
            if ( (*i1).get_price()>price) {
                string day(date,0,2);
                string m(date,3,2);
                string year(date, 6,4);
                int d,mt,d2,mt2,y2;
                int y;
                d=stoi(day);
                mt=stoi(m);
                y=stoi(year);
                string day1((*i1).get_date(),0,2);
                string m1((*i1).get_date(),3,2);
                string year1((*i1).get_date(), 6,4);
                d2=stoi( day1);
                mt2=stoi(m1);
                y2=stoi(year1);
                if(y2<=y){
                    if (y2<y){
                        fl=1;
                    }
                    if(mt2<=mt){
                        if(mt2<mt)fl=1;
                        if(d2<=d){
                            fl = 1;
                        }
                    }
                }
            }
            if(fl==1){
                cout << "FIND: " << (*i1) ;
                i++;
            }
            --i1;
        }
        if (i == 0) {
            cout << "There isn't such object in the list";
        }
    }

};
int Dictionary::size = 0;

