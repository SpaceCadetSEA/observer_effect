#ifndef GUARD_frame_manager
#define GUARD_frame_manager

#include <deque>
#include <opencv2/opencv.hpp>
#include "Colorizer.h"

using namespace std;
using namespace cv;

class FrameManager {
    private:
        deque<Mat> frames;
        Colorizer* colorizer;
    public:
        FrameManager();
        ~FrameManager();
        void push_frame(Mat& frame);
        void display_frame(bool observed);
        bool is_full() {
            return frames.size() == 3;
        }
};

#endif