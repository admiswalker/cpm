#pragma once
#include <sstd/sstd.hpp>


namespace cpm{
    int plus(int, int);
    
    struct verRange{
        std::string L;
        uint LIS; // left inequality-sign
        uint RIS; // right inequality-sign
        std::string R;
    };

    struct verRange str2verStruct(const std::string& verStr);
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

