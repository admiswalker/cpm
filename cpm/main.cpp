#include <vector>
#include <string>

struct pkg{
    std::string name; // for dbg
    uint ver100=0;
    uint ver010=0;
    uint ver001=0;
    bool latest=false;
    std::vector<struct pkg> v_depend;
};
namespace sstd{
    void print(const struct pkg& rhs);
    void print_for_vT(const struct pkg& rhs);
    void for_printn(const struct pkg& rhs);
}
void sstd::print(const struct pkg& rhs){
    printf("name: %s v%d.%d.%d latest: %c v_depend: [ ", rhs.name.c_str(), rhs.ver100, rhs.ver010, rhs.ver001, (rhs.latest ? 'T':'F'));
    for(uint i=0; i<rhs.v_depend.size(); ++i){
        sstd::print_for_vT(rhs.v_depend[i]);
    }
    printf("]\n");
}
void sstd::print_for_vT(const struct pkg& rhs){
    printf("[name: %s v%d.%d.%d latest: %c v_depend: [", rhs.name.c_str(), rhs.ver100, rhs.ver010, rhs.ver001, (rhs.latest ? 'T':'F'));
    for(uint i=0; i<rhs.v_depend.size(); ++i){
        sstd::print_for_vT((const struct pkg&)rhs.v_depend[i]);
    }
    printf("]]");
}
void sstd::for_printn(const struct pkg& rhs){ printf(" = "); sstd::print(rhs); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

#include <sstd/sstd.hpp> // include after "sstd::print_for_vT"
#include <unordered_map>


sstd::vvec<std::string> read_packages_txt(const std::string& path_packages){
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

bool read_packages_dir(std::unordered_map<std::string,std::vector<struct pkg>>& table_vPkg_ret){
    table_vPkg_ret.clear();
    std::vector<std::string> v_package = sstd::glob("./cpm/packages/*", "d");

    for(uint p=0; p<v_package.size(); ++p){
        std::vector<std::string> v_package_inst, v_package_deps;
        
        v_package_inst = sstd::glob(v_package[p]+"/install_v*.sh", "f");
        v_package_deps = sstd::glob(v_package[p]+"/install_v*_dependents.txt", "f");
        uint len = v_package_inst.size(); if(len != v_package_deps.size()){ sstd::pdbg("ERROR: get_packagesList(): number of install_v*.sh and install_v*_dependents.txt is not same.\n"); return false; }
        for(uint i=0; i<len; ++i){
            std::string ret_ver;   sstd::strmatch_getWC(sstd::getFileName(v_package_inst[i].c_str()), "install_v*.sh", ret_ver);
            std::string ret_ver_d; sstd::strmatch_getWC(sstd::getFileName(v_package_deps[i].c_str()), "install_v*_dependents.txt", ret_ver_d);
            if(ret_ver != ret_ver_d){ sstd::pdbg("ERROR: get_packagesList(): version of install_v*.sh and install_v*_dependents.txt is not same.\n"); return false; }
            
            std::vector<std::string> ver = sstd::split(ret_ver, '.');
            struct pkg r;
            r.name   = sstd::getFileName( v_package[p].c_str() );
            r.ver100 = std::stoi(ver[0]);
            r.ver010 = std::stoi(ver[1]);
            r.ver001 = std::stoi(ver[2]);
//          r.v_depend = read_dependents_txt();
            
            table_vPkg_ret[ r.name ] <<= r;
        }
        
        v_package_inst = sstd::glob(v_package[p]+"/install_latest.sh", "f");
        v_package_deps = sstd::glob(v_package[p]+"/install_latest_dependents.txt", "f");
        len = v_package_inst.size(); if(len != v_package_deps.size()){ sstd::pdbg("ERROR: get_packagesList(): number of install_latest.sh and install_latest_dependents.txt is not same.\n"); return false; }
        struct pkg r;
        r.name   = sstd::getFileName( v_package[p].c_str() );
        r.latest = true;
//      r.v_depend = read_dependents_txt();
        
        table_vPkg_ret[ r.name ] <<= r;
    }
    return true;
}
std::vector<struct pkg> solve_depends___dummy(const sstd::vvec<std::string>& vv_packages, const std::unordered_map<std::string, std::vector<struct pkg>>& table_vPkg){
    std::vector<struct pkg> v_inst_pkg;
    
    for(uint i=0; i<vv_packages.size(); ++i){
        sstd::printn(vv_packages[i]);
        
//        table_vPkg = vv_packages[i];

//        v_inst_pkg <<= ;
    }
    
    
    return v_inst_pkg;
}
void install_libs(const std::string& dir_install, const std::string& dir_tmp, const std::vector<struct pkg>& v_inst_pkg){
    return ;
}

int main(int argc, char *argv[]){
    std::string dir_install   = "env_cpm";          // -i env_cpm
    std::string path_packages = "packages_cpm.txt"; // -p packages_cpm.txt
    std::string dir_tmp       = "tmp_cpm";          // -t tmp_cpm
    
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
    
    sstd::vvec<std::string> vv_packages = read_packages_txt( path_packages );
//  sstd::printn( vv_packages );
    
    std::unordered_map<std::string, std::vector<struct pkg>> table_vPkg; if(!read_packages_dir(table_vPkg)){ return -1; }
    for(auto itr=table_vPkg.begin(); itr!=table_vPkg.end(); ++itr) {
        sstd::printn(itr->first);
        sstd::printn(itr->second);
        printf("\n");
    }
    
    // Solveing the dependencies
    //   Not implimented yet.
//  std::vector<struct pkg> v_inst_pkg = solve_depends(vv_packages, v_pkg);
    std::vector<struct pkg> v_inst_pkg = solve_depends___dummy(vv_packages, table_vPkg);
    
    install_libs(dir_install, dir_tmp, v_inst_pkg);
    
    return 0;
}

