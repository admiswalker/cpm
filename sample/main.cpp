#include <stdio.h>
#include <cpmex/cpmex.hpp>
#include <sstd/sstd.hpp>


int main(){
    printf("Welcome to the sample program that explains how to use CPM!\n");
    printf("\n");

    printf("test cpmex\n");
    printf("cpmex::plus_ii(1, 1) = %d\n", cpmex::plus_ii(1, 1));
    printf("\n");
    
    printf("test sstd\n");
    uint i=0; sstd::printn(i);
    printf("\n");

    return 0;
}

