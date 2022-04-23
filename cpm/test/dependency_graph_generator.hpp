#pragma once
#include "../src/dependency_graph_generator.hpp"


//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
TEST(vLine2instGraph, example_test){
    sstd::vvec<std::string> vLine={
        {"ARCHITECTURE", "amd64"},
        {"IMPORT", "CPM_libExample_to_IMPORT", "0.1.0", "https://github.com/admiswalker/CPM_libExample_to_IMPORT/raw/main/cpm_import/script/0.1.0/download_installation_scripts.sh"},
                                   
        {"INSTALL_MODE", "archive"},
        {"m4", "==1.4.15"},
        {"gmp", "==6.1.0"},
        {"mpfr", "==3.1.4"},
        {"mpc", "==1.0.3"},
        {"isl", "==0.18"},
        {"gcc", "==11.2.0"},
                                   
        {"INSTALL_MODE", "source"},
        {"BUILD_ENV", "CPM_ENV"},
        {"sstd", "==2.0.1"},
        {"CPM_libExample_to_IMPORT"," ==0.1.0"}
    };
    
    bool ret;
    class cpm::PATH p(cpm::baseDir_default);
    std::unordered_map<std::string, struct cpm::install_cmd> table_reqPkg = cpm::vLine2instGraph(ret, p, vLine);
    if(!ret){ sstd::pdbg("ERROR: packageTxt2instCmd() is failed."); }
}
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(vLine2instGraph, example_test02){
    sstd::vvec<std::string> vLine={
        {"ARCHITECTURE", "amd64"},
//        {"IMPORT", "CPM_libExample_to_IMPORT", "0.1.0", "https://github.com/admiswalker/CPM_libExample_to_IMPORT/raw/main/cpm_import/script/0.1.0/download_installation_scripts.sh"},
                                   
        {"INSTALL_MODE", "archive"},
        {"m4", "==1.4.15"},
        {"gmp", "==6.1.0"},
        {"mpfr", "==3.1.4"},
        {"mpc", "==1.0.3"},
        {"isl", "==0.18"},
        {"gcc", "==11.2.0"},
                                   
        {"INSTALL_MODE", "source"},
        {"BUILD_ENV", "CPM_ENV"},
        {"sstd", "==2.0.1"},
//        {"CPM_libExample_to_IMPORT"," ==0.1.0"}
    };
    
    bool ret;
    class cpm::PATH p(cpm::baseDir_default);
    std::unordered_map<std::string, struct cpm::install_cmd> table_reqPkg = cpm::vLine2instGraph(ret, p, vLine);
    if(!ret){ sstd::pdbg("ERROR: packageTxt2instCmd() is failed."); }
    /*
    for(auto pkg: table_reqPkg){
        sstd::printn(pkg.first);
        cpm::print(pkg.second);
        printf("\n");
    }
    */
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
