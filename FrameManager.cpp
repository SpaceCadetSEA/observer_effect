#include <deque>
#include <opencv2/opencv.hpp>
#include "FrameManager.h"
#include "Colorizer.h"

using namespace std;
using namespace cv;


FrameManager::FrameManager() {
    this->colorizer = new Colorizer();
}

FrameManager::~FrameManager() {
    delete colorizer;
}

void FrameManager::push_frame(Mat& frame) {
    if (is_full()) {
        frames.pop_front();
    }
    frames.push_back(frame);
}

void FrameManager::display_frame(bool observed) {
    if (observed) {
        imshow("observed", frames[frames.size() - 1]);
    } else {
        // not implemented
        // insert the work with colorizer here
        // question: do we continuously update the frames in Colorizer,
        // or do we only produce the effect when an observer is not seen?

        // // Create a 3-channel image with only the green channel active
        // Mat green_only;
        // Mat zeros = Mat::zeros(frame.size(), CV_8UC1);
        // vector<Mat> green_channels = {zeros, channels[1], zeros}; // B=0,
        // G=green, R=0 merge(green_channels, green_only);

        imshow("", frames[0]);
        imshow("", frames[1]);
        imshow("", frames[2]);
    }
}