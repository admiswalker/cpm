#include <sstd/sstd.hpp>
#include <gtest/gtest.h>


// src code test
//#include "test/src/version_processor.hpp"
//#include "test/src/dependency_graph_generator.hpp"

// archive installation test
#include "test/packages/amd64/gcc/12.1.0/archive_installation_test.hpp"

// full build and installation test


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
