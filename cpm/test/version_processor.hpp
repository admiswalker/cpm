#pragma once
#include "../src/version_processor.hpp"

#define CPM_NULL 0 // initial value
#define CPM_LT 1   // <  : less than
#define CPM_LE 2   // <= : less than or equal to
#define CPM_EQ 3   // == : equal to
#define CPM_GE 4   // >= : greater than or equal to
#define CPM_GT 5   // >= : greater than
#define CPM_NE 6   // != : not equal to


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
    struct cpm::vis r1 = cpm::str2vis(s);
    ASSERT_EQ(r1.is, CPM_NULL);
    std::string r2=cpm::is2str(r1.is);
    ASSERT_STREQ(r2.c_str(), "");
}
TEST(version_processor, str2vis_case01){
    std::string s = "  <=  1.0.0  ";
    struct cpm::vis r = cpm::str2vis(s);
    ASSERT_STREQ(cpm::is2str(r.is).c_str(), "<=");
    ASSERT_STREQ(r.ver.c_str(), "1.0.0");
}
TEST(version_processor, str2vis_case02){
    std::string s = "<=";
    struct cpm::vis r = cpm::str2vis(s);
    ASSERT_STREQ(cpm::is2str(r.is).c_str(), "<=");
    ASSERT_STREQ(r.ver.c_str(), "");
}
TEST(version_processor, str2vis_case03){
    std::string s = ">=-inf";
    struct cpm::vis r = cpm::str2vis(s);
    ASSERT_STREQ(cpm::is2str(r.is).c_str(), ">=");
    ASSERT_STREQ(r.ver.c_str(), "-inf");
}
TEST(version_processor, str2vis_case04){
    std::string s = "<=inf";
    struct cpm::vis r = cpm::str2vis(s);
    ASSERT_STREQ(cpm::is2str(r.is).c_str(), "<=");
    ASSERT_STREQ(r.ver.c_str(), "inf");
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

TEST(version_processor, sort_case01_01){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<0.1.0");
    struct cpm::vis e2 = cpm::str2vis("<0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis("<0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case01_02){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<0.1.0");
    struct cpm::vis e2 = cpm::str2vis("<=0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis("<=0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case01_03){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">=0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">=0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case01_04){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}

//---

TEST(version_processor, sort_case02_01){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2 = cpm::str2vis("<0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis("<=0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case02_02){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2 = cpm::str2vis("<=0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis("<=0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case02_03){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">=0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">=0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case02_04){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}

//---

TEST(version_processor, sort_case03_01){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis e2 = cpm::str2vis("<0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">=0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case03_02){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis e2 = cpm::str2vis("<=0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">=0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case03_03){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">=0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis(">=0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">=0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case03_04){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis(">=0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}

//---

TEST(version_processor, sort_case04_01){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">0.1.0");
    struct cpm::vis e2 = cpm::str2vis("<0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case04_02){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">0.1.0");
    struct cpm::vis e2 = cpm::str2vis("<=0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<=0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case04_03){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">=0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis(">=0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}
TEST(version_processor, sort_case04_04){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">0.1.0");
    v = {e1, e2};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis(">0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis(">0.1.0");
    ASSERT_EQ(v.size(), (uint)2);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
}

//---

TEST(version_processor, sort_composite_case_01){
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">0.1.0");
    struct cpm::vis e2 = cpm::str2vis(">=0.1.0");
    struct cpm::vis e3 = cpm::str2vis("<=0.1.0");
    struct cpm::vis e4 = cpm::str2vis("<0.1.0");
    v = {e1, e2, e3, e4};
    
    std::sort(v.begin(), v.end());
    
    struct cpm::vis e1_ans = cpm::str2vis("<0.1.0");
    struct cpm::vis e2_ans = cpm::str2vis("<=0.1.0");
    struct cpm::vis e3_ans = cpm::str2vis(">=0.1.0");
    struct cpm::vis e4_ans = cpm::str2vis(">0.1.0");
    ASSERT_EQ(v.size(), (uint)4);
    ASSERT_TRUE(v[0]==e1_ans);
    ASSERT_TRUE(v[1]==e2_ans);
    ASSERT_TRUE(v[2]==e3_ans);
    ASSERT_TRUE(v[3]==e4_ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(version_processor, cmpVer_str_eq_case01){
    std::string lhs = "1.0.0";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_str_eq_case02_a){
    std::string lhs = "010.00.00";
    std::string rhs = "10.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_str_eq_case02_b){
    std::string lhs = "10.0.0";
    std::string rhs = "010.00.00";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}

//---

TEST(version_processor, cmpVer_str_lt_case01_a){
    std::string lhs = "1.0.0";
    std::string rhs = "10.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_lt_case01_b){
    std::string lhs = "1.1.0";
    std::string rhs = "1.10.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_lt_case01_c){
    std::string lhs = "1.1.0";
    std::string rhs = "1.1.10";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}

TEST(version_processor, cmpVer_str_lt_case02_a){
    std::string lhs = "1.0.0";
    std::string rhs = "1.1.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_lt_case02_b){
    std::string lhs = "1.0.0";
    std::string rhs = "1.0.1";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_lt_case02_c){
    std::string lhs = "1.0.10";
    std::string rhs = "1.0.11";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}

TEST(version_processor, cmpVer_str_lt_case03){
    std::string lhs = "1.0.0";
    std::string rhs = "1.0.0.m";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}

TEST(version_processor, cmpVer_str_lt_composite_case_a){
    std::string lhs = "0.0.9";
    std::string rhs = "0.0.11";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_lt_composite_case_b){
    std::string lhs = "10.0.10";
    std::string rhs = "10.0.11";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_lt_composite_case_c){
    std::string lhs = "10.0.9";
    std::string rhs = "11.0.1";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}

//---

TEST(version_processor, cmpVer_str_gt_case01_a){
    std::string lhs = "10.0.0";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_str_gt_case01_b){
    std::string lhs = "1.10.0";
    std::string rhs = "1.1.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_str_gt_case01_c){
    std::string lhs = "1.1.10";
    std::string rhs = "1.1.1";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}

TEST(version_processor, cmpVer_str_gt_case02_a){
    std::string lhs = "1.1.0";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_str_gt_case02_b){
    std::string lhs = "1.0.1";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_str_gt_case02_c){
    std::string lhs = "1.0.11";
    std::string rhs = "1.0.10";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}

TEST(version_processor, cmpVer_str_gt_case03){
    std::string lhs = "1.0.0.m";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}

TEST(version_processor, cmpVer_str_gt_composite_case_a){
    std::string lhs = "0.0.11";
    std::string rhs = "0.0.9";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_str_gt_composite_case_b){
    std::string lhs = "10.0.11";
    std::string rhs = "10.0.10";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_str_gt_composite_case_c){
    std::string lhs = "11.0.1";
    std::string rhs = "10.0.9";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}

//---

TEST(version_processor, cmpVer_str_inf_case01a){
    std::string lhs = "-inf";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_inf_case01b){
    std::string lhs = "1.0.0";
    std::string rhs = "-inf";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  1);
}
TEST(version_processor, cmpVer_str_inf_case02a){
    std::string lhs = "inf";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  1);
}
TEST(version_processor, cmpVer_str_inf_case02b){
    std::string lhs = "1.0.0";
    std::string rhs = "inf";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_inf_case03a){
    std::string lhs = "-inf";
    std::string rhs = "inf";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  -1);
}
TEST(version_processor, cmpVer_str_inf_case03b){
    std::string lhs = "inf";
    std::string rhs = "-inf";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  1);
}
TEST(version_processor, cmpVer_str_inf_case04){
    std::string lhs = "-inf";
    std::string rhs = "-inf";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  0);
}
TEST(version_processor, cmpVer_str_inf_case05){
    std::string lhs = "inf";
    std::string rhs = "inf";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  0);
}

//---

TEST(version_processor, cmpVer_str_wc_case01a){
    std::string lhs = "1.*.*";
    std::string rhs = "1.2.3";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_str_wc_case01b){
    std::string lhs = "1.2.3";
    std::string rhs = "1.*.*";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_str_wc_case01c){
    std::string lhs = "1.*.*";
    std::string rhs = "1.*.*";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}

TEST(version_processor, cmpVer_str_wc_case02a){
    std::string lhs = "1.0.*.*";
    std::string rhs = "1.0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_str_wc_case02b){
    std::string lhs = "1.0.0";
    std::string rhs = "1.0.*.*";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}

TEST(version_processor, cmpVer_str_wc_case03a){
    std::string lhs = "1.?.?";
    std::string rhs = "1.2.3";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_str_wc_case03b){
    std::string lhs = "1.2.3";
    std::string rhs = "1.?.?";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_str_wc_case03c){
    std::string lhs = "1.?.?";
    std::string rhs = "1.?.?";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}

TEST(version_processor, cmpVer_str_wc_case04){
    std::string lhs = "1.1?.0";
    std::string rhs = "1.10.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 0);
}
TEST(version_processor, cmpVer_str_wc_case05){
    std::string lhs = "1.2?.0";
    std::string rhs = "1.10.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), 1);
}
TEST(version_processor, cmpVer_str_wc_case06){
    std::string lhs = "1.1?.0";
    std::string rhs = "1.20.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_wc_case07a){
    std::string lhs = "1.?0.0";
    std::string rhs = "1.100.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs), -1);
}
TEST(version_processor, cmpVer_str_wc_case07b){
    std::string lhs = "1.100.0";
    std::string rhs = "1.?0.0";
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  1);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(version_processor, cmpVer_vis_eq_case00){
    struct cpm::vis lhs = cpm::str2vis("<=1.0.0");
    struct cpm::vis rhs = cpm::str2vis("<=1.0.0");
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  0);
}
TEST(version_processor, cmpVer_vis_case01a){
    struct cpm::vis lhs = cpm::str2vis("<=1.0.0");
    struct cpm::vis rhs = cpm::str2vis("<=5.0.0");
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  -1);
}
TEST(version_processor, cmpVer_vis_case01b){
    struct cpm::vis lhs = cpm::str2vis("<=5.0.0");
    struct cpm::vis rhs = cpm::str2vis("<=1.0.0");
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  1);
}
TEST(version_processor, cmpVer_vis_case02){
    struct cpm::vis lhs = cpm::str2vis("==1.0.0");
    struct cpm::vis rhs = cpm::str2vis("==1.0.0");
    ASSERT_EQ(cpm::cmpVer(lhs, rhs),  0);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(version_processor, visAND_split_range_case01a_begin){
    // lhs: ver <= 1.0.0
    
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<=1.0.0");
    v = {e1};
    
    bool tf;
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    std::vector<T_pair> ret = cpm::split_by_range(tf, v);
//    for(auto r: ret){ cpm::print(r.first); cpm::print(r.second); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<=1.0.0");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)1);
    ASSERT_TRUE(ret[0].first ==l1_ans);
    ASSERT_TRUE(ret[0].second==r1_ans);
}
TEST(version_processor, visAND_split_range_case01b_end){
    // lhs: 1.0.0 <= ver
    
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis(">=1.0.0");
    v = {e1};
    
    bool tf;
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    std::vector<T_pair> ret = cpm::split_by_range(tf, v);
//    for(auto r: ret){ cpm::print(r.first); cpm::print(r.second); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<inf");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)1);
    ASSERT_TRUE(ret[0].first ==l1_ans);
    ASSERT_TRUE(ret[0].second==r1_ans);
}
TEST(version_processor, visAND_split_range_case03_middle01){
    // lhs: ver  <= 1.0.0,  2.0.0 <=  ver  <= 3.0.0, 4.0.0 <= ver
    
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<=1.0.0");
    struct cpm::vis e2 = cpm::str2vis(">=2.0.0");
    struct cpm::vis e3 = cpm::str2vis("<=3.0.0");
    struct cpm::vis e4 = cpm::str2vis(">=4.0.0");
    v = {e1, e2, e3, e4};
    
    bool tf;
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    std::vector<T_pair> ret = cpm::split_by_range(tf, v);
//  for(auto r: ret){ cpm::print(r.first); cpm::print(r.second); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<=1.0.0");
    struct cpm::vis l2_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r2_ans = cpm::str2vis("<=3.0.0");
    struct cpm::vis l3_ans = cpm::str2vis(">=4.0.0");
    struct cpm::vis r3_ans = cpm::str2vis("<inf");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)3);
    ASSERT_TRUE(ret[0].first ==l1_ans);
    ASSERT_TRUE(ret[0].second==r1_ans);
    ASSERT_TRUE(ret[1].first ==l2_ans);
    ASSERT_TRUE(ret[1].second==r2_ans);
    ASSERT_TRUE(ret[2].first ==l3_ans);
    ASSERT_TRUE(ret[2].second==r3_ans);
}
TEST(version_processor, visAND_split_range_case03_middle02){
    // rhs: ver  <= 5.0.0, 6.0.0 <=  ver
    
    std::vector<struct cpm::vis> v;
    struct cpm::vis e1 = cpm::str2vis("<=5.0.0");
    struct cpm::vis e2 = cpm::str2vis(">=6.0.0");
    v = {e1, e2};
    
    bool tf;
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    std::vector<T_pair> ret = cpm::split_by_range(tf, v);
//  for(auto r: ret){ cpm::print(r.first); cpm::print(r.second); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<=5.0.0");
    struct cpm::vis l2_ans = cpm::str2vis(">=6.0.0");
    struct cpm::vis r2_ans = cpm::str2vis("<inf");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0].first ==l1_ans);
    ASSERT_TRUE(ret[0].second==r1_ans);
    ASSERT_TRUE(ret[1].first ==l2_ans);
    ASSERT_TRUE(ret[1].second==r2_ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(version_processor, visAND_scalar_case01){
    // lhs: 1.0.0 <= ver <= 1.0.0
    // rhs: 1.0.0 <= ver <= 1.0.0
    
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    T_pair L;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=1.0.0");
    L.first  = l1;
    L.second = l2;
    T_pair R;
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=1.0.0");
    R.first  = r1;
    R.second = r2;
    
    bool tf;
    std::vector<struct cpm::vis> ret = cpm::visAND(tf, L, R);
//    for(auto r: ret){ cpm::print(r); }
    
    struct cpm::vis l1_ans = cpm::str2vis("==1.0.0");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)1);
    ASSERT_TRUE(ret[0]==l1_ans);
}
TEST(version_processor, visAND_scalar_case02a){
    // lhs: 1.0.0 <= ver <= 2.0.0
    // rhs:                 2.0.0 <= ver <= 3.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=3.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    struct cpm::vis l1_ans = cpm::str2vis("==2.0.0");
    ASSERT_EQ(ret.size(), (uint)1);
    ASSERT_TRUE(ret[0]==l1_ans);
}
TEST(version_processor, visAND_scalar_case02b){
    // lhs:                 2.0.0 <= ver <= 3.0.0
    // rhs: 1.0.0 <= ver <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=3.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    struct cpm::vis l1_ans = cpm::str2vis("==2.0.0");
    ASSERT_EQ(ret.size(), (uint)1);
    ASSERT_TRUE(ret[0]==l1_ans);
}
TEST(version_processor, visAND_scalar_case03a){
    // lhs:    2.0.0 <= ver <= 3.0.0
    // rhs: 1.0.0 <=    ver    <= 4.0.0
    
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    T_pair L;
    struct cpm::vis l1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=3.0.0");
    L.first  = l1;
    L.second = l2;
    T_pair R;
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=4.0.0");
    R.first  = r1;
    R.second = r2;
    
    bool tf;
    std::vector<struct cpm::vis> ret = cpm::visAND(tf, L, R);
//    for(auto r: ret){ cpm::print(r); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<=3.0.0");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_scalar_case03b){
    // lhs: 1.0.0 <=    ver    <= 4.0.0
    // rhs:    2.0.0 <= ver <= 3.0.0
    
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    T_pair L;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=4.0.0");
    L.first  = l1;
    L.second = l2;
    T_pair R;
    struct cpm::vis r1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=3.0.0");
    R.first  = r1;
    R.second = r2;
    
    bool tf;
    std::vector<struct cpm::vis> ret = cpm::visAND(tf, L, R);
//    for(auto r: ret){ cpm::print(r); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<=3.0.0");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_scalar_case04a){
    // lhs: 4.0.0 <= ver
    // rhs:          ver  <= 5.0.0
    
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    T_pair L;
    struct cpm::vis l1 = cpm::str2vis(">=4.0.0");
    struct cpm::vis l2 = cpm::str2vis("<inf");
    L.first  = l1;
    L.second = l2;
    T_pair R;
    struct cpm::vis r1 = cpm::str2vis(">-inf");
    struct cpm::vis r2 = cpm::str2vis("<=5.0.0");
    R.first  = r1;
    R.second = r2;
    
    bool tf;
    std::vector<struct cpm::vis> ret = cpm::visAND(tf, L, R);
//    for(auto r: ret){ cpm::print(r); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">=4.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<=5.0.0");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_scalar_case04a_border_case){
    // lhs: ver <= 1.0.0,
    // rhs:               2.0.0 <= ver
    
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    T_pair L;
    struct cpm::vis l1 = cpm::str2vis(">-inf");
    struct cpm::vis l2 = cpm::str2vis("<=1.0.0");
    L.first  = l1;
    L.second = l2;
    T_pair R;
    struct cpm::vis r1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis r2 = cpm::str2vis("<inf");
    R.first  = r1;
    R.second = r2;
    
    bool tf;
    std::vector<struct cpm::vis> ret = cpm::visAND(tf, L, R);
    for(auto r: ret){ cpm::print(r); }
    
    struct cpm::vis l1_ans = cpm::str2vis("==1.0.0");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)0);
}
TEST(version_processor, visAND_scalar_case04b){
    // lhs:          ver  <= 5.0.0
    // rhs: 4.0.0 <= ver
    
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    T_pair L;
    struct cpm::vis l1 = cpm::str2vis(">-inf");
    struct cpm::vis l2 = cpm::str2vis("<=5.0.0");
    L.first  = l1;
    L.second = l2;
    T_pair R;
    struct cpm::vis r1 = cpm::str2vis(">=4.0.0");
    struct cpm::vis r2 = cpm::str2vis("<inf");
    R.first  = r1;
    R.second = r2;
    
    bool tf;
    std::vector<struct cpm::vis> ret = cpm::visAND(tf, L, R);
//    for(auto r: ret){ cpm::print(r); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">=4.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<=5.0.0");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_scalar_case04b_02){
    // lhs: 4.0.0 <= ver
    // rhs:      6.0.0 <= ver
    
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    T_pair L;
    struct cpm::vis l1 = cpm::str2vis(">=4.0.0");
    struct cpm::vis l2 = cpm::str2vis("<inf");
    L.first  = l1;
    L.second = l2;
    T_pair R;
    struct cpm::vis r1 = cpm::str2vis(">=6.0.0");
    struct cpm::vis r2 = cpm::str2vis("<inf");
    R.first  = r1;
    R.second = r2;
    
    bool tf;
    std::vector<struct cpm::vis> ret = cpm::visAND(tf, L, R);
//    for(auto r: ret){ cpm::print(r); }
    
    struct cpm::vis l1_ans = cpm::str2vis(">=6.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<inf");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_scalar_case04b_border_case){
    // lhs:               2.0.0 <= ver
    // rhs: ver <= 1.0.0,
    
    using T_pair = std::pair<struct cpm::vis,struct cpm::vis>;
    T_pair L;
    struct cpm::vis l1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis l2 = cpm::str2vis("<inf");
    L.first  = l1;
    L.second = l2;
    T_pair R;
    struct cpm::vis r1 = cpm::str2vis(">-inf");
    struct cpm::vis r2 = cpm::str2vis("<=1.0.0");
    R.first  = r1;
    R.second = r2;
    
    bool tf;
    std::vector<struct cpm::vis> ret = cpm::visAND(tf, L, R);
    for(auto r: ret){ cpm::print(r); }
    
    struct cpm::vis l1_ans = cpm::str2vis("==1.0.0");
    ASSERT_TRUE(tf);
    ASSERT_EQ(ret.size(), (uint)0);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(version_processor, visAND_case00){
    // lhs:
    // rhs:
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    ASSERT_EQ(ret.size(), (uint)0);
}
TEST(version_processor, visAND_case01gl){
    // lhs: 1.0.0 <=
    // rhs:           <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r1 = cpm::str2vis("<=2.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case01lg){
    // lhs:           <= 2.0.0
    // rhs: 1.0.0 <=
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case01ll_a){
    // lhs: 1.0.0 <=
    // rhs:           <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<=1.0.0");
    struct cpm::vis r1 = cpm::str2vis("<=2.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<=1.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_case01ll_b){
    // lhs: 1.0.0 <=
    // rhs:           <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis("<=1.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<=1.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_case01gg_a){
    // lhs: 1.0.0 <=
    // rhs:           <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=2.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<inf");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_case01gg_b){
    // lhs: 1.0.0 <=
    // rhs:           <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    vLhs <<= l1;
    vRhs <<= r1;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<inf");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}

TEST(version_processor, visAND_case02a){
    // lhs: 0.1.0 <=  ver  <= 2.0.0
    // rhs:          1.0.0 <=  ver  <= 3.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis l2 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=3.0.0");
    vLhs <<= l1;
    vLhs <<= l2;
    vRhs <<= r1;
    vRhs <<= r2;
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case02b){
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
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case03a){
    // lhs: 0.1.0 <=     ver     <= 2.0.0
    // rhs:    0.4.0 <=  ver  <= 0.6.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis l2 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=0.4.0");
    struct cpm::vis r2 = cpm::str2vis("<=0.6.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">=0.4.0");
    struct cpm::vis r_ans = cpm::str2vis("<=0.6.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case03b){
    // lhs:    0.4.0 <=  ver  <= 0.6.0
    // rhs: 0.1.0 <=     ver     <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=0.4.0");
    struct cpm::vis l2 = cpm::str2vis("<=0.6.0");
    struct cpm::vis r1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis r2 = cpm::str2vis("<=2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">=0.4.0");
    struct cpm::vis r_ans = cpm::str2vis("<=0.6.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case04_01){
    // lhs: 1.0.0 <=  ver  <= 2.0.0
    // rhs: 1.0.0 <=  ver  <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case04_02){
    // lhs: 1.0.0 <=  ver  <= 2.0.0
    // rhs: 1.0.0 <=  ver  <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<2.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case04_03){
    // lhs: ver <= 1.0.0, 2.0.0 <= ver
    // rhs: ver <= 1.0.0, 2.0.0 <= ver
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<=1.0.0");
    struct cpm::vis l2 = cpm::str2vis(">=2.0.0");
    struct cpm::vis r1 = cpm::str2vis("<=1.0.0");
    struct cpm::vis r2 = cpm::str2vis(">=2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<=1.0.0");
    struct cpm::vis l2_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r2_ans = cpm::str2vis("<inf");
    ASSERT_EQ(ret.size(), (uint)4);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
    ASSERT_TRUE(ret[2]==l2_ans);
    ASSERT_TRUE(ret[3]==r2_ans);
}
TEST(version_processor, visAND_case05_01){
    // lhs: 1.0.0 <=  ver  <= 2.0.0
    // rhs: 1.0.0 <=     ver     <= 3.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=3.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case05_02){
    // lhs:      1.0.0 <=  ver  <= 2.0.0
    // rhs: 0.1.0 <=       ver  <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis l2 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)2);
    ASSERT_TRUE(ret[0]==l_ans);
    ASSERT_TRUE(ret[1]==r_ans);
}
TEST(version_processor, visAND_case05_03){
    // lhs: ver <= 1.0.0, 2.0.0 <= ver
    // rhs: ver <= 1.0.0, 1.5.0 <= ver
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<=1.0.0");
    struct cpm::vis l2 = cpm::str2vis(">=2.0.0");
    struct cpm::vis r1 = cpm::str2vis("<=1.0.0");
    struct cpm::vis r2 = cpm::str2vis(">=1.5.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<=1.0.0");
    struct cpm::vis l2_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r2_ans = cpm::str2vis("<inf");
    ASSERT_EQ(ret.size(), (uint)4);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
    ASSERT_TRUE(ret[2]==l2_ans);
    ASSERT_TRUE(ret[3]==r2_ans);
}
TEST(version_processor, visAND_case06a){
    // lhs: 1.0.0 <=     ver     <= 2.0.0
    // rhs:   ver <= 1.4.0, 1.6.0 <= ver
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis("<=1.4.0");
    struct cpm::vis r2 = cpm::str2vis(">=1.6.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<=1.4.0");
    struct cpm::vis l2_ans = cpm::str2vis(">=1.6.0");
    struct cpm::vis r2_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)4);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
    ASSERT_TRUE(ret[2]==l2_ans);
    ASSERT_TRUE(ret[3]==r2_ans);
}
TEST(version_processor, visAND_case06b){
    // lhs:   ver <= 1.4.0, 1.6.0 <= ver
    // rhs: 1.0.0 <=     ver     <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<=1.4.0");
    struct cpm::vis l2 = cpm::str2vis(">=1.6.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">=1.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<=1.4.0");
    struct cpm::vis l2_ans = cpm::str2vis(">=1.6.0");
    struct cpm::vis r2_ans = cpm::str2vis("<=2.0.0");
    ASSERT_EQ(ret.size(), (uint)4);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
    ASSERT_TRUE(ret[2]==l2_ans);
    ASSERT_TRUE(ret[3]==r2_ans);
}

TEST(version_processor, visAND_case07a){
    // lhs: 1.0.0 <= ver <= 2.0.0
    // rhs:                 2.0.0 <= ver <= 3.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=3.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    struct cpm::vis l1_ans = cpm::str2vis("==2.0.0");
    ASSERT_EQ(ret.size(), (uint)1);
    ASSERT_TRUE(ret[0]==l1_ans);
}
TEST(version_processor, visAND_case07b){
    // lhs:                 2.0.0 <= ver <= 3.0.0
    // rhs: 1.0.0 <= ver <= 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">=2.0.0");
    struct cpm::vis l2 = cpm::str2vis("<=3.0.0");
    struct cpm::vis r1 = cpm::str2vis(">=1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<=2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    struct cpm::vis l1_ans = cpm::str2vis("==2.0.0");
    ASSERT_EQ(ret.size(), (uint)1);
    ASSERT_TRUE(ret[0]==l1_ans);
}
TEST(version_processor, visAND_case08a){
    // lhs: 1.0.0 < ver < 2.0.0
    // rhs:               2.0.0 < ver < 3.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">2.0.0");
    struct cpm::vis r2 = cpm::str2vis("<3.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    ASSERT_EQ(ret.size(), (uint)0);
}
TEST(version_processor, visAND_case08b){
    // lhs:               2.0.0 < ver < 3.0.0
    // rhs: 1.0.0 < ver < 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">2.0.0");
    struct cpm::vis l2 = cpm::str2vis("<3.0.0");
    struct cpm::vis r1 = cpm::str2vis(">1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    ASSERT_EQ(ret.size(), (uint)0);
}
TEST(version_processor, visAND_case09a){
    // lhs: 1.0.0 < ver < 2.0.0
    // rhs:                     3.0.0 < ver < 4.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<2.0.0");
    struct cpm::vis r1 = cpm::str2vis(">3.0.0");
    struct cpm::vis r2 = cpm::str2vis("<4.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    ASSERT_EQ(ret.size(), (uint)0);
}
TEST(version_processor, visAND_case09b){
    // lhs:                     3.0.0 < ver < 4.0.0
    // rhs: 1.0.0 < ver < 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">3.0.0");
    struct cpm::vis l2 = cpm::str2vis("<4.0.0");
    struct cpm::vis r1 = cpm::str2vis(">1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    ASSERT_EQ(ret.size(), (uint)0);
}
TEST(version_processor, visAND_case10a){
    // lhs: 1.0.0 < v < 2.0.0
    // rhs:                 v < 3.0.0, 4.0.0 < v
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis(">1.0.0");
    struct cpm::vis l2 = cpm::str2vis("<2.0.0");
    struct cpm::vis r1 = cpm::str2vis("<3.0.0");
    struct cpm::vis r2 = cpm::str2vis(">4.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    ASSERT_EQ(ret.size(), (uint)2);
    struct cpm::vis l1_ans = cpm::str2vis(">1.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<2.0.0");
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_case10b){
    // lhs:                 v < 3.0.0, 4.0.0 < v
    // rhs: 1.0.0 < v < 2.0.0
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<3.0.0");
    struct cpm::vis l2 = cpm::str2vis(">4.0.0");
    struct cpm::vis r1 = cpm::str2vis(">1.0.0");
    struct cpm::vis r2 = cpm::str2vis("<2.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    ASSERT_EQ(ret.size(), (uint)2);
    struct cpm::vis l1_ans = cpm::str2vis(">1.0.0");
    struct cpm::vis r1_ans = cpm::str2vis("<2.0.0");
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
}
TEST(version_processor, visAND_case11a){
    // lhs: v < 1.0.0, 2.0.0 < v < 3.0.0, 4.0.0 < v
    // rhs:                                       v < 5.0.0, 6.0.0 < v
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<1.0.0");
    struct cpm::vis l2 = cpm::str2vis(">2.0.0");
    struct cpm::vis l3 = cpm::str2vis("<3.0.0");
    struct cpm::vis l4 = cpm::str2vis(">4.0.0");
    struct cpm::vis r1 = cpm::str2vis("<5.0.0");
    struct cpm::vis r2 = cpm::str2vis(">6.0.0");
    vLhs = {l1, l2, l3, l4};
    vRhs = {r1, r2};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<1.0.0");
    struct cpm::vis l2_ans = cpm::str2vis(">2.0.0");
    struct cpm::vis r2_ans = cpm::str2vis("<3.0.0");
    struct cpm::vis l3_ans = cpm::str2vis(">4.0.0");
    struct cpm::vis r3_ans = cpm::str2vis("<5.0.0");
    struct cpm::vis l4_ans = cpm::str2vis(">6.0.0");
    struct cpm::vis r4_ans = cpm::str2vis("<inf");
    ASSERT_EQ(ret.size(), (uint)8);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
    ASSERT_TRUE(ret[2]==l2_ans);
    ASSERT_TRUE(ret[3]==r2_ans);
    ASSERT_TRUE(ret[4]==l3_ans);
    ASSERT_TRUE(ret[5]==r3_ans);
    ASSERT_TRUE(ret[6]==l4_ans);
    ASSERT_TRUE(ret[7]==r4_ans);
}
TEST(version_processor, visAND_case11b){
    // lhs:                                       v < 5.0.0, 6.0.0 < v
    // rhs: v < 1.0.0, 2.0.0 < v < 3.0.0, 4.0.0 < v
    
    std::vector<struct cpm::vis> vLhs;
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis l1 = cpm::str2vis("<5.0.0");
    struct cpm::vis l2 = cpm::str2vis(">6.0.0");
    struct cpm::vis r1 = cpm::str2vis("<1.0.0");
    struct cpm::vis r2 = cpm::str2vis(">2.0.0");
    struct cpm::vis r3 = cpm::str2vis("<3.0.0");
    struct cpm::vis r4 = cpm::str2vis(">4.0.0");
    vLhs = {l1, l2};
    vRhs = {r1, r2, r3, r4};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
//    cpm::print(ret);
    
    struct cpm::vis l1_ans = cpm::str2vis(">-inf");
    struct cpm::vis r1_ans = cpm::str2vis("<1.0.0");
    struct cpm::vis l2_ans = cpm::str2vis(">2.0.0");
    struct cpm::vis r2_ans = cpm::str2vis("<3.0.0");
    struct cpm::vis l3_ans = cpm::str2vis(">4.0.0");
    struct cpm::vis r3_ans = cpm::str2vis("<5.0.0");
    struct cpm::vis l4_ans = cpm::str2vis(">6.0.0");
    struct cpm::vis r4_ans = cpm::str2vis("<inf");
    ASSERT_EQ(ret.size(), (uint)8);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
    ASSERT_TRUE(ret[2]==l2_ans);
    ASSERT_TRUE(ret[3]==r2_ans);
    ASSERT_TRUE(ret[4]==l3_ans);
    ASSERT_TRUE(ret[5]==r3_ans);
    ASSERT_TRUE(ret[6]==l4_ans);
    ASSERT_TRUE(ret[7]==r4_ans);
}

TEST(version_processor, visAND_composite_case_01a){
    // lhs:   0.1.0 <=  ver  <= 1.0.0,  2.0.0 <=  ver  <= 3.0.0
    // rhs: ver  <= 0.4.0, 0.6.0 <=  ver  <= 2.4.0, 2.6.0 <= ver
    
    std::vector<struct cpm::vis> vLhs;
    struct cpm::vis l1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis l2 = cpm::str2vis("<=1.0.0");
    struct cpm::vis l3 = cpm::str2vis(">=2.0.0");
    struct cpm::vis l4 = cpm::str2vis("<=3.0.0");
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis r1 = cpm::str2vis("<=0.4.0");
    struct cpm::vis r2 = cpm::str2vis(">=0.6.0");
    struct cpm::vis r3 = cpm::str2vis("<=2.4.0");
    struct cpm::vis r4 = cpm::str2vis(">=2.6.0");
    vLhs = {l1, l2, l3, l4};
    vRhs = {r1, r2, r3, r4};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">=0.1.0");
    struct cpm::vis r1_ans = cpm::str2vis("<=0.4.0");
    struct cpm::vis l2_ans = cpm::str2vis(">=0.6.0");
    struct cpm::vis r2_ans = cpm::str2vis("<=1.0.0");
    struct cpm::vis l3_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r3_ans = cpm::str2vis("<=2.4.0");
    struct cpm::vis l4_ans = cpm::str2vis(">=2.6.0");
    struct cpm::vis r4_ans = cpm::str2vis("<=3.0.0");
    ASSERT_EQ(ret.size(), (uint)8);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
    ASSERT_TRUE(ret[2]==l2_ans);
    ASSERT_TRUE(ret[3]==r2_ans);
    ASSERT_TRUE(ret[4]==l3_ans);
    ASSERT_TRUE(ret[5]==r3_ans);
    ASSERT_TRUE(ret[6]==l4_ans);
    ASSERT_TRUE(ret[7]==r4_ans);
}
TEST(version_processor, visAND_composite_case_01b){
    // lhs: ver  <= 0.4.0, 0.6.0 <=  ver  <= 2.4.0, 2.6.0 <= ver
    // rhs:   0.1.0 <=  ver  <= 1.0.0,  2.0.0 <=  ver  <= 3.0.0
    
    std::vector<struct cpm::vis> vLhs;
    struct cpm::vis l1 = cpm::str2vis("<=0.4.0");
    struct cpm::vis l2 = cpm::str2vis(">=0.6.0");
    struct cpm::vis l3 = cpm::str2vis("<=2.4.0");
    struct cpm::vis l4 = cpm::str2vis(">=2.6.0");
    std::vector<struct cpm::vis> vRhs;
    struct cpm::vis r1 = cpm::str2vis(">=0.1.0");
    struct cpm::vis r2 = cpm::str2vis("<=1.0.0");
    struct cpm::vis r3 = cpm::str2vis(">=2.0.0");
    struct cpm::vis r4 = cpm::str2vis("<=3.0.0");
    vLhs = {l1, l2, l3, l4};
    vRhs = {r1, r2, r3, r4};
    
    std::vector<struct cpm::vis> ret = cpm::visAND(vLhs, vRhs);
    
    struct cpm::vis l1_ans = cpm::str2vis(">=0.1.0");
    struct cpm::vis r1_ans = cpm::str2vis("<=0.4.0");
    struct cpm::vis l2_ans = cpm::str2vis(">=0.6.0");
    struct cpm::vis r2_ans = cpm::str2vis("<=1.0.0");
    struct cpm::vis l3_ans = cpm::str2vis(">=2.0.0");
    struct cpm::vis r3_ans = cpm::str2vis("<=2.4.0");
    struct cpm::vis l4_ans = cpm::str2vis(">=2.6.0");
    struct cpm::vis r4_ans = cpm::str2vis("<=3.0.0");
    ASSERT_EQ(ret.size(), (uint)8);
    ASSERT_TRUE(ret[0]==l1_ans);
    ASSERT_TRUE(ret[1]==r1_ans);
    ASSERT_TRUE(ret[2]==l2_ans);
    ASSERT_TRUE(ret[3]==r2_ans);
    ASSERT_TRUE(ret[4]==l3_ans);
    ASSERT_TRUE(ret[5]==r3_ans);
    ASSERT_TRUE(ret[6]==l4_ans);
    ASSERT_TRUE(ret[7]==r4_ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

#undef CPM_NE
#undef CPM_GT
#undef CPM_GE
#undef CPM_EQ
#undef CPM_LE
#undef CPM_LT
#undef CPM_NULL
