#pragma once
#include "libs.h"
#include "error.h"
#include "Product.h"
class File {
private:
    fstream file;
    string path;
    int key, size;

public:
    File() {
        this->path = "Nothing";
        this->key = 0;
        this->size = 0;
    }
    File(string path, int key) {
        this->path = path;
        this->key = key;
        this->size = 0;
    }
    ~File() {}
    void open(string mode) {
        switch (this->key)
        {
            case 1:
                if (mode == "r") file.open(path, ios::in);
                if (mode == "add") file.open(path, ios::app);
                if (mode == "w") file.open(path, ios::out);
                if (mode == "wr") file.open(path, ios::in | ios::out);
                break;
            case 2:
                if (mode == "r") file.open(path, ios::binary | ios::in);
                if (mode == "add") file.open(path, ios::binary | ios::app);
                if (mode == "w") file.open(path, ios::binary | ios::out);
                if (mode == "wr") file.open(path, ios::binary | ios::in | ios::out);
                break;
            default:
                break;
        }
        try {
            if (!file.is_open())
            {
                throw 1;
            }
        }
        catch (int i)
        {
            Exception ex(i);
            ex.Print();
            return;
        }
    }
    void close() {
        file.close();
    }
    void begin() {
        this->file.seekg(0, ios_base::beg);
    }
    void set_size(int s) {
        this->size = s;
    }
    int get_size() {
        return this->size;
    }
    void sortName();
    void sortNumber();
    void sortPrice();
    void sortDate();
    void edit(int line);
    Product get_item() {
        string str;
        int number;
        double price;
        Product item;
        getline(this->file, str, ' ');
        item.set_name(str);
        getline(this->file, str, ' ');
        number = stoi(str);
        item.set_number(number);
        getline(this->file, str, ' ');
        price = stod(str);
        item.set_price(price);
        getline(this->file, str);
        item.set_data(str);
        return item;
    }
    friend Product& operator<<(Product& item, File& f);
    friend File& operator<<(File& file, const char* s);
    friend ostream& operator<<(ostream& out, File& file);
    friend File& operator<<(File& file, Product& item);
    friend File* operator<<(File* file, Product& item);
};
