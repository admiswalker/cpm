#pragma once
#include <sstd/sstd.hpp>


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
    bool operator==(const struct vis& lhs, const struct vis& rhs);
    
    uchar str2is(bool& ret, const std::string& ra);
    std::string is2str(const uchar& is);
    
    struct vis str2vis(const        char* pStr);
    struct vis str2vis(const std::string&  str);
    
    std::vector<struct vis> split_visNE(const struct vis& vis);
    
    int cmpVer(const std::string& lhs, const std::string& rhs);
    int cmpVer(const struct vis& lhs, const struct vis& rhs);

    std::vector<struct vis> visAND(const std::vector<struct vis>& vLhs, const std::vector<struct vis>& vRhs);

    void print(const struct vis& vis);
    void print(const std::vector<struct vis>& v);
}

// range: L, R
// - '-inf'
// - '0.0.0' ~ '*.*.*'
// - 'inf'

// inequality-sign
// - ASCII Code
//   - <: 92
//   - =: 93
//   - >: 94

