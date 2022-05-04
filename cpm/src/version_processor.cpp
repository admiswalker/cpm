#include "version_processor.hpp"


extern const uchar cpm::CPM_NULL = 0; // initial value
extern const uchar cpm::CPM_LT = 1;   // <  : less than
extern const uchar cpm::CPM_LE = 2;   // <= : less than or equal to
extern const uchar cpm::CPM_EQ = 3;   // == : equal to
extern const uchar cpm::CPM_GE = 4;   // >= : greater than or equal to
extern const uchar cpm::CPM_GT = 5;   // >= : greater than
extern const uchar cpm::CPM_NE = 6;   // != : not equal to

bool cpm::operator==(const struct cpm::ver& lhs, const struct cpm::ver& rhs){
    return (lhs.ineq==rhs.ineq) && (lhs.ver==rhs.ver);
}
bool cpm::operator<(const struct cpm::ver& lhs, const struct cpm::ver& rhs){
    return cmpVer(lhs, rhs) < 0;
}

//---

std::string cpm::print_str(const struct cpm::ver& ver){
    return sstd::ssprintf("ineq: %s, ver: %s", cpm::ineq2str(ver.ineq).c_str(), ver.ver.c_str());
}
std::string cpm::print_str(const std::vector<struct cpm::ver>& vVer){
    std::string ret;
    if(vVer.size()==0){ return ret; }
    
    for(int i=0; i<(int)vVer.size()-1; ++i){
        ret += "[ ";
        ret += print_str(vVer[i]);
        ret += " ], ";
    }
    ret += "[ ";
    ret += print_str(vVer[vVer.size()-1]);
    ret += " ]";
    return ret;
}
void cpm::print(const             struct cpm::ver &  ver){ printf("%s\n", cpm::print_str( ver).c_str()); }
void cpm::print(const std::vector<struct cpm::ver>& vVer){ printf("%s\n", cpm::print_str(vVer).c_str()); }

//---

std::string cpm::print_str(const             cpm::verLR &  ver){
    std::string l = cpm::print_str(ver.first );
    std::string r = cpm::print_str(ver.second);
    return '['+l+"], ["+r+']';
}
std::string cpm::print_str(const std::vector<cpm::verLR>& vVer){
    std::string ret;
    if(vVer.size()==0){ return ret; }
    
    for(int i=0; i<(int)vVer.size()-1; ++i){
        ret += "[ ";
        ret += print_str(vVer[i]);
        ret += " ], ";
    }
    ret += "[ ";
    ret += print_str(vVer[vVer.size()-1]);
    ret += " ]";
    return ret;
}
void cpm::print(const             cpm::verLR &  ver){ printf("%s\n", cpm::print_str( ver).c_str()); }
void cpm::print(const std::vector<cpm::verLR>& vVer){ printf("%s\n", cpm::print_str(vVer).c_str()); }

//-------------

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

std::string cpm::ineq2str(const uchar& ineq){
    switch(ineq){
    case CPM_NULL: { return std::string(""); }
    case CPM_LT: { return std::string("<" ); }
    case CPM_LE: { return std::string("<="); }
    case CPM_EQ: { return std::string("=="); }
    case CPM_GE: { return std::string(">="); }
    case CPM_GT: { return std::string(">" ); }
    case CPM_NE: { return std::string("!="); }
    default: { sstd::pdbg_err("ineq2str() has invalid value.\n"); return std::string(""); }
    }
}
uchar cpm::str2ineq(bool& ret, const std::string& ra){
    ret=true;
    if(ra.size()==0){ return 0; }
    if(ra.size()!=1 && ra.size()!=2){
        sstd::pdbg_err("inputted inequality-sign is invalid.\n");
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
        sstd::pdbg_err("inputted inequality-sign (%s) is invalid.\n", ra.c_str());
        ret=false;
        return 0;
    }
}
struct cpm::ver str2ver_base(bool& ret, const char* pStr){
    std::string s = sstd::stripAll(pStr, " ");
    
    std::string ra  = getWhile_c(s, "<=>!");
    std::string ver = std::string(&s[ra.size()], s.size()-ra.size());

    uchar ret_ineq = cpm::str2ineq(ret, ra); if(!ret){ return cpm::ver(); }

    struct cpm::ver r;
    r.ineq = ret_ineq;
    r.ver = ver;

    return r;
}
            struct cpm::ver  cpm::str2ver(const                    char * pStr){ bool ret; return str2ver_base(ret, pStr        ); }
            struct cpm::ver  cpm::str2ver(const             std::string &  str){ bool ret; return str2ver_base(ret,  str.c_str()); }
std::vector<struct cpm::ver> cpm::str2ver(const std::vector<std::string>& vStr){
    std::vector<struct cpm::ver> vVer(vStr.size());
    for(uint i=0; i<vStr.size(); ++i){
        bool ret;
        vVer[i] = str2ver_base(ret, vStr[i].c_str());
        if(!ret){ sstd::pdbg_err("Invalid input: \"%s\". cpm::str2ver() is failed.\n", vStr[i].c_str()); return std::vector<struct cpm::ver>(); }
    }
    return vVer;
}

std::vector<struct cpm::ver> cpm::split_verNE(const struct cpm::ver& v){
    struct cpm::ver l;
    l.ineq  = CPM_LT;
    l.ver = v.ver;
    
    struct cpm::ver r;
    r.ineq  = CPM_GT;
    r.ver = v.ver;
    
    return std::vector<struct cpm::ver>({l, r});
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
    
    if(lhs=="latest"){ return  1; }
    if(rhs=="latest"){ return -1; }
    
    std::vector<std::string> vL = sstd::split(lhs, '.');
    std::vector<std::string> vR = sstd::split(rhs, '.');
    
    // remove head 0 padding. ex: ver 01.00.00 -> 1..
    for(uint i=0; i<vL.size(); ++i){ sstd::lstrip_ow(vL[i], '0'); }
    for(uint i=0; i<vR.size(); ++i){ sstd::lstrip_ow(vR[i], '0'); }
//  if(vL==vR){ return 0; }
    
    uint len=sstd::min(vL.size(), vR.size());
    for(uint vi=0; vi<len; ++vi){
        if(sstd::strmatch(vL[vi], vR[vi]) || sstd::strmatch(vR[vi], vL[vi])){ continue; }
        if(vL[vi].size() < vR[vi].size()){ return -1; } // lt_case01_a, lt_case01_b, lt_case01_c
        if(vL[vi].size() > vR[vi].size()){ return  1; } // gt_case01_a, gt_case01_b, gt_case01_c
        
        for(uint i=0; i<vL[vi].size(); ++i){
            if(vL[vi][i] < vR[vi][i]){ return -1; } // follow the ASCII Code order // lt_case02_a, lt_case02_b, lt_case02_c
            if(vL[vi][i] > vR[vi][i]){ return  1; } // follow the ASCII Code order // gt_case02_a, gt_case02_b, gt_case02_c
        }
    }
    bool tf_eq=true;
    for(uint i=len; i<vL.size(); ++i){
        if(vL[i]=="*" || vL[i]=="?"){ continue; }
        tf_eq=false;
    }
    for(uint i=len; i<vR.size(); ++i){
        if(vR[i]=="*" || vR[i]=="?"){ continue; }
        tf_eq=false;
    }
    if(tf_eq){ return 0; }
    if(vL.size() != vR.size()){ return (vL.size() < vR.size() ? -1:1); } // lt_case03, gt_case03
    
    return 0; // eq_case02_a, eq_case02_b
}
int cpm::cmpVer(const struct cpm::ver& lhs, const struct cpm::ver& rhs){
    // lhs <  rhs: -2
    // lhs <= rhs: -1
    // lhs == rhs:  0
    // lhs >= rhs:  1
    // lhs >  rhs:  2
    
    int c = cmpVer(lhs.ver, rhs.ver);
    if( c < 0 ){ return -2; }
    if( c > 0 ){ return  2; }

    // c == 0
    // order: <, <=, ==, >=, >
    if(lhs.ineq==CPM_LT){
        if(rhs.ineq==CPM_LT){ return  0; }
        return -2;
    }
    if(lhs.ineq==CPM_LE){
        if(rhs.ineq==CPM_LT){ return  2; }
        if(rhs.ineq==CPM_EQ){ return  1; }
        if(rhs.ineq==CPM_LE){ return  0; }
        if(rhs.ineq==CPM_GE){ return -1; }
        return -2;
    }
    if(lhs.ineq==CPM_EQ){
        if(rhs.ineq==CPM_LT){ return  2; }
        if(rhs.ineq==CPM_LE){ return  1; }
        if(rhs.ineq==CPM_EQ){ return  0; }
        if(rhs.ineq==CPM_GE){ return -1; }
        return -1;
    }
    if(lhs.ineq==CPM_GE){
        if(rhs.ineq==CPM_LT){ return  2; }
        if(rhs.ineq==CPM_LE){ return  1; }
        if(rhs.ineq==CPM_EQ){ return  1; }
        if(rhs.ineq==CPM_GE){ return  0; }
        return -2;
    }
    if(lhs.ineq==CPM_GT){
        if(rhs.ineq==CPM_GT){ return  0; }
        return  2;
    }
    
    sstd::pdbg_err("lhs.ineq has unexpected value: %d.\n", lhs.ineq);
    return -1;
}
void cpm::rm_same_ver(std::vector<struct cpm::ver>& v){
    // --- NOTE: Needs to input sorted value ---
    
    int vi=0;
    int i=0;
    if(v.size()<=1){ return; }
    for(; i<(int)v.size()-1;){
        if(v[i].ineq==v[i+1].ineq && v[i].ver==v[i+1].ver){ ++i; }
        v[vi] = v[i]; ++vi; ++i;
    }
    if(i<(int)v.size()){
        v[vi] = v[i]; ++vi;
    }
    
    v.resize(vi);
}
std::vector<cpm::verLR> cpm::split_by_range(bool& ret_TF, const std::vector<struct cpm::ver>& v){
    // --- NOTE: Needs to input sorted value ---
    
    ret_TF=true;
    std::vector<cpm::verLR> vR;

    // begin: case01a_begin
    if(v.size()==0){ return vR; }
    uint b=0;
    if(v[b].ineq==CPM_LT || v[b].ineq==CPM_LE){
        cpm::verLR r;
        r.first.ineq  =CPM_GT;
        r.first.ver ="-inf";
        r.second.ineq =v[b].ineq;
        r.second.ver=v[b].ver;
        vR <<= r;
        ++b;
    }

    // end: case01b_end
    uint e=v.size(); // end
    cpm::verLR r_end;
    bool TF_pushBack=false;
    if(v[e-1].ineq==CPM_GT || v[e-1].ineq==CPM_GE){
        r_end.first.ineq  =v[e-1].ineq;
        r_end.first.ver =v[e-1].ver;
        r_end.second.ineq =CPM_LT;
        r_end.second.ver="inf";
        --e;
        TF_pushBack=true;
    }

    // middle: case02_middle01, case02_middle02
    for(uint i=b; i<e; ++i){
        cpm::verLR r;
        if(v[i].ineq==CPM_EQ){
            r.first.ineq  =CPM_EQ;
            r.first.ver =v[i].ver;
            r.second.ineq =CPM_EQ;
            r.second.ver=v[i].ver;
        }else{
            if(i+1>=e){ ret_TF=false; sstd::pdbg_err("Unexpected vec size. Inequality-sign is not closed.\n"); return vR; }
            if(!( (v[i  ].ineq==CPM_GT || v[i  ].ineq==CPM_GE) &&
                  (v[i+1].ineq==CPM_LT || v[i+1].ineq==CPM_LE)    )){ ret_TF=false; sstd::pdbg_err("Unexpected inequality-sign. Inequality-sign is not closed.\n"); return vR; }
            
            r.first.ineq  =v[i  ].ineq;
            r.first.ver =v[i  ].ver;
            r.second.ineq =v[i+1].ineq;
            r.second.ver=v[i+1].ver;
            ++i;
        }
        vR <<= r;
    }
    
    if(TF_pushBack){ vR <<= r_end; }
    return vR;
}
std::string getMoreConcrete(const std::string& lhs, const std::string& rhs){
    // returning more concrete version string
    // - Example1. When compareing a) 1.0.0 and b) 1.*.*, a) is more concrete.
    // - Example2. When compareing a) 1.0.? and b) 1.*.*, a) is more concrete.

    
    // The following is a minimal implementation, 
    // just selects and returns a string without wildcard.
    if(sstd::charIn('*', lhs) || sstd::charIn('?', lhs)){
        return rhs;
    }else{
        return lhs;
    }
}
std::vector<struct cpm::ver> cpm::verAND(bool& ret_TF, const cpm::verLR& l, const cpm::verLR& r){
    
    ret_TF=true;
    std::vector<struct cpm::ver> ret;
    if(l.first.ineq==CPM_NULL || l.second.ineq==CPM_NULL || r.first.ineq==CPM_NULL || r.second.ineq==CPM_NULL){ ret_TF=false; return ret; }
    if(l.first.ver.size()==0 || l.second.ver.size()==0 || r.first.ver.size()==0 || r.second.ver.size()==0){ ret_TF=false; return ret; }
    
    // ll: l.first
    // lr: l.second
    // rl: r.first
    // rr: r.second

// NOTE: case01 contained in the other cases, os no longer needed to implimenting.
//
//    // case01, case01wc_a, case01wc_b
//    // ll == rl && lr == rr && ll.ver == lr.ver
//    // l: ll <---> lr
//    // r: rl <---> rr
//    if(cmpVer(l.first, r.first)==0){ // ll == rl
//        if(cmpVer(l.second, r.second)==0){ // lr == rr
//            if(cmpVer(l.first.ver, r.second.ver)==0){ // ll == rr
//                struct cpm::ver v;
//                v.ineq  = CPM_EQ;
//                v.ver = getMoreConcrete(l.first.ver, r.first.ver);
//                ret <<= v;
//                return ret;
//            }
//        }
//    }
    
    // case02a, case02a_wc
    // lr.ineq=='<=' && rl.ineq=='>=' && lr.ver == rl.ver
    // l: ll <---> lr
    // r:          rl <---> rr
    if(cmpVer(l.second.ver, r.first.ver)==0){ // lr.ver == rl.ver
        if(l.second.ineq==CPM_LE){ // lr.ineq=='<='
            if(r.first.ineq==CPM_GE){ // rl.ineq=='>='
                struct cpm::ver v;
                v.ineq  = CPM_EQ;
                v.ver = getMoreConcrete(l.second.ver, r.first.ver);
                ret <<= v;
                return ret;
            }
        }
    }
    
    // case02b, case02b_wc
    // rr.ineq=='<=' && ll.ineq=='>=' && rr.ver == ll.ver
    // l:          ll <---> lr
    // r: rl <---> rr
    if(cmpVer(r.second.ver, l.first.ver)==0){ // rr.ver == ll.ver
        if(r.second.ineq==CPM_LE){ // rr.ineq=='<='
            if(l.first.ineq==CPM_GE){ // ll.ineq=='>='
                struct cpm::ver v;
                v.ineq  = CPM_EQ;
                v.ver = getMoreConcrete(l.first.ver, r.second.ver);
                ret <<= v;
                return ret;
            }
        }
    }
    
    // case03a, case03a_wcLR01, case03a_wcLR02, case03b_wcLR02 (is on border between case03a and case03b)
    // l ⊂ r: rl <= ll && lr <= rr
    // l:       ll <---> lr
    // r: rl <---------------> rr
    if(cmpVer(l.first, r.first)>=-1){ // ll >= rl
        if(cmpVer(l.second, r.second)<=1){ // lr <= rr
            struct cpm::ver vr;
            if(cmpVer(l.first.ver, r.first.ver)==0){ // ll.ver == rl.ver
                vr.ineq = l.first.ineq;
                vr.ver  = getMoreConcrete(l.first.ver, r.first.ver);
            }else{
                vr = l.first;
            }
            
            struct cpm::ver vl;
            if(cmpVer(l.second.ver, r.second.ver)==0){ // lr.ver == rr.ver
                vl.ineq = l.second.ineq;
                vl.ver  = getMoreConcrete(l.second.ver, r.second.ver);
            }else{
                vl = l.second;
            }
            
            ret <<= vr;
            ret <<= vl;
            return ret;
        }
    }
    
    // case03b, case03b_wcLR01, case03b_wcL
    // l ⊃ r
    // l: ll <---------------> lr
    // r:       rl <---> rr
    if(cmpVer(l.first, r.first)<=1){ // ll <= rl
        if(cmpVer(l.second, r.second)>=-1){ // lr >= rr
            struct cpm::ver vr;
            if(cmpVer(l.first.ver, r.first.ver)==0){ // ll.ver == rl.ver
                vr.ineq = r.first.ineq;
                vr.ver  = getMoreConcrete(l.first.ver, r.first.ver);
            }else{
                vr = r.first;
            }
            
            struct cpm::ver vl;
            if(cmpVer(l.second.ver, r.second.ver)==0){ // lr.ver == rr.ver
                vl.ineq = r.second.ineq;
                vl.ver  = getMoreConcrete(l.second.ver, r.second.ver);
            }else{
                vl = r.second;
            }
            
            ret <<= vr;
            ret <<= vl;
            return ret;
        }
    }
    
    // case04a, case04a_border_case
    // l ∩ r (1): rl <= ll <= rr && rr <= lr
    // l:       ll <--------> lr
    // r: rl <-------> rr
    if(cmpVer(l.first, r.first)>=0){ // ll >= rl
        if(cmpVer(l.first, r.second)<=0){ // ll <= rr
            if(cmpVer(l.second, r.second)>=0){ // lr >= rr
                ret <<= l.first;
                ret <<= r.second;
                return ret;
            }
        }
    }
    
    // case04b, case04b_border_case
    // l ∩ r (2): ll <= rl <= lr && lr <= rr
    // l: ll <-------> lr
    // r:       rl <--------> rr
    if(cmpVer(r.first, l.first)>=0){ // rl >= ll
        if(cmpVer(r.first, l.second)<=0){ // rl <= lr
            if(cmpVer(l.second, r.second)<=0){ // lr <= rr
                ret <<= r.first;
                ret <<= l.second;
                return ret;
            }
        }
    }
    
    return ret;
}
std::vector<struct cpm::ver> cpm::verAND(bool& ret_TF, const std::vector<struct cpm::ver>& vLhs_in, const std::vector<struct cpm::ver>& vRhs_in){
    std::vector<struct cpm::ver> ret;
    
    std::vector<struct cpm::ver> vLhs;
    std::vector<struct cpm::ver> vRhs;
    for(uint i=0; i<vLhs_in.size(); ++i){
        if(vLhs_in[i].ineq==CPM_NE){
            std::vector<struct cpm::ver> r = cpm::split_verNE(vLhs_in[i]);
            vLhs <<= r;
            continue;
        }
        vLhs <<= vLhs_in[i];
    }
    for(uint i=0; i<vRhs_in.size(); ++i){
        if(vRhs_in[i].ineq==CPM_NE){
            std::vector<struct cpm::ver> r = cpm::split_verNE(vRhs_in[i]);
            vRhs <<= r;
            continue;
        }
        vRhs <<= vRhs_in[i];
    }
    
    std::sort(vLhs.begin(), vLhs.end());
    std::sort(vRhs.begin(), vRhs.end());
    cpm::rm_same_ver(vLhs);
    cpm::rm_same_ver(vRhs);
    
    std::vector<cpm::verLR> vL = cpm::split_by_range(ret_TF, vLhs); if(!ret_TF){ return ret; }
    std::vector<cpm::verLR> vR = cpm::split_by_range(ret_TF, vRhs); if(!ret_TF){ return ret; }
    
    for(uint li=0; li<vL.size(); ++li){
        for(uint ri=0; ri<vR.size(); ++ri){
            std::vector<struct cpm::ver> r = cpm::verAND(ret_TF, vL[li], vR[ri]); if(!ret_TF){ return std::vector<struct cpm::ver>(); }
            ret <<= r;
        }
    }
    
    return ret;
}
