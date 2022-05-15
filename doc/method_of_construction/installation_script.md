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
   ```sh
   cd <prj>/cpm/packages/<architecture>/
   mkdir <libName>
   ```
   NOTE: In this document, \<prj\> is a project directory.
1. Copy `common_fn.sh`, `common_fn_envDependents.sh`, `download_archive.sh`, `download_src.sh`, `init_path.sh`, `install_archive.sh`, `install_src.sh` and `is_installed.sh` files from the installation scripts directory of the referencing library.
   ```sh
   cd <prj>/cpm/packages/<architecture>/<libName of the referencing library>/
   cp common_fn.sh common_fn_envDependents.sh download_archive.sh download_src.sh init_path.sh install_archive.sh install_src.sh is_installed.sh ../<libName>
   ```
1. Make a blank `packages_cpm.txt` file and write the dependencies.
   ```sh
   cd <prj>/cpm/packages/<architecture>/<libName>
   touch packages_cpm.txt
   nano packages_cpm.txt  # write the dependencies
   ```
1. Edit `download_src.sh` file  
   The role of `download_src.sh` file is to download the source file and its hash file to the `CPM_CACHE_DIR` directory and to check the hash value of source file. The `CPM_CACHE_DIR` which is a environment variable is provided by cpm/exe. The user needs to edit the shell variables of `URL` and `URL_hash` at least. The user also need to edit `fName`, `fName_hash`, etc. as needed.
   ```sh
   cd <prj>/cpm/packages/<architecture>/<libName>
   nano download_src.sh  # edit `URL` and `URL_hash` for installation library
   ```
1. Edit `install_src.sh` file  
   The role of `install_src.sh` file is to unpack the archived source file to `CPM_BUILD_DIR` directory, to build source file and to install to `CPM_INST_WDIR` directory. The `CPM_INST_WDIR` which is a environment variable is provided by cpm/exe.
   ```sh
   cd <prj>/cpm/packages/<architecture>/<libName>
   nano install_src.sh  # edit installation process for installation library
   ```
   NOTE: Dependent libraries are installed in the `CPM_DLIB_PATH` directory. Not in `CPM_INST_WDIR`. The concrete path of `CPM_DLIB_PATH` directory is usually `cpm_env/local`, and the concrete path of `CPM_INST_WDIR` direcotry is usually `cpm_env/local_work`.
1. Edit `common_fn_envDependents.sh` for `is_installed.sh` file  
   The role of `is_installed.sh` file is to notify cpm/exe of the library's installation status. And the substance of the `is_installed.sh` file is in the `common_fn_envDependents.sh` file.

   The user needs to edit the shell function of `cfn_isInstalled()` in the `common_fn_envDependents.sh` file called from the `is_installed.sh` file.
   ```sh
   cd <prj>/cpm/packages/<architecture>/<libName>
   nano common_fn_envDependents.sh  # edit `cfn_isInstalled()` for installation library
   ```
1. Check the edited source installation script works correctly  
   1. Make a `packages_cpm.txt` file to check the edited installation script
      ```sh
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
      ```sh
      cd <prj>
      cpm/exe -p ./packages_cpm.txt
      ```

   **NOTE: If you are referencing the `Case 3` scripts, this is the end of the construction.**
1. Generate archive file for archive installation  
   1. Run cpm/exe with archive option
      ```sh
      cd <prj>
      cpm/exe -a true -p ./packages_cpm.txt
      ```
   1. Check the archive file is in `cpm_env/archive` directory
1. Upload the generated archive files and get its URL  
   Usually, uploading file is `<architecture>-<libName>-<version>-sha256sum.txt` and `<architecture>-<libName>-<version>.tar.xz`. When the file size is over 100 MB, cpm/exe also generates splitted archive file like `*.tar.xz-00`, `*.tar.xz-01`, ... `*.tar.xz-XX`. Upload the best file for your situation.
1. Edit `common_fn_envDependents.sh` for `download_archive.sh` file and `install_archive.sh` file  
   **About the `download_archive.sh` file**:  
   The role of `download_archive.sh` file is to download the archive file (`*.tar.xz`) and its hash file (`*-sha256sum.txt`) to the `CPM_CACHE_DIR` directory and to check the hash value of archive file. The `CPM_CACHE_DIR` which is a environment variable is provided by cpm/exe. A substance of the `download_archive.sh` file is in the `common_fn.sh` file and the configuration of the `download_archive.sh` file is in the `common_fn_envDependents.sh` file.
   
   The user needs to edit the shell function of `cfn_set_archive_URL()` in the `common_fn_envDependents.sh` file called from the `download_archive.sh` file.

   **About the `install_archive.sh` file**:  
   The role of `install_archive.sh` file is to unpack and install the archived source file to `CPM_INST_WDIR` directory. The `CPM_INST_WDIR` which is a environment variable is provided by cpm/exe.

   The user needs to edit the shell function of `cfn_set_archive_fName()` in the `common_fn_envDependents.sh` file called from the `install_archive.sh` file.
   ```sh
   cd <prj>/cpm/packages/<architecture>/<libName>
   nano common_fn_envDependents.sh  # edit `cfn_set_archive_URL()` and `cfn_set_archive_fName()` for installation library
   ```
1. Check the edited archive installation script works correctly  
   1. Make a `packages_cpm.txt` file to check the edited installation script
      ```sh
      cd <prj>
      echo -e 'ARCHITECTURE, <architecture>;' >> packages_cpm.txt
      echo -e 'INSTALL_MODE, archive;'        >> packages_cpm.txt
      echo -e 'BUILD_ENV, SYSTEM_ENV;'        >> packages_cpm.txt
      echo -e 'gcc, >=12.*.*;'                >> packages_cpm.txt
      echo -e 'BUILD_ENV, CPM_ENV;'           >> packages_cpm.txt
      echo -e '<libName>, ==<version>'        >> packages_cpm.txt
      ```
   1. Run cpm/exe
      ```sh
      cd <prj>
      cpm/exe -p ./packages_cpm.txt
      ```

## Publish a user-defined installation script using the IMPORT command
See [----]()
