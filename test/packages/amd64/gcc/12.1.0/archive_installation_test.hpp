#pragma once
#include "../../../../test_tools/archive_installation.hpp"

#include <sstd/sstd.hpp>


#define INIT()                                                          \
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
    std::string ret;

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(archive_installation_test, gcc_12_1_0){
    INIT();
    
    std::string pkg_script = R"(
    ARCHITECTURE, amd64;
    BUILD_ENV, CPM_ENV;
    INSTALL_MODE, archive;
    gcc, ==12.1.0;
    )";
    sstd::write(pkg_script_path, pkg_script);
    
    std::string cmd_inst;
    cmd_inst += "cpm/exe";
    cmd_inst += " -b "+base_dir;
    cmd_inst += " -c "+acv_dir;
    cmd_inst += " -p "+pkg_script_path;
    sstd::printn(cmd_inst);
    ret = sstd::system_stdout(cmd_inst);
    sstd::printn(ret);

    std::string test_script;
    test_script += "#!/bin/bash\n";
    test_script += "source "+base_dir+"/local/set_env.sh;\n";
    test_script += "gcc --version;\n";
    sstd::write(test_script_path, test_script);

    std::string cmd_r = "bash "+test_script_path+";\n";
    sstd::printn(cmd_r);
    
    ret = sstd::system_stdout(cmd_r);
    sstd::printn(ret);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

