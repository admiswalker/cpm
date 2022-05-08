# File descriptions of installation scripts

CPM requires `download_archive.sh`, `download_src.sh`, `install_archive.sh`, `install_src.sh`, `is_installed.sh` and `packages_cpm.txt` (hereinafter referred to as an installation scripts) as CPM installation scripts.

This section describes these file organization.
<!-- To check the order of file usage refers to [CPM data flow](../cpm_data_flow.md). -->

## Available environment values
When CPM calls installation scripts, CPM sets environment values of `$CPM_CACHE_DIR`, `$CPM_BUILD_DIR`, `$CPM_DLIB_PATH`, `$CPM_INST_WDIR` and `$CPM_INST_PATH`.
These environment values are passed as relative paths so that the Docker container can solve the path from the container's root.
Some libraries require an absolute path during installation, so it is recommended that you convert the relative path to an absolute path in your build environment before installing the library.

## File name and its Description
### `download_archive.sh`
downloads archive files for installation by archive extracting.

### `download_src.sh`
downloads source files for installation with source building.

### `install_archive.sh`
extracts archive file and installs in the `cpm_env/local_work` directory.

The installation script must install the package in the temporary directory of `cpm_env/local_work` to ensure that the processe of building the package and the process of generating the installation archive follow the same path.

### `install_src.sh`
builds source file and installs in the `cpm_env/local_work` directory.

The installation script must install the package in the temporary directory of `cpm_env/local_work` to ensure that the processe of building the package and the process of generating the installation archive follow the same path.

### `is_installed.sh`
is used from the CPM to ensure that the library is installed.

### `packages_cpm.txt`
is used to define dependent files for installation.
The CPM checks this `packages_cpm.txt` file and solve the dependencies.

### File examples
See [cpm/packages](../../cpm/packages/).
