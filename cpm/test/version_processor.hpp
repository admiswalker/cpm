#pragma once
#include "../src/version_processor.hpp"


//sstd, 0.0.0<=ver<=2.0.1;

//sstd, ver<=2.0.1;
//sstd, 2.0.1>=ver>-inf;

//sstd, 2.0.1;
//sstd, ver==2.0.1;
//sstd, 2.0.1==ver;
//sstd, ver==2.0.*;
//sstd, ver==2.*.*;

//sstd, 2.0.1<=ver;
//sstd, 2.0.1<=ver<inf;
//sstd,     ver>=2.0.1;
//sstd, inf>ver>=2.0.1;


TEST(version_processor, v01){
    ASSERT_EQ(1, 1);
}
/*
TEST(version_processor, case01){
    std::string v = "0.0.0<=ver<=2.0.1";
    
    struct cpm::verRange vr = cpm::str2verStruct( v );
    
    ASSERT_EQ(1, 1);
}
TEST(version_processor, case02){
    std::string v = "<=0.0.0<=ver<=2.0.1";
    
    struct cpm::verRange vr = cpm::str2verStruct( v );
    
    ASSERT_EQ(1, 1);
}
TEST(version_processor, case03){
    std::string v = "0.0.0<=ver<=2.0.1<=";
    
    struct cpm::verRange vr = cpm::str2verStruct( v );
    
    ASSERT_EQ(1, 1);
}
*/
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
    v.is  = 6;
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
