#include "version_processor.hpp"


#define CPM_LT 1 // <  : less than
#define CPM_LE 2 // <= : less than or equal to
#define CPM_EQ 3 // == : equal to
#define CPM_GE 4 // >= : greater than or equal to
#define CPM_GT 5 // >= : greater than
#define CPM_NE 6 // != : not equal to


int cpm::plus(int lhs, int rhs){
    return lhs+rhs;
}

bool cpm::operator==(const struct cpm::vis& lhs, const struct cpm::vis& rhs){
    return (lhs.is==rhs.is) && (lhs.ver==rhs.ver);
}
bool cpm::operator<(const struct cpm::vis& lhs, const struct cpm::vis& rhs){
    int c = cmpVer(lhs.ver, rhs.ver);
    if      ( c < 0 ){ return true;
    }else if( c > 0 ){ return false;
    }else{
        // c == 0

        // order: <, <=, >=, >
        if      (lhs.is==CPM_LT){ return true;
        }else if(lhs.is==CPM_LE &&  rhs.is==CPM_LT){ return false;
        }else if(lhs.is==CPM_GE && (rhs.is==CPM_LT || rhs.is==CPM_LE)){ return false;
        }else if(lhs.is==CPM_GT && (rhs.is==CPM_LT || rhs.is==CPM_LE || rhs.is==CPM_GE)){ return false;
        }
    }
    
    return true;
}


void print_owN(const struct cpm::vis& vis){
    printf("is: %s, ver: %s", cpm::is2str(vis.is).c_str(), vis.ver.c_str());
}
void cpm::print(const struct cpm::vis& vis){
    print_owN(vis);
    printf("\n");
}
void cpm::print(const std::vector<struct cpm::vis>& v){
    for(uint i=0; i<v.size(); ++i){
        printf("[ ");
        print_owN(v[i]);
        printf(" ], ");
    }
    printf("\n");
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
struct cpm::vis cpm::str2vis(const char* pStr){
    std::string s = sstd::stripAll(pStr, " ");
    
    std::string ra  = getWhile_c(s, "<=>!");
    std::string ver = std::string(&s[ra.size()], s.size()-ra.size());

    bool ret;
    uchar ret_is = cpm::str2is(ret, ra); if(!ret){ return cpm::vis(); }

    struct cpm::vis r;
    r.is = ret_is;
    r.ver = ver;

    return r;
}
struct cpm::vis cpm::str2vis(const std::string& str){ return cpm::str2vis(str.c_str()); }

std::vector<struct cpm::vis> cpm::split_visNE(const struct cpm::vis& v){
    struct vis l;
    l.is  = CPM_LT;
    l.ver = v.ver;
    
    struct vis r;
    r.is  = CPM_GT;
    r.ver = v.ver;
    
    return std::vector<struct cpm::vis>({l, r});
}
int cpm::cmpVer(const std::string& lhs, const std::string& rhs){
    // lhs <  rhs: -1
    // lhs == rhs:  0
    // lhs >  rhs:  1
    
    if(lhs==rhs){ return 0; } // eq_case01
    
    std::vector<std::string> vL = sstd::split(lhs, '.');
    std::vector<std::string> vR = sstd::split(rhs, '.');
    
    // remove head 0 padding. ex: ver 01.00.00 -> 1..
    for(uint i=0; i<vL.size(); ++i){ sstd::lstrip_ow(vL[i], '0'); }
    for(uint i=0; i<vR.size(); ++i){ sstd::lstrip_ow(vR[i], '0'); }
//  if(vL==vR){ return 0; }
    
    for(uint vi=0; vi<sstd::min(vL.size(), vR.size()); ++vi){
        if(vL[vi].size() < vR[vi].size()){ return -1; } // lt_case01_a, lt_case01_b, lt_case01_c
        if(vL[vi].size() > vR[vi].size()){ return  1; } // gt_case01_a, gt_case01_b, gt_case01_c
        
        for(uint i=0; i<vL[vi].size(); ++i){
            if(vL[vi][i] < vR[vi][i]){ return -1; } // follow the ASCII Code order // lt_case02_a, lt_case02_b, lt_case02_c
            if(vL[vi][i] > vR[vi][i]){ return  1; } // follow the ASCII Code order // gt_case02_a, gt_case02_b, gt_case02_c
        }
    }
    if(vL.size() != vR.size()){ return (vL.size() < vR.size() ? -1:1); } // lt_case03, gt_case03
    
    return 0; // eq_case02_a, eq_case02_b
}
int cpm::cmpVer(const struct cpm::vis& lhs, const struct cpm::vis& rhs){
    return cpm::cmpVer(lhs.ver, rhs.ver);
}
/*
// Old impliments
std::vector<struct cpm::vis> cpm::visAND(const std::vector<struct vis>& vLhs, const std::vector<struct vis>& vRhs){
    printf("in cpm::visAND\n");
    std::vector<struct cpm::vis> ret;
    
    // sort_vis(vLhs);
    // sort_vis(vRhs);

    for(uint li=0; li<vLhs.size(); ++li){
        if(vLhs[li].is==CPM_EQ){
        }else if(vLhs[li].is==CPM_GT || vLhs[li].is==CPM_GE){
            for(uint ri=0; ri<vRhs.size(); ++ri){
                int c = cpm::cmpVer(vRhs[ri].ver, vLhs[li].ver);
                if(vRhs[ri].is==CPM_LT || vRhs[ri].is==CPM_LE){
                    if( c > 0 ){
                        // when: vRhs[ri].ver > vLhs[li].ver
                        ret <<= vLhs[li];
                        ret <<= vRhs[ri]; // case01a, case02a
                        break;
                    }else if( c < 0 ){
                        // c == 0
                        // when: vRhs[ri].ver == vLhs[li].ver
                    }
                }else if(vRhs[ri].is==CPM_GT || vRhs[ri].is==CPM_GE){
                    if( c > 0 ){
                        // when: vRhs[ri].ver < vLhs[li].ver
                        break; // case02a
                    }else{
                    }
                }
            }
        }else if(vLhs[li].is==CPM_LT || vLhs[li].is==CPM_LE){
            for(int ri=vRhs.size()-1; ri>=0; --ri){
                int c = cpm::cmpVer(vRhs[ri].ver, vLhs[li].ver);
                if(vRhs[ri].is==CPM_GT || vRhs[ri].is==CPM_GE){
                    if( c < 0 ){
                        // when: vRhs[ri].ver < vLhs[li].ver
                        ret <<= vRhs[ri];
                        ret <<= vLhs[li]; // case01b, case02b
                        break;
                    }
                }else if(vRhs[ri].is==CPM_LT || vRhs[ri].is==CPM_LE){
                    if( c < 0 ){
                        // when: vRhs[ri].ver < vLhs[li].ver
                        break; // case02b
                    }else{
                    }
                }
            }
        }
    }
    return ret;
}
*/

std::vector<struct cpm::vis> cpm::visAND(const std::vector<struct vis>& vLhs, const std::vector<struct vis>& vRhs){
    printf("in cpm::visAND\n");

    std::vector<std::pair<struct cpm::vis, char>> vVC(vLhs.size()+vRhs.size());

    uint n=0;
    for(uint i=0; i<vLhs.size(); ++i, ++n){ vVC[n] = {vLhs[i], 'l'}; }
    for(uint i=0; i<vRhs.size(); ++i, ++n){ vVC[n] = {vRhs[i], 'r'}; }
    
    std::sort(vVC.begin(), vVC.end());
    
    for(auto VC: vVC){
        cpm::print(VC.first);
        sstd::printn(VC.second);
    }

    std::vector<struct cpm::vis> ret;
    if(vVC.size()<=2){ return ret; }
    {
        struct cpm::vis prev_v = vVC[0].first;
        char prev_c = vVC[0].second;
        
        for(uint i=1; i<vVC.size(); ++i){
            struct cpm::vis now_v = vVC[i].first;
            char now_c = vVC[i].second;
            
//            if(prev_v.is == now_c.is){}
        }
    }

    
    
    /*
    // sort_vis(vLhs);
    // sort_vis(vRhs);
    for(uint li=0; li<vLhs.size(); ++li){
        if(vLhs[li].is==CPM_EQ){
        }else if(vLhs[li].is==CPM_GT || vLhs[li].is==CPM_GE){
            for(uint ri=0; ri<vRhs.size(); ++ri){
                int c = cpm::cmpVer(vRhs[ri].ver, vLhs[li].ver);
                if(vRhs[ri].is==CPM_LT || vRhs[ri].is==CPM_LE){
                    if( c > 0 ){
                        // when: vRhs[ri].ver > vLhs[li].ver
                        ret <<= vLhs[li];
                        ret <<= vRhs[ri]; // case01a, case02a
                        break;
                    }else if( c < 0 ){
                        // c == 0
                        // when: vRhs[ri].ver == vLhs[li].ver
                    }
                }else if(vRhs[ri].is==CPM_GT || vRhs[ri].is==CPM_GE){
                    if( c > 0 ){
                        // when: vRhs[ri].ver < vLhs[li].ver
                        break; // case02a
                    }else{
                    }
                }
            }
        }else if(vLhs[li].is==CPM_LT || vLhs[li].is==CPM_LE){
            for(int ri=vRhs.size()-1; ri>=0; --ri){
                int c = cpm::cmpVer(vRhs[ri].ver, vLhs[li].ver);
                if(vRhs[ri].is==CPM_GT || vRhs[ri].is==CPM_GE){
                    if( c < 0 ){
                        // when: vRhs[ri].ver < vLhs[li].ver
                        ret <<= vRhs[ri];
                        ret <<= vLhs[li]; // case01b, case02b
                        break;
                    }
                }else if(vRhs[ri].is==CPM_LT || vRhs[ri].is==CPM_LE){
                    if( c < 0 ){
                        // when: vRhs[ri].ver < vLhs[li].ver
                        break; // case02b
                    }else{
                    }
                }
            }
        }
    }
    */
    return ret;
}


#undef CPM_NE
#undef CPM_GT
#undef CPM_GE
#undef CPM_EQ
#undef CPM_LE
#undef CPM_LT
