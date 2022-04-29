#include "dependency_graph_generator.hpp"
#include "definition.hpp"


void cpm::print(struct install_cmd& lhs){
    printf("[build_env: %s, install_mode: %s, architecture: %s, libName: %s, ", lhs.build_env.c_str(), lhs.install_mode.c_str(), lhs.architecture.c_str(), lhs.libName.c_str());
    printf("vVer: %s, ", cpm::print_str(lhs.vVer).c_str());

    auto itr = lhs.depTbl.begin();
    if(lhs.depTbl.size()>=1){ printf("depTbl: [ %s", itr->first.c_str()); ++itr; }
    for(; itr!=lhs.depTbl.end(); ++itr){
        printf(", %s", itr->first.c_str());
    }
    printf(" ]\n");
}
void cpm::print(std::vector<struct install_cmd>& vLhs){
    printf("[");
    if(vLhs.size()>=1){ cpm::print(vLhs[0]); }
    for(uint i=1; i<vLhs.size(); ++i){
        cpm::print(vLhs[i]);
        printf(", ");
    }
    printf("]\n");
}
bool cpm::vLine2instGraph(std::unordered_map<std::string, struct install_cmd>& ret_table_reqPkg, const class cpm::PATH& p, const sstd::vec<uint>& vLineNum_in, const sstd::vvec<std::string>& vLine_in, const char* fileName){
    
    std::string build_env;
    std::string install_mode;
    
    std::string architecture;
    std::string import_libName;
    std::string import_ver;
    std::string import_URL;

    if(vLineNum_in.size() != vLine_in.size()){ sstd::pdbg_err("vector size of \"vLineNum\" and \"vLine\" is not match."); return false; }
    sstd::vec<uint> vLineNum = vLineNum_in;
    sstd::vvec<std::string> vLine = vLine_in;
    sstd::vec<std::string> vFileName(vLine.size(), fileName);
    
    for(uint i=0; i<vLine.size(); ++i){
        const uint lineNum = vLineNum[i];
        const std::vector<std::string>& line = vLine[i];
        const std::string& fileName = vFileName[i];
        
        if(line[0]==cpm::cmd_ARCHITECTURE){
            if(line.size()!=2){ sstd::pdbg_err("The \"ARCHITECTURE\" command requires 1 args."); return false; }
            
            architecture = line[1];
            
        }else if(line[0]==cpm::cmd_BUILD_ENV){
            if(line.size()!=3){ sstd::pdbg_err("The \"BUILD_ENV\" command requires 2 args."); return false; }
            if(! (line[1]==cpm::cmd_CPM_ENV || line[1]==cpm::cmd_DOCKER_ENV || line[1]==cpm::cmd_SYSTEM_ENV) ){ sstd::pdbg_err("Unexpected BUILD_ENV option."); }
            
            build_env = line[1];
            
        }else if(line[0]==cpm::cmd_IMPORT){
            if(line.size()!=4){ sstd::pdbg_err("The \"IMPORT\" command requires 3 args."); return false; }
            
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
            if(line.size()!=2){ sstd::pdbg_err("The \"INSTALL_MODE\" command requires 1 args."); return false; }
            if(! (line[1]==cpm::cmd_INSTALL_MODE_auto || line[1]==cpm::cmd_INSTALL_MODE_source || line[1]==cpm::cmd_INSTALL_MODE_archive) ){ sstd::pdbg_err("Unexpected INSTALL_MODE option."); }
            
            install_mode = line[1];
            
        }else{
            if(line.size()!=2){ sstd::pdbg_err("When specifing the library, version needs to be defined."); return false; }
            
            struct cpm::install_cmd ic;
            ic.build_env    = build_env;
            ic.install_mode = install_mode;
            ic.architecture = architecture;
            ic.libName      = line[0];
            ic.vVer         = cpm::str2ver( line && sstd::slice(1, sstd::end()) );
            
            // ライブラリを table に追加する
            auto itr = ret_table_reqPkg.find( ic.libName );
            if(itr!=ret_table_reqPkg.end()){
                bool tf;
                itr->second.vVer = cpm::verAND(tf, ic.vVer, itr->second.vVer); // solve the range of version
                if(! tf ){
                    sstd::pdbg_err("cpm::verAND() is failed. An error occured while reading the following line in the file:\n  FileName: \"%s\"\n  LineNum: %u.\n", fileName.c_str(), lineNum);
                    return false;
                }
                if(itr->second.vVer.size()==0){
                    sstd::pdbg_err("The lib \"%s\" is required conflicting version. cpm::verAND() can't get version between %s and %s.\n", itr->first.c_str(), cpm::print_str(ic.vVer).c_str(), cpm::print_str(itr->second.vVer).c_str());
                    return false;
                }
            }
            
            // 利用可能なパッケージの一覧を取得する
            std::vector<std::string> ret_vPath;
            std::vector<cpm::ver> ret_vVer;
            cpm::get_available_pkg(ret_vPath, ret_vVer, p.PACKS_DIR, architecture, ic.libName);
            if(i<0){ sstd::pdbg_err("There is no available \"%s\" library.", ic.libName.c_str()); return false; }
//            sstd::printn(ret_vPath);
//            cpm::print(ret_vVer);
            
            // 利用可能なパッケージ version と，要求 version の AND を取る
            bool tf;
            std::vector<cpm::ver> vVerAND = cpm::verAND(tf, ic.vVer, ret_vVer);
            int idx=vVerAND.size()-1;
            for(; idx>=0; --idx){
                if(vVerAND[idx].ineq==cpm::CPM_EQ){ break; }
            }
            if(idx<0){
                sstd::pdbg_err("There is no available \"%s\" library.\n  required: %s\n  available: %s\n", ic.libName.c_str(), cpm::print_str(ic.vVer).c_str(), cpm::print_str(ret_vVer).c_str());
                return false;
            }
            std::string latest_ver = vVerAND[vVerAND.size()-1].ver;
            
            // パッケージの依存関係を取得する
            // 1. read packages_cpm.txt
            struct cpm::pkg pg;
            pg.name = ic.libName;
            pg.ver  = latest_ver;
            const std::string packsPkg_dir = cpm::getPath_packsPkgDir(p.PACKS_DIR, architecture, pg);
            const std::string depPkg_txt = cpm::getTxt_depPkg(packsPkg_dir);
            // 1. packages_cpm.txt の内容を vLine に追記する．
            sstd::vec<uint> ret_vLineNum;
            sstd::vvec<std::string> ret_vLine;
            bool ret = sstd::txt2vCmdList(ret_vLineNum, ret_vLine, depPkg_txt);
            if(!ret){ sstd::pdbg_err("Failed to read %s.", depPkg_txt.c_str()); return false; }
            vLine     <<= ret_vLine;
            vLineNum  <<= ret_vLineNum;
            vFileName <<= std::vector<std::string>(ret_vLine.size(), depPkg_txt);
            
            // 依存グラフの作成
//            sstd::printn(ret_vLine);
            for(uint i=0; i<ret_vLine.size(); ++i){
                ic.depTbl[ ret_vLine[i][0] ];
            }
//            sstd::printn(ic.depTbl);
            ret_table_reqPkg[ ic.libName ] = ic;
        }
    }
    
    return true;
}
bool cpm::txt2instGraph(std::unordered_map<std::string, struct cpm::install_cmd>& ret_table_reqPkg, const class cpm::PATH& p, const char* packages_path){
    bool ret_tf;
    
    sstd::vec<uint> vLineNum;
    sstd::vvec<std::string> vLine;
    ret_tf = sstd::txt2vCmdList(vLineNum, vLine, packages_path);
    if(!ret_tf){ sstd::pdbg_err("sstd::txt2vCmdList() is failed."); return false; }

    std::string fileName = sstd::getFileName( packages_path );
    ret_tf = cpm::vLine2instGraph(ret_table_reqPkg, p, vLineNum, vLine, fileName.c_str());
    if(!ret_tf){ sstd::pdbg_err("packageTxt2instCmd() is failed."); }
    
    return true;
}


bool cpm::instGraph2instOrder(std::vector<cpm::install_cmd>& ret_vInst, const std::unordered_map<std::string, struct cpm::install_cmd>& table_reqPkg){

    std::unordered_map<std::string, bool> isInst;
    
    // copy table to stack
    std::vector<cpm::install_cmd> stack;
    for(auto itr=table_reqPkg.begin(); itr!=table_reqPkg.end(); ++itr){
        stack <<= itr->second;
        isInst[ itr->first ] = false;
    }

    // 全部 copy しているが，最初の 1 つだけでよいのでは？
    // → グラフとして繋がっていないものは，引っ張り出しておく必要がある．
    // → どうせ依存関係が解決されていれば，size()==0 で次のループに遷移するだけなので，気にしなくてよいのでは？
    // → ret_vInst に重複した値が入らない？
    // → 重複だけチェックする

    cpm::print(stack);
    printf("imh\n");
    for(int i=stack.size()-1; i>=0; --i){
        int next_stack_idx = i;
        for(auto itr=stack[i].depTbl.begin(); itr!=stack[i].depTbl.end();){
            std::string libName = itr->first;
            
            if( isInst[ libName ] ){
                itr = stack[i].depTbl.erase( itr );
                continue;
            }
            
            // ここで stack に積む
            auto itr_t = table_reqPkg.find( libName );
            stack <<= itr_t->second;
            next_stack_idx = stack.size();
            ++itr;
        }

        if( stack[i].depTbl.size() == 0 ){
            if(! isInst[ stack[i].libName ] ){
                isInst[ stack[i].libName ] = true;
                ret_vInst <<= stack[i];
            }
            stack.erase(stack.begin()+i);
            continue;
        }

        i = next_stack_idx;
    }
    
    return true;
}

    
