#pragma once
#include <sstd/sstd.hpp>


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
        PATH(const std::string& baseDir);
        ~PATH();
    };
    
    extern const std::string buildin_packages_dir;

    //---
    
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
    };
    
    std::string getPath_acvPkgDir      (const std::string& ACV_DIR,   const std::string& architecture, const struct pkg& p);
    std::string getPath_acvBaseName    (const std::string& ACV_DIR,   const std::string& architecture, const struct pkg& p);
    std::string getPath_packsPkgDir    (const std::string& PACKS_DIR, const struct pkg& p);
    std::string getPath_cachePkgDir_acv(const std::string& CACHE_DIR, const std::string& architecture, const struct pkg& p);
    std::string getPath_cachePkgDir_src(const std::string& CACHE_DIR, const std::string& architecture, const struct pkg& p);
    std::string getPath_buildPkgDir    (const std::string& BUILD_DIR, const std::string& architecture, const struct pkg& p);

    std::string getSh_dlAcv  (const std::string& packsPkg_dir);
    std::string getSh_dlSrc  (const std::string& packsPkg_dir);
    std::string getSh_instAcv(const std::string& packsPkg_dir);
    std::string getSh_instSrc(const std::string& packsPkg_dir);
    std::string getSh_isInst (const std::string& packsPkg_dir);

    std::string getTxt_depPkg(const std::string& packsPkg_dir);
    
    //---
}
