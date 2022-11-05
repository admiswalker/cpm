#include "archive_installation.hpp"
#include <sstd/sstd.hpp>


std::string cpm_test::get_call_path(){
    std::string s = sstd::system_stdout("pwd");
    s = sstd::rstrip(s, '\n');
    return s;
}

