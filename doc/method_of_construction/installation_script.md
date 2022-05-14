# Method of constructing installation scripts

This document describes the method of constructing installation scripts of `download_archive.sh`, `download_src.sh`, `install_archive.sh`, `install_src.sh`, `is_installed.sh` and `packages_cpm.txt` with a concrete example.

### The steps of constructing `packages_cpm.txt` file
1. Choose the base script  
   Constructing these scripts from scratch can be laborious. Check the existing `cpm/packages/<architecture>/<libName>` and see them.
   - <u>Case 1: The archive file for installation is over 100MB. And the archive file to download is split to multiple files.</u>  
     See `cpm/packages/amd64/gcc/12.1.0` to refer
   - <u>Case 2: The archive file for installation is not over 100MB. And the archive file to download is Not split to multiple files.</u>  
     See `cpm/packages/amd64/sstd/2.0.1` to refer
   - <u>Case 3: Use the latest source code from the internet</u>  
     See `cpm/packages/amd64/sstd/latest` to refer. (This installation scripts downloads the source code from the latest commit of `sstd` main branch and compiles `sstd` and installs `sstd` to `cpm_env/local`).

1. Make `download_src.sh` file
   1. Copy `init_path.sh`
   1. Make directory of library name under the `cpm/packages/<architecture>/`.
      ```
      cd cpm/packages/<architecture>/
      mkdir <libName>
      ```
1. Make `packages_cpm.txt` file
1. Make `install_src.sh` file
1. Make `is_installed.sh` file
1. Run cpm/exe and ... modifying xxx
1. Run cpm/exe and generate archive files
1. Upload archive files
1. Make `download_archive.sh` file
   1. Copy `common_fn.sh`
1. Make `install_archive.sh` file
   1. Copy `common_fn_envDependents.sh`



