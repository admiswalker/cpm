# Method of `packages_cpm.txt` file construction

This document describes the method of `packages_cpm.txt` file construction with a concrete example.


## Ex. 1) Build and archive the gcc compiler (build all libraries)
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

## Ex. 2) Build and archive the gcc compiler (build only gcc)
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

## Ex. 3) Use gcc compiler as a base environment and install user requiring libraries
```
gcc, ==12.1.0; // dependents: gmp, mpfr, mpc, isl
```


## Appendix


### Archive files of libraries
#### Archive files
##### Repository
[cpm_archive](https://github.com/admiswalker/cpm_archive)
##### Compression format and its compression ratio
tar.gz, zip, ...


#### Build time
| build target | environment                                           | build time     |
| ------------ | ----------------------------------------------------- | -------------- |
| sstd-1.0.0   | 8 core, 32 GB / gcc-8.4.0 / Ubuntu 20.04 LTS          |  0 mins 20 sec |
| gcc-8.4.0    | 8 core, 32 GB / gcc-7.5.0 / Ubuntu 18.04 LTS (Docker) | 70 mins        |
| cmake-3.20.1 | 8 core, 32 GB / gcc-8.4.0 / Ubuntu 20.04 LTS          | 45 mins        |

Note. Building gcc and cmake may require a lot of memory. In this case, we recommend to use 32 or 64 GB RAM machine and adding a swap memory as insurance.