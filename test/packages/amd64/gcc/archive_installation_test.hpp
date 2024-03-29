#pragma once
#include "../../../test_tools/archive_installation.hpp"

#include <sstd/sstd.hpp>


//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(archive_installation_test, gcc_12_1_0){
    CPM_TEST_INIT();
    
    std::string pkg_script;
    pkg_script += "ARCHITECTURE, amd64;\n";
    pkg_script += "BUILD_ENV, CPM_ENV;\n";
    pkg_script += "INSTALL_MODE, archive;\n";
    pkg_script += "gcc, ==12.1.0;\n";
    sstd::write(pkg_script_path, pkg_script);
    
    std::string ret = sstd::system_stdout(cmd_inst); // installation

    std::string test_script;
    test_script += "#!/bin/bash\n";
    test_script += "source "+base_dir+"/local/set_env.sh;\n";
    test_script += "gcc --version;\n";
    sstd::write(test_script_path, test_script); // generate test script

    std::string cmd_test = "bash "+test_script_path+";\n";
    std::string test_ret = sstd::system_stdout(cmd_test); // run test script
    
    std::string test_ret_ans;
    test_ret_ans += "gcc (GCC) 12.1.0\n";
    test_ret_ans += "Copyright (C) 2022 Free Software Foundation, Inc.\n";
    test_ret_ans += "This is free software; see the source for copying conditions.  There is NO\n";
    test_ret_ans += "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
    test_ret_ans += "\n";
    
    ASSERT_STREQ(test_ret.c_str(), test_ret_ans.c_str()); // test
}

TEST(archive_installation_test, gcc_11_2_0){
    CPM_TEST_INIT();
    
    std::string pkg_script;
    pkg_script += "ARCHITECTURE, amd64;\n";
    pkg_script += "BUILD_ENV, CPM_ENV;\n";
    pkg_script += "INSTALL_MODE, archive;\n";
    pkg_script += "gcc, ==11.2.0;\n";
    sstd::write(pkg_script_path, pkg_script);
    
    std::string ret = sstd::system_stdout(cmd_inst); // installation

    std::string test_script;
    test_script += "#!/bin/bash\n";
    test_script += "source "+base_dir+"/local/set_env.sh;\n";
    test_script += "gcc --version;\n";
    sstd::write(test_script_path, test_script); // generate test script

    std::string cmd_test = "bash "+test_script_path+";\n";
    std::string test_ret = sstd::system_stdout(cmd_test); // run test script
    
    std::string test_ret_ans;
    test_ret_ans += "gcc (GCC) 11.2.0\n";
    test_ret_ans += "Copyright (C) 2021 Free Software Foundation, Inc.\n";
    test_ret_ans += "This is free software; see the source for copying conditions.  There is NO\n";
    test_ret_ans += "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
    test_ret_ans += "\n";
    
    ASSERT_STREQ(test_ret.c_str(), test_ret_ans.c_str()); // test
}

TEST(archive_installation_test, gcc_10_3_0){
    CPM_TEST_INIT();
    
    std::string pkg_script;
    pkg_script += "ARCHITECTURE, amd64;\n";
    pkg_script += "BUILD_ENV, CPM_ENV;\n";
    pkg_script += "INSTALL_MODE, archive;\n";
    pkg_script += "gcc, ==10.3.0;\n";
    sstd::write(pkg_script_path, pkg_script);
    
    std::string ret = sstd::system_stdout(cmd_inst); // installation

    std::string test_script;
    test_script += "#!/bin/bash\n";
    test_script += "source "+base_dir+"/local/set_env.sh;\n";
    test_script += "gcc --version;\n";
    sstd::write(test_script_path, test_script); // generate test script

    std::string cmd_test = "bash "+test_script_path+";\n";
    std::string test_ret = sstd::system_stdout(cmd_test); // run test script
    
    std::string test_ret_ans;
    test_ret_ans += "gcc (GCC) 10.3.0\n";
    test_ret_ans += "Copyright (C) 2020 Free Software Foundation, Inc.\n";
    test_ret_ans += "This is free software; see the source for copying conditions.  There is NO\n";
    test_ret_ans += "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
    test_ret_ans += "\n";
    
    ASSERT_STREQ(test_ret.c_str(), test_ret_ans.c_str()); // test
}

TEST(archive_installation_test, gcc_9_4_0){
    CPM_TEST_INIT();
    
    std::string pkg_script;
    pkg_script += "ARCHITECTURE, amd64;\n";
    pkg_script += "BUILD_ENV, CPM_ENV;\n";
    pkg_script += "INSTALL_MODE, archive;\n";
    pkg_script += "gcc, ==9.4.0;\n";
    sstd::write(pkg_script_path, pkg_script);
    
    std::string ret = sstd::system_stdout(cmd_inst); // installation

    std::string test_script;
    test_script += "#!/bin/bash\n";
    test_script += "source "+base_dir+"/local/set_env.sh;\n";
    test_script += "gcc --version;\n";
    sstd::write(test_script_path, test_script); // generate test script

    std::string cmd_test = "bash "+test_script_path+";\n";
    std::string test_ret = sstd::system_stdout(cmd_test); // run test script
    
    std::string test_ret_ans;
    test_ret_ans += "gcc (GCC) 9.4.0\n";
    test_ret_ans += "Copyright (C) 2019 Free Software Foundation, Inc.\n";
    test_ret_ans += "This is free software; see the source for copying conditions.  There is NO\n";
    test_ret_ans += "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
    test_ret_ans += "\n";
    
    ASSERT_STREQ(test_ret.c_str(), test_ret_ans.c_str()); // test
}

TEST(archive_installation_test, gcc_8_4_0){
    CPM_TEST_INIT();
    
    std::string pkg_script;
    pkg_script += "ARCHITECTURE, amd64;\n";
    pkg_script += "BUILD_ENV, CPM_ENV;\n";
    pkg_script += "INSTALL_MODE, archive;\n";
    pkg_script += "gcc, ==8.4.0;\n";
    sstd::write(pkg_script_path, pkg_script);
    
    std::string ret = sstd::system_stdout(cmd_inst); // installation

    std::string test_script;
    test_script += "#!/bin/bash\n";
    test_script += "source "+base_dir+"/local/set_env.sh;\n";
    test_script += "gcc --version;\n";
    sstd::write(test_script_path, test_script); // generate test script

    std::string cmd_test = "bash "+test_script_path+";\n";
    std::string test_ret = sstd::system_stdout(cmd_test); // run test script
    
    std::string test_ret_ans;
    test_ret_ans += "gcc (GCC) 8.4.0\n";
    test_ret_ans += "Copyright (C) 2018 Free Software Foundation, Inc.\n";
    test_ret_ans += "This is free software; see the source for copying conditions.  There is NO\n";
    test_ret_ans += "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
    test_ret_ans += "\n";
    
    ASSERT_STREQ(test_ret.c_str(), test_ret_ans.c_str()); // test
}

TEST(archive_installation_test, gcc_7_5_0){
    CPM_TEST_INIT();
    
    std::string pkg_script;
    pkg_script += "ARCHITECTURE, amd64;\n";
    pkg_script += "BUILD_ENV, CPM_ENV;\n";
    pkg_script += "INSTALL_MODE, archive;\n";
    pkg_script += "gcc, ==7.5.0;\n";
    sstd::write(pkg_script_path, pkg_script);
    
    std::string ret = sstd::system_stdout(cmd_inst); // installation

    std::string test_script;
    test_script += "#!/bin/bash\n";
    test_script += "source "+base_dir+"/local/set_env.sh;\n";
    test_script += "gcc --version;\n";
    sstd::write(test_script_path, test_script); // generate test script

    std::string cmd_test = "bash "+test_script_path+";\n";
    std::string test_ret = sstd::system_stdout(cmd_test); // run test script
    
    std::string test_ret_ans;
    test_ret_ans += "gcc (GCC) 7.5.0\n";
    test_ret_ans += "Copyright (C) 2017 Free Software Foundation, Inc.\n";
    test_ret_ans += "This is free software; see the source for copying conditions.  There is NO\n";
    test_ret_ans += "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
    test_ret_ans += "\n";
    
    ASSERT_STREQ(test_ret.c_str(), test_ret_ans.c_str()); // test
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

