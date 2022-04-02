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
    
    struct vis str2vis(const std::string& str);
    
    uchar str2is(bool& ret, const std::string& ra);
    std::string is2str(const uchar& is);
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

