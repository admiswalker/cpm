# CPM data flow

This document describes the specific data flow of CPM.

## 1) When installing packages

1. User run cpm/exe
1. cpm/exe reads `packages_cpm.txt`
1. cpm/exe initializes `cpm_env` directory and copy `cpm/packages` to `cpm_env/packages`
1. cpm/exe solves the dependent of installation packages on `packages_cpm.txt` reading the dependencies from `cpm_env/packages`. And when using the IMPORT command, the dependency information of `packages_cpm.txt` files are downloaded to the `cpm_env/cache/packages` directory and copy to the `cpm_env/packages` direcotry
1. cpm/exe downloads source files or archive files to `cpm_env/cache`
1. cpm/exe builds source files or unpacks archive files to `cpm_env/local_work`
1. cpm/exe replace paths of `*.la` files in `cpm_env/local_work` direcotry from `*/cpm_env/local` to `*/cpm_env/local_work`. (When the archive flag is enabled, cpm/exe archives the contents of the `cpm_env/local_work` directory).
1. cpm/exe move files from `cpm_env/local_work` directory to `cpm_env/local` directory
