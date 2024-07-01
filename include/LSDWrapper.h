#pragma once
#ifndef LSD_WRAPPER_H
#define LSD_WRAPPER_H

#include <iostream>
#include <memory>

extern "C"
{
    #include "lsd.h"
}

// for OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

namespace LSDWrapper
{

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if (p){delete[](p);} p = nullptr;}
#endif

class LSD{
public:
    typedef std::shared_ptr<LSD> Ptr;

    LSD(){}
    ~LSD(){this->Release();}

    void Release();


public:
    /**
     * @brief initialization somethings before Run
     * 
     */
    void compute();

    /**
     * @brief Wrapper funcs
     * @param {cpp_var}-->{c_var} 参数对应(不完全)
     * @param src           --> img
     * @param dst_mask      --> reg_img
     * @param num_line_out  --> n_out
     * @param ret           --> return array
     * @param scale         --> scale
     * @param sigma_scale   --> sigma_scale
     * @param quant_error_threshold     --> quant
     * @param angle_threshold           --> ang_th
     * @param false_threshold           --> log_eps
     * @param density_threshold         --> density_th
     * 
     */
    void Call_C_LineSegmentDetection(cv::Mat& src, cv::Mat& dst_mask, int& num_line_out, std::vector<std::vector<double>>& ret,
                                     double scale, double sigma_scale, double quant_error_bound, int num_bins,
                                     double angle_threshold, double false_threshold, double density_threshold);
    
    /**
     * @brief Wrapper funcs
     * @param {cpp_var}-->{c_var} 参数对应(不完全)
     * @param src           --> img
     * @param dst_mask      --> reg_img
     * @param num_line_out  --> n_out
     * @param ret           --> return array
     * @param scale         --> scale
     * 
     */
    void Call_C_lsd_scale_region(cv::Mat& src, cv::Mat& dst_mask, int& num_line_out, std::vector<std::vector<double>>& ret, double scale);

    /**
     * @brief Wrapper funcs
     * @param {cpp_var}-->{c_var} 参数对应(不完全)
     * @param src           --> img
     * @param num_line_out  --> n_out
     * @param ret           --> return array
     * @param scale         --> scale
     * 
     */
    void Call_C_lsd_scale(cv::Mat& src, int& num_line_out, std::vector<std::vector<double>>& ret, double scale);

    /**
     * @brief Wrapper funcs
     * @param {cpp_var}-->{c_var} 参数对应(不完全)
     * @param src           --> img
     * @param num_line_out  --> n_out
     * @param ret           --> return array
     * 
     */
    void Call_C_lsd(cv::Mat& src, int& num_line_out, std::vector<std::vector<double>>& ret);

    

private:
    int height = 0;
    int width = 0;
    double* image = nullptr;
    std::vector<std::vector<double>> lines;



};

}

#endif