#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include "ost.hh" 

int main() {
    ost::WeightBalancedTree<int> *tree = ost::default_tree<int>(); 
    int a, b, s, r; 
    std::vector<int> buf; 
    while (1) {
        printf("0: insert first [data]\n");
        printf("1: insert last [data]\n");
        printf("2: insert [index] [data]\n");
        printf("3: query [index]\n");
        printf("4: query all\n");
        printf("5: delete first & display\n"); 
        printf("6: delete last & display\n");
        printf("7: delete [index] & display\n"); 
        r = scanf("%d", &s); 
        if (r != 1) return EXIT_FAILURE; 
        if (s == 0) {
            r = scanf("%d", &a); 
            if (r != 1) return EXIT_FAILURE; 
            ost::insert_first(tree, a); 
            printf("INSERT [0] = %d\n", a); 
        } else if (s == 1) {
            r = scanf("%d", &a); 
            if (r != 1) return EXIT_FAILURE; 
            ost::insert_last(tree, a); 
            printf("INSERT [%d] = %d\n", (int ) ost::size(tree) - 1, a); 
        } else if (s == 2) {
            r = scanf("%d%d", &a, &b); 
            if (r != 2) return EXIT_FAILURE; 
            if (ost::size(tree) <= a) {
                printf("INSERT Out of Bound\n"); 
            } else {
                ost::insert(tree, a, b); 
                printf("INSERT [%d] = %d\n", a, b); 
            }
        } else if (s == 3) {
            r = scanf("%d", &a); 
            if (r != 1) return EXIT_FAILURE; 
            if (ost::size(tree) <= a) {
                printf("QUERY Out of Bound\n"); 
            } else {
                printf("QUERY [%d] = %d\n", a, ost::query(tree, a)); 
            }
        } else if (s == 4) {
            buf.clear(); 
            ost::walk(tree, [&buf](auto x) { buf.push_back(x); });             
            printf("QUERY ALL: "); 
            for (auto x : buf) {
                printf("%d ", x); 
            }
            printf("\n"); 
        } else if (s == 5) {
            if (ost::size(tree) == 0) {
                printf("DELETE EMPTY\n"); 
            } else {
                int val; 
                ost::delete_first(tree, &val); 
                printf("DELETE FIRST: %d\n", val); 
            }
        } else if (s == 6) {
            if (ost::size(tree) == 0) {
                printf("DELETE EMPTY\n"); 
            } else {
                int val; 
                ost::delete_last(tree, &val); 
                printf("DELETE LAST: %d\n", val); 
            }
        } else if (s == 7) {
            r = scanf("%d", &a); 
            if (r != 1) return EXIT_FAILURE; 
            if (ost::size(tree) <= a) {
                printf("DELETE Out of Bound\n"); 
            } else {
                int val; 
                ost::delete_at(tree, a, &val); 
                printf("DELETE [%d] = %d\n", a, val); 
            }
        } else {
            printf("Invalid Command\n"); 
        }
    }
    return 0; 
}
