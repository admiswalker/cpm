#!/bin/bash


cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/gcc ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
cfn_check_hash_value(){
    if [[ $fName_hash == *"sha256"* ]]; then
	find $CPM_CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CPM_CACHE_DIR/$fName) >/dev/null 2>&1
	if [ ! $? = 0 ]; then
	    echo -e "\e[31mERROR: hash value of downloaded file is not match.\e[m"
	    exit -1
	fi
    elif [[ $fName_hash == *"sha512"* ]]; then
	find $CPM_CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha512sum $CPM_CACHE_DIR/$fName) >/dev/null 2>&1
	if [ ! $? = 0 ]; then
	    echo -e "\e[31mERROR: hash value of downloaded file is not match.\e[m"
	    exit -1
	fi
    else
	echo -e "\e[31mERROR: invalid hash file name.\e[m"
    fi
}
cfn_echo_download_begin(){
    local libName=$1
    local ver=$2
    
    title='download'
    begin_string='--- begin: '$title' '$libName'/'$ver' ------------------------------------------------------------------'
    echo ${begin_string:0:80}
}
cfn_echo_download_end(){
    local libName=$1
    local ver=$2
    
    title='download'
    end_string='-------------------------------------------------------------------- end: '$title' '$libName'/'$ver' ---'
    echo ${end_string: -80:80}
}
cfn_echo_install_begin(){
    local libName=$1
    local ver=$2
    
    title='install'
    begin_string='--- begin: '$title' '$libName'/'$ver' ------------------------------------------------------------------'
    echo ${begin_string:0:80}
}
cfn_echo_install_end(){
    local libName=$1
    local ver=$2
    
    title='install'
    end_string='-------------------------------------------------------------------- end: '$title' '$libName'/'$ver' ---'
    echo ${end_string: -80:80}
}