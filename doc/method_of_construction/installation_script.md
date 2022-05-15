# Method of constructing installation scripts

This document describes the method of constructing installation scripts of `download_archive.sh`, `download_src.sh`, `install_archive.sh`, `install_src.sh`, `is_installed.sh` and `packages_cpm.txt` with a concrete example.

## The steps of constructing installation scripts
1. Choose the base script  
   Constructing these scripts from scratch can be laborious. Check the existing `cpm/packages/<architecture>/<libName>` and see them.
   - <u>Case 1: The archive file for installation is over 100MB. And the archive file to download is split to multiple files.</u>  
     See `cpm/packages/amd64/gcc/12.1.0` to refer
   - <u>Case 2: The archive file for installation is not over 100MB. And the archive file to download is Not split to multiple files.</u>  
     See `cpm/packages/amd64/sstd/2.0.1` to refer
   - <u>Case 3: Use the latest source code from the internet</u>  
     See `cpm/packages/amd64/sstd/latest` to refer. (This installation scripts downloads the source code from the latest commit of `sstd` main branch and compiles `sstd` and installs `sstd` to `cpm_env/local`).

1. Make base directory for installation scripts
   ```
   cd <prj>/cpm/packages/<architecture>/
   mkdir <libName>
   ```
   NOTE: In this document, \<prj\> is a project directory.
1. Copy `common_fn.sh`, `common_fn_envDependents.sh`, `download_archive.sh`, `download_src.sh`, `init_path.sh`, `install_archive.sh`, `install_src.sh` and `is_installed.sh` files from the installation scripts directory of the referencing library.
   ```
   cd <prj>/cpm/packages/<architecture>/<libName of the referencing library>/
   cp common_fn.sh common_fn_envDependents.sh download_archive.sh download_src.sh init_path.sh install_archive.sh install_src.sh is_installed.sh ../<libName>
   ```
1. Make a blank `packages_cpm.txt` file and write the dependencies.
   ```
   cd <prj>/cpm/packages/<architecture>/<libName>
   touch packages_cpm.txt
   nano packages_cpm.txt  # write the dependencies
   ```
1. Edit `download_src.sh` file  
   The role of `download_src.sh` file is to download the source file and its hash file to the `CPM_CACHE_DIR` directory and to check the hash value of source file. The `CPM_CACHE_DIR` which is a environment variable is provided by cpm/exe. The user needs to edit the shell variables of `URL` and `URL_hash` at least. The user also need to edit `fName`, `fName_hash`, etc. as needed.
   ```
   cd <prj>/cpm/packages/<architecture>/<libName>
   nano download_src.sh  # edit `URL` and `URL_hash` for installation library
   ```
1. Edit `install_src.sh` file  
   The role of `install_src.sh` file is to unpack the archived source file to `CPM_BUILD_DIR` directory, to build source file and to install to `CPM_INST_WDIR` directory.
   ```
   cd <prj>/cpm/packages/<architecture>/<libName>
   nano install_src.sh  # edit installation process for installation library
   ```
   NOTE: Dependent libraries are installed in the `CPM_DLIB_PATH` directory. Not in `CPM_INST_WDIR`. The concrete path of `CPM_DLIB_PATH` directory is usually `cpm_env/local`, and the concrete path of `CPM_INST_WDIR` direcotry is usually `cpm_env/local_work`.
1. Edit `common_fn_envDependents.sh` for `is_installed.sh` file  
   The role of `is_installed.sh` file is to notify cpm/exe of the library's installation status. And the substance of the `is_installed.sh` file is in the `common_fn_envDependents.sh` file.

   The user needs to edit the shell function of `cfn_isInstalled()` in the `common_fn_envDependents.sh` file called from the `is_installed.sh` file.
   ```
   cd <prj>/cpm/packages/<architecture>/<libName>
   nano common_fn_envDependents.sh  # edit `cfn_isInstalled()` for installation library
   ```
1. Check the edited installation script works correctly  
   1. Make a `packages_cpm.txt` file to check the edited installation script
      ```
      cd <prj>
      echo -e 'ARCHITECTURE, <architecture>;' >> packages_cpm.txt
      echo -e 'INSTALL_MODE, archive;'        >> packages_cpm.txt
      echo -e 'BUILD_ENV, SYSTEM_ENV;'        >> packages_cpm.txt
      echo -e 'gcc, >=12.*.*;'                >> packages_cpm.txt
      echo -e 'INSTALL_MODE, source;'         >> packages_cpm.txt
      echo -e 'BUILD_ENV, CPM_ENV;'           >> packages_cpm.txt
      echo -e '<libName>, ==<version>'        >> packages_cpm.txt
      ```
   1. Run cpm/exe
      ```
      cd <prj>
      cpm/exe -p ./packages_cpm.txt
      ```

   **NOTE: If you are referencing the `Case 3` scripts, this is the end of the construction.**
1. Generate archive file for archive installation  
   Run cpm/exe with archive option
   ```
   cd <prj>
   cpm/exe -a true -p ./packages_cpm.txt
   ```
1. Run cpm/exe and ... modifying xxx
1. Run cpm/exe and generate archive files
1. Upload archive files
1. Make `download_archive.sh` file
   1. Copy `common_fn.sh`
1. Make `install_archive.sh` file
   1. Copy `common_fn_envDependents.sh`

## Publish a user-defined installation script using the IMPORT command
See [----]()
