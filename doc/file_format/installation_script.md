# File organization of installation scripts

CPM requires `download_archive.sh`, `download_src.sh`, `install_archive.sh`, `install_src.sh`, `is_installed.sh` and `packages_cpm.txt` (hereinafter referred to as an installation scripts) as CPM installation scripts.

This section describes these file organization.
To check the order of file usage refers to [CPM data flow](../cpm_data_flow.md).

## Available environment values

When CPM calls installation scripts, CPM sets environment values of `$CPM_CACHE_DIR`, `$CPM_BUILD_DIR`, `$CPM_DLIB_PATH`, `$CPM_INST_WDIR` and `$CPM_INST_PATH`. These 



// When using Docker, the absolute path is determined at run time.

## File name and its Description
### `download_archive.sh`
### `download_src.sh`
### `install_archive.sh`
### `install_src.sh`
### `is_installed.sh`
### `packages_cpm.txt`
