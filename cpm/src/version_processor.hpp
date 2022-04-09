#pragma once
#include <sstd/sstd.hpp>


#define T_pair std::pair<struct vis,struct vis>

namespace cpm{
    int plus(int, int);
    /*
    struct verRange{
        std::string L;
        uint LIS; // left inequality-sign
        uint RIS; // right inequality-sign
        std::string R;
    };

    struct verRange str2verStruct(const std::string& verStr);
    */
    struct vis{ // version inequality-sign
        uchar is=0; // inequality-sign
        std::string ver;
    };
    // version の ver とかの方がまだわかる．
    bool operator==(const struct vis& lhs, const struct vis& rhs);
    bool operator<(const struct vis& lhs, const struct vis& rhs);
    
    uchar str2is(bool& ret, const std::string& ra);
    std::string is2str(const uchar& is);
    
    struct vis str2vis(const        char* pStr);
    struct vis str2vis(const std::string&  str);
    
    std::vector<struct vis> split_visNE(const struct vis& vis);
    
    int cmpVer(const std::string& lhs, const std::string& rhs);
    int cmpVer(const struct vis& lhs, const struct vis& rhs);
    
    void rm_same_vis(std::vector<struct vis>& v);
    
    std::vector<T_pair> split_by_range(bool& ret_TF, const std::vector<struct vis>& vLhs);
    std::vector<struct vis> visAND(bool& ret_TF, const T_pair& l, const T_pair& r);
    std::vector<struct vis> visAND(const std::vector<struct vis>& vLhs, const std::vector<struct vis>& vRhs);
    // 関数名: verAND とかの方がまだわかる．

    void print(const struct vis& vis);
    void print(const std::vector<struct vis>& v);
}

#undef T_pair
