#include <stdio.h>

#include <vector>

#include "ost.hh"

int main() {
    ost::WBT<int> *tree = ost::default_tree<int>();     
    int up = 10000000; 
    std::vector<int> rst; 
    for (int i = 0; i < up; i++) {
        ost::insert_last(tree, 8888); 
        if (i % 100000 == 0) 
            rst.push_back(ost::height(tree)); 
    }
    for (int i = 0; i < rst.size(); ++i) {
        printf("%9d size, %4d height\n", i * 100000, rst[i]);
    }
}