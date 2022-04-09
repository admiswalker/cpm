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
#include "src/version_processor.hpp"


#define cmd_ARCHITECTURE "ARCHITECTURE"
#define cmd_IMPORT       "IMPORT"

#define cmd_BUILD_ENV  "BUILD_ENV"
#define cmd_CPM_ENV    "CPM_ENV"
#define cmd_DOCKER_ENV "DOCKER_ENV"
#define cmd_SYSTEM_ENV "SYSTEM_ENV"

#define cmd_INSTALL_MODE         "INSTALL_MODE"
#define cmd_INSTALL_MODE_auto    "auto"
#define cmd_INSTALL_MODE_source  "source"
#define cmd_INSTALL_MODE_archive "archive"


std::string getPath_acvPkgDir      (const std::string& ACV_DIR,   const std::string& architecture, const struct pkg& p){ return ACV_DIR + '/' + architecture + '/' + p.name + '/' + p.ver; }
std::string getPath_acvBaseName    (const std::string& ACV_DIR,   const std::string& architecture, const struct pkg& p){ return getPath_acvPkgDir(ACV_DIR, architecture, p) + '/' + architecture + '-' + p.name + '-' + p.ver; }
std::string getPath_packsPkgDir    (const std::string& PACKS_DIR, const struct pkg& p){ return PACKS_DIR + '/' + p.name + '/' + p.ver; }
std::string getPath_cachePkgDir_acv(const std::string& CACHE_DIR, const std::string& architecture, const struct pkg& p){ return CACHE_DIR + "/archive/" + architecture + '-' + p.name + '-' + p.ver; }
std::string getPath_cachePkgDir_src(const std::string& CACHE_DIR, const std::string& architecture, const struct pkg& p){ return CACHE_DIR + "/src/"     + architecture + '-' + p.name + '-' + p.ver; }
std::string getPath_buildPkgDir    (const std::string& BUILD_DIR, const std::string& architecture, const struct pkg& p){ return BUILD_DIR + '/' + architecture + '-' + p.name + '-' + p.ver; }

std::string getSh_dlAcv  (const std::string& packsPkg_dir){ return packsPkg_dir + "/download_archive.sh"; }
std::string getSh_dlSrc  (const std::string& packsPkg_dir){ return packsPkg_dir + "/download_src.sh";     }
std::string getSh_instAcv(const std::string& packsPkg_dir){ return packsPkg_dir + "/install_archive.sh";  }
std::string getSh_instSrc(const std::string& packsPkg_dir){ return packsPkg_dir + "/install_src.sh";      }
std::string getSh_isInst (const std::string& packsPkg_dir){ return packsPkg_dir + "/is_installed.sh";     }

std::string getTxt_depPkg(const std::string& packsPkg_dir){ return packsPkg_dir + "/packages_cpm.txt";     }


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
//        std::string depPkg_txt = getTxt_depPkg( getPath_packsPkgDir(PACKS_DIR, p) );
        v_pkg_ret <<= r;
    }
    return v_pkg_ret;
}
bool read_packages_dir(std::unordered_map<std::string,std::vector<struct pkg>>& table_vPkg_ret, const std::string& PACKS_DIR){
    table_vPkg_ret.clear();
    std::vector<std::string> v_package = sstd::glob(PACKS_DIR+"/*", "d");

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
std::vector<struct pkg> solve_dependencies(bool& ret,
                                           const std::vector<struct pkg>& v_pkg_requested,
                                           const std::unordered_map<std::string, std::vector<struct pkg>>& table_vPkg){
    ret=true;
    std::vector<struct pkg> v_pkg_ret;
    
    for(uint ri=0; ri<v_pkg_requested.size(); ++ri){
        auto itr = table_vPkg.find( v_pkg_requested[ri].name ); if(itr==table_vPkg.end()){ sstd::pdbg("ERROR: A package name of \"%s\" is not defined.\n", v_pkg_requested[ri].name.c_str()); ret=false; return std::vector<struct pkg>(); }
        std::vector<struct pkg> v_pkg_exist = itr->second;
        
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
std::string return_set_env_cmd(const std::string& INST_PATH){
    return sstd::read(INST_PATH+"/set_env.sh");
}
void replace_PATH_in_laFile(const std::string& la_file_path, const std::string& SRC_PATH, const std::string& DST_PATH){
    // replace path in the '*.la' file.
    std::string cmd_r;
    cmd_r += "cd " + la_file_path + ';';
    cmd_r += "find . -type f -name '*.la' -print0 | xargs -0 sed -i 's!" + SRC_PATH + '!' + DST_PATH + "!g'"; // $ find . -type f -name '*.la' -print0 | xargs -0 sed -i 's!cpm_env/local_archive!cpm_env/local!g'
    sstd::system(cmd_r);
}
void gen_archive(const std::string& save_name, const std::string& archive_ext, const std::string& path){
    
    if      (archive_ext=="tar.xz"){ sstd::system(sstd::ssprintf("cd %s; tar -Jcf %s *", path.c_str(), save_name.c_str()));
    }else if(archive_ext=="zip"   ){ sstd::system(sstd::ssprintf("cd %s; zip -rq %s *", path.c_str(), save_name.c_str()));
    }else                          { sstd::pdbg("Error: Unexpected extension.");
    }
    
    uint64 size = std::stoull(sstd::system_stdout(sstd::ssprintf("ls -al %s | cut -d ' ' -f 5", save_name.c_str())));
    if(size >= 104857600){
        sstd::system(sstd::ssprintf("split -d -b 100m %s %s-", save_name.c_str(), save_name.c_str())); // test by zip to reduce excusion time.
    }
    return;
}
void gen_hashFile(const std::string& ACV_DIR, const std::string& save_name){
    std::string w_str;
    
    std::vector<std::string> vPath = sstd::glob(ACV_DIR+R"(/*)");
    for(uint i=0; i<vPath.size(); ++i){
        w_str += sstd::system_stdout("cd "+ACV_DIR+"; sha256sum "+&vPath[i][ACV_DIR.size()+1]);
    }
    sstd::write(save_name, w_str);
    return;
}
bool install_libs(const std::string& CACHE_DIR,
                  const std::string& BUILD_DIR,
                  const std::string& INST_PATH,
                  const std::string& INST_WDIR,
                  const std::vector<std::string>& v_build_env,
                  const std::string& architecture,
                  const std::string& PACKS_DIR,
                  const std::vector<struct pkg>& v_pkg,
                  const bool TF_genArchive, const std::string& ACV_DIR, const std::string& archive_ext,
                  const bool TF_dl_dps2cache_only,
                  const std::string& install_mode)
{
    std::string call_path = sstd::system_stdout("pwd"); sstd::stripAll_ow(call_path, "\r\n");
    
    for(uint i=0; i<v_pkg.size(); ++i){
        struct pkg p = v_pkg[i];
        
        std::string archivePkg_dir;
        std::string archive_baseName;
        if(TF_genArchive){
            archivePkg_dir   = getPath_acvPkgDir  (ACV_DIR, architecture, p);
            archive_baseName = getPath_acvBaseName(ACV_DIR, architecture, p);
            if(sstd::fileExist(archive_baseName+'.'+archive_ext)){ continue; }
        }
        
        std::string packsPkg_dir = getPath_packsPkgDir(PACKS_DIR, p);
        bool TF_useArchive = sstd::isFile(getSh_dlAcv(packsPkg_dir)) && (install_mode != cmd_INSTALL_MODE_source);
        
        std::string cachePkg_dir = (TF_useArchive ? getPath_cachePkgDir_acv(CACHE_DIR, architecture, p):getPath_cachePkgDir_src(CACHE_DIR, architecture, p));
        std::string buildPkg_dir = getPath_buildPkgDir(BUILD_DIR, architecture, p);
        sstd::mkdir(cachePkg_dir);
        if(!TF_useArchive){
            sstd::mkdir(buildPkg_dir);
        }
        
        std::string cmd_env;
        std::string runner = ""; // "sh"
        std::string options;
        if(v_build_env.size()==0){ sstd::pdbg("ERROR: BUILD_ENV is not set.\n"); }
        if      (v_build_env[0] == cmd_CPM_ENV   ){ cmd_env += return_set_env_cmd(INST_PATH);
        }else if(v_build_env[0] == cmd_DOCKER_ENV){ runner = "sh " + v_build_env[1] + "/docker_run.sh";
                                                    options = "--env CPM_CACHE_DIR --env CPM_BUILD_DIR --env CPM_DLIB_PATH --env CPM_INST_WDIR --env CPM_INST_PATH";
        }else if(v_build_env[0] == cmd_SYSTEM_ENV){ // do nothing
        }else{
            sstd::pdbg("ERROR: BUILD_ENV has invalid value: %s.\n", v_build_env[0].c_str());
            return false;
        }
        cmd_env += "export CPM_BUILD_DIR=" + buildPkg_dir + '\n';
        cmd_env += "export CPM_DLIB_PATH=" + INST_PATH + '\n'; // dependent library
        cmd_env += "export CPM_INST_WDIR=" + INST_WDIR + '\n'; // working dir
        cmd_env += "export CPM_INST_PATH=" + INST_PATH + '\n';
        cmd_env += "\n";
        std::string cmd_run;
        if(TF_dl_dps2cache_only){
            std::string cacheDir_acv = getPath_cachePkgDir_acv(CACHE_DIR, architecture, p);
            std::string cacheDir_src = getPath_cachePkgDir_src(CACHE_DIR, architecture, p);
            std::string cmd_env4acv = cmd_env + "export CPM_CACHE_DIR=" + cacheDir_acv + '\n';
            std::string cmd_env4src = cmd_env + "export CPM_CACHE_DIR=" + cacheDir_src + '\n';
            std::string cmd_run4acv = runner + ' ' + getSh_dlAcv(packsPkg_dir) + ' ' + options + '\n';
            std::string cmd_run4src = runner + ' ' + getSh_dlSrc(packsPkg_dir) + ' ' + options + '\n';
            sstd::system(cmd_env4acv + cmd_run4acv); // download archive files
            sstd::system(cmd_env4src + cmd_run4src); // download src files
            continue;
        }
        cmd_env += "export CPM_CACHE_DIR=" + cachePkg_dir + '\n';
        if(TF_useArchive){
            cmd_run += runner + ' ' + getSh_dlAcv  (packsPkg_dir) + ' ' + options + '\n';
            cmd_run += runner + ' ' + getSh_instAcv(packsPkg_dir) + ' ' + options + '\n';
        }else{
            cmd_run += runner + ' ' + getSh_dlSrc  (packsPkg_dir) + ' ' + options + '\n';
            cmd_run += runner + ' ' + getSh_instSrc(packsPkg_dir) + ' ' + options + '\n';
        }
        //std::string str_isInstalled = sstd::system_stdout_stderr(cmd_env+runner+' '+getSh_isInst(packsPkg_dir)+' '+options+'\n');
        std::string str_isInstalled = sstd::system_stdout_stderr(cmd_env + getSh_isInst(packsPkg_dir));
        bool TF_isInstalled = sstd::strIn("true", str_isInstalled);
        if(TF_isInstalled){ continue; }
        sstd::mkdir(INST_WDIR);
        sstd::system(cmd_env + cmd_run); // install to INST_WDIR
        
        std::string rtxt_path = INST_WDIR + "/replacement_path_for_cpm_archive.txt";
        
        // replace path on '*la' and 'replacement_path_for_cpm_archive.txt' file (preproc to install on INST_PATH)
        if(sstd::fileExist(rtxt_path)){
            std::string cmd_r;
            
            std::string SRC_PATH = sstd::read(rtxt_path); sstd::stripAll_ow(SRC_PATH, "\r\n");
            std::string DST_PATH = call_path + '/' + INST_PATH;
            if(v_build_env[0] == cmd_DOCKER_ENV){ DST_PATH = sstd::read(v_build_env[1]+"/docker_base_path.txt"); sstd::stripAll_ow(DST_PATH, "\r\n"); DST_PATH += '/' + INST_PATH; }
            
            replace_PATH_in_laFile(INST_WDIR, SRC_PATH, DST_PATH);
            //replace_PATH_in_laFile(INST_WDIR+"/*.la", SRC_PATH, DST_PATH); 
            sstd::write(rtxt_path, DST_PATH);
        }
        
        // copy file (move INST_WDIR to INST_PATH)
        std::vector<std::string> vPath = sstd::glob(INST_WDIR+"/*", "df");
        if(vPath.size()!=0){
            sstd::cp(INST_WDIR+"/*", INST_PATH, "pu");
//          sstd::mv(WORK_PATH+"/*", INST_PATH); // Not implimented yet
        }else{
            sstd::pdbg("ERROR: CPM_INST_WDIR is empty.");
            return false;
        }
        
        TF_isInstalled = sstd::stripAll(sstd::system_stdout(cmd_env + getSh_isInst(packsPkg_dir)), " \r\n")=="true";
        if(!TF_isInstalled){
            sstd::pdbg("ERROR: Installation is failed.");
            return false;
        }
        if(TF_genArchive && !TF_useArchive){
            if(sstd::glob(INST_WDIR+"/*.la", "fr").size()!=0 && sstd::fileExist(rtxt_path)==false){
                sstd::pdbg("ERROR: replacement_path_for_cpm_archive.txt is not found.");
                return false;
            }
            
            sstd::mkdir(archivePkg_dir);
            gen_archive(call_path+'/'+archive_baseName+'.'+archive_ext, archive_ext, call_path+'/'+INST_WDIR);
            gen_hashFile(archivePkg_dir, archive_baseName+"-sha256sum.txt");
        }
        sstd::rm(INST_WDIR);
    }
    
    return true;
}
sstd::vvec<std::string> read_packages_path(const std::string& packages_path){
    sstd::vec<std::string> vLine = sstd::getCommandList( packages_path );
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

struct install_cmd{
    std::string build_env;
    std::string install_mode;
    
    std::string architecture;
    std::string libName;
    std::string ver;
    
    std::vector<std::string> vDep; // dependencies
};
std::unordered_map<std::string, struct install_cmd> packageTxt2instGraph(bool& ret_tf, const std::string& packages_path){
    std::unordered_map<std::string, struct install_cmd> ret_table_vPkg; // a package list including dependency graph.
    ret_tf=true;
    
    std::string build_env;
    std::string install_mode;
    
    std::string architecture;
    std::string import_libName;
    std::string import_ver;
    std::string import_URL;
    
    sstd::vvec<std::string> vLine = read_packages_path( packages_path );
    for(uint i=0; i<vLine.size(); ++i){
        std::vector<std::string>& line = vLine[i];
        
        if(line[0]==cmd_ARCHITECTURE){
            if(line.size()!=2){ sstd::pdbg("ERROR: The \"ARCHITECTURE\" command requires 1 args."); ret_tf=false; return std::unordered_map<std::string, struct install_cmd>(); }
            
            architecture = line[1];
            
        }else if(line[0]==cmd_BUILD_ENV){
            if(line.size()!=2){ sstd::pdbg("ERROR: The \"BUILD_ENV\" command requires 1 args."); ret_tf=false; return std::unordered_map<std::string, struct install_cmd>(); }
            if(! (line[1]==cmd_CPM_ENV || line[1]==cmd_DOCKER_ENV || line[1]==cmd_SYSTEM_ENV) ){ sstd::pdbg("ERROR: Unexpected BUILD_ENV option."); }
            
            build_env = line[1];
            
        }else if(line[0]==cmd_IMPORT){
            if(line.size()!=4){ sstd::pdbg("ERROR: The \"IMPORT\" command requires 3 args."); ret_tf=false; return std::unordered_map<std::string, struct install_cmd>(); }
            
            import_libName = line[1];
            import_ver     = line[2];
            import_URL     = line[3];
            
            // import するライブラリを table に追加する
            
            // パッケージの依存関係を取得する
            // ここでダウンロードする
            // - ダウンロードした packages_cpm.txt を stack に積む
            //     - ダウンロードした依存ライブラリを stack に積む
            //     - ダウンロードした IMPORT 命令を stack に積む
            
        }else if(line[0]==cmd_INSTALL_MODE){
            if(line.size()!=4){ sstd::pdbg("ERROR: The \"INSTALL_MODE\" command requires 1 args."); ret_tf=false; return std::unordered_map<std::string, struct install_cmd>(); }
            if(! (line[1]==cmd_INSTALL_MODE_auto || line[1]==cmd_INSTALL_MODE_source || line[1]==cmd_INSTALL_MODE_archive) ){ sstd::pdbg("ERROR: Unexpected INSTALL_MODE option."); }
            
            install_mode = line[1];
            
        }else{
            if(line.size()!=2){ sstd::pdbg("ERROR: When specifing the library, version needs to be defined."); ret_tf=false; return std::unordered_map<std::string, struct install_cmd>(); }
            
            struct install_cmd ic;
            ic.build_env    = build_env;
            ic.install_mode = install_mode;
            ic.architecture = architecture;
            ic.libName      = line[0];
            ic.ver          = line[1];
            
            // ライブラリを table に追加する
            auto itr = ret_table_vPkg.find( ic.libName );
            if(itr!=ret_table_vPkg.end()){
                // solve the range of version
                ;
            }
            ret_table_vPkg[ ic.libName ] = ic;
            
            // パッケージの依存関係を取得する
            // 1. read packages_cpm.txt
            // 1. packages_cpm.txt の内容を vLine に追記する．
            
            // 依存グラフの作成
        }
    }
    
    return ret_table_vPkg;
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
    
    std::string packages_path = "packages_cpm.txt"; // -p packages_cpm.txt
    std::string buildin_packages_dir = "cpm/packages";
    bool TF_genArchive = false;
    std::string archive_ext = "tar.xz";
    //std::string archive_ext = "zip"; // test by zip to reduce excusion time.
    bool TF_dl_dps2cache_only = false; // Only downloads depending files to chache directory and exits.
    std::string base_dir = "cpm_env";
    
    char c = ' ';
    for(int i=1; i<argc; ++i){
        std::string s = argv[i]; if(s.size() < 2){ sstd::pdbg("ERROR: Unexpectec input: %s.\n", s.c_str()); return -1; }
        if(s[0] == '-'){ c=s[1]; continue; }
        
        switch(c){
        case 'a': { TF_genArchive = (sstd::strcmp(s,"true") ? true:false); break; }
        case 'b': { base_dir=s; break; }
        case 'c': { TF_dl_dps2cache_only = (sstd::strcmp(s,"true") ? true:false); break; }
        case 'p': { packages_path=s; break; }
        default: { break; }
        }
    }
    
    // Because of when using Docker, the absolute path is determined at run time.
    // Use relative path internally and convert absolute path when immediately before running scripts and commands.
    std::string CACHE_DIR = base_dir+"/cache";
    std::string PACKS_DIR = base_dir+"/packages";
    std::string BUILD_DIR = base_dir+"/build";
    std::string INST_WDIR = base_dir+"/local_work";
    std::string INST_PATH = base_dir+"/local";
    std::string ACV_DIR   = base_dir+"/archive";
    sstd::mkdir(CACHE_DIR);
    sstd::mkdir(PACKS_DIR);
    sstd::mkdir(BUILD_DIR);
    sstd::mkdir(INST_WDIR);
    sstd::mkdir(INST_PATH);
    sstd::cp(buildin_packages_dir+"/*", PACKS_DIR);
    sstd::cp("cpm/init.sh",    INST_PATH);
    sstd::cp("cpm/set_env.sh", INST_PATH);

    bool ret;
    std::unordered_map<std::string, struct install_cmd> ret_table_vPkg = packageTxt2instGraph(ret, packages_path); if(!ret){ sstd::pdbg("ERROR: packageTxt2instCmd() is failed."); }
//    for(uint i=0; i<ret_table_vPkg.size(); ++i){
        // install here
//    }
    return -1;
    //---------------------------------------------------------------------------------------------------------------------------------
    
    std::string architecture;
    std::string install_mode="auto"; // , "source" or "archive"
    std::unordered_map<std::string, std::vector<struct pkg>> table_vPkg;
    sstd::vec<std::string> v_build_env;
    sstd::vvec<std::string> vvLine = read_packages_path( packages_path );
    sstd::vec<sstd::vvec<std::string>> v_vvLine = split_pksList_by_scope(vvLine, {cmd_ARCHITECTURE, cmd_BUILD_ENV, cmd_IMPORT, cmd_INSTALL_MODE});
    for(uint n=0; n<v_vvLine.size(); ++n){
        uint l=0;
        sstd::vec<std::string>& vCmd = v_vvLine[n][l];
        
        ++l;
        if(vCmd[0]==cmd_ARCHITECTURE){
            architecture = vCmd[1]; if(!read_packages_dir( table_vPkg, PACKS_DIR+'/'+architecture)){ return -1; }
            
        }else if(vCmd[0]==cmd_BUILD_ENV){
            v_build_env = vCmd && sstd::slice(1, sstd::end());
            std::string rtxt_path = INST_PATH + "/replacement_path_for_cpm_archive.txt";
            
            if(v_build_env[0]==cmd_CPM_ENV){
                if(sstd::fileExist(rtxt_path)){ sstd::system(INST_PATH+"/init.sh"); }
                
            }else if(v_build_env[0]==cmd_DOCKER_ENV){
                sstd::system(v_build_env[1]+"/docker_build.sh");
                if(sstd::fileExist(rtxt_path)){ sstd::system("sh "+v_build_env[1]+"/docker_run.sh "+INST_PATH+"/init.sh"); }
                
            }else if(v_build_env[0]==cmd_SYSTEM_ENV){
                // Nothing to do
                
            }else{
                sstd::pdbg("ERROR: Unexpected BUILD_ENV option.");
            }
            
        }else if(vCmd[0]==cmd_IMPORT){
            std::string libName = vCmd[1];
            std::string ver     = vCmd[2];
            std::string URL     = sstd::stripAll(vCmd[3], "\"");
            std::string cacheIptScr_dir = CACHE_DIR+"/import/"+libName+'/'+ver;
            std::string cachePkg_dir    = CACHE_DIR+"/packages/"+libName+'/'+ver;
            std::string packsPkg_dir    = PACKS_DIR + '/' + architecture + '/' + libName + '/' + ver;
            sstd::mkdir(cacheIptScr_dir);
            sstd::mkdir(cachePkg_dir);
            sstd::mkdir(packsPkg_dir);
            std::string dl_script = cacheIptScr_dir + '/' + sstd::getFileName( URL.c_str() );
            if(!sstd::fileExist(dl_script)){
                sstd::system("wget -P "+cacheIptScr_dir+' '+URL);
            }
            
            std::string cmd;
            cmd += "export CPM_CACHE_DIR=" + cachePkg_dir + '\n';
            cmd += "./" + dl_script;
            sstd::system(cmd);
            sstd::cp(cachePkg_dir+"/*", packsPkg_dir, "pu");
            
            // add pkg to table_vPkg
            struct pkg r; if(!str2struct_pkg(r, libName, ver)){ return false; }
            table_vPkg[ r.name ] <<= r;
        }else if(vCmd[0]==cmd_INSTALL_MODE){
            if(vCmd.size()<2){ sstd::pdbg("ERROR: INSTALL_MODE is empty."); return -1; }
            
            if      (vCmd[1]==cmd_INSTALL_MODE_auto   ){ install_mode = cmd_INSTALL_MODE_auto;
            }else if(vCmd[1]==cmd_INSTALL_MODE_source ){ install_mode = cmd_INSTALL_MODE_source;
            }else if(vCmd[1]==cmd_INSTALL_MODE_archive){ install_mode = cmd_INSTALL_MODE_archive;
            }else{
                sstd::pdbg("ERROR: Unexpected INSTALL_MODE. \"%s\" is not defined.", vCmd[1].c_str());
                return -1;
            }
            
        }else{
            --l;
        }
        
        sstd::vvec<std::string> vPkgList = v_vvLine[n] && sstd::slice(l, sstd::end());
        
        bool ret=true;
        std::vector<struct pkg> v_pkg_requested = vPkgList2vPkg(ret, vPkgList); if(!ret){ return -1; }
        std::vector<struct pkg> v_inst_pkg      = solve_dependencies(ret, v_pkg_requested, table_vPkg); if(!ret){ return -1; }
        install_libs(CACHE_DIR, BUILD_DIR, INST_PATH, INST_WDIR, v_build_env, architecture, PACKS_DIR+'/'+architecture, v_inst_pkg, TF_genArchive, ACV_DIR, archive_ext, TF_dl_dps2cache_only, install_mode);
    }

    printf("\n");
    sstd::measureTime_stop_print(timem);
    return 0;
}

#undef cmd_INSTALL_MODE_archive
#undef cmd_INSTALL_MODE_source
#undef cmd_INSTALL_MODE_auto
#undef cmd_INSTALL_MODE

#undef cmd_SYSTEM_ENV
#undef cmd_DOCKER_ENV
#undef cmd_CPM_ENV
#undef cmd_BUILD_ENV

#undef cmd_IMPORT
#undef cmd_ARCHITECTURE
