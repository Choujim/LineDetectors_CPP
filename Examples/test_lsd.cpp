#include <iostream>
#include "LSDWrapper.h"

using namespace std;
using namespace LSDWrapper;

int main(){
    LSD::Ptr lsd(new LSD);
    assert(lsd != nullptr);
    
    cv::VideoCapture cap;
    int nCamIndex = 1;
    cap.open(nCamIndex);
    assert(cap.isOpened() == true);

    cv::namedWindow("lsd");
    int nWaitSeconds = 30;
    auto t1 = chrono::steady_clock::now();
    auto t2 = chrono::steady_clock::now();
    while (1){
        cv::Mat frame;
        cap >> frame;

        cv::Mat mask;
        int num_line;
        std::vector<std::vector<double>> ret;
        lsd->Call_C_lsd_scale_region(frame, mask, num_line, ret, 0.8);
        cout << "--- num_lines: "<< num_line << "\t";
        

        t2 = chrono::steady_clock::now();
        auto time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
        cout << "--- time used: " << time_used.count() << " s" << endl; 
        double fps = 1.0 / time_used.count();
        t1 = t2;
        string fps_text = "FPS: ";
        char fps_decimal[20];
        sprintf_s(fps_decimal, "%.1f", fps);
        fps_text += fps_decimal;
        auto FPS_color = cv::Scalar(50, 150, 50, 0);
        cv::putText(frame, fps_text, cv::Point(5, 20), CV_FONT_HERSHEY_COMPLEX, 0.5, FPS_color, 1);

        cv::normalize(mask, mask, 0, 1, cv::NORM_MINMAX);
        mask *= 255;
        mask.convertTo(mask, CV_8U);
        cv::cvtColor(mask, mask, CV_GRAY2BGR);
        cv::resize(mask, mask, cv::Size(frame.cols, frame.rows));
        cv::Mat ret2show;
        cv::hconcat(frame, mask, ret2show);
        cv::imshow("lsd", ret2show);


        if(cv::waitKey(nWaitSeconds)>=0){
            break;
        }
    }
    cv::destroyAllWindows();

    return 0;
}