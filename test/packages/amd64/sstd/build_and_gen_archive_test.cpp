#pragma once
#include "../../../test_tools/archive_installation.hpp"

#include <sstd/sstd.hpp>

TEST(build_and_gen_archive_test, sstd_2_1_0_build_and_archive){
    CPM_TEST_INIT();

    std::string pkg_script = R"(
ARCHITECTURE, amd64;
BUILD_ENV, CPM_ENV;
INSTALL_MODE, archive;
gcc, ==9.4.0;
INSTALL_MODE, source;
sstd, ==2.0.1;
)";
    sstd::write(pkg_script_path, pkg_script);

    cmd_inst += " -a true"; // add: archive option
    std::string ret = sstd::system_stdout(cmd_inst); // installation

    std::string lib_test_code = R"(
#include <stdio.h>
#include <sstd/sstd.hpp>
int main(){
    std::string s = sstd::ssprintf("hello sstd");
    sstd::print(s);
    return 0;
}
)";
    sstd::write(base_dir+"/main.cpp", lib_test_code); // generate test script
    
    std::string test_script = R"(#!/bin/bash
SCRIPT_DIR=`cd $(dirname ${BASH_SOURCE:-$0}); pwd`
cd ${SCRIPT_DIR}
source ./local/set_env.sh
gcc -o exe main.cpp -lstdc++ -lsstd
./exe
)";
    sstd::write(test_script_path, test_script); // generate test script
    
    std::string cmd_test = "bash "+test_script_path+";\n";
    std::string test_ret = sstd::system_stdout(cmd_test); // run test script
    
    std::string test_ret_ans;
    test_ret_ans += "\"hello sstd\"\n";
    ASSERT_STREQ(test_ret.c_str(), test_ret_ans.c_str()); // test

    std::vector<std::string> vPath = sstd::glob(base_dir+"/archive/*", "fr");

    // check archive file name (check name only)
    std::vector<std::string> vPath_ans = {
        "./tmp/test/build_and_gen_archive_test_sstd_2_1_0_build_and_archive/archive/amd64/sstd/2.0.1/amd64-sstd-2.0.1-buildRecipe.txt",
        "./tmp/test/build_and_gen_archive_test_sstd_2_1_0_build_and_archive/archive/amd64/sstd/2.0.1/amd64-sstd-2.0.1-sha256sum.txt",
        "./tmp/test/build_and_gen_archive_test_sstd_2_1_0_build_and_archive/archive/amd64/sstd/2.0.1/amd64-sstd-2.0.1.tar.xz"};
    ASSERT_TRUE(vPath == vPath_ans); // test

    sstd::rm(tmp_dir);
}

