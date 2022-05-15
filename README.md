# CPM (C++ Package Manager)

CPM is a toy package manager for C++, works on Ubuntu OS, without using `sudo` (root privileges).

NOTE: Every time CPM users should check the safety of installation scripts and packages at their own risk.

## File and Directory descriptions

| File or directory name        | Description Origin |
| ----------------------------- | ------------------ |
| cpm/                          | Files that make up the CPM |
| cpm/build_env/docker/         | Dockerfile to build gcc and generate gcc archives |
| cpm/packages/                 | Installation scripts for the CPM packages |
| cpm/src/                      | Source files for the CPM |
| cpm/test/                     | Test files for the CPM |
| cpm/Makefile                  | Makefile to build `cpm/main.cpp` and `cpm/main_test.cpp` |
| cpm/SubStandardLibrary-SSTD--master.zip | Depending library |
| cpm/exe                       | Entry point of the CPM. (Build from `cpm/main.cpp`) |
| cpm/exe_test                  | Entry point of the tests. (Build from `cpm/main_test.cpp`) |
| cpm/googletest-master.zip | Depending library |
| cpm/main.cpp                  | Entry point of the CPM |
| cpm/main_test.cpp             | Entry point of the tests for the functions at `cpm/src/` |
| cpm_env/                      | Default destination path of the CPM |
| cpm_env/archive/              | Destination directory to archive package files of installation packages with running `cpm/exe` using `a` option |
| cpm_env/build/                | Temporary directory for build |
| cpm_env/cache/                | Cache directory for installation files to download |
| cpm_env/local/                | Destination directory for installation |
| cpm_env/local_work/           | Temporary directory for installation |
| doc/                          | Documents |
| .git/                         | git files          |
| LICENSE                       | License file |
| Makefile                      | Makefile to call `cpm/Makefile` |
| READMD.md                     | This file          |
| packages_cpm.txt              | Packages list to install by `cpm/exe` |
| .gitignore                    | Ignoring list not to track files on git |

## Initial setting
### Installing CPM in your project direcotry
1. Download the CPM
   ```
   git clone git@github.com:admiswalker/cpm.git
   ```
2. Build CPM
   ```
   cd cpm
   make
   ```
   NOTE: Building CPM requires build-essential at least.
3. Copy all of under cpm to \<Your project directory\>
   ```
   cp -ra cpm <Your project directory>
   ```

### Docker engine installation
When using `DOCKER_ENV` option in `BUILD_ENV` command in the `packages_cpm.txt` file, docker engine should be installed in the local system.

NOTE: Installing docker engine requires that you have `sudo` (root privileges).
If you don't have `sudo`, you should get the privileges, request your system admin to install docker engine, or avoid using the `DOCKER_ENV` option.

[docker engine installation](./doc/docker.md)

## Usage
### Local package installation (Online installation)
1. Set requiring packages to `packages_cpm.txt`  
   `packages_cpm.txt` is a file to request install packages to CPM. The command needs to split by `,` and end by `;`. And comments rules of `//` and `/* ~ */` are available. For more information, see [packages file format](./doc/file_format/packages_cpm.txt.md).

   A example of `packages_cpm.txt`:
   ```
   ARCHITECTURE, amd64; // must define
   INSTALL_MODE, auto; // select `src`, `archive` or `auto`.
   BUILD_ENV, SYSTEM_ENV; // select `SYSTEM_ENV`, `CPM_ENV` or `DOCKER_ENV`.
   
   /*
    * select base compiler in order not to depend on local system compiler
    * As a default, gcc 7.5.0, 8.4.0, 9.4.0, 10.3.0 and 11.2.0 are defined at `cpm/cpm/packages/amd64/gcc`
    */
   gcc, >=11.*.*;
   
   /*
    * select installation environment which is initialized at above line
    */
   BUILD_ENV, CPM_ENV;
   
   /*
    * CPM user can install packages defined at `cpm/cpm/packages/`.
    */
   sstd, ==2.*.*;
   googletest; // Without specifying the version, the latest version among the matching versions will be installed.
   
   /*
    * CPM user can install packages using user defined installation scripts on the Internet.
    * NOTE: Users should check the safety of installation scripts and packages at their own risk.
    */
   IMPORT, CPM_libExample_to_IMPORT, 0.1.0, "https://github.com/admiswalker/CPM_libExample_to_IMPORT/raw/main/cpm_import/script/0.1.0/download_installation_scripts.sh";
   CPM_libExample_to_IMPORT, ==0.1.0;
   ```
2. Install packages on `packages_cpm.txt` to your local project directory
   ```
   cpm/exe
   ```
   Options:
   - -a: a flag to switch whether generagte packages archive or not. This option can take `true` or `false` and the default setting is `false`.
   - -b: Set base directory for the CPM environment. `CACHE_DIR`, `PACKS_DIR`, `BUILD_DIR`, `INST_WDIR`, `INST_PATH` and `ACV_DIR` are generated under base directory. (Default setting is `./cpm_env`)
   - -c: a flag to select whether only download installation requirements to cache and not installing packages or not. This option can take `true` or `false` and the default setting is `false`.
   - -p: a path to the package list. The default setting is `./packages_cpm.txt`.
   
   Note: 
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
### Local package installation (Offline installation)

An online machine is required for offline installation.
First, download the required packages to your online machine.
Then copy the CPM containing the downloaded package files to your offline machine.
Finally, run the CPM installation process.

1. Set requiring packages to `packages_cpm.txt`. (Same as the online installation)
2. Download source and archive files
   ```
   Online-machine$ cpm/exe -c ture
   ```
3. Copy files from online machine to the offline machine
   1. Copy files from online machine to USB flash drive or something similar
      ```
      Online-machine$ cp -ra cpm <USB flash drive>
      Online-machine$ cp -ra cpm_env <USB flash drive>
      ```
      The `cpm` directory contains CPM binary files and dependent files. The `cpm_env` direcotry contains `cpm_env/cache/` direcotry where the source and archive files are collected.
   2. Copy files from USB flash drive to offline machine
      ```
      Offline-machine$ cp -ra <USB flash drive>/cpm <Project directory>
      Offline-machine$ cp -ra <USB flash drive>/cpm_env <Project directory>
      ```
4. Install packages on `packages_cpm.txt` to your local project directory. (Same as the online installation)  
5. Set environmental variables. (Same as the online installation)
6. Run what you want. (Same as the online installation)

## File descriptions and their method of construction
- Packages file (`packages_cpm.txt`)
  - [file descriptions](./doc/file_format/packages_cpm.txt.md)
  - [method of construction](./doc/method_of_construction/packages_cpm.txt.md)
- Installation scripts (`download_archive.sh`, `download_src.sh`, `install_archive.sh`, `install_src.sh`, `is_installed.sh`, `packages_cpm.txt`)
  - [file descriptions](./doc/file_format/installation_script.md)
  - [method of construction](./doc/method_of_construction/installation_script.md)
- Import script for `IMPORT` command (`download_installation_scripts.sh`)
  - [file descriptions](./doc/file_format/import_script.md)
  - [method of construction](./doc/method_of_construction/import_script.md)

## Internal process of CPM
### Data flow
See [CPM data flow](./doc/cpm_data_flow.md)
### Version processing
See [Version comparison specifications](./doc/ver_comp_specifications.md)

## Archived libraries
See [Default archived libraries for CPM](./doc/archived_lib.md)

## License
MIT (See [license file](./LICENSE))
