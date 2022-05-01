#include <vector>
#include <string>
#include "src/pathProc.hpp"

/*
namespace sstd{
    void print(const struct cpm::pkg& rhs);
    void print_for_vT(const struct cpm::pkg& rhs);
    void for_printn(const struct cpm::pkg& rhs);
}
void sstd::print(const struct cpm::pkg& rhs){
    printf("name: %s, verStr: %s, ver: %d.%d.%d, verExtra: %s, v_depend: [ ", rhs.name.c_str(), rhs.ver.c_str(), rhs.ver100, rhs.ver010, rhs.ver001, rhs.verExtra.c_str());
    for(uint i=0; i<rhs.v_depend.size(); ++i){
        sstd::print_for_vT(rhs.v_depend[i]);
    }
    printf("]\n");
}
void sstd::print_for_vT(const struct cpm::pkg& rhs){
    printf("[name: %s, verStr: %s, ver: %d.%d.%d, verExtra: %s, v_depend: [", rhs.name.c_str(), rhs.ver.c_str(), rhs.ver100, rhs.ver010, rhs.ver001, rhs.verExtra.c_str());
    for(uint i=0; i<rhs.v_depend.size(); ++i){
        sstd::print_for_vT((const struct cpm::pkg&)rhs.v_depend[i]);
    }
    printf("]]");
}
void sstd::for_printn(const struct cpm::pkg& rhs){ printf(" = "); sstd::print(rhs); }
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

#include <sstd/sstd.hpp> // include after "sstd::print_for_vT"
#include <unordered_map>
#include "src/definition.hpp"
#include "src/dependency_graph_generator.hpp"
#include "src/version_processor.hpp"

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
    }else                          { sstd::pdbg_err("Unexpected extension.");
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

struct runTimeOptions{
    bool TF_genArchive;
    std::string archive_ext;
    bool TF_dl_dps2cache_only;
};
bool install_lib(const cpm::PATH& p,
                 const struct runTimeOptions& rto,
                 const cpm::install_cmd& c){
    std::string call_path = sstd::system_stdout("pwd"); sstd::stripAll_ow(call_path, "\r\n");
    
    std::string archivePkg_dir;
    std::string archive_baseName;
    if(rto.TF_genArchive){
        archivePkg_dir   = cpm::getPath_acvPkgDir  (p.ACV_DIR, c.architecture, c.libName, c.vVer[0].ver);
        archive_baseName = cpm::getPath_acvBaseName(p.ACV_DIR, c.architecture, c.libName, c.vVer[0].ver);
        if(sstd::fileExist(archive_baseName+'.'+rto.archive_ext)){ return true; }
    }
    
    std::string packsPkg_dir = cpm::getPath_packsPkgDir(p.PACKS_DIR, c.architecture, c.libName, c.vVer[0].ver);
    bool TF_useArchive = sstd::isFile(cpm::getSh_dlAcv(packsPkg_dir)) && (c.install_mode != cpm::cmd_INSTALL_MODE_source);
    
    std::string cachePkg_dir = (TF_useArchive ? cpm::getPath_cachePkgDir_acv(p.CACHE_DIR, c.architecture, c.libName, c.vVer[0].ver):cpm::getPath_cachePkgDir_src(p.CACHE_DIR, c.architecture, c.libName, c.vVer[0].ver));
    std::string buildPkg_dir = cpm::getPath_buildPkgDir(p.BUILD_DIR, c.architecture, c.libName, c.vVer[0].ver);
    sstd::mkdir(cachePkg_dir);
    if(!TF_useArchive){
        sstd::mkdir(buildPkg_dir);
    }
    
    std::string cmd_env;
    std::string runner = "bash";
    std::string options;
    if(c.build_env.size()==0){ sstd::pdbg_err("BUILD_ENV is not set.\n"); }
    if      (c.build_env == cpm::cmd_CPM_ENV   ){ cmd_env += return_set_env_cmd(p.INST_PATH);
    }else if(c.build_env == cpm::cmd_DOCKER_ENV){ runner = "bash " + c.build_env_path + "/docker_run.sh";
                                                  options = "--env CPM_CACHE_DIR --env CPM_BUILD_DIR --env CPM_DLIB_PATH --env CPM_INST_WDIR --env CPM_INST_PATH";
    }else if(c.build_env == cpm::cmd_SYSTEM_ENV){ // do nothing
    }else{
        sstd::pdbg_err("BUILD_ENV has invalid value: %s.\n", c.build_env.c_str());
        return false;
    }
    cmd_env += "export CPM_BUILD_DIR=" + buildPkg_dir + '\n';
    cmd_env += "export CPM_DLIB_PATH=" + p.INST_PATH + '\n'; // dependent library
    cmd_env += "export CPM_INST_WDIR=" + p.INST_WDIR + '\n'; // working dir
    cmd_env += "export CPM_INST_PATH=" + p.INST_PATH + '\n';
    cmd_env += "\n";
    std::string cmd_run;
    if(rto.TF_dl_dps2cache_only){
        std::string cacheDir_acv = cpm::getPath_cachePkgDir_acv(p.CACHE_DIR, c.architecture, c.libName, c.vVer[0].ver);
        std::string cacheDir_src = cpm::getPath_cachePkgDir_src(p.CACHE_DIR, c.architecture, c.libName, c.vVer[0].ver);
        std::string cmd_env4acv = cmd_env + "export CPM_CACHE_DIR=" + cacheDir_acv + '\n';
        std::string cmd_env4src = cmd_env + "export CPM_CACHE_DIR=" + cacheDir_src + '\n';
        std::string cmd_run4acv = "bash " + cpm::getSh_dlAcv(packsPkg_dir) + ' ' + options + '\n';
        std::string cmd_run4src = "bash " + cpm::getSh_dlSrc(packsPkg_dir) + ' ' + options + '\n';
        sstd::system(cmd_env4acv + cmd_run4acv); // download archive files
        sstd::system(cmd_env4src + cmd_run4src); // download src files
        return true;
    }
    cmd_env += "export CPM_CACHE_DIR=" + cachePkg_dir + '\n';
    if(TF_useArchive){
        cmd_run += runner + ' ' + cpm::getSh_dlAcv  (packsPkg_dir) + ' ' + options + '\n';
        cmd_run += runner + ' ' + cpm::getSh_instAcv(packsPkg_dir) + ' ' + options + '\n';
    }else{
        cmd_run += runner + ' ' + cpm::getSh_dlSrc  (packsPkg_dir) + ' ' + options + '\n';
        cmd_run += runner + ' ' + cpm::getSh_instSrc(packsPkg_dir) + ' ' + options + '\n';
    }
    //std::string str_isInstalled = sstd::system_stdout_stderr(cmd_env+runner+' '+cpm::getSh_isInst(packsPkg_dir)+' '+options+'\n');
    std::string str_isInstalled = sstd::system_stdout_stderr(cmd_env + "bash "+cpm::getSh_isInst(packsPkg_dir));
    bool TF_isInstalled = sstd::strIn("true", str_isInstalled);
    if(TF_isInstalled){ return true; }
    sstd::mkdir(p.INST_WDIR);
    sstd::system(cmd_env + cmd_run); // install to INST_WDIR
    
    std::string rtxt_path = p.INST_WDIR + "/replacement_path_for_cpm_archive.txt";
    
    // replace path on '*la' and 'replacement_path_for_cpm_archive.txt' file (preproc to install on INST_PATH)
    if(sstd::fileExist(rtxt_path)){
        std::string cmd_r;
        
        std::string SRC_PATH = sstd::read(rtxt_path); sstd::stripAll_ow(SRC_PATH, "\r\n");
        std::string DST_PATH = call_path + '/' + p.INST_PATH;
        if(c.build_env == cpm::cmd_DOCKER_ENV){ DST_PATH = sstd::read(c.build_env_path+"/docker_base_path.txt"); sstd::stripAll_ow(DST_PATH, "\r\n"); DST_PATH += '/' + p.INST_PATH; }
        
        replace_PATH_in_laFile(p.INST_WDIR, SRC_PATH, DST_PATH);
        //replace_PATH_in_laFile(INST_WDIR+"/*.la", SRC_PATH, DST_PATH); 
        sstd::write(rtxt_path, DST_PATH);
    }
    
    // copy file (move INST_WDIR to INST_PATH)
    std::vector<std::string> vPath = sstd::glob(p.INST_WDIR+"/*", "df");
    if(vPath.size()!=0){
        sstd::cp(p.INST_WDIR+"/*", p.INST_PATH, "pu");
//      sstd::mv(p.WORK_PATH+"/*", p.INST_PATH); // Not implimented yet
    }else{
//        sstd::pdbg_err("CPM_INST_WDIR is empty. installation of \"%s\" (ver: %s) is faild.\n", c.libName.c_str(), c.vVer[0].ver.c_str());
//        return false;
    }
    
    TF_isInstalled = sstd::stripAll(sstd::system_stdout(cmd_env + "bash "+cpm::getSh_isInst(packsPkg_dir)), " \r\n")=="true";
    if(!TF_isInstalled){
        sstd::pdbg_err("Installation is failed.\n");
        return false;
    }
    if(rto.TF_genArchive && !TF_useArchive){
        if(sstd::glob(p.INST_WDIR+"/*.la", "fr").size()!=0 && sstd::fileExist(rtxt_path)==false){
            sstd::pdbg_err("replacement_path_for_cpm_archive.txt is not found.\n");
            return false;
        }
        
        sstd::mkdir(archivePkg_dir);
        gen_archive(call_path+'/'+archive_baseName+'.'+rto.archive_ext, rto.archive_ext, call_path+'/'+p.INST_WDIR);
        gen_hashFile(archivePkg_dir, archive_baseName+"-sha256sum.txt");
    }
    sstd::rm(p.INST_WDIR);
    
    return true;
}
bool install_lib(const cpm::PATH& p, const struct runTimeOptions& rto, const std::vector<cpm::install_cmd>& vInstCmd){
    for(uint i=0; i<vInstCmd.size(); ++i){
        if(!install_lib(p, rto, vInstCmd[i])){ return false; }
    }
    return true;
}

int main(int argc, char *argv[]){
    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|                                                   |\n");
    printf("|      Welcome to C++ Package Manager (CPM) !       |\n");
    printf("|                                                   |\n");
    printf("+---------------------------------------------------+\n");
    printf("\n");
    time_m timem; sstd::measureTime_start(timem);

    std::string packages_path = "packages_cpm.txt"; // -p packages_cpm.txt
    struct runTimeOptions rto;
    rto.TF_genArchive = false;
    rto.archive_ext = "tar.xz";
    //rto.archive_ext = "zip"; // test by zip to reduce excusion time.
    rto.TF_dl_dps2cache_only = false; // Only downloads depending files to chache directory and exits.
    std::string base_dir = cpm::baseDir_default;
    
    char c = ' ';
    for(int i=1; i<argc; ++i){
        std::string s = argv[i]; if(s.size() < 2){ sstd::pdbg_err("Unexpectec input: %s.\n", s.c_str()); return -1; }
        if(s[0] == '-'){ c=s[1]; continue; }
        
        switch(c){
        case 'a': { rto.TF_genArchive = (sstd::strcmp(s,"true") ? true:false); break; }
        case 'b': { base_dir=s; break; }
        case 'c': { rto.TF_dl_dps2cache_only = (sstd::strcmp(s,"true") ? true:false); break; }
        case 'p': { packages_path=s; break; }
        default: { break; }
        }
    }
    
    // Because of when using Docker, the absolute path is determined at run time.
    // Use relative path internally and convert absolute path when immediately before running scripts and commands.
    class cpm::PATH p(base_dir);
    std::string CACHE_DIR = p.CACHE_DIR;
    std::string PACKS_DIR = p.PACKS_DIR;
    std::string BUILD_DIR = p.BUILD_DIR;
    std::string INST_WDIR = p.INST_WDIR;
    std::string INST_PATH = p.INST_PATH;
    std::string ACV_DIR   = p.ACV_DIR;
    sstd::mkdir(CACHE_DIR);
    sstd::mkdir(PACKS_DIR);
    sstd::mkdir(BUILD_DIR);
    sstd::mkdir(INST_WDIR);
    sstd::mkdir(INST_PATH);
    sstd::cp(cpm::buildin_packages_dir+"/*", PACKS_DIR);
    sstd::cp("cpm/init.sh",    INST_PATH);
    sstd::cp("cpm/set_env.sh", INST_PATH);
    
    
    bool ret;
    std::unordered_map<std::string, struct cpm::install_cmd> table_reqPkg;
    ret = cpm::txt2instGraph(table_reqPkg, p, packages_path.c_str());
    if(!ret){ sstd::pdbg_err("packageTxt2instCmd() is failed.\n"); return -1; }
    
    std::vector<cpm::install_cmd> vInst;
    ret = cpm::instGraph2instOrder(vInst, table_reqPkg);
    //*
    for(uint i=0; i<vInst.size(); ++i){
        sstd::printn(vInst[i].readOrder);
        sstd::printn(vInst[i].libName);
    }
    //*/
    
    install_lib(p, rto, vInst);
    
    return 0;
}
