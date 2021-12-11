#include <sstd/sstd.hpp>


sstd::vvec<std::string> read_packagesList(const std::string& path_packages){
    sstd::printn(path_packages);
    std::vector<std::string> v_line = sstd::getCommandList( path_packages );
    uint len=v_line.size();
    
    sstd::vvec<std::string> vv_ret(len);
    for(uint i=0; i<len; ++i){
        std::vector<std::string> v_cmd = sstd::splitByComma( v_line[i] );
        for(uint n=0; n<v_cmd.size(); ++n){
            vv_ret[i] <<= v_cmd[n];
        }
    }
    return vv_ret;
}

int main(int argc, char *argv[]){
    std::string dir_tmp       = "tmp_cpm";          // -t tmp_cpm
    std::string dir_install   = "env_cpm";          // -i env_cpm
    std::string path_packages = "packages_cpm.txt"; // -p packages_cpm.txt
    
    char c = ' ';
    for(int i=1; i<argc; ++i){
        std::string s = argv[i]; if(s.size() < 2){ sstd::pdbg("ERROR: Unexpectec input: %s.\n", s.c_str()); return -1; }
        if(s[0] == '-'){ c=s[1]; continue; }
        
        switch(c){
        case 'i': { dir_install=s; break; }
        case 'p': { path_packages=s; break; }
        case 't': { dir_tmp=s; break; }
        default: { break; }
        }
    }
    sstd::print(dir_install);
    sstd::print(dir_tmp);
    sstd::print(path_packages);

    sstd::vvec<std::string> vv_packages = read_packagesList( path_packages );
    sstd::printn( vv_packages );
    
    /*
    std::string tmpDir   = argv[1];
    std::string path_in  = argv[2];
    std::string path_out = argv[3];
    */
    
    
    return 0;
}
