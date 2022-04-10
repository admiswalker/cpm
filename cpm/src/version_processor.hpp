#pragma once
#include <sstd/sstd.hpp>


#define T_verLR std::pair<struct ver,struct ver>

namespace cpm{
    struct ver{ // version inequality-sign
        uchar ineq=0; // inequality-sign
        std::string ver;
    };
    bool operator==(const struct ver& lhs, const struct ver& rhs);
    bool operator<(const struct ver& lhs, const struct ver& rhs);
    
    uchar str2is(bool& ret, const std::string& ra);
    std::string is2str(const uchar& is);
    
    struct ver str2ver(const        char* pStr);
    struct ver str2ver(const std::string&  str);
    
    std::vector<struct ver> split_verNE(const struct ver& ver);
    
    int cmpVer(const std::string& lhs, const std::string& rhs);
    int cmpVer(const struct ver& lhs, const struct ver& rhs);
    
    void rm_same_ver(std::vector<struct ver>& v);
    
    std::vector<T_verLR> split_by_range(bool& ret_TF, const std::vector<struct ver>& vLhs);
    std::vector<struct ver> verAND(bool& ret_TF, const T_verLR& l, const T_verLR& r);
    std::vector<struct ver> verAND(const std::vector<struct ver>& vLhs, const std::vector<struct ver>& vRhs);

    void print(const struct ver& ver);
    void print(const std::vector<struct ver>& v);
}

#undef T_verLR
