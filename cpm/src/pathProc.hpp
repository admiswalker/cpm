#pragma once
#include <sstd/sstd.hpp>

#include "version_processor.hpp"


namespace cpm{
    extern const std::string baseDir_default;
    class PATH{
    private:
    public:
        const std::string BASE_DIR;
        const std::string CACHE_DIR;
        const std::string PACKS_DIR;
        const std::string BUILD_DIR;
        const std::string INST_WDIR;
        const std::string INST_PATH;
        const std::string ACV_DIR;
        explicit PATH(const std::string& baseDir);
        explicit PATH(const std::string& baseDir,
                      const std::string& cacheDir,
                      const std::string& packsDir,
                      const std::string& buildDir,
                      const std::string& instWDir,
                      const std::string& instPDir,
                      const std::string& acvPDir);
        ~PATH();
    };
    
    extern const std::string buildin_packages_dir;

    //---
    
    std::string getPath_acvPkgDir      (const std::string& ACV_DIR,   const std::string& architecture, const std::string& libName, const std::string& ver);
    std::string getPath_acvBaseName    (const std::string& ACV_DIR,   const std::string& architecture, const std::string& libName, const std::string& ver);
    std::string getPath_packsPkgDir    (const std::string& PACKS_DIR, const std::string& architecture, const std::string& libName, const std::string& ver);
    std::string getPath_cachePkgDir_acv(const std::string& CACHE_DIR, const std::string& architecture, const std::string& libName, const std::string& ver);
    std::string getPath_cachePkgDir_src(const std::string& CACHE_DIR, const std::string& architecture, const std::string& libName, const std::string& ver);
    std::string getPath_buildPkgDir    (const std::string& BUILD_DIR, const std::string& architecture, const std::string& libName, const std::string& ver);

    std::string getSh_init   (const class cpm::PATH& p);
    std::string getSh_dlAcv  (const std::string& packsPkg_dir);
    std::string getSh_dlSrc  (const std::string& packsPkg_dir);
    std::string getSh_instAcv(const std::string& packsPkg_dir);
    std::string getSh_instSrc(const std::string& packsPkg_dir);
    std::string getSh_isInst (const std::string& packsPkg_dir);

    std::string getTxt_depPkg(const std::string& packsPkg_dir);
    
    //---
    
    bool get_available_pkg(std::vector<std::string>& ret_vPath, std::vector<cpm::ver>& ret_vVer, const std::string& PACKS_DIR, const std::string& architecture, const std::string& libName);
}
