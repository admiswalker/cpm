#include <algorithm>
#include <functional>
#include <iostream>

#include "dependency_graph_generator.hpp"
#include "definition.hpp"


bool cpm::operator<(const struct cpm::install_cmd& lhs, const struct cpm::install_cmd& rhs){
    return lhs.readOrder < rhs.readOrder;
}
bool cpm::operator>(const struct cpm::install_cmd& lhs, const struct cpm::install_cmd& rhs){
    return lhs.readOrder > rhs.readOrder;
}
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
std::string vStr2printStr(const std::vector<std::string>& v){
    std::string r;
    if(v.size()>=1){
        r += sstd::ssprintf("[ %s", v[0].c_str());
    }
    for(uint i=1; i<v.size(); ++i){
        r += sstd::ssprintf(", %s", v[i].c_str());
    }
    r += sstd::ssprintf(" ]");
    
    return r;
}

void add_defalutSettings(sstd::vec<uint>& vLineNum, sstd::vvec<std::string>& vLine, sstd::vec<std::string>& vFileName){
    // refresh the settings to the default whenever cpm read a new packages_cpm.txt
    vLineNum  <<= 0;
    vLine     <<= std::vector<std::string>({"INSTALL_MODE", "auto"});
    vFileName <<= std::string("cpm appends default setting");

    vLineNum  <<= 0;
    vLine     <<= std::vector<std::string>({"BUILD_ENV", "CPM_ENV"});
    vFileName <<= std::string("cpm appends default setting");
}
bool cpm::vLine2instGraph(std::unordered_map<std::string, struct install_cmd>& ret_table_reqPkg, const class cpm::PATH& p, const sstd::vec<uint>& vLineNum_in, const sstd::vvec<std::string>& vLine_in, const char* fileName){
    
    std::string build_env;
    std::string build_env_path;
    std::string install_mode;
    
    std::string architecture;

    sstd::vec<uint> vLineNum;
    sstd::vvec<std::string> vLine;
    sstd::vec<std::string> vFileName;
    add_defalutSettings(vLineNum, vLine, vFileName);
    
    if(vLineNum_in.size() != vLine_in.size()){ sstd::pdbg_err("vector size of \"vLineNum\" and \"vLine\" is not match.\n"); return false; }
    vLineNum  <<= vLineNum_in;
    vLine     <<= vLine_in;
    vFileName <<= sstd::vec<std::string>(vLine_in.size(), fileName);

    uint readOrder=0;
    for(uint i=0; i<vLine.size(); ++i, ++readOrder){
        const uint lineNum = vLineNum[i];
        const std::vector<std::string>& line = vLine[i];
        const std::string& fileName = vFileName[i];
        
        if(line[0]==cpm::cmd_ARCHITECTURE){
            if(line.size()!=2){ sstd::pdbg_err("The \"ARCHITECTURE\" command requires 1 args.\n"); return false; }
            
            architecture = line[1];
            
        }else if(line[0]==cpm::cmd_BUILD_ENV){
            build_env_path="";
            
            if(line.size()<2){
                sstd::pdbg_err("The \"BUILD_ENV\" command requires at least 1 arg.\n");
                sstd::pdbg_err("An error occured while reading the following line in the file:\n    FileName: \"%s\"\n    LineNum: %u\n    line: %s.\n", fileName.c_str(), lineNum, vStr2printStr(line).c_str());
                return false;
            }
            build_env = line[1];
            
            if      (line[1]==cpm::cmd_CPM_ENV   ){ // do nothing
            }else if(line[1]==cpm::cmd_DOCKER_ENV){ build_env_path = line[2];
                                                    std::string cmd;
                                                    cmd += "chmod +x "+build_env_path+"/docker_build.sh\n";
                                                    cmd += build_env_path+"/docker_build.sh\n";
                                                    sstd::system(cmd);
            }else if(line[1]==cpm::cmd_SYSTEM_ENV){ // do nothing
            }else{
                sstd::pdbg_err("Unexpected BUILD_ENV option.\n");
                sstd::pdbg_err("An error occured while reading the following line in the file:\n    FileName: \"%s\"\n    LineNum: %u\n    line: %s.\n", fileName.c_str(), lineNum, vStr2printStr(line).c_str());
                return false;
            }
            
        }else if(line[0]==cpm::cmd_IMPORT){
            if(line.size()!=4){ sstd::pdbg_err("The \"IMPORT\" command requires 3 args.\n"); return false; }
            
            std::string libName = line[1];
            std::string ver     = line[2];
            std::string URL     = sstd::stripAll(line[3], "\"");
            
            std::string cacheIptScr_dir = p.CACHE_DIR+"/import/"+libName+'/'+ver;
            std::string cachePkg_dir    = p.CACHE_DIR+"/packages/"+libName+'/'+ver;
            std::string packsPkg_dir    = p.PACKS_DIR + '/' + architecture + '/' + libName + '/' + ver;
            sstd::mkdir(cacheIptScr_dir);
            sstd::mkdir(cachePkg_dir);
            sstd::mkdir(packsPkg_dir);
            std::string dl_script = cacheIptScr_dir + '/' + sstd::getFileName( URL.c_str() );
            if(!sstd::fileExist(dl_script)){
                sstd::system("wget -P "+cacheIptScr_dir+' '+URL);
            }
            
            std::string cmd;
            cmd += "export CPM_CACHE_DIR=" + cachePkg_dir + '\n';
            cmd += "chmod +x " + dl_script + '\n';
            cmd += "./" + dl_script;
            sstd::system(cmd);
            sstd::cp(cachePkg_dir+"/*", packsPkg_dir, "pu");
            
        }else if(line[0]==cpm::cmd_INSTALL_MODE){
            if(line.size()!=2){ sstd::pdbg_err("The \"INSTALL_MODE\" command requires 1 args.\n"); return false; }
            if(! (line[1]==cpm::cmd_INSTALL_MODE_auto || line[1]==cpm::cmd_INSTALL_MODE_source || line[1]==cpm::cmd_INSTALL_MODE_archive) ){ sstd::pdbg_err("\"%s\" is unexpected INSTALL_MODE option.\n", line[1].c_str()); return false; }
            
            install_mode = line[1];
            
        }else{
            if(line.size()<2){
                sstd::pdbg_err("When specifing the library, version needs to be defined.\n");
                printf("  An error occured while reading the following line in the file:\n    FileName: \"%s\"\n    LineNum: %u\n    line: %s.\n", fileName.c_str(), lineNum, vStr2printStr(line).c_str());
                return false;
            }
            
            struct cpm::install_cmd ic;
            ic.readOrder      = readOrder;
            ic.build_env      = build_env;
            ic.build_env_path = build_env_path;
            ic.install_mode   = install_mode;
            ic.architecture   = architecture;
            ic.libName        = line[0];
            ic.vVer           = cpm::str2ver( line && sstd::slice(1, sstd::end()) );
            
            // check the library is on the table or not.
            auto itr = ret_table_reqPkg.find( ic.libName );
            if(itr!=ret_table_reqPkg.end()){
                bool tf;
                std::vector<cpm::ver> vVer = cpm::verAND(tf, ic.vVer, itr->second.vVer); // solve the range of version
                if(! tf ){
                    sstd::pdbg_err("cpm::verAND() is failed. An error occured while reading the following line in the file:\n  FileName: \"%s\"\n  LineNum: %u\n  line: %s.\n", fileName.c_str(), lineNum, vStr2printStr(line).c_str());
                    return false;
                }
                if(vVer.size()==0){
                    sstd::pdbg_err("cpm::verAND() is failed. An error occured while reading the following line in the file:\n  FileName: \"%s\"\n  LineNum: %u\n  line: %s.\n", fileName.c_str(), lineNum, vStr2printStr(line).c_str());
                    sstd::pdbg_err("The lib \"%s\" is required conflicting version. cpm::verAND() can't get version between %s and %s.\n", itr->first.c_str(), cpm::print_str(ic.vVer).c_str(), cpm::print_str(itr->second.vVer).c_str());
                    return false;
                }
                itr->second.vVer = vVer;
                continue;
            }
            
            // get available packages list
            std::vector<std::string> ret_vPath;
            std::vector<cpm::ver> ret_vVer;
            bool ret = cpm::get_available_pkg(ret_vPath, ret_vVer, p.PACKS_DIR, architecture, ic.libName);
            if(!ret){ sstd::pdbg_err("There is no available \"%s\" library.\n", ic.libName.c_str()); return false; }
            
            // get the latest package version of available packages
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
            ic.vVer = vVerAND;
            std::string latest_pkg_ver = vVerAND[vVerAND.size()-1].ver;

            // refresh the settings to the default whenever cpm read a new packages_cpm.txt
            add_defalutSettings(vLineNum, vLine, vFileName);
            
            // get dependent packages
            //   1. read packages_cpm.txt
            const std::string packsPkg_dir = cpm::getPath_packsPkgDir(p.PACKS_DIR, architecture, ic.libName, latest_pkg_ver);
            const std::string depPkg_txt = cpm::getTxt_depPkg(packsPkg_dir);
            //   2. Add the contents of packages_cpm.txt to stacks (vLine, vLineNum, vFileName).
            sstd::vec<uint> ret_vLineNum;
            sstd::vvec<std::string> ret_vLine;
            ret = sstd::txt2vCmdList(ret_vLineNum, ret_vLine, depPkg_txt);
            if(!ret){ sstd::pdbg_err("Failed to read %s.\n", depPkg_txt.c_str()); return false; }
            vLine     <<= ret_vLine;
            vLineNum  <<= ret_vLineNum;
            vFileName <<= std::vector<std::string>(ret_vLine.size(), depPkg_txt);
            //  3. registering dependent packages
            for(uint i=0; i<ret_vLine.size(); ++i){
                ic.depTbl[ ret_vLine[i][0] ];
            }
            
            // registering the package to the table
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
    if(!ret_tf){ sstd::pdbg_err("sstd::txt2vCmdList() is failed.\n"); return false; }

    std::string fileName = sstd::getFileName( packages_path );
    ret_tf = cpm::vLine2instGraph(ret_table_reqPkg, p, vLineNum, vLine, fileName.c_str());
    if(!ret_tf){ sstd::pdbg_err("packageTxt2instCmd() is failed.\n"); return false; }
    
    return true;
}


bool cpm::instGraph2instOrder(std::vector<cpm::install_cmd>& ret_vInst, const std::unordered_map<std::string, struct cpm::install_cmd>& table_reqPkg){

    std::vector<cpm::install_cmd> stack;
    std::unordered_map<std::string, bool> isInst;
    for(auto itr=table_reqPkg.begin(); itr!=table_reqPkg.end(); ++itr){
        stack <<= itr->second;
        isInst[ itr->first ] = false;
    }
    sstd::sort_gr(stack); // constrain the installation order by list (packages_cpm.txt) order
    
    while( stack.size()!=0 ){
        uint i = stack.size()-1;
        
        for(auto itr=stack[i].depTbl.begin(); itr!=stack[i].depTbl.end();){
            std::string libName = itr->first;
            
            if( isInst[ libName ] ){
                itr = stack[i].depTbl.erase( itr );
                continue;
            }
            
            auto itr_t = table_reqPkg.find( libName );
            stack <<= itr_t->second;
            ++itr;
        }

        if( stack[i].depTbl.size() == 0 ){
            auto itr_iI = isInst.find( stack[i].libName );
            if(! itr_iI->second ){
                itr_iI->second = true;
                ret_vInst <<= stack[i];
            }
            stack.erase(stack.begin()+i);
        }
    }
    
    return true;
}

    
