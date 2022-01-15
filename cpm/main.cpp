#include <vector>
#include <string>

struct pkg{
private:
public:
    std::string name; // for dbg
    std::string ver;
    uint ver100=0; // v_major
    uint ver010=0; // v_minor
    uint ver001=0; // v_patch
    std::string verExtra;
    std::vector<struct pkg> v_depend;
    /*
    pkg(){
        ver100=0;
        ver010=0;
        ver001=0;
    }
    pkg(const std::string& name_in, const uint ver100_in, const uint ver010_in, const uint ver001_in){
        name  =name_in;
        ver100=ver100_in;
        ver010=ver010_in;
        ver001=ver001_in;
    }
    ~pkg(){}
    */
};
namespace sstd{
    void print(const struct pkg& rhs);
    void print_for_vT(const struct pkg& rhs);
    void for_printn(const struct pkg& rhs);
}
void sstd::print(const struct pkg& rhs){
    printf("name: %s, verStr: %s, ver: %d.%d.%d, verExtra: %s, v_depend: [ ", rhs.name.c_str(), rhs.ver.c_str(), rhs.ver100, rhs.ver010, rhs.ver001, rhs.verExtra.c_str());
    for(uint i=0; i<rhs.v_depend.size(); ++i){
        sstd::print_for_vT(rhs.v_depend[i]);
    }
    printf("]\n");
}
void sstd::print_for_vT(const struct pkg& rhs){
    printf("[name: %s, verStr: %s, ver: %d.%d.%d, verExtra: %s, v_depend: [", rhs.name.c_str(), rhs.ver.c_str(), rhs.ver100, rhs.ver010, rhs.ver001, rhs.verExtra.c_str());
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


bool isSameVer(const struct pkg& lhs, const struct pkg& rhs){
    return ((lhs.ver100==rhs.ver100) && (lhs.ver010==rhs.ver010) && (lhs.ver001==rhs.ver001) && (lhs.ver==rhs.ver));
}
/*
void split_tag_ver(std::string& tag_ret, std::string& ver_ret, const std::string& ver_in, const char splitter){
    std::vector<std::string> v = sstd::split(ver_in, splitter);
    if(v.size()>=2){
        tag_ret = v[0];
        ver_ret = v[1];
    }else{
        ver_ret = v[0];
    }
}
*/
bool is_ver_num(const std::vector<std::string>& ver){
    return ( ver.size()>=3 && sstd::isNum(ver[0]) && sstd::isNum(ver[1]) && sstd::isNum(ver[2]) );
}
bool str2struct_pkg(struct pkg& r, const std::string& name_in, const std::string& ver_in){
//    std::string tag, ver_sd; split_tag_ver(tag, ver_sd, ver_in, ':'); // "tag:ver" -> "tag", "ver"
    
    std::vector<std::string> ver = sstd::split(ver_in, '.');
    if(ver.size()>=3){
        if(ver[0].size()==0){ sstd::pdbg("ERROR: ver[0].size()==0.\n"); return false; }
        if(ver[1].size()==0){ sstd::pdbg("ERROR: ver[1].size()==0.\n"); return false; }
        if(ver[2].size()==0){ sstd::pdbg("ERROR: ver[2].size()==0.\n"); return false; }
    }
    
    r.name = name_in;
    r.ver  = ver_in;
    if( is_ver_num(ver) ){
        r.ver100 = std::stoi( ver[0] );
        r.ver010 = std::stoi( ver[1] );
        r.ver001 = std::stoi( ver[2] );
    }
    if(ver.size()==4){
        r.verExtra = ver[3];
    }
    
    return true;
}
//bool struct_pkg2str(std::string& s, const struct pkg& ret){
//    return true;
//}

bool read_packages_txt(std::vector<struct pkg>& v_pkg_ret, const std::string& path_packages){
    std::vector<std::string> v_line = sstd::getCommandList( path_packages );
    uint len=v_line.size();
    
    for(uint i=0; i<len; ++i){
        std::vector<std::string> v_cmd = sstd::splitByComma( v_line[i] ); if(v_cmd.size() != 2){ sstd::pdbg("ERROR: v_cmd.size() != 2.\n"); return false; }
        
        struct pkg r; if(!str2struct_pkg(r, v_cmd[0], v_cmd[1])){ return false; }
        v_pkg_ret <<= r;
    }
    return true;
}
bool read_packages_dir(std::unordered_map<std::string,std::vector<struct pkg>>& table_vPkg_ret, const std::string& packages_dir){
    table_vPkg_ret.clear();
    std::vector<std::string> v_package = sstd::glob(packages_dir+"/*", "d");

    for(uint p=0; p<v_package.size(); ++p){
        std::vector<std::string> v_ver_path; //, v_package_inst, v_package_deps;

        v_ver_path = sstd::glob(v_package[p]+"/*", "d");
        sstd::print(v_ver_path);
        if(v_ver_path.size()==0){ sstd::pdbg("ERROR: %s: number of installable package is 0.\n", v_package[p].c_str()); return false; }
        
        for(uint i=0; i<v_ver_path.size(); ++i){
            std::string name    = sstd::getFileName( v_package[p].c_str() );
            std::string ver_str = sstd::getFileName( v_ver_path[i].c_str() );
            
            struct pkg r; if(!str2struct_pkg(r, name, ver_str)){ return false; }
//          r.v_depend = read_dependents_txt();
            
            table_vPkg_ret[ r.name ] <<= r;
        }
    }
    
    return true;
}
bool solve_depends___dummy(std::vector<struct pkg>& v_pkg_ret,
                           const std::vector<struct pkg>& v_pkg_requested,
                           const std::unordered_map<std::string, std::vector<struct pkg>>& table_vPkg){
    sstd::printn(v_pkg_requested);
    
    for(uint ri=0; ri<v_pkg_requested.size(); ++ri){
        std::vector<struct pkg> v_pkg_exist = table_vPkg.at( v_pkg_requested[ri].name );
        
        struct pkg r;
        for(uint ei=0;; ++ei){
            if(ei == v_pkg_exist.size()){ sstd::pdbg("ERROR: Required package is not exist in `cpm/packages`.\n"); return false; }
            if(! isSameVer(v_pkg_exist[ei], v_pkg_requested[ri]) ){ continue; }
            
            r = v_pkg_exist[ei];
            break;
        }
        v_pkg_ret <<= r;
    }
    
    return true;
}
void install_libs(const std::string& CACHE_DIR,
                  const std::string& BUILD_DIR,
                  const std::string& INST_PATH,
                  const std::string& packages_dir, 
                  const std::vector<struct pkg>& v_pkg){
    // mkdir in the install.sh
    // 
    // sstd::mkdir(CACHE_DIR);
    // sstd::mkdir(BUILD_DIR);
    // sstd::mkdir(INST_PATH);
    
    for(uint i=0; i<v_pkg.size(); ++i){
        struct pkg p = v_pkg[i];

        std::string build_pkg_dir = sstd::ssprintf("%s/%s-%s", BUILD_DIR.c_str(), p.name.c_str(), p.ver.c_str());
        sstd::system("mkdir -p "+build_pkg_dir);
        
        std::string cmd;
        cmd += sstd::ssprintf("export CACHE_DIR=%s\n", CACHE_DIR.c_str());
        cmd += sstd::ssprintf("export BUILD_DIR=%s\n", build_pkg_dir.c_str());
        cmd += sstd::ssprintf("export INST_PATH=%s\n", INST_PATH.c_str());
        cmd += "\n";
        cmd += sstd::ssprintf("sh %s/%s/%s/install.sh\n", packages_dir.c_str(), p.name.c_str(), p.ver.c_str());
        
        sstd::system(cmd);
    }
    
    return;
}

int main(int argc, char *argv[]){
    std::string path_packages = "packages_cpm.txt"; // -p packages_cpm.txt
    
    std::string call_path = sstd::system_stdout("pwd"); call_path.pop_back(); // pop_back() delete '\n'.
    std::string CACHE_DIR = call_path+"/env_cpm/cache";
    std::string BUILD_DIR = call_path+"/env_cpm/build"; // -t env_cpm/build
    std::string INST_PATH = call_path+"/env_cpm/local"; // -i env_cpm/local
    
    std::string packages_dir = call_path+"/cpm/packages";
    
    char c = ' ';
    for(int i=1; i<argc; ++i){
        std::string s = argv[i]; if(s.size() < 2){ sstd::pdbg("ERROR: Unexpectec input: %s.\n", s.c_str()); return -1; }
        if(s[0] == '-'){ c=s[1]; continue; }
        
        switch(c){
        case 'i': { INST_PATH=s; break; }
        case 'p': { path_packages=s; break; }
        case 't': { BUILD_DIR=s; break; }
        default: { break; }
        }
    }

    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|                                                   |\n");
    printf("|      Welcome to Cpp Package Manager (CPM) !       |\n");
    printf("|                                                   |\n");
    printf("+---------------------------------------------------+\n");
    printf("\n");
    time_m timem; sstd::measureTime_start(timem);
    
    sstd::printn(path_packages);
    sstd::printn(call_path);
    sstd::printn(CACHE_DIR);
    sstd::printn(BUILD_DIR);
    sstd::printn(INST_PATH);

    std::vector<struct pkg> v_pkg_requested; if(!read_packages_txt( v_pkg_requested, path_packages )){ return -1; }
//    sstd::printn( v_pkg_requested );
    
    std::unordered_map<std::string, std::vector<struct pkg>> table_vPkg; if(!read_packages_dir( table_vPkg, packages_dir )){ return -1; }
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
    
//  return 0;
    install_libs(CACHE_DIR, BUILD_DIR, INST_PATH, packages_dir, v_inst_pkg);
    
    printf("\n");
    sstd::measureTime_stop_print(timem);
    sstd::pauseIfWin32();
    return 0;
}

