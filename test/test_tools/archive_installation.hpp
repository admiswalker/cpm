#pragma once
#include <string>


#define CPM_TEST_INIT()                                                 \
    const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info(); \
    std::string test_case_name = test_info->test_case_name();           \
    std::string test_name = test_info->name();                          \
    std::string tmp_dir = "./tmp/test/"+test_case_name+'_'+test_name;   \
    sstd::mkdir(tmp_dir);                                               \
                                                                        \
    std::string call_path = cpm_test::get_call_path();                  \
    std::string acv_dir = "tmp/test/cache";                             \
    std::string base_dir = tmp_dir;                                     \
    std::string pkg_script_path = tmp_dir+"/packages_cpm.txt";          \
    std::string test_script_path = tmp_dir+"/test.sh";                  \
                                                                        \
    std::string cmd_inst;                                               \
    cmd_inst += "cpm/exe";                                              \
    cmd_inst += " -b "+base_dir;                                        \
    cmd_inst += " -c "+acv_dir;                                         \
    cmd_inst += " -p "+pkg_script_path;


namespace cpm_test{
    
    std::string get_call_path();
    
}

