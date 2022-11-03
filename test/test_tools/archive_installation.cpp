#include "archive_installation.hpp"
#include <sstd/sstd.hpp>

int cpm_test::test_tool(){
    printf("hello\n");
    return 0;
}

std::string cpm_test::get_call_path(){
    std::string s = sstd::system_stdout("pwd");
    s = sstd::rstrip(s, '\n');
    return s;
}

