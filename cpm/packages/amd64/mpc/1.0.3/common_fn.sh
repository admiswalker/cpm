#!/bin/bash


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


cfn_download_archive(){
    # SET: fName, fName_base, arcName, libName, ver
    fName=''
    if [ ${#URL} != 0 ]; then
	fName=${URL##*/}       # <architecture>-<libName>-<version>.tar.xz
    elif [ ${#URL00} != 0 ]; then
	fName00=${URL00##*/}   # <architecture>-<libName>-<version>.tar.xz-00
	fName=${fName00%-00}   # <architecture>-<libName>-<version>.tar.xz
    else
	echo -e "\e[31mERROR: unexpected URL pattern.\e[m"
	exit -1
    fi
    fName_base=${fName%.*.*}   # <architecture>-<libName>-<version>
    tmp=${fName%-*}            # <architecture>-<libName>
    arcName=${tmp%-*}          # <architecture>
    libName=${tmp#*-}          # <libName>
    ver=${fName_base#*-*-}     # <version>
    fName_hash=${URL_hash##*/} # <architecture>-<libName>-<version>-sha256sum.txt


    cfn_echo_download_begin $libName $ver


    # downloading archive file
    if [ ${#URL} != 0 ]; then
	# downloading single-archive file
	if [ ! -e $CPM_CACHE_DIR/$fName ]; then
	    wget -P $CPM_CACHE_DIR $URL
	fi
    else
	# downloading multiple-archive file
	for i in `seq 0 99`
	do
	    num=`printf "%02d\n" $i`
	    
	    URL_xx=URL$num
	    cmd_u='echo $'$URL_xx
	    URL_str=`eval $cmd_u`
	    URL_len=${#URL_str}

	    if [ $URL_len == 0 ]; then
		break
	    fi
	    
	    fName_xx=${URL_str##*/} # <architecture>-<libName>-<version>.tar.xz-xx
	    if [ ! -e $CPM_CACHE_DIR/$fName_xx ]; then
		wget -P $CPM_CACHE_DIR $URL_str
	    fi
	done
	if [ ! -e $CPM_CACHE_DIR/$fName ]; then
	    cat $CPM_CACHE_DIR/$fName-* >> $CPM_CACHE_DIR/$fName
	fi
    fi
    if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
	wget -P $CPM_CACHE_DIR $URL_hash
    fi
    cfn_check_hash_value


    cfn_echo_download_end $libName $ver
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
cfn_install_archive(){
    fName_base=${fName%.*.*}  # <architecture>-<libName>-<version>
    tmp=${fName%-*}           # <architecture>-<libName>
    arcName=${tmp%-*}         # <architecture>
    libName=${tmp#*-}         # <libName>
    ver=${fName_base#*-*-}    # <version>


    cfn_echo_install_begin $libName $ver


    # installation
    if [ `cfn_isInstalled` = 'false' ]; then
	tar -Jxf $CPM_CACHE_DIR/$fName -C $CPM_INST_WDIR # tar.xz
    fi
    

    cfn_echo_install_end $libName $ver
}
