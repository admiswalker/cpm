#include "dependency_graph_generator.hpp"
#include "definition.hpp"


void cpm::print(struct install_cmd& lhs){
    std::vector<std::string> vDep; // dependencies
    printf("[build_env: %s, install_mode: %s, architecture: %s, libName: %s, ", lhs.build_env.c_str(), lhs.install_mode.c_str(), lhs.architecture.c_str(), lhs.libName.c_str());
    printf("vVer: %s, ", cpm::print_str(lhs.vVer).c_str());
    printf("vDep: [ ");
    for(uint i=0; i<vDep.size(); ++i){
        printf("%s, ", lhs.vDep[i].c_str());
    }
    printf("]\n");
}

std::unordered_map<std::string, struct cpm::install_cmd> cpm::vLine2instGraph(bool& ret_tf, class cpm::PATH& p, const sstd::vvec<std::string>& vLine){
    std::unordered_map<std::string, struct cpm::install_cmd> ret_table_vPkg; // a package list including dependency graph.
    ret_tf=true;
    
    std::string build_env;
    std::string install_mode;
    
    std::string architecture;
    std::string import_libName;
    std::string import_ver;
    std::string import_URL;
    
    for(uint i=0; i<vLine.size(); ++i){
        const std::vector<std::string>& line = vLine[i];
        
        if(line[0]==cpm::cmd_ARCHITECTURE){
            if(line.size()!=2){ sstd::pdbg("ERROR: The \"ARCHITECTURE\" command requires 1 args."); ret_tf=false; return std::unordered_map<std::string, struct cpm::install_cmd>(); }
            
            architecture = line[1];
            
        }else if(line[0]==cpm::cmd_BUILD_ENV){
            if(line.size()!=2){ sstd::pdbg("ERROR: The \"BUILD_ENV\" command requires 1 args."); ret_tf=false; return std::unordered_map<std::string, struct cpm::install_cmd>(); }
            if(! (line[1]==cpm::cmd_CPM_ENV || line[1]==cpm::cmd_DOCKER_ENV || line[1]==cpm::cmd_SYSTEM_ENV) ){ sstd::pdbg("ERROR: Unexpected BUILD_ENV option."); }
            
            build_env = line[1];
            
        }else if(line[0]==cpm::cmd_IMPORT){
            if(line.size()!=4){ sstd::pdbg("ERROR: The \"IMPORT\" command requires 3 args."); ret_tf=false; return std::unordered_map<std::string, struct cpm::install_cmd>(); }
            
            import_libName = line[1];
            import_ver     = line[2];
            import_URL     = line[3];
            
            // import するライブラリを table に追加する
            
            // パッケージの依存関係を取得する
            // ここでダウンロードする
            // - ダウンロードした packages_cpm.txt を stack に積む
            //     - ダウンロードした依存ライブラリを stack に積む
            //     - ダウンロードした IMPORT 命令を stack に積む
            
        }else if(line[0]==cpm::cmd_INSTALL_MODE){
            if(line.size()!=2){ sstd::pdbg("ERROR: The \"INSTALL_MODE\" command requires 1 args."); ret_tf=false; return std::unordered_map<std::string, struct cpm::install_cmd>(); }
            if(! (line[1]==cpm::cmd_INSTALL_MODE_auto || line[1]==cpm::cmd_INSTALL_MODE_source || line[1]==cpm::cmd_INSTALL_MODE_archive) ){ sstd::pdbg("ERROR: Unexpected INSTALL_MODE option."); }
            
            install_mode = line[1];
            
        }else{
            if(line.size()!=2){ sstd::pdbg("ERROR: When specifing the library, version needs to be defined."); ret_tf=false; return std::unordered_map<std::string, struct cpm::install_cmd>(); }
            
            struct cpm::install_cmd ic;
            ic.build_env    = build_env;
            ic.install_mode = install_mode;
            ic.architecture = architecture;
            ic.libName      = line[0];
            ic.vVer         = cpm::str2ver( line && sstd::slice(1, sstd::end()) );
            
            // ライブラリを table に追加する
            auto itr = ret_table_vPkg.find( ic.libName );
            if(itr!=ret_table_vPkg.end()){
                std::vector<cpm::ver> tmp = cpm::verAND(ic.vVer, itr->second.vVer); // solve the range of version
                if(itr->second.vVer.size()==0){
                    sstd::pdbg("ERROR: The lib \"%s\" is required conflicting version. cpm::verAND() can't get version between %s and %s.\n", itr->first.c_str(), cpm::print_str(ic.vVer).c_str(), cpm::print_str(itr->second.vVer).c_str());
                }
            }
            ret_table_vPkg[ ic.libName ] = ic;
            
            // パッケージの一覧を取得する
            
            // パッケージの依存関係を取得する
            // 1. read packages_cpm.txt
            struct cpm::pkg pg;
            pg.name = ic.libName;
//            pg.ver  = ic.vVer[ic.vVer.size()-1].ver;
//            const std::string packsPkg_dir = cpm::getPath_packsPkgDir(p.PACKS_DIR, pg);
//            const std::string depPkg_txt = cpm::getTxt_depPkg(packsPkg_dir);
            // 1. packages_cpm.txt の内容を vLine に追記する．
            
            // 依存グラフの作成
        }
    }
    
    return ret_table_vPkg;
}
