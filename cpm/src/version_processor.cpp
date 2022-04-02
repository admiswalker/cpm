#include "version_processor.hpp"


int cpm::plus(int lhs, int rhs){
    return lhs+rhs;
}

/*
std::vector<std::string> split(const char* str, const std::vector<std::string>& vSplitter){
    std::vector<std::string> ret_vStr;
    
    for(uint i=0; i<str.size(); ++i){
        for(uint si=0; si<vSplitter.size(); ++si){
            uint len = vSplitter[si].size();
            if(i+len >= str.size()){ continue; }
            
            if(strEq_len(&str[i], &vSplitter[si], len)){
                
            }
        }
    }
    
    return ret_vStr;
}*/
bool strEq_len(uint ii, const char* lhs, const char* rhs, const uint len){
    for(uint i=0; i<len; ++i){
        if(lhs[i]!=rhs[i]){ return false; }
    }
    return true;
}
std::vector<std::string> split(const std::string& str, const std::string& splitter){
    std::vector<std::string> vRet;
    
    std::string r;
    uint i=0;
    if(strEq_len(i, &str[i], splitter.c_str(), splitter.size())){
        vRet <<= splitter;
        i += splitter.size();
    }
    for(; i<str.size() - splitter.size(); ++i){
        sstd::printn(i);
        if(strEq_len(i, &str[i], splitter.c_str(), splitter.size())){
            vRet <<= r; r.clear();
            vRet <<= splitter;
            i += splitter.size() - 1; // minus 1, because of the end of for-loop ++i
        }else{
            r += str[i];
        }
    }
    for(; i<str.size(); ++i){ r += str[i]; }
    if(r.size()!=0){ vRet <<= r; }
    
    return vRet;
}
struct cpm::verRange cpm::str2verStruct(const std::string& verStr){
    sstd::printn(verStr);
    
//    std::vector<std::string> v = split(verStr, {"==", "<=", ">=", "<", ">"});
    std::vector<std::string> v = split(verStr, std::string("<="));
    sstd::printn(v);
    
    
    struct cpm::verRange vr;
    



    
    return vr;
}
