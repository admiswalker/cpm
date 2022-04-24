#pragma once
#include <sstd/sstd.hpp>
#include "pathProc.hpp"
#include "version_processor.hpp"


namespace cpm{
    struct install_cmd{
        std::string build_env;
        std::string install_mode;
    
        std::string architecture;
        std::string libName;
//      std::string ver;
        std::vector<cpm::ver> vVer;
        
        std::unordered_map<std::string, char> vDep; // dependencies. 'char' is a dummy type (not used).
    };
    void print(struct install_cmd& lhs);
    
    std::unordered_map<std::string, struct install_cmd> vLine2instGraph(bool& ret_tf, class cpm::PATH& p, const sstd::vec<uint>& vLineNum, const sstd::vvec<std::string>& vLine, const char* fileName);
}
