#pragma once
#include "libs.h"
class Wear
{
public:
    static int i;
    int id;
    string name;
    int cost;
public:
    void randomize()
    {
        this->cost = 1 + rand() % 1650;
    }
    Wear();
    Wear(string a, int b);
    ~Wear();
    Wear& operator=(const Wear it);
    friend bool operator==(Wear it1, Wear it2);
    friend ostream& operator<<(ostream& out, const Wear it);
};
