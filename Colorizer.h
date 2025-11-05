#ifndef GUARD_colorizer
#define GUARD_colorizer

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class Colorizer {
    private:
        deque<Mat> raw_frames;
    public:
        Mat& colorizeFrame(Mat& frame);
        Mat& combineFrames();
};

#endif