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


bool read_packages_txt(std::vector<struct pkg>& v_pkg_ret, const std::string& path_packages){
    std::vector<std::string> v_line = sstd::getCommandList( path_packages );
    uint len=v_line.size();
    
    for(uint i=0; i<len; ++i){
        std::vector<std::string> v_cmd = sstd::splitByComma( v_line[i] ); if(v_cmd.size() != 2){ sstd::pdbg("ERROR: v_cmd.size() != 2.\n"); return false; }
        std::vector<std::string> ver = sstd::split(v_cmd[1], '.'); if(ver.size() != 3){ sstd::pdbg("ERROR: ver.size() != 3.\n"); return false; } if(ver[0].size()==0){ sstd::pdbg("ERROR: ver[0].size()==0.\n"); return false; } if(ver[1].size()==0){ sstd::pdbg("ERROR: ver[1].size()==0.\n"); return false; } if(ver[2].size()==0){ sstd::pdbg("ERROR: ver[2].size()==0.\n"); return false; }
        
        struct pkg r;
        r.name = v_cmd[0];
        r.ver100 = std::stoi(ver[0]);
        r.ver010 = std::stoi(ver[1]);
        r.ver001 = std::stoi(ver[2]);
        
        v_pkg_ret <<= r;
    }
    return true;
}

bool read_packages_dir(std::unordered_map<std::string,std::vector<struct pkg>>& table_vPkg_ret){
    table_vPkg_ret.clear();
    std::vector<std::string> v_package = sstd::glob("./cpm/packages/*", "d");

    for(uint p=0; p<v_package.size(); ++p){
        std::vector<std::string> v_package_inst, v_package_deps;
        
        v_package_inst = sstd::glob(v_package[p]+"/install_v*.sh", "f");
        v_package_deps = sstd::glob(v_package[p]+"/install_v*_dependents.txt", "f");
        uint len = v_package_inst.size(); if(len != v_package_deps.size()){ sstd::pdbg("ERROR: number of install_v*.sh and install_v*_dependents.txt is not same.\n"); return false; }
        for(uint i=0; i<len; ++i){
            std::string ret_ver;   sstd::strmatch_getWC(sstd::getFileName(v_package_inst[i].c_str()), "install_v*.sh", ret_ver);
            std::string ret_ver_d; sstd::strmatch_getWC(sstd::getFileName(v_package_deps[i].c_str()), "install_v*_dependents.txt", ret_ver_d);
            if(ret_ver != ret_ver_d){ sstd::pdbg("ERROR: version of install_v*.sh and install_v*_dependents.txt is not same.\n"); return false; }
            
            std::vector<std::string> ver = sstd::split(ret_ver, '.'); if(ver.size() != 3){ sstd::pdbg("ERROR: ver.size() != 3.\n"); return false; }
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
        len = v_package_inst.size(); if(len != v_package_deps.size()){ sstd::pdbg("ERROR: number of install_latest.sh and install_latest_dependents.txt is not same.\n"); return false; }
        struct pkg r;
        r.name   = sstd::getFileName( v_package[p].c_str() );
        r.latest = true;
//      r.v_depend = read_dependents_txt();
        
        table_vPkg_ret[ r.name ] <<= r;
    }
    return true;
}
bool solve_depends___dummy(std::vector<struct pkg>& v_pkg_ret, const std::vector<struct pkg>& v_pkg_requested, const std::unordered_map<std::string, std::vector<struct pkg>>& table_vPkg){
    for(uint ri=0; ri<v_pkg_requested.size(); ++ri){
        std::vector<struct pkg> v_pkg_exist = table_vPkg.at( v_pkg_requested[ri].name );
        
        struct pkg r;
        for(uint ei=0;; ++ei){
            if(ei == v_pkg_exist.size()){ sstd::pdbg("ERROR: No package meets request.\n"); return false; }
            if( v_pkg_exist[ei].ver100==v_pkg_requested[ri].ver100 &&
                v_pkg_exist[ei].ver010==v_pkg_requested[ri].ver010 &&
                v_pkg_exist[ei].ver001==v_pkg_requested[ri].ver001 ){
                
                r = v_pkg_exist[ei];
                break;
            }
        }
        v_pkg_ret <<= r;
    }
    
    return true;
}
void install_libs(const std::string& dir_install, const std::string& dir_tmp, const std::vector<struct pkg>& v_inst_pkg){
    sstd::mkdir(dir_tmp);
    sstd::mkdir(dir_install);
    
    for(uint i=0; i<v_inst_pkg.size(); ++i){
        struct pkg p = v_inst_pkg[i];
        sstd::mkdir(sstd::ssprintf("%s/%s", dir_tmp.c_str(), p.name.c_str()));
        std::string     inst = sstd::ssprintf("install_v%d.%d.%d.sh", p.ver100, p.ver010, p.ver001);
        std::string dir_inst = sstd::ssprintf("cpm/packages/%s", p.name.c_str());
        std::string dir_tmp_pkg = sstd::ssprintf("%s/%s", dir_tmp.c_str(), p.name.c_str());
        
        sstd::system(sstd::ssprintf("cp %s/%s %s", dir_inst.c_str(), inst.c_str(), dir_tmp_pkg.c_str()));
        sstd::system(sstd::ssprintf("cd %s; sh ./%s", dir_tmp_pkg.c_str(), inst.c_str()));
    }
    
    return;
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

    std::vector<struct pkg> v_pkg_requested; if(!read_packages_txt( v_pkg_requested, path_packages )){ return -1; }
//  sstd::printn( v_pkg );
    
    std::unordered_map<std::string, std::vector<struct pkg>> table_vPkg; if(!read_packages_dir( table_vPkg )){ return -1; }
    for(auto itr=table_vPkg.begin(); itr!=table_vPkg.end(); ++itr) {
        sstd::printn(itr->first);
        sstd::printn(itr->second);
        printf("\n");
    }
    
    // Solveing the dependencies
    //   Not implimented yet.
//  std::vector<struct pkg> v_inst_pkg = solve_depends(vv_packages, v_pkg);
    std::vector<struct pkg> v_inst_pkg; if(!solve_depends___dummy( v_inst_pkg, v_pkg_requested, table_vPkg )){ return -1; }
    sstd::printn(v_inst_pkg);
    
    install_libs(dir_install, dir_tmp, v_inst_pkg);
    
    return 0;
}

