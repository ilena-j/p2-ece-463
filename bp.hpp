#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <inttypes.h>
using namespace std;

class Predictor;

#define PRINT_DEBUG false

class Predictor {
public:

    bool gshare;
    unsigned long int m; // number of index bits
    unsigned long int n;
    unsigned long int bhr;
    vector<int> bhtable;
    size_t table_size;

    unsigned long int predictions; // statistics
    unsigned long int mispredictions;

    Predictor(unsigned long int _m, unsigned long int _n, bool _gshare) {
        m = _m;
        n = _n;
        gshare = _gshare;
        bhr = 0;

        predictions = 0;
        mispredictions = 0;

        cout << "m: " << m << " n: " << n << " gshare: " << gshare << endl;

        table_size = 1 << m;
        if (PRINT_DEBUG) cout << "Table size: " << table_size << endl;
        //bhtable.resize(table_size);
        //fill(bhtable.begin(), bhtable.end(), 2); // init counters to 2

        for (size_t i = 0; i < table_size; i++) {
            bhtable.push_back(2);
        }

        if (PRINT_DEBUG) cout << "Last counter value is: " << bhtable[0] << endl;
    }

    void predict(unsigned long int pc, bool taken);
    unsigned long int get_index(unsigned long int pc);
    void update(unsigned long int index, bool taken);
    void update_bhr(bool taken);
    void print_stuff(void);
};