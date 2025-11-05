#include <opencv2/opencv.hpp>
#include "Colorizer.h"

using namespace cv;


Mat& Colorizer::colorizeFrame(Mat& frame) {
    return frame;
}

Mat& Colorizer::combineFrames() {
    return this->raw_frames[0];
}