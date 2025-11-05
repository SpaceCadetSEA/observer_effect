#include <opencv2/opencv.hpp>
#include <vector>
#include <deque>

#include "FrameManager.h"

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);  // Open the default camera

    if (!cap.isOpened()) {
        // Handle error if camera cannot be opened
        return -1;
    }

    Mat frame, binary, gray, output_frame, color_frame;
    vector<Mat> red, green, blue;
    deque<Mat> frames;

    uint16_t frame_count;
    float transition_speed = 0.05;

    while (true) {
        cap >> frame;  // Capture a frame

        if (frame.empty()) {
            break;
        }

        frame_count++;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        threshold(gray, binary, 127, 255, THRESH_BINARY);

        if (frame_count > 30) {
            if (frames.size() > 5) {
                frames.pop_front();
            }
            // invert binary and add to deque
            Mat inversed;
            cv::bitwise_not(binary, inversed);
            frames.push_back(inversed.clone());  // Use clone() to make a copy
        }

        Mat zeros = Mat::zeros(frame.size(), CV_8UC1);

        float progress = fmod(frame_count * transition_speed, 3.0);
        float blue_weight = 0.0, green_weight = 0.0, red_weight = 0.0;

        if (progress < 1.0) {
            blue_weight = 1.0 - progress;
            green_weight = progress;
        } else if (progress < 2.0) {
            green_weight = 2.0 - progress;
            red_weight = progress - 1.0;
        } else {
            red_weight = 3.0 - progress;
            blue_weight = progress - 2.0;
        }
        Mat blue_channel, green_channel, red_channel;
        binary.convertTo(blue_channel, CV_8UC1, blue_weight);
        binary.convertTo(green_channel, CV_8UC1, green_weight);
        binary.convertTo(red_channel, CV_8UC1, red_weight);

        vector<Mat> channels = {blue_channel, green_channel, red_channel};
        merge(channels, color_frame);

        if (frames.size() > 0) {
            // Need to merge the vector into a Mat first
            Mat frozen_frame;
            Mat frozen_blue, frozen_green, frozen_red;

            float frozen_blue_weight = 0.0, frozen_green_weight = 0.0, frozen_red_weight = 0.0;

            if (progress < 1.0) {
                frozen_red_weight = 1.0 - progress;
                frozen_blue_weight = progress;
            } else if (progress < 2.0) {
                frozen_blue_weight = 2.0 - progress;
                frozen_green_weight = progress - 1.0;
            } else {
                frozen_green_weight = 3.0 - progress;
                frozen_red_weight = progress - 2.0;
            }

            frames[0].convertTo(frozen_blue, CV_8UC1, frozen_blue_weight);
            frames[0].convertTo(frozen_green, CV_8UC1, frozen_green_weight);
            frames[0].convertTo(frozen_red, CV_8UC1, frozen_red_weight);
            vector<Mat> frozen_channels = {frozen_blue, frozen_green, frozen_red};
            merge(frozen_channels, frozen_frame);

            // Now add them together
            addWeighted(frozen_frame, 1.0, color_frame, 1.0, 0.0, output_frame);
        } else {
            // Before we have a frozen frame, just show the color transition
            output_frame = color_frame;
        }

        cv::imshow("color_transition", output_frame);

        // if (frame_count == 30) {
        //     frames.push_back(binary.clone());
        // }

        // if (frame_count > 30) {
        //     blue = {binary, zeros, frames[0]};
        //     merge(blue, output_frame);
        //     cv::imshow("output_frame", output_frame);
        // }

        if (cv::waitKey(1) == 'q') {  // Exit on 'q' key press
            break;
        }
    }

    // release resources
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
