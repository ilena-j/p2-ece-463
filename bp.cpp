#include <iostream>
#include <vector>
#include <stdio.h>
#include <inttypes.h>
#include "bp.hpp"

void Predictor::predict(unsigned long int pc, bool taken) {
    unsigned long int index = get_index(pc);
    update(index, taken);
    if (gshare) update_bhr(taken);
}

void Predictor::update(unsigned long int index, bool taken) {

    bool predict_taken = false;

    if (bhtable[index] > 1) {
        if (PRINT_DEBUG) cout << "Predict T at index: " << index << endl;
        predict_taken = true;
    }
    else {
        if (PRINT_DEBUG) cout << "Predict N at index: " << index << endl;
    }

    // update table
    if (taken) {
        if (bhtable[index] < 3) bhtable[index] = bhtable[index] + 1;
    }
    else {
        if (bhtable[index] > 0) bhtable[index] = bhtable[index] - 1;
    }

    // update statistics
    predictions++;
    if (taken != predict_taken) mispredictions++;

}

unsigned long int Predictor::get_index(unsigned long int pc) {
    // extract PC[m+1:2]

    //cout << hex << pc << "\n";
    unsigned long int index = pc >> 2;
    //cout << index << "\n";
    unsigned long int mask = (1 << m) - 1; // build mask of M * 1s
    //cout << mask << "\n";
    index = index & mask;
    
    // for bimodal
    if (!gshare) {
        if (index > table_size) {
            cout << "PC too large: " << hex << index << endl;
            exit(EXIT_FAILURE);
        }
        else return index;
    }

    // else, for gshare: xor with appropriately left-shifted BHR
    unsigned long int shifted_bhr = bhr << (m-n);
    index = index ^ shifted_bhr;

    if (index > table_size) {
        cout << "Index to large: " << index << endl;
        exit(EXIT_FAILURE);
    }
    
    return index;
}

void Predictor::update_bhr(bool taken) {
    bhr = bhr >> 1;
    if (taken) {
        bhr = bhr | (1 << (n-1));
    }
}

void Predictor::print_stuff(void) {
    cout << "OUTPUT\n";
    cout << " number of predictions:    " << predictions << "\n";
    cout << " number of mispredictions: " << mispredictions << "\n";
    float miss_rate = 100 * (float)mispredictions / (float)predictions;
    printf(" misprediction rate:       %.2lf%\n", miss_rate);
    
    if (!gshare) cout << "FINAL BIMODAL CONTENTS\n";
    else cout << "FINAL GSHARE CONTENTS\n";
    for (unsigned long int i = 0; i < table_size; i++) {
        printf("%ld\t%d\n", i, bhtable[i]);
    }

    return;
}