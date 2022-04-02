#pragma once
#include "../src/version_processor.hpp"


//sstd, 0.0.0<=ver<=2.0.1;

//sstd, ver<=2.0.1;
//sstd, 2.0.1>=ver>-inf;

//sstd, 2.0.1;
//sstd, ver==2.0.1;
//sstd, 2.0.1==ver;

//sstd, 2.0.1<=ver;
//sstd, 2.0.1<=ver<inf;
//sstd,     ver>=2.0.1;
//sstd, inf>ver>=2.0.1;


TEST(version_processor, v01){
    ASSERT_EQ(1, 1);
}
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
