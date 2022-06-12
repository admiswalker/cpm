#!/bin/bash


echo '-- set CPM environment ---'
. cpm_env/local/set_env.sh

echo '-- check compiler version ---'
gcc --version

echo '-- compile ---'
# with CUDA
#g++ sample/main_opencv.cpp -I cpm_env/local/include/opencv4 -L cpm_env/local/lib -lopencv_cudabgsegm -lopencv_cudaobjdetect -lopencv_cudastereo -lopencv_dnn -lopencv_ml -lopencv_shape -lopencv_stitching -lopencv_cudafeatures2d -lopencv_superres -lopencv_cudacodec -lopencv_videostab -lopencv_cudaoptflow -lopencv_cudalegacy -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_photo -lopencv_imgcodecs -lopencv_cudawarping -lopencv_cudaimgproc -lopencv_cudafilters -lopencv_video -lopencv_objdetect -lopencv_imgproc -lopencv_flann -lopencv_cudaarithm -lopencv_core -lopencv_cudev -o exe

# without CUDA
g++ sample/main_opencv.cpp -I cpm_env/local/include/opencv4 -L cpm_env/local/lib -lopencv_dnn -lopencv_ml -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_photo -lopencv_imgcodecs -lopencv_video -lopencv_objdetect -lopencv_imgproc -lopencv_flann -lopencv_core -o exe

echo '-- run exe file ---'
./exe

