#include <sstd/sstd.hpp>
#include <gtest/gtest.h>


// src code test
//#include "test/src/version_processor.hpp"
//#include "test/src/dependency_graph_generator.hpp"

// archive installation test
#include "test/packages/amd64/gcc/archive_installation_test.hpp"

// full build and installation test


int main(int argc, char *argv[]){
    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|                                                   |\n");
    printf("|      Welcome to The Test Codes of                 |\n");
    printf("|             The Cpp Package Manager (CPM) !       |\n");
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
