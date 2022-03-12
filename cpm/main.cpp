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
std::vector<struct pkg> vPkgList2vPkg(bool& ret, const sstd::vvec<std::string>& vPkgList){
    ret=true;
    std::vector<struct pkg> v_pkg_ret;
    
    for(uint i=0; i<vPkgList.size(); ++i){
        if(vPkgList[i].size() != 2){ sstd::pdbg("ERROR: vPkgList[i].size() != 2.\n"); ret=false; return v_pkg_ret; }
        
        struct pkg r; if(!str2struct_pkg(r, vPkgList[i][0], vPkgList[i][1])){ ret=false; return v_pkg_ret; }
        v_pkg_ret <<= r;
    }
    return v_pkg_ret;
}
bool read_packages_dir(std::unordered_map<std::string,std::vector<struct pkg>>& table_vPkg_ret, const std::string& packages_dir){
    table_vPkg_ret.clear();
    std::vector<std::string> v_package = sstd::glob(packages_dir+"/*", "d");

    for(uint p=0; p<v_package.size(); ++p){
        std::vector<std::string> v_ver_path; //, v_package_inst, v_package_deps;

        v_ver_path = sstd::glob(v_package[p]+"/*", "d");
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
std::vector<struct pkg> solve_depends___dummy(bool& ret,
                           const std::vector<struct pkg>& v_pkg_requested,
                           const std::unordered_map<std::string, std::vector<struct pkg>>& table_vPkg){
    ret=true;
    std::vector<struct pkg> v_pkg_ret;
    
    for(uint ri=0; ri<v_pkg_requested.size(); ++ri){
        std::vector<struct pkg> v_pkg_exist = table_vPkg.at( v_pkg_requested[ri].name );
        
        struct pkg r;
        for(uint ei=0;; ++ei){
            if(ei == v_pkg_exist.size()){ sstd::pdbg("ERROR: Required package is not exist in `cpm/packages`.\n"); ret=false; return v_pkg_ret; }
            if(! isSameVer(v_pkg_exist[ei], v_pkg_requested[ri]) ){ continue; }
            
            r = v_pkg_exist[ei];
            break;
        }
        v_pkg_ret <<= r;
    }
    
    return v_pkg_ret;
}
std::string return_set_env_cmd(){
    return sstd::read("./cpm/set_env.sh");
}
void gen_archive(const std::string& save_name, const std::string& ext, const std::string& path){
    std::string call_path = sstd::system_stdout("pwd"); call_path.pop_back(); // pop_back() delete '\n'.
    std::string path_tmp      = call_path + '/' + path;      // When using Docker, the absolute path is determined at run time.
    std::string save_name_tmp = call_path + '/' + save_name; // When using Docker, the absolute path is determined at run time.
    
    if      (ext=="tar.xz"){ sstd::system(sstd::ssprintf("cd %s; tar -Jcf %s *", path_tmp.c_str(), save_name_tmp.c_str()));
    }else if(ext=="zip"   ){ sstd::system(sstd::ssprintf("cd %s; zip -rq %s *", path_tmp.c_str(), save_name_tmp.c_str()));
    }else                  { sstd::pdbg("Error: Unexpected extension.");
    }
    
    uint64 size = std::stoull(sstd::system_stdout(sstd::ssprintf("ls -al %s | cut -d ' ' -f 5", save_name_tmp.c_str())));
    if(size >= 104857600){
        sstd::system(sstd::ssprintf("split -d -b 100m %s %s-", save_name_tmp.c_str(), save_name_tmp.c_str())); // test by zip to reduce excusion time.
    }
    return;
}
void gen_hashFile(const std::string& archive_dir, const std::string& save_name, const std::string& ext){
    std::string w_str;
    
    std::vector<std::string> vPath = sstd::glob(archive_dir+R"(/*)");
    for(uint i=0; i<vPath.size(); ++i){
        w_str += sstd::system_stdout("cd "+archive_dir+"; sha256sum "+&vPath[i][archive_dir.size()+1]) + '\n';
        w_str.pop_back(); // pop_back() is removing '\n'.
    }
    sstd::write(save_name, w_str);
    return;
}
bool install_libs(const std::string& CACHE_DIR,
                  const std::string& BUILD_DIR,
                  const std::string& INST_PATH,
                  const std::vector<std::string>& v_build_env,
                  const std::string& architecture,
                  const std::string& packages_dir,
                  const std::vector<struct pkg>& v_pkg,
                  const bool TF_genArchive, const std::string& archive_dir){
    // mkdir in the install.sh
    // 
    // sstd::mkdir(CACHE_DIR);
    // sstd::mkdir(BUILD_DIR);
    // sstd::mkdir(INST_PATH);
    sstd::mkdir(INST_PATH);
    std::string INST_PATH_acv = INST_PATH + "_archive";
    
    //const std::string ext = "tar.xz";
    const std::string ext = "zip"; // test by zip to reduce excusion time.
    
    for(uint i=0; i<v_pkg.size(); ++i){
        struct pkg p = v_pkg[i];
        
        std::string archive_pkg_dir;
        std::string archive_path;
        if(TF_genArchive){
            sstd::mkdir(INST_PATH_acv);
            
            archive_pkg_dir = archive_dir + '/' + architecture + '-' + p.name + '-' + p.ver;
            archive_path = archive_pkg_dir + '/' + architecture + '-' + p.name + '-' + p.ver;
            if(sstd::fileExist(archive_path+'.'+ext)){ continue; }
        }

        std::string pkg_shell_dir = packages_dir + '/' + p.name + '/' + p.ver;
        bool TF_useArchive = sstd::isFile(pkg_shell_dir + "/download_archive.sh");
        
        std::string cache_pkg_dir = CACHE_DIR + '/' + (TF_useArchive ? "archive":"src") + '/' + architecture + '-' + p.name + '-' + p.ver;
        std::string build_pkg_dir = BUILD_DIR + '/' + architecture + '-' + p.name + '-' + p.ver;
        sstd::mkdir(cache_pkg_dir);
        if(!TF_useArchive){
            sstd::mkdir(build_pkg_dir);
        }
        
        std::string cmd;
        std::string runner = "sh";
        std::string options;
        if(v_build_env.size()==0){ sstd::pdbg("ERROR: BUILD_ENV is not set.\n"); }
        if      (v_build_env[0] == "CPM_ENV"   ){ cmd += return_set_env_cmd();
        }else if(v_build_env[0] == "DOCKER_ENV"){ sstd::system(v_build_env[1]+"/docker_build.sh"); // build docker image
                                                  runner = "sh " + v_build_env[1] + "/docker_run.sh";
                                                  options = "--env CACHE_DIR --env BUILD_DIR --env INST_PATH";
        }else if(v_build_env[0] == "SYSTEM_ENV"){ // do nothing
        }else{
            sstd::pdbg("ERROR: BUILD_ENV has invalid value: %s.\n", v_build_env[0].c_str());
            return false;
        }
        cmd += "export CACHE_DIR=" + cache_pkg_dir + '\n';
        cmd += "export BUILD_DIR=" + build_pkg_dir + '\n';
        cmd += "export INST_PATH=" + (TF_genArchive ? INST_PATH_acv:INST_PATH) + '\n';
        cmd += "\n";
        if(TF_useArchive){
            cmd += runner + ' ' + pkg_shell_dir + "/download_archive.sh" + ' ' + options + '\n';
            cmd += runner + ' ' + pkg_shell_dir + "/install_archive.sh" + ' ' + options + '\n';
        }else{
            cmd += runner + ' ' + pkg_shell_dir + "/download_src.sh" + ' ' + options + '\n';
            cmd += runner + ' ' + pkg_shell_dir + "/install_src.sh" + ' ' + options + '\n';
        }
        sstd::printn(cmd);
        sstd::system(cmd);
        
        if(TF_genArchive){
            sstd::mkdir(archive_pkg_dir);
            gen_archive(archive_path+'.'+ext, ext, INST_PATH_acv);
            gen_hashFile(archive_pkg_dir, archive_path+"-sha256sum.txt", ext);
            
            sstd::cp(INST_PATH_acv+"/*", INST_PATH, "npu");
//          sstd::mv(INST_PATH_arc+"/*", INST_PATH); // Not implimented yet
            
            sstd::rm(INST_PATH_acv);
        }
    }
    
    return true;
}
sstd::vvec<std::string> read_path_packages(const std::string& path_packages){
    sstd::vec<std::string> vLine = sstd::getCommandList( path_packages );
    sstd::vvec<std::string> vvLine;
    for(uint i=0; i<vLine.size(); ++i){
        vvLine <<= sstd::splitByComma( vLine[i] );
    }
    return vvLine;
}
sstd::vec<sstd::vvec<std::string>> split_pksList_by_scope(const sstd::vvec<std::string>& vvLine, const std::vector<std::string>& splitList){
    std::unordered_map<std::string, char> sTable;
    for(uint i=0; i<splitList.size(); ++i){
        sTable[ splitList[i] ] = 0;
    }
    
    int n=-1;
    sstd::vec<sstd::vvec<std::string>> v_vvLine;
    for(uint i=0; i<vvLine.size(); ++i){
        
        auto itr = sTable.find( vvLine[i][0] );
        if(i==0 || itr!=sTable.end()){
            ++n;
            v_vvLine <<= sstd::vvec<std::string>();
        }
        
        v_vvLine[n] <<= vvLine[i];
    }
    
    return v_vvLine;
}

int main(int argc, char *argv[]){
    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|                                                   |\n");
    printf("|      Welcome to Cpp Package Manager (CPM) !       |\n");
    printf("|                                                   |\n");
    printf("+---------------------------------------------------+\n");
    printf("\n");
    time_m timem; sstd::measureTime_start(timem);
    
    std::string path_packages = "packages_cpm.txt"; // -p packages_cpm.txt
    
//  std::string call_path = sstd::system_stdout("pwd"); call_path.pop_back(); // pop_back() delete '\n'.
//  std::string CACHE_DIR = call_path+"/env_cpm/cache";
//  std::string BUILD_DIR = call_path+"/env_cpm/build"; // -b env_cpm/build
//  std::string INST_PATH = call_path+"/env_cpm/local"; // -i env_cpm/local
//  std::string archive_dir = call_path+"/env_cpm/archive";
//  std::string packages_dir = call_path+"/cpm/packages";

    // Because of when using Docker, the absolute path is determined at run time.
    // Use relative path internally and convert absolute path when immediately before running scripts and commands.
    std::string CACHE_DIR = "env_cpm/cache";
    std::string BUILD_DIR = "env_cpm/build"; // -b env_cpm/build
    std::string INST_PATH = "env_cpm/local"; // -i env_cpm/local
    bool TF_genArchive = false;
    std::string archive_dir  = "env_cpm/archive";
    std::string packages_dir = "cpm/packages";
    
    char c = ' ';
    for(int i=1; i<argc; ++i){
        std::string s = argv[i]; if(s.size() < 2){ sstd::pdbg("ERROR: Unexpectec input: %s.\n", s.c_str()); return -1; }
        if(s[0] == '-'){ c=s[1]; continue; }
        
        switch(c){
        case 'a': { TF_genArchive = (sstd::strcmp(s,"true") ? true:false); break; }
        case 'b': { BUILD_DIR=s; break; }
        case 'i': { INST_PATH=s; break; }
        case 'p': { path_packages=s; break; }
        default: { break; }
        }
    }
    
    std::string architecture;
    std::unordered_map<std::string, std::vector<struct pkg>> table_vPkg;
    sstd::vec<std::string> v_build_env;
    #define cmd_ARCHITECTURE "ARCHITECTURE"
    #define cmd_BUILD_ENV    "BUILD_ENV"
    #define cmd_IMPORT       "IMPORT"
    sstd::vvec<std::string> vvLine = read_path_packages( path_packages );
    sstd::vec<sstd::vvec<std::string>> v_vvLine = split_pksList_by_scope(vvLine, {cmd_ARCHITECTURE, cmd_BUILD_ENV, cmd_IMPORT});
    for(uint n=0; n<v_vvLine.size(); ++n){
        for(uint l=0; l<v_vvLine[n].size(); ++l){
            if(v_vvLine[n][l].size() == 0){ sstd::pdbg("ERROR: v_vvLine[n][i].size() == 0.\n"); return false; }
            sstd::vec<std::string> vCmd = v_vvLine[n][l];
            
            if      (vCmd[0] == cmd_ARCHITECTURE){ architecture = vCmd[1]; if(!read_packages_dir( table_vPkg, packages_dir+'/'+architecture)){ return -1; }
            }else if(vCmd[0] == cmd_BUILD_ENV   ){ v_build_env  = vCmd && sstd::slice(1, sstd::end());
            }else if(vCmd[0] == cmd_IMPORT      ){ /* Not implimented */
            }else{
                sstd::vvec<std::string> vPkgList = v_vvLine[n] && sstd::slice(l, sstd::end());
                
                bool ret=true;
                std::vector<struct pkg> v_pkg_requested = vPkgList2vPkg(ret, vPkgList); if(!ret){ return -1; }
                std::vector<struct pkg> v_inst_pkg      = solve_depends___dummy(ret, v_pkg_requested, table_vPkg); if(!ret){ return -1; }
                install_libs(CACHE_DIR, BUILD_DIR, INST_PATH, v_build_env, architecture, packages_dir+'/'+architecture, v_inst_pkg, TF_genArchive, archive_dir);
            }
        }
    }
    #undef cmd_IMPORT
    #undef cmd_BUILD_ENV
    #undef cmd_ARCHITECTURE
    
    printf("\n");
    sstd::measureTime_stop_print(timem);
    return 0;
}

