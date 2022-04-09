#include "version_processor.hpp"


#define CPM_NULL 0 // initial value
#define CPM_LT 1   // <  : less than
#define CPM_LE 2   // <= : less than or equal to
#define CPM_EQ 3   // == : equal to
#define CPM_GE 4   // >= : greater than or equal to
#define CPM_GT 5   // >= : greater than
#define CPM_NE 6   // != : not equal to


int cpm::plus(int lhs, int rhs){
    return lhs+rhs;
}

bool cpm::operator==(const struct cpm::vis& lhs, const struct cpm::vis& rhs){
    return (lhs.is==rhs.is) && (lhs.ver==rhs.ver);
}
bool cpm::operator<(const struct cpm::vis& lhs, const struct cpm::vis& rhs){
    return cmpVer(lhs, rhs) < 0;
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
    case CPM_NULL: { return std::string(""); }
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
    if(ra.size()==0){ return 0; }
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
    if(lhs=="-inf"){ return -1; }
    if(lhs== "inf"){ return  1; }
    if(rhs=="-inf"){ return  1; }
    if(rhs== "inf"){ return -1; }
    
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
    // lhs <  rhs: -1
    // lhs == rhs:  0
    // lhs >  rhs:  1
    
    int c = cmpVer(lhs.ver, rhs.ver);
    if( c < 0 ){ return -1; }
    if( c > 0 ){ return  1; }

    // c == 0
    // order: <, <=, ==, >=, >
    if(lhs.is==CPM_LT){
        if(rhs.is==CPM_LT){ return  0; }
        return -1;
    }
    if(lhs.is==CPM_LE){
        if(rhs.is==CPM_LT){ return  1; }
        if(rhs.is==CPM_LE){ return  0; }
        return -1;
    }
    if(lhs.is==CPM_EQ){
        if(rhs.is==CPM_LT){ return  1; }
        if(rhs.is==CPM_LE){ return  1; }
        if(rhs.is==CPM_EQ){ return  0; }
        return -1;
    }
    if(lhs.is==CPM_GE){
        if(rhs.is==CPM_LT){ return  1; }
        if(rhs.is==CPM_LE){ return  1; }
        if(rhs.is==CPM_EQ){ return  1; }
        if(rhs.is==CPM_GE){ return  0; }
        return -1;
    }
    if(lhs.is==CPM_GT){
        if(rhs.is==CPM_GT){ return  0; }
        return  1;
    }
    
    sstd::pdbg("ERROR: lhs.is has unexpected value: %d.\n", lhs.is);
    return -1;
}

/*
uint gotoEnd_of_LTLG(bool& l_used, bool& r_used, const std::vector<T_pair>& vVC, const uint begin_idx){
    uint i_end;
    uint i=begin_idx;
    for(; i<vVC.size(); ++i){
        if(vVC[i].first.is!=CPM_LT && vVC[i].first.is!=CPM_LE){ break; }
        l_used = (vVC[i].second=='l');
        r_used = (vVC[i].second=='r');
    }
    i_end = i;
    return i_end;
}
int gotoBegin_of_GTGE(bool& l_used, bool& r_used, const std::vector<T_pair>& vVC, const uint end_idx){
    int i_begin;
    int i=end_idx;
    for(; i>=0; --i){
        if(vVC[i].first.is!=CPM_GT && vVC[i].first.is!=CPM_GE){ break; }
        l_used = (vVC[i].second=='l');
        r_used = (vVC[i].second=='r');
    }
    i_begin = i+1;
    return i_begin;
}
*/


#define T_pair std::pair<struct cpm::vis,struct cpm::vis>

std::vector<T_pair> cpm::split_by_range(bool& ret_TF, const std::vector<struct cpm::vis>& v)
{
    ret_TF=true;
    std::vector<T_pair> vR;

    // begin
    if(v.size()==0){ return vR; }
    uint b=0;
    if(v[b].is==CPM_LT || v[b].is==CPM_LE){
        T_pair r;
        r.first.is  =CPM_GT;
        r.first.ver ="-inf";
        r.second.is =v[b].is;
        r.second.ver=v[b].ver;
        vR <<= r;
        ++b;
    }

    // end
    if(v.size()==1){ return vR; }
    uint e=v.size(); // end
    T_pair r_end;
    bool TF_pushBack=false;
    if(v[e-1].is==CPM_GT || v[e-1].is==CPM_GE){
        r_end.first.is  =v[e-1].is;
        r_end.first.ver =v[e-1].ver;
        r_end.second.is =CPM_LT;
        r_end.second.ver="inf";
        --e;
        TF_pushBack=true;
    }

    // middle
    for(uint i=b; i<e; ++i){
        T_pair r;
        if(v[i].is==CPM_EQ){
            r.first.is  =CPM_EQ;
            r.first.ver =v[i].ver;
            r.second.is =CPM_EQ;
            r.second.ver=v[i].ver;
        }else{
            if(i+1>=e){ ret_TF=false; sstd::pdbg("ERROR: Unexpected vec size. Inequality-sign is not closed.\n"); return vR; }
            if(!( (v[i  ].is==CPM_GT || v[i  ].is==CPM_GE) &&
                  (v[i+1].is==CPM_LT || v[i+1].is==CPM_LE)    )){ ret_TF=false; sstd::pdbg("ERROR: Unexpected inequality-sign. Inequality-sign is not closed.\n"); return vR; }
            
            r.first.is  =v[i  ].is;
            r.first.ver =v[i  ].ver;
            r.second.is =v[i+1].is;
            r.second.ver=v[i+1].ver;
            ++i;
        }
        vR <<= r;
    }
    
    if(TF_pushBack){ vR <<= r_end; }
    return vR;
}
std::vector<struct cpm::vis> cpm::visAND(bool& ret_TF, const T_pair& l, const T_pair& r)
{
    ret_TF=true;
    std::vector<struct cpm::vis> ret;
    if(l.first.is==CPM_NULL || l.second.is==CPM_NULL || r.first.is==CPM_NULL || r.second.is==CPM_NULL){ ret_TF=false; return ret; }
    if(l.first.ver.size()==0 || l.second.ver.size()==0 || r.first.ver.size()==0 || r.second.ver.size()==0){ ret_TF=false; return ret; }
    
    cpm::print(l.first);
    cpm::print(r.first);
    sstd::printn(cmpVer(l.first, r.first));
    cpm::print(l.second);
    cpm::print(r.second);
    sstd::printn(cmpVer(l.second, r.second));
    
    // ll: l.first
    // lr: l.second
    // rl: r.first
    // rr: r.second

    // case06
    // l == r
    // l, r: ll == lr == rl == rr
    if(cmpVer(l.first, r.first)==0){ // ll == rl
        if(cmpVer(l.second, r.second)==0){ // lr == rr
            if(l.first.ver==l.second.ver){ // ll == rr
                struct cpm::vis r;
                r.is  = CPM_EQ;
                r.ver = l.first.ver;
                ret <<= r;
                return ret;
            }
        }
    }
    
    // case01, case02, case05a
    // l ⊂ r: rl <= ll && lr <= rr
    // l:       ll <---> lr
    // r: rl <---------------> rr
    if(cmpVer(l.first, r.first)>=0){ // ll >= rl
        if(cmpVer(l.second, r.second)<=0){ // lr <= rr
            ret <<= l.first;
            ret <<= l.second;
            return ret;
        }
    }
    
    // case05b
    // l ⊃ r
    // l: ll <---------------> lr
    // r:       rl <---> rr
    if(cmpVer(l.first, r.first)<=0){ // ll <= rl
        if(cmpVer(l.second, r.second)>=0){ // lr >= rr
            ret <<= r.first;
            ret <<= r.second;
            return ret;
        }
    }
    
    // case03a
    // l ∩ r (1): rl <= ll && rr <= lr
    // l:       ll <--------> lr
    // r: rl <-------> rr
    if(cmpVer(l.first, r.first)>=0){ // ll >= rl
        if(cmpVer(l.second, r.second)>=0){ // lr >= rr
            ret <<= l.first;
            ret <<= r.second;
            return ret;
        }
    }
    
    // case03b, case04a
    // l ∩ r (2): ll <= rl && lr <= rr
    // l: ll <-------> lr
    // r:       rl <--------> rr
    if(cmpVer(l.first, r.first)<=0){ // ll <= rl
        if(cmpVer(l.second, r.second)<=0){ // lr <= rr
            ret <<= r.first;
            ret <<= l.second;
            return ret;
        }
    }
    
    return ret;
}
std::vector<struct cpm::vis> cpm::visAND(const std::vector<struct vis>& vLhs_in, const std::vector<struct vis>& vRhs_in){
    std::vector<struct vis> vLhs=vLhs_in;
    std::vector<struct vis> vRhs=vRhs_in;
    std::sort(vLhs.begin(), vLhs.end());
    std::sort(vRhs.begin(), vRhs.end());

    bool tf;
    std::vector<T_pair> vL = split_by_range(tf, vLhs);
    std::vector<T_pair> vR = split_by_range(tf, vRhs);
    for(auto l: vL){ cpm::print(l.first); cpm::print(l.second); }
    for(auto r: vR){ cpm::print(r.first); cpm::print(r.second); }
    
    std::vector<struct cpm::vis> ret;
    /*
    for(uint li=0; li<vL.size(); ++li){
        for(uint ri=ri_begin; ri<vL.size(); ++ri){
            std::vector<struct cpm::vis> r;
            bool TF_include = visAND_range(r, vL[li], vR[ri]);
            ret <<= r;
        }
    }
    */
    return ret;
}

#undef T_pair


#undef CPM_NE
#undef CPM_GT
#undef CPM_GE
#undef CPM_EQ
#undef CPM_LE
#undef CPM_LT
#undef CPM_NULL
