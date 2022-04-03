#pragma once
#include "../src/version_processor.hpp"

#define CPM_LT 1 // <  : less than
#define CPM_LE 2 // <= : less than or equal to
#define CPM_EQ 3 // == : equal to
#define CPM_GE 4 // >= : greater than or equal to
#define CPM_GT 5 // >= : greater than
#define CPM_NE 6 // != : not equal to


//sstd, >=0.0.0, <=2.0.1;

//sstd, <=2.0.1;
//sstd, >-inf, <=2.0.1;

//sstd, ==2.0.1;
//sstd, ==2.0.*;
//sstd, ==2.*.*;

//sstd, >=2.0.1;
//sstd, >=2.0.1, <inf;

TEST(version_processor, str2vis_case00){
    std::string s = "";
    struct cpm::vis r = cpm::str2vis(s);
    sstd::printn(cpm::is2str(r.is));
    sstd::printn(r.ver);
}
TEST(version_processor, str2vis_case01){
//    ASSERT_EQ(1, 1);

    std::string s = "  <=  1.0.0  ";
    struct cpm::vis r = cpm::str2vis(s);
    sstd::printn(cpm::is2str(r.is));
    sstd::printn(r.ver);
}
TEST(version_processor, str2vis_case02){
    std::string s = "<=";
    struct cpm::vis r = cpm::str2vis(s);
    sstd::printn(cpm::is2str(r.is));
    sstd::printn(r.ver);
}

TEST(version_processor, split_visNE){
    struct cpm::vis v;
    v.is  = CPM_NE;
    v.ver = "1.0.0";
    
    std::vector<struct cpm::vis> v_vis = cpm::split_visNE(v);
    
    ASSERT_TRUE(cpm::is2str(v_vis[0].is) == "<");
    ASSERT_STREQ(v_vis[0].ver.c_str(), "1.0.0");
    ASSERT_TRUE(cpm::is2str(v_vis[1].is) == ">");
    ASSERT_STREQ(v_vis[1].ver.c_str(), "1.0.0");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(version_processor, cmpVer_eq_case01){
    std::string lhs = "1.0.0";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_eq_case02_a){
    std::string lhs = "010.00.00";
    std::string rhs = "10.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_eq_case02_b){
    std::string lhs = "10.0.0";
    std::string rhs = "010.00.00";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}

//---

TEST(version_processor, cmpVer_lt_case01_a){
    std::string lhs = "1.0.0";
    std::string rhs = "10.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_lt_case01_b){
    std::string lhs = "1.1.0";
    std::string rhs = "1.10.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_lt_case01_c){
    std::string lhs = "1.1.0";
    std::string rhs = "1.1.10";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}

TEST(version_processor, cmpVer_lt_case02_a){
    std::string lhs = "1.0.0";
    std::string rhs = "1.1.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_lt_case02_b){
    std::string lhs = "1.0.0";
    std::string rhs = "1.0.1";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_lt_case02_c){
    std::string lhs = "1.0.10";
    std::string rhs = "1.0.11";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}

TEST(version_processor, cmpVer_lt_case03){
    std::string lhs = "1.0.0";
    std::string rhs = "1.0.0.m";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}

TEST(version_processor, cmpVer_lt_composite_case_a){
    std::string lhs = "0.0.9";
    std::string rhs = "0.0.11";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_lt_composite_case_b){
    std::string lhs = "10.0.10";
    std::string rhs = "10.0.11";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_lt_composite_case_c){
    std::string lhs = "10.0.9";
    std::string rhs = "11.0.1";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}

//---

TEST(version_processor, cmpVer_gt_case01_a){
    std::string lhs = "10.0.0";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_gt_case01_b){
    std::string lhs = "1.10.0";
    std::string rhs = "1.1.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_gt_case01_c){
    std::string lhs = "1.1.10";
    std::string rhs = "1.1.1";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}

TEST(version_processor, cmpVer_gt_case02_a){
    std::string lhs = "1.1.0";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_gt_case02_b){
    std::string lhs = "1.0.1";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_gt_case02_c){
    std::string lhs = "1.0.11";
    std::string rhs = "1.0.10";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}

TEST(version_processor, cmpVer_gt_case03){
    std::string lhs = "1.0.0.m";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}

TEST(version_processor, cmpVer_gt_composite_case_a){
    std::string lhs = "0.0.11";
    std::string rhs = "0.0.9";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_gt_composite_case_b){
    std::string lhs = "10.0.11";
    std::string rhs = "10.0.10";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_gt_composite_case_c){
    std::string lhs = "11.0.1";
    std::string rhs = "10.0.9";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(version_processor, visAND_case01a){
    // lhs: 1.0.0 <=
    // rhs:           <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r1 = cpm::str2vis("<=2.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    cpm::print(ret);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_TRUE(ret.size()==2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case01b){
    // lhs:           <= 2.0.0
    // rhs: 1.0.0 <=
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    cpm::print(ret);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_TRUE(ret.size()==2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case02a){
    // lhs:          1.0.0 <=  ver  <= 3.0.0
    // rhs: 0.1.0 <=  ver  <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=3.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis r2 = cpm::str2vis("<=2.0.0");
    vLhs <<= l1;
    vLhs <<= l2;
    vRhs <<= r1;
    vRhs <<= r2;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    cpm::print(ret);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_TRUE(ret.size()==2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
/*
TEST(version_processor, visAND_case02b){
    // lhs: 0.1.0 <=  ver  <= 2.0.0
    // rhs:          1.0.0 <=  ver  <= 3.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r1 = cpm::str2vis("<=2.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    cpm::print(ret);
    ASSERT_TRUE(ret[0]==r1);
    ASSERT_TRUE(ret[1]==l1);
}
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

#undef CPM_NE
#undef CPM_GT
#undef CPM_GE
#undef CPM_EQ
#undef CPM_LE
#undef CPM_LT