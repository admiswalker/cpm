# Method of `packages_cpm.txt` file construction

This document describes the method of constructing `packages_cpm.txt` file with a concrete example.


### The steps of constructing `packages_cpm.txt` file
1. Set architecture like `ARCHITECTURE, amd64;`.
2. Set build environment like `BUILD_ENV, CPM_ENV;`, `BUILD_ENV, SYSTEM_ENV;` or `BUILD_ENV, DOCKER_ENV, ./cpm/build_env/docker/ubuntu18.04_for_build_gcc;`.
3. Set installation mode like `INSTALL_MODE, source;`, `INSTALL_MODE, archive;` or `INSTALL_MODE, auto;`
4. Set installing packages that you want.

## Ex. 1) Build and archive the gcc compiler (build all libraries)
When building the libraries from source file, set `INSTALL_MODE, source;`.

- <u>**sample/packages_cpm_00.txt**</u>
  ```
  ARCHITECTURE, amd64;
  BUILD_ENV, DOCKER_ENV, ./cpm/build_env/docker/ubuntu18.04_for_build_gcc;
  
  INSTALL_MODE, source;
  m4, ==1.4.15;
  gmp, ==6.1.0;
  mpfr, ==3.1.4;
  mpc, ==1.0.3;
  isl, ==0.18;
  gcc, ==12.1.0;
  ```
- run `sample/packages_cpm_00.txt`
  ```
  cpm/exe -p sample/packages_cpm_00.txt
  ```

## Ex. 2) Build and archive the gcc compiler (build only gcc)
To change the installation mode within the same `packages_cpm.txt`, set `INSTALL_MODE` once more. (About the scopy of `INSTALL_MODE`, see [INSTALL_MODE](../file_format/packages_cpm.txt.md))

- <u>**sample/packages_cpm_02.txt**</u>
  ```
  ARCHITECTURE, amd64;
  BUILD_ENV, DOCKER_ENV, ./cpm/build_env/docker/ubuntu18.04_for_build_gcc;
  
  INSTALL_MODE, archive;
  m4, ==1.4.15;
  gmp, ==6.1.0;
  mpfr, ==3.1.4;
  mpc, ==1.0.3;
  isl, ==0.18;
  
  INSTALL_MODE, source;
  gcc, ==12.1.0;
  ```
- run `sample/packages_cpm_02.txt`
  ```
  cpm/exe -p sample/packages_cpm_02.txt
  ```

## Ex. 3) Use gcc compiler as a base environment and install user requiring libraries
When building a gcc-based environment, first set the gcc archive, then set the required libraries.
### Case A: Specifying the version
- <u>**sample/packages_cpm_03a.txt**</u>
  ```
  ARCHITECTURE, amd64;
  BUILD_ENV, CPM_ENV;
  INSTALL_MODE, auto;
  
  /*
   * set gcc as a base environmet
   */
  gcc, ==12.1.0;
  
  /*
   * install what you want
   */
  cmake, ==3.*.*;
  googletest, ==1.*.*;
  ```
- run `sample/packages_cpm_03a.txt`
  ```
  cpm/exe -p sample/packages_cpm_03a.txt
  ```
### Case B: Not specifying the version
In this case, the latest versions of `cmake` and `googletest` among the matching versions of each library will be installed.
- <u>**sample/packages_cpm_03b.txt**</u>
  ```
  ARCHITECTURE, amd64;
  BUILD_ENV, CPM_ENV;
  INSTALL_MODE, auto;
  
  /*
   * set gcc as a base environmet
   */
  gcc, ==12.1.0;
  
  /*
   * install what you want
   */
  cmake;
  googletest;
  ```
- run `sample/packages_cpm_03b.txt`
  ```
  cpm/exe -p sample/packages_cpm_03b.txt
  ```
