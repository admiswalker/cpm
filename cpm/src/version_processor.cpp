#include "version_processor.hpp"


int cpm::plus(int lhs, int rhs){
    return lhs+rhs;
}

//-------------
/*
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
    for(; i<str.size() - splitter.size() + 1; ++i){
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
std::vector<std::string> split(const char* str, const std::vector<std::string>& vSplitter){
    std::vector<std::string> vRet;
    
    std::string r;
    uint i=0;
    if(strEq_len(i, &str[i], splitter.c_str(), splitter.size())){
        vRet <<= splitter;
        i += splitter.size();
    }
    for(; i<str.size() - splitter.size() + 1; ++i){
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
*/
/*
// 欲しい関数

std::string s = sstd::stripAll(str, ' ');

*/


#define CPM_LT 1 // <  : less than
#define CPM_LE 2 // <= : less than or equal to
#define CPM_EQ 3 // == : equal to
#define CPM_GE 4 // >= : greater than or equal to
#define CPM_GT 5 // >= : greater than
#define CPM_NE 6 // != : not equal to

bool strMatch_chars(const char c, const char* cs, const uint cs_len){
    bool ret = false;
    for(uint i=0; i<cs_len; ++i){
        if(c!=cs[i]){ continue; }
        ret = true;
        break;
    }
    return ret;
}
std::string getWhile_c(const std::string& s, const char* cs){
    std::string ret;
    for(uint i=0; i<s.size(); ++i){
        if(strMatch_chars(s[i], cs, strlen(cs))){
            ret += s[i];
        }else{
            return ret;
        }
    }
    return ret;
}
//std::string getWhile_s(const std::string& s, const std::string& while_include_this_str){
//}

std::string cpm::is2str(const uchar& is){
    switch(is){
    case CPM_LT: { return std::string("<" ); }
    case CPM_LE: { return std::string("<="); }
    case CPM_EQ: { return std::string("=="); }
    case CPM_GE: { return std::string(">="); }
    case CPM_GT: { return std::string(">" ); }
    case CPM_NE: { return std::string("!="); }
    default: { sstd::pdbg("ERROR: is2str() has invalid value.\n"); return std::string(""); }
    }
}
uchar cpm::str2is(bool& ret, const std::string& ra){
    ret=true;
    if(ra.size()!=1 && ra.size()!=2){
        sstd::pdbg("ERROR: inputted inequality-sign is invalid.\n");
        ret=false;
        return 0;
    }
    
    if      (sstd::strcmp(ra, "<" )){ return CPM_LT;
    }else if(sstd::strcmp(ra, "<=")){ return CPM_LE;
    }else if(sstd::strcmp(ra, "==")){ return CPM_EQ;
    }else if(sstd::strcmp(ra, ">=")){ return CPM_GE;
    }else if(sstd::strcmp(ra, ">" )){ return CPM_GT;
    }else if(sstd::strcmp(ra, "!=")){ return CPM_NE;
    }else{
        sstd::pdbg("ERROR: inputted inequality-sign (%s) is invalid.\n", ra.c_str());
        ret=false;
        return 0;
    }
}
struct cpm::vis cpm::str2vis(const std::string& str){
    std::string s = sstd::stripAll(str, " ");
    
    std::string ra  = getWhile_c(s, "<=>!");
    std::string ver = std::string(&s[ra.size()], s.size()-ra.size());

    bool ret;
    uchar ret_is = cpm::str2is(ret, ra); if(!ret){ return cpm::vis(); }

    struct cpm::vis r;
    r.is = ret_is;
    r.ver = ver;

    return r;
}


#undef CPM_NE
#undef CPM_GT
#undef CPM_GE
#undef CPM_EQ
#undef CPM_LE
#undef CPM_LT
