# `packages_cpm.txt` file

The `packages_cpm.txt` file is used to indicate the libraries that user will install or to indicate the dependent libraries of the installation library.

## File format
The command needs to split by `,` and end by `;`.
A string up to the first comma is a command or library name. And the character string after that is

exapmle:
```
<command or libName>, [arg1], [arg2], ...;
```

Comments rules of `//` and `/* ~ */` are available.

exapmle:
```
// comments

/*
comments
*/
```

## Commands for `packages_cpm.txt` file

### <u>ARCHITECTURE</u>
#### NAME
ARCHITECTURE - set an architecture of installation libraries
#### SYNOPSIS
ARCHITECTURE \<architecture\>
#### DESCRIPTION
ARCHITECTURE is a initialization command to set architecture name.
Architecture name is used to identifying architecture, for example in the packages directory, in the cache file name, archive directory, archive file, and so on.

NOTE: ARCHITECTURE should be defined at the beginning of the `packages_cpm.txt` file in order to seek the package directory.
#### EXAMPLES
```
ARCHITECTURE, amd64;
```
#### SEE ALSO
―――.

### <u>BUILD_ENV</u>
#### NAME
BUILD_ENV - set an environment for build source file or extracting archive file
#### SYNOPSIS
BUILD_ENV \<<em>CPM_ENV|DOCKER_ENV|SYSTEM_ENV</em>\> [<em>directory-path-to-the-dependent-files</em>]
#### DESCRIPTION
- CPM_ENV (Default setting)  
  Libraries and compilers under `cpm_env/local` are used because of the environment value is set to `cpm_env/local`
- DOCKER_ENV  
  Docker environment defined by the argument is used. 
  The user must set the directory PATH to the dependent files of `docker_base_path.txt`, `docker_build.sh` and `docker_run.sh` in the 1st argument.
- SYSTEM_ENV  
  System defined libraries and compilers are used. (The environment value is not changed).
#### EXAMPLES
- set CPM_ENV  
  ```
  BUILD_ENV, CPM_ENV;
  ```
- set DOCKER_ENV
  ```
  BUILD_ENV, DOCKER_ENV, cpm/build_env/docker/ubuntu18.04_for_build_gcc;
  ```
- set SYSTEM_ENV
  ```
  BUILD_ENV, SYSTEM_ENV;
  ```
#### SEE ALSO
―――.

### <u>IMPORT</u>
#### NAME
IMPORT - set a URL of the user defined downloading script to download user defined installation script.
#### SYNOPSIS
IMPORT \<<em>libName-using-in-the-packages_cpm.txt</em>\> \<<em>lib-version</em>\> \<<em>URL-to-the-downloading-script</em>\>
#### DESCRIPTION
IMPORT command is downloading user defined library which is not defined by CPM package directory.
1st argument defines library name using in the `packages_cpm.txt`. 2nd argument defines a URL to the downloading script to download installation scripts.

CPM downloads scripts using wget command and the URL must be public.
While the IMPORT command is convenient to supply user defined libraries, library user needs to check the safety of installation scripts and packages at their own risk.
#### EXAMPLES
```
IMPORT, CPM_libExample_to_IMPORT, 0.1.0, "https://github.com/admiswalker/CPM_libExample_to_IMPORT/raw/main/cpm_import/script/0.1.0/download_installation_scripts.sh";
```
#### SEE ALSO
―――.

### <u>INSTALL_MODE</u>
#### NAME
INSTALL_MODE - set installation source.
#### SYNOPSIS
INSTALL_MODE \<<em>archive|auto|source</em>\>
#### DESCRIPTION
- archive  
  uses archive file (built binary) to install.
- auto (Default setting)  
  tries to use `archive` at first, and if `archive` is not found, use source file at second.
  tries to use `archive` at first. If `archive` is not found, use the source file second.
- source  
  uses source file to install and build on the system. Build environment is defined by `BUILD_ENV` command.
#### EXAMPLES
- archive
  ```
  INSTALL_MODE, archive;
  ```
- auto
  ```
  INSTALL_MODE, auto;
  ```
- source
  ```
  INSTALL_MODE, source;
  ```
#### SEE ALSO
―――.
