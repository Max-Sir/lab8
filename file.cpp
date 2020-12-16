
#include "file.h"
#include "libs.h"
Product& operator<<(Product& item, File& file) {
    string str;
    std::getline(file.file, str);
    return item;
}
File& operator<<(File& file, const char* s) {
    try {
        if (!file.file.is_open()) throw 1;
    }
    catch (int i)
    {
        Exception ex(i);
        ex.Print();
    }
    string str = s;
    file.file << str;
    return file;
}
ostream& operator<<(ostream& out, File& file) {
    try {
        if (!file.file.is_open()) throw 1;
    }
    catch (int i)
    {
        Exception ex(i);
        ex.Print();
    }
    if (file.key == 1) {
        string str;
        while (!file.file.eof()) {
            std::getline(file.file, str);
            out << str << endl;
        }
    }
    else if (file.key == 2) {
        int i = 0;
        while (i < file.size) {
            size_t len;
            file.file.read((char*)(&len), sizeof(len));
            char* name = new char[len];
            int number = 0;
            double price = 0;
            file.file.read((char*)(name), len);
            name[len - 1] = '\0';
            file.file.read((char*)(&number), sizeof(number));
            file.file.read((char*)(&price), sizeof(price));
            file.file.read((char*)(&len), sizeof(len));
            char* date = new char[len];
            file.file.read((char*)(date), len);
            cout << name << " " << number <<  " " << price << " " << date << endl;
            i++;
            delete []name;
        }
    }
}
File& operator<<(File& file, Product& item) {
    try {
        if (!file.file.is_open()) throw 1;
    }
    catch (int i)
    {
        Exception ex(i);
        ex.Print();
    }
    if(file.key==1) {
        file.file << item.get_name();
        file.file << " ";
        file.file << item.get_number();
        file.file << " ";
        file.file << item.get_price();
        file.file << " ";
        file.file << item.get_date();
        file.file << " ";
        file.file<<"\n";
    }
    else if(file.key==2){
        string name = item.get_name();
        size_t len = name.length() + 1;
        int number = item.get_number();
        double price = item.get_price();
        string data = item.get_date();
        size_t len2 = data.length() + 1;
        file.file.write((char*)(&len), sizeof(len));
        file.file.write((char*)(name.c_str()), len);
        file.file.write((char*)(&number), sizeof(number));
        file.file.write((char *)(&price), sizeof(price));
        file.file.write((char*)(&len2), sizeof(len2));
        file.file.write((char*)(data.c_str()), len2);
    }
    return file;
}
File* operator<<(File* file, Product& item) {
    try {
        if (!file->file.is_open()) throw 1;
    }
    catch (int i)
    {
        Exception ex(i);
        ex.Print();
    }
    if(file->key==1){
        file->file << item.get_name();
        file->file << " ";
        file->file << item.get_number();
        file->file << " ";
        file->file << item.get_price();
        file->file << " ";
        file->file << item.get_date();
        file->file << " ";
    }
    else if(file->key==2){
        string name = item.get_name();
        size_t len = name.length() + 1;
        int number = item.get_number();
        double price = item.get_price();
        string data = item.get_date();
        size_t len2 = data.length() + 1;
        file->file.write((char*)(&len), sizeof(len));
        file->file.write((char*)(name.c_str()), sizeof(len));
        file->file.write((char*)(&number), sizeof(number));
        file->file.write((char *)(&price), sizeof(price));
        file->file.write((char*)(&len2), sizeof(len2));
        file->file.write((char*)(data.c_str()), sizeof(len2));
    }
    return file;
}
void File::sortName(){
    string temp;
    string j1, j2;
    int pos;
    this->open("wr");
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
    for (int i = 0; i < this->size - 1; i++) {
        for (int j = 0; j < this->size - i - 1; j++) {
            this->file.seekg(0, ios_base::beg);
            for (int k = 0; k < j; k++) {
                getline(this->file, j1);
            }
            getline(this->file, j1, ' ');
            getline(this->file, j2);
            getline(this->file, j2, ' ');
            if (j1 > j2) {
                this->file.seekg(0, ios_base::beg);
                pos = this->file.tellg();
                for (int k = 0; k <= j; k++) {
                    getline(this->file, j1);
                    pos = this->file.tellg();
                }
                temp = j1;
                getline(this->file, j2);
                this->file.seekg(0, ios_base::beg);
                for (int k = 0; k < j; k++) {
                    getline(this->file, j1);
                }
                pos = this->file.tellg();
                this->file.seekg(pos, ios_base::beg);
                this->file << j2 << '\n';
                this->file << temp << '\n';
            }
        }
    }
    this->close();

}
void File::sortNumber() {
    string temp;
    string j1, j2;
    int i1, i2;
    int pos;
    this->open("wr");
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
    for (int i = 0; i < this->size - 1; i++) {
        for (int j = 0; j < this->size - i - 1; j++) {
            this->file.seekg(0, ios_base::beg);
            for (int k = 0; k < j; k++) {
                getline(this->file, j1);
            }
            getline(this->file, j1, ' ');
            getline(this->file, j1, ' ');
            getline(this->file, j2);
            getline(this->file, j2, ' ');
            getline(this->file, j2, ' ');
            i1 = stoi(j1);
            i2 = stoi(j2);
            if (i1 > i2) {
                this->file.seekg(0, ios_base::beg);
                pos = this->file.tellg();
                for (int k = 0; k <= j; k++) {
                    getline(this->file, j1);
                    pos = this->file.tellg();
                }
                temp = j1;
                getline(this->file, j2);
                this->file.seekg(0, ios_base::beg);
                for (int k = 0; k < j; k++) {
                    getline(this->file, j1);
                }
                pos = this->file.tellg();
                this->file.seekg(pos, ios_base::beg);
                this->file << j2 << '\n';
                this->file << temp << '\n';
            }
        }
    }
    this->close();
}
void File::sortPrice() {
    string temp;
    string j1, j2;
    double i1, i2;
    int pos;
    this->open("wr");
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
    for (int i = 0; i < this->size - 1; i++) {
        for (int j = 0; j < this->size - i - 1; j++) {
            this->file.seekg(0, ios_base::beg);
            for (int k = 0; k < j; k++) {
                getline(this->file, j1);
            }
            getline(this->file, j1, ' ');
            getline(this->file, j1, ' ');
            getline(this->file, j1, ' ');
            getline(this->file, j2);
            getline(this->file, j2, ' ');
            getline(this->file, j2, ' ');
            getline(this->file, j2, ' ');
            i1 = stod(j1);
            i2 = stod(j2);
            if (i1 > i2) {
                this->file.seekg(0, ios_base::beg);
                pos = this->file.tellg();
                for (int k = 0; k <= j; k++) {
                    getline(this->file, j1);
                    pos = this->file.tellg();
                }
                temp = j1;
                getline(this->file, j2);
                this->file.seekg(0, ios_base::beg);
                for (int k = 0; k < j; k++) {
                    getline(this->file, j1);
                }
                pos = this->file.tellg();
                this->file.seekg(pos, ios_base::beg);
                this->file << j2 << '\n';
                this->file << temp << '\n';
            }
        }
    }
    this->close();
}
void File::sortDate() {
    string temp;
    string j1, j2;
    string i1, i2, i11, i22;
    int pos;
    this->open("wr");
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
    for (int i = 0; i < this->size - 1; i++) {
        for (int j = 0; j < this->size - i - 1; j++) {
            this->file.seekg(0, ios_base::beg);
            for (int k = 0; k < j; k++) {
                getline(this->file, j1);
            }
            getline(this->file, j1, ' ');
            getline(this->file, j1, ' ');
            getline(this->file, j1, ' ');
            getline(this->file, j1, ' ');
            i1 = j1;
            getline(this->file, j2);
            getline(this->file, j2, ' ');
            getline(this->file, j2, ' ');
            getline(this->file, j2, ' ');
            getline(this->file, j2, ' ');
            i2 = j2;
            if (i1 > i2) {
                this->file.seekg(0, ios_base::beg);
                pos = this->file.tellg();
                for (int k = 0; k <= j; k++) {
                    getline(this->file, j1);
                    pos = this->file.tellg();
                }
                temp = j1;
                getline(this->file, j2);
                this->file.seekg(0, ios_base::beg);
                for (int k = 0; k < j; k++) {
                    getline(this->file, j1);
                }
                pos = this->file.tellg();
                this->file.seekg(pos, ios_base::beg);
                this->file << j2 << '\n';
                this->file << temp << '\n';
            }
        }
    }
    this->close();
}
void File::edit(int line) {
    this->open("wr");
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
    Product item;
    if (this->key == 1) {
        string temp;
        for (int i = 0; i < line - 1; i++) {
            getline(this->file, temp);
        }
        getline(this->file, temp, ' ');
        item.set_name(temp);
        getline(this->file, temp, ' ');
        item.set_number(stoi(temp));
        getline(this->file, temp, ' ');
        item.set_price(stod(temp));
        getline(this->file, temp, ' ');
        item.set_data(temp);
    }
    else if (this->key == 2) {
        size_t len;
        for (int i = 0; i < line; i++) {
            size_t len;
            this->file.read((char*)(&len), sizeof(len));
            char* name = new char[len];
            int number = 0;
            double price = 0;
            this->file.read((char*)(name), len);
            name[len - 1] = '\0';
            this->file.read((char*)(&number), sizeof(number));
            this->file.read((char*)(&price), sizeof(price));
            this->file.read((char*)(&len), sizeof(len));
            char* date = new char[len];
            this->file.read((char*)(date), len);
            item.set_name(name);
            item.set_number(number);
            item.set_price(price);
            item.set_data(date);
            delete []name;
            delete []date;
        }
    }
    cout << "What do you want to change?\n1 - name\n2-number\n3-price\n4-date" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: {
            string a;
            cin >> a;
            item.set_name(a);
            break;
        }
        case 2: {
            int a;
            cin >> a;
            item.set_number(a);
            break;
        }
        case 3: {
            double a;
            cin >> a;
            item.set_price(a);
            break;
        }
        case 4: {
            string a;
            cin >> a;
            item.set_data(a);
            break;
        }
    }
    this->file.seekg(0, ios_base::beg);
    if (this->key == 1) {
        string temp;
        for (int i = 0; i < line - 1; i++) {
            getline(this->file, temp);
        }
        int pos = this->file.tellg();
        this->file.seekg(pos, ios_base::beg);
        this->file << item;
    }
    else if (this->key == 2) {
        size_t len;
        for (int i = 0; i < line - 1; i++) {
            size_t len;
            this->file.read((char*)(&len), sizeof(len));
            char* name = new char[len];
            int number = 0;
            double price = 0;
            this->file.read((char*)(name), len);
            name[len - 1] = '\0';
            this->file.read((char*)(&number), sizeof(number));
            this->file.read((char*)(&price), sizeof(price));
            this->file.read((char*)(&len), sizeof(len));
            char* date = new char[len];
            this->file.read((char*)(date), len);
            item.set_name(name);
            item.set_number(number);
            item.set_price(price);
            item.set_data(date);
            delete []name;
            delete []date;
        }
        int pos = this->file.tellg();
        this->file.seekg(pos, ios_base::beg);
        this << item;
    }
    this->close();
}
