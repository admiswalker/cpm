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
    
        std::vector<std::string> vDep; // dependencies
    };
    void print(struct install_cmd& lhs);
    
//    sstd::vvec<std::string> packagesTxt2vLine(const std::string& packages_path);
    bool packagesTxt2vLine(std::vector<uint>& vLineNum, sstd::vvec<std::string>& vvLine, const std::string& packages_path);
    std::unordered_map<std::string, struct install_cmd> vLine2instGraph(bool& ret_tf, class cpm::PATH& p, const sstd::vvec<std::string>& vLine);
}
