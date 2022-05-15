# Method of constructing scripts for IMPORT command
This document describes the method of constructing scripts of `download_installation_scripts.sh` for IMPORT command with a concrete example.

## The steps of constructing scripts for IMPORT command

The role of `download_installation_scripts.sh` file is to download the installation files (`common_fn.sh`, `common_fn_envDependents.sh`, `download_archive.sh`, `download_src.sh`, `init_path.sh`, `install_archive.sh`, `install_src.sh`, `is_installed.sh` and `packages_cpm.txt`) to the `CPM_CACHE_DIR` directory. The `CPM_CACHE_DIR` which is a environment variable is provided by cpm/exe. 

1. Copy [download_installation_scripts.sh](https://github.com/admiswalker/CPM_libExample_to_IMPORT/blob/main/cpm_import/script/0.1.0/download_installation_scripts.sh) and edit for your installation library
1. Upload the `download_installation_scripts.sh` file to a location where the cpm/exe can download using `wget` command
