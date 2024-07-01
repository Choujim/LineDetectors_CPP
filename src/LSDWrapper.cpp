#include "LSDWrapper.h"

namespace LSDWrapper
{


void LSD::Release(){
    SAFE_DELETE(this->image);
}

void LSD::compute(){

}

void LSD::Call_C_LineSegmentDetection(cv::Mat& src, cv::Mat& dst_mask, int& num_line_out, std::vector<std::vector<double>>& ret,
                                      double scale, double sigma_scale, double quant_error_bound, int num_bins,
                                      double angle_threshold, double false_threshold, double density_threshold){
    cv::Mat gray;
    cv::cvtColor(src, gray, CV_RGB2GRAY);

    int rows = src.rows;
    int cols = src.cols;
    if (rows>this->height || cols>this->width){
        this->height = (rows > height) ? (rows*2) : this->height;
        this->width = (cols > width) ? (cols*2) : this->width;
        SAFE_DELETE(image);
        if (image == nullptr){
            this->image = new double[this->height * this->width];
        }else{
            cerr << "------ Unsafe delete!" << endl;
            return;
        }
    }
    for (int i=0; i<rows; ++i){
        for (int j=0; j<cols; ++j){
            this->image[i*cols+j] = (double)*gray.ptr<uchar>(i,j);
        }
    }
    int n_out;
    double* out;

    int* mask = NULL;
    int mask_height, mask_width;
    out = LineSegmentDetection(&n_out, this->image, cols, rows, scale, sigma_scale, quant_error_bound,
                               angle_threshold, false_threshold, density_threshold,
                               num_bins, &mask, &mask_width, &mask_height);

    dst_mask = cv::Mat_<int>::zeros(mask_height, mask_width);
    for (int i=0; i<mask_height; ++i){
        for (int j=0; j<mask_width; ++j){
            *dst_mask.ptr<int>(i,j) = mask[i*mask_width+j];
        }
    }

    if (n_out > this->lines.size()){
        this->lines = std::vector<std::vector<double>>(n_out*2, std::vector<double>(7, 0));
    }
    for (int i=0; i<n_out; ++i){
        for (int j=0; j<7; ++j){
            this->lines[i][j] = out[7*i+j];
        }
    }
    num_line_out = n_out;
    ret = this->lines;
    
    SAFE_DELETE(out);
    SAFE_DELETE(mask);
}

void LSD::Call_C_lsd_scale_region(cv::Mat& src, cv::Mat& dst_mask, int& num_line_out, std::vector<std::vector<double>>& ret, double scale){
    cv::Mat gray;
    cv::cvtColor(src, gray, CV_RGB2GRAY);

    int rows = src.rows;
    int cols = src.cols;
    if (rows>this->height || cols>this->width){
        this->height = (rows > height) ? (rows*2) : this->height;
        this->width = (cols > width) ? (cols*2) : this->width;
        SAFE_DELETE(image);
        if (image == nullptr){
            this->image = new double[this->height * this->width];
        }else{
            cerr << "------ Unsafe delete!" << endl;
            return;
        }
    }
    for (int i=0; i<rows; ++i){
        for (int j=0; j<cols; ++j){
            this->image[i*cols+j] = (double)*gray.ptr<uchar>(i,j);
        }
    }
    int n_out;
    double* out;

    int* mask = NULL;
    int mask_height, mask_width;
    out = lsd_scale_region(&n_out, this->image, cols, rows, scale, &mask, &mask_width, &mask_height);

    dst_mask = cv::Mat_<int>::zeros(mask_height, mask_width);
    for (int i=0; i<mask_height; ++i){
        for (int j=0; j<mask_width; ++j){
            *dst_mask.ptr<int>(i,j) = mask[i*mask_width+j];
        }
    }

    if (n_out > this->lines.size()){
        this->lines = std::vector<std::vector<double>>(n_out*2, std::vector<double>(7, 0));
    }
    for (int i=0; i<n_out; ++i){
        for (int j=0; j<7; ++j){
            this->lines[i][j] = out[7*i+j];
        }
    }
    num_line_out = n_out;
    ret = this->lines;
    
    SAFE_DELETE(out);
    SAFE_DELETE(mask);
}

void LSD::Call_C_lsd_scale(cv::Mat& src, int& num_line_out, std::vector<std::vector<double>>& ret, double scale){
    cv::Mat gray;
    cv::cvtColor(src, gray, CV_RGB2GRAY);

    int rows = src.rows;
    int cols = src.cols;
    if (rows>this->height || cols>this->width){
        this->height = (rows > height) ? (rows*2) : this->height;
        this->width = (cols > width) ? (cols*2) : this->width;
        SAFE_DELETE(image);
        if (image == nullptr){
            this->image = new double[this->height * this->width];
        }else{
            cerr << "------ Unsafe delete!" << endl;
            return;
        }
    }
    for (int i=0; i<rows; ++i){
        for (int j=0; j<cols; ++j){
            this->image[i*cols+j] = (double)*gray.ptr<uchar>(i,j);
        }
    }
    int n_out;
    double* out;

    out = lsd_scale(&n_out, this->image, cols, rows, scale);

    if (n_out > this->lines.size()){
        this->lines = std::vector<std::vector<double>>(n_out*2, std::vector<double>(7, 0));
    }
    for (int i=0; i<n_out; ++i){
        for (int j=0; j<7; ++j){
            this->lines[i][j] = out[7*i+j];
        }
    }
    num_line_out = n_out;
    ret = this->lines;

    SAFE_DELETE(out);

}

void LSD::Call_C_lsd(cv::Mat& src, int& num_line_out, std::vector<std::vector<double>>& ret){

    cv::Mat gray;
    cv::cvtColor(src, gray, CV_RGB2GRAY);

    int rows = src.rows;
    int cols = src.cols;
    if (rows>this->height || cols>this->width){
        this->height = (rows > height) ? (rows*2) : this->height;
        this->width = (cols > width) ? (cols*2) : this->width;
        SAFE_DELETE(image);
        if (image == nullptr){
            this->image = new double[this->height * this->width];
        }else{
            cerr << "------ Unsafe delete!" << endl;
            return;
        }
    }
    for (int i=0; i<rows; ++i){
        for (int j=0; j<cols; ++j){
            this->image[i*cols+j] = (double)*gray.ptr<uchar>(i,j);
        }
    }
    int n_out;
    double* out;

    out = lsd(&n_out, this->image, cols, rows);

    if (n_out > this->lines.size()){
        this->lines = std::vector<std::vector<double>>(n_out*2, std::vector<double>(7, 0));
    }
    for (int i=0; i<n_out; ++i){
        for (int j=0; j<7; ++j){
            this->lines[i][j] = out[7*i+j];
        }
    }
    num_line_out = n_out;
    ret = this->lines;

    SAFE_DELETE(out);
}


}


