#pragma once
#include <sstd/sstd.hpp>

namespace cpm{
    extern const uchar CPM_NULL; // initial value
    extern const uchar CPM_LT;   // <  : less than
    extern const uchar CPM_LE;   // <= : less than or equal to
    extern const uchar CPM_EQ;   // == : equal to
    extern const uchar CPM_GE;   // >= : greater than or equal to
    extern const uchar CPM_GT;   // >= : greater than
    extern const uchar CPM_NE;   // != : not equal to

    struct ver{ // version inequality-sign
        uchar ineq=0; // inequality-sign
        std::string ver;
    };
    using verLR = std::pair<struct ver,struct ver>;
    
    bool operator==(const struct ver& lhs, const struct ver& rhs);
    bool operator<(const struct ver& lhs, const struct ver& rhs);
    
    std::string print_str(const             struct ver &  ver);
    std::string print_str(const std::vector<struct ver>& vVer);
    void print(const             struct ver &  ver);
    void print(const std::vector<struct ver>& vVer);
    
    std::string print_str(const             verLR &  ver);
    std::string print_str(const std::vector<verLR>& vVer);
    void print(const             verLR &  ver);
    void print(const std::vector<verLR>& vVer);
    
    uchar str2ineq(bool& ret, const std::string& ra);
    std::string ineq2str(const uchar& ineq);
    
                struct ver  str2ver(const                    char*  pStr);
                struct ver  str2ver(const             std::string&   str);
    std::vector<struct ver> str2ver(const std::vector<std::string>& vStr);
    
    std::vector<struct ver> split_verNE(const struct ver& ver);
    
    int cmpVer(const std::string& lhs, const std::string& rhs);
    int cmpVer(const struct ver& lhs, const struct ver& rhs);
    
    void rm_same_ver(std::vector<struct ver>& v);
    
    std::vector<verLR> split_by_range(bool& ret_TF, const std::vector<struct ver>& vLhs);
    std::vector<struct ver> verAND(bool& ret_TF, const             verLR &  l, const             verLR &  r);
    std::vector<struct ver> verAND(bool& ret_TF, const std::vector<struct ver>& vLhs, const std::vector<struct ver>& vRhs);
}
