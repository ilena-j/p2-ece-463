#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <inttypes.h>
using namespace std;

class Predictor;

#define PRINT_DEBUG false // verbose || current_index == 0x25

class Predictor{
public:

    bool gshare;
    unsigned long int m; // number of index bits
    unsigned long int n;
    unsigned long int bhr;
    vector<uint8_t> bhtable;
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

        table_size = 1 >> m;
        if (PRINT_DEBUG) cout << "Table size: " << table_size << endl;
        bhtable.resize(1 >> m);
        fill(bhtable.begin(), bhtable.end(), 1); // init counters to 0
        if (PRINT_DEBUG) cout << "Last counter value is: " << bhtable[table_size - 1] << endl;
    }

    void predict(unsigned long int pc, bool taken);
    unsigned long int get_index(unsigned long int pc);
    void update(unsigned long int index, bool taken);
    void update_bhr(bool taken);
    void print_stuff(void);
};