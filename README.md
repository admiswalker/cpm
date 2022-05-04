# CPM (C++ Package Manager)

CPM is a toy package manager for C++.

## Usage
### Setting
#### Local package installation
1. Set requiring packages to `packages_cpm.txt`  
   example:
   ```
   ```
2. Run installation commands
   ```
   cpm/exe
   ```
   options:
   - -a: a flag to switch whether generagte packages archive or not. This option can take `true` or `false` and the default setting is `false`.
   - -b: Set base directory for CPM environment. `CACHE_DIR`, `PACKS_DIR`, `BUILD_DIR`, `INST_WDIR`, `INST_PATH` and `ACV_DIR` are generated under base directory. (Default setting is `./cpm_env`)
   - -c: a flag to select whether only download installation requirements to cache and not installing packages or not. This option can take `true` or `false` and the default setting is `false`.
   - -p: a path to the package list. The default setting is `./packages_cpm.txt`.
   
   Note: 
   - Running `cpm_env/local/set_env.sh` set environmental variables.
   - Whenever the base directory of the CPM environment changes, the user should run `cpm_env/local/init.sh` to solve the path dependency of installed packages.
3. Set environmental variables
   1. Running a script to set environmental variables
      ```
      source cpm_env/local/set_env.sh
      ```
   2. Make sure the environment variables are valid by checking the installed packages are valid
      ```
      gcc --version
      ```
4. Run what you want  
   example:
   1. Generate a main.cpp file
      ```
      echo -e '#include <iostream>'                                                 >> main.cpp
      echo -e 'int main(){'                                                         >> main.cpp
      echo -e '    std::cout << "Hello CPM!" << std::endl;'                         >> main.cpp
      echo -e '    std::cout << "GCC version is " << __GNUC__ << "." << std::endl;' >> main.cpp
      echo -e '    return 0;'                                                       >> main.cpp
      echo -e '}'                                                                   >> main.cpp
      ```
   2. Compile the main.cpp file
      ```
      g++ main.cpp
      ```
   3. Run generated binary
      ```
      ./a.out
      ```

#### Docker engine installation
When using `DOCKER_ENV` option in `BUILD_ENV` command in the `packages_cpm.txt` file, docker engine should be installed in the local system.

NOTE: Installing docker engine requires that you have `sudo` (root privileges).
If you don't have `sudo`, you should get the privileges, request your system admin to install docker engine, or avoid using the `DOCKER_ENV` option.

[docker engine installation](./doc/docker.md)

## File and Directory descriptions

| File or directory name        | Description Origin |
| ----------------------------- | ------------------ |
| cpm/                          | Files that make up CPM |
| cpm/packages/                 | Installation scripts for CPM packages |
| cpm/exe                       | Entry point of CPM. (Build from `cpm/main.cpp`) |
| cpm/main.cpp                  | Entry point of CPM |
| env_cpm/                      | Default destination path of CPM |
| env_cpm/archive/              | Destination directory to archive package files of installation packages with running `./cpm/exe` using `a` option |
| env_cpm/build/                | Temporary directory for build |
| env_cpm/cache/                | Cache directory for installation files to download |
| env_cpm/local/                | Destination directory for installation |
| env_cpm/local_archive/        | Temporary directory for generate archive |
| test/                         | Test files for programming installation scripts |
| .git/                         | git files          |
| Makefile                      | Makefile to build `./cpm/main.cpp` |
| READMD.md                     | This file          |
| packages_cpm.txt              | Packages list to install by `./cpm/exe` |
| .gitignore                    | Ignoring list not to track files on git |


## Build time

| build target | environment                                           | build time     |
| ------------ | ----------------------------------------------------- | -------------- |
| sstd-1.0.0   | 8 core, 32 GB / gcc-8.4.0 / Ubuntu 20.04 LTS          |  0 mins 20 sec |
| gcc-8.4.0    | 8 core, 32 GB / gcc-7.5.0 / Ubuntu 18.04 LTS (Docker) | 70 mins        |
| cmake-3.20.1 | 8 core, 32 GB / gcc-8.4.0 / Ubuntu 20.04 LTS          | 45 mins        |

Note. Building gcc and cmake may require a lot of memory. Using 32 or 64 GB RAM machine and adding a swap memory as insurance.


