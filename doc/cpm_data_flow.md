# CPM data flow

This document describes the specific data flow of CPM.

## 1) When installing packages

1. cpm/exe reads `packages_cpm.txt`
2. cpm/exe initialozes `cpm_env` directory and copy `cpm/packages` to `cpm_env/packages`
3. cpm/exe solves the dependent of installation packages on `packages_cpm.txt` reading the dependencies from `cpm_env/packages`. And IMPORT dependent packages to cache

