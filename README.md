# CPM (Cpp Package Manager)

CPM is a toy package manager for C++.

## Usage
1. Set required packages to `packages_cpm.txt`
2. Run installation commands
   ```
   ./cpm/cpm.exe
   ```
   options:
   - a: Set `true` or `false` to switch whether generagte packages archive or not. (Default is `false`)
   - b: Set installation directory (`BUILD_DIR`). (Default setting is `./env_cpm/build`)
   - i: Set installation path (`INST_PATH`). (Default setting is `./env_cpm/local`)
   - p: Set path to the package list. (Default setting is `./packages_cpm.txt`)
3. Set environmental variables
   ```
   source ./cpm/set_env.sh
   ```
   Note: Whenever you use cpm, you needs to run `./cpm/set_env.sh` before running what you want.
4. Run what you want.  
   Ex:
   ```
   echo -e '#include <iostream>\n\nint main(){\n    std::cout << "Hello CPM!" << std::endl;\n    return 0;\n}' >> main.cpp
   g++ main.cpp
   ./a.out
   ```

## File and Directory descriptions

| File or directory name        | Description Origin |
| ----------------------------- | ------------------ |
| cpm/                          | Files that make up CPM |
| cpm/packages/                 | Installation scripts for CPM packages |
| cpm/cpm.exe                   | Entry point of CPM. (Build from `cpm/main.cpp`) |
| cpm/main.cpp                  | Entry point of CPM |
| env_cpm/                      | Default destination path of CPM |
| env_cpm/archive/              | Destination directory to archive package files of installation packages with running `./cpm/cpm.exe` using `a` option |
| env_cpm/build/                | Temporary directory for build |
| env_cpm/cache/                | Cache directory for installation files to download |
| env_cpm/local/                | Destination directory for installation |
| env_cpm/local_archive/        | Temporary directory for generate archive |
| test/                         | Test files for programming installation scripts |
| .git/                         | git files          |
| Makefile                      | Makefile to build `./cpm/main.cpp` |
| READMD.md                     | This file          |
| packages_cpm.txt              | Packages list to install by `./cpm/cpm.exe` |
| .gitignore                    | Ignoring list not to track files on git |


## Build time

| build target | environment                                           | build time     |
| ------------ | ----------------------------------------------------- | -------------- |
| sstd-1.0.0   | 8 core, 32 GB / gcc-8.4.0 / Ubuntu 20.04 LTS          |  0 mins 20 sec |
| gcc-8.4.0    | 8 core, 32 GB / gcc-7.5.0 / Ubuntu 18.04 LTS (Docker) | 70 mins        |
| cmake-3.20.1 | 8 core, 32 GB / gcc-8.4.0 / Ubuntu 20.04 LTS          | 45 mins        |

Note. Building gcc and cmake may require a lot of memory. Using 32 or 64 GB RAM machine and adding a swap memory as insurance.


