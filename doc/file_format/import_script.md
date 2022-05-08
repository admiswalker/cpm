# File descriptions of import scripts
CPM requires `download_installation_scripts.sh` (hereinafter referred to as an import script) as a CPM import script.

## Available environment values
When CPM calls installation scripts, CPM sets a environment value of `$CPM_CACHE_DIR`.
This environment value is passed as relative path so that the Docker container can solve the path from the container's root.

## File name and its Description
### `download_installation_scripts.sh`
downloads installation scripts in the `$CPM_CACHE_DIR`.
This script must download all of depending scripts.
For example, `download_archive.sh`, `download_src.sh`, `install_archive.sh`, `install_src.sh`, `is_installed.sh`, `packages_cpm.txt` and the other files of depending files.

NOTE: As a general rule, do not use scripts under the cpm directory and download all necessary scripts to avoid the effects of unexpected file changes.

### File examples
See [github.com/admiswalker/CPM_libExample_to_IMPORT/ ~ /download_installation_scripts.sh](https://github.com/admiswalker/CPM_libExample_to_IMPORT/blob/main/cpm_import/script/0.1.0/download_installation_scripts.sh).
