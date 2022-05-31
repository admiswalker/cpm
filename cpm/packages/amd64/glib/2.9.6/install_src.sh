#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh
CPM_CALL_DIR=`pwd -P`
. $CPM_INST_PATH/set_env.sh


fName='glib-2.9.6.tar.gz'
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -nq $CPM_CACHE_DIR/$fName -d $CPM_BUILD_DIR
    #tar -xf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    #tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
    tar -zxvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.gz
fi

# fix installation error
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/$fName_base/

    # 补丁出处 http://bugs.gentoo.org/156475
    # 内容如下：
    # --- glib2.0-2.13.4.orig/glib/gutils.h 2007-06-16 18:27:37.000000000 +0200
    # +++ glib2.0-2.13.4/glib/gutils.h 2007-06-16 18:30:08.000000000 +0200
    # @@ -96,9 +96,14 @@
    # #ifdef G_IMPLEMENT_INLINES
    # # define G_INLINE_FUNC
    # # undef G_CAN_INLINE
    # -#elif defined (__GNUC__)
    # -# define G_INLINE_FUNC extern inline
    # -#elif defined (G_CAN_INLINE)
    # +#elif defined (__GNUC__)
    # +# if __GNUC_PREREQ (4,2) && defined (__STDC_VERSION__) \
    # + && __STDC_VERSION__ >= 199901L
    # +# define G_INLINE_FUNC extern __inline __attribute__ ((__gnu_inline__))
    # +# else
    # +# define G_INLINE_FUNC extern __inline
    # +# endif
    # +#elif defined (G_CAN_INLINE)
    # # define G_INLINE_FUNC static inline
    # #else /* can't inline */
    # # define G_INLINE_FUNC
    #
    # ref: https://www.phpfans.net/ask/fansa1/7272870023.html
    cd glib
    cp gutils.h gutils_backup_by_CPM.h
    sed -i -e "99i \/\/ --- Begin: Replacing by CPM (c++ package manager) ------" gutils.h
    sed -i -e "100 s/#elif defined (__GNUC__)/\/\/#elif defined (__GNUC__)/g" gutils.h
    sed -i -e "101 s/#  define G_INLINE_FUNC extern inline/\/\/#  define G_INLINE_FUNC extern inline/g" gutils.h
    sed -i -e "102 s/#elif defined (G_CAN_INLINE)/\/\/#elif defined (G_CAN_INLINE)/g" gutils.h
    sed -i -e "103i #elif defined (__GNUC__)" gutils.h
    sed -i -e "104i # if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L" gutils.h
    sed -i -e "105i # define G_INLINE_FUNC extern __inline __attribute__ ((__gnu_inline__))" gutils.h
    sed -i -e "106i # else" gutils.h
    sed -i -e "107i # define G_INLINE_FUNC extern __inline" gutils.h
    sed -i -e "108i # endif" gutils.h
    sed -i -e "109i #elif defined (G_CAN_INLINE)" gutils.h
    sed -i -e "110i \/\/ --- End: Replacing by cpm (c++ package manager) ------" gutils.h
    sed -i -e "111i \ " gutils.h
#    echo gutils.h \
#	| xargs sed -e "99i \/\/ --- Begin: Replacing by CPM (c++ package manager) ------" \
#	| sed -e "100 s/#elif defined (__GNUC__)/\/\/#elif defined (__GNUC__)/g" \
#	| sed -e "101 s/#  define G_INLINE_FUNC extern inline/\/\/#  define G_INLINE_FUNC extern inline/g" \
#	| sed -e "102 s/#elif defined (G_CAN_INLINE)/\/\/#elif defined (G_CAN_INLINE)/g" \
#	| sed -e "103i #elif defined (__GNUC__)" \
#	| sed -e "104i # if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L" \
#	| sed -e "105i # define G_INLINE_FUNC extern __inline __attribute__ ((__gnu_inline__))" \
#	| sed -e "106i # else" \
#	| sed -e "107i # define G_INLINE_FUNC extern __inline" \
#	| sed -e "108i # endif" \
#	| sed -e "109i #elif defined (G_CAN_INLINE)" \
#	| sed -e "110i \/\/ --- End: Replacing by cpm (c++ package manager) ------" \
#	| sed -e "111i \ "
    cd ..
    
    cd $CPM_CALL_DIR
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/$fName_base/

    ./configure --prefix=$CPM_INST_WDIR
    
    make -j
    make install
    
    # gen `replacement_path_for_cpm_archive.txt`
    echo $CPM_INST_WDIR > $CPM_INST_WDIR/replacement_path_for_cpm_archive.txt
    
    cd $CPM_CALL_DIR
fi
