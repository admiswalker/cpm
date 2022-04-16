#include "pathProc.hpp"


const std::string cpm::baseDir_default = "cpm_env";
cpm::PATH::PATH(const std::string& baseDir):
    BASE_DIR(baseDir),
    CACHE_DIR(BASE_DIR+"/cache"),
    PACKS_DIR(BASE_DIR+"/packages"),
    BUILD_DIR(BASE_DIR+"/build"),
    INST_WDIR(BASE_DIR+"/local_work"),
    INST_PATH(BASE_DIR+"/local"),
    ACV_DIR  (BASE_DIR+"/archive")
{
}
cpm::PATH::~PATH(){}

const std::string cpm::buildin_packages_dir = "cpm/packages";

std::string cpm::getPath_acvPkgDir      (const std::string& ACV_DIR,   const std::string& architecture, const struct cpm::pkg& p){ return ACV_DIR + '/' + architecture + '/' + p.name + '/' + p.ver; }
std::string cpm::getPath_acvBaseName    (const std::string& ACV_DIR,   const std::string& architecture, const struct cpm::pkg& p){ return getPath_acvPkgDir(ACV_DIR, architecture, p) + '/' + architecture + '-' + p.name + '-' + p.ver; }
std::string cpm::getPath_packsPkgDir    (const std::string& PACKS_DIR, const struct cpm::pkg& p){ return PACKS_DIR + '/' + p.name + '/' + p.ver; }
std::string cpm::getPath_cachePkgDir_acv(const std::string& CACHE_DIR, const std::string& architecture, const struct cpm::pkg& p){ return CACHE_DIR + "/archive/" + architecture + '-' + p.name + '-' + p.ver; }
std::string cpm::getPath_cachePkgDir_src(const std::string& CACHE_DIR, const std::string& architecture, const struct cpm::pkg& p){ return CACHE_DIR + "/src/"     + architecture + '-' + p.name + '-' + p.ver; }
std::string cpm::getPath_buildPkgDir    (const std::string& BUILD_DIR, const std::string& architecture, const struct cpm::pkg& p){ return BUILD_DIR + '/' + architecture + '-' + p.name + '-' + p.ver; }

std::string cpm::getSh_dlAcv  (const std::string& packsPkg_dir){ return packsPkg_dir + "/download_archive.sh"; }
std::string cpm::getSh_dlSrc  (const std::string& packsPkg_dir){ return packsPkg_dir + "/download_src.sh";     }
std::string cpm::getSh_instAcv(const std::string& packsPkg_dir){ return packsPkg_dir + "/install_archive.sh";  }
std::string cpm::getSh_instSrc(const std::string& packsPkg_dir){ return packsPkg_dir + "/install_src.sh";      }
std::string cpm::getSh_isInst (const std::string& packsPkg_dir){ return packsPkg_dir + "/is_installed.sh";     }

std::string cpm::getTxt_depPkg(const std::string& packsPkg_dir){ return packsPkg_dir + "/packages_cpm.txt";     }

