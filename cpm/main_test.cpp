#include <sstd/sstd.hpp>
#include <gtest/gtest.h>


#include "test/version_processor.hpp"


int main(int argc, char *argv[]){
    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|                                                   |\n");
    printf("|      Welcome to the test codes of                 |\n");
    printf("|                 Cpp Package Manager (CPM) !       |\n");
    printf("|                                                   |\n");
    printf("+---------------------------------------------------+\n");
    printf("\n");
    time_m timem; sstd::measureTime_start(timem);
    ::testing::InitGoogleTest(&argc, argv);
    
    auto ret = RUN_ALL_TESTS();
    
    printf("\n");
    sstd::measureTime_stop_print(timem);
    return ret;
}
