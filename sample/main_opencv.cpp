#include <opencv2/opencv.hpp>

int main(){
    cv::Mat img = cv::imread("sample/test.png");
    cv::imwrite("test_out.png", img);
    cv::imwrite("test_out.jpg", img);

    // terminate called after throwing an instance of 'cv::Exception'
    //   what():  OpenCV(4.5.5) /mnt/sd/documents/projects/cpm/cpm_env/build/amd64-opencv-4.5.5/opencv-4.5.5/modules/highgui/src/window.cpp:1268: error: (-2:Unspecified error) The function is not implemented. Rebuild the library with Windows, GTK+ 2.x or Cocoa support. If you are on Ubuntu or Debian, install libgtk2.0-dev and pkg-config, then re-run cmake or configure script in function 'cvShowImage'

    // libgtk2.0-dev and pkg-config

    return 0;
}
