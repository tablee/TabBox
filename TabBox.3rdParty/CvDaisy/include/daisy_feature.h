#pragma once

#ifndef __DAISY_FEATURE_H
#define __DAISY_FEATURE_H
#pragma managed(push, off)
#include <cv.h>
#pragma managed(pop)
#include "feature.h"
#include "daisy/daisy.h"
//using namespace cv;

/** \class DaisyFeatureExtractor
  Extract DAISY features from input image
 */
class DaisyDescriptorExtractor
{
public:   
    DaisyDescriptorExtractor(double rad, int radq, int histq, int thq);
    ~DaisyDescriptorExtractor();
    void compute(const cv::Mat& image, std::vector<cv::KeyPoint>& keypoints, cv::Mat& descriptors);
	void compute(const cv::Mat& image, cv::Mat& descriptors);
    //void compute(const cv::Mat& image, const cv::Mat& query_points, cv::Mat& descriptors);
    void compute_dense(const cv::Mat& image, cv::Mat& descriptors);
	int add_point(cv::KeyPoint& keypoint);
	void SetVerboseLevel(int level);
	void clear_point();
    int feature_length() const;
	std::vector<cv::KeyPoint> keypoints();
private:
    int verbose_level_; //!< How verbose is our daisy computation output

    double rad_;
    int radq_;
    int histq_;
    int thq_;

	std::vector<cv::KeyPoint> vkps_;
    daisy* desc_; //!< Daisy descriptor structure
    //Mat image_; //!< in case the input image is not continous, we need to copy it before processing
};

#endif
