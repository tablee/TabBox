#pragma managed(push, off)
#include <cv.h>
#pragma managed(pop)
#include "feature.h"
//using namespace cv;

void BasicDescriptorExtractor::compute_dense(const cv::Mat& image, cv::Mat& descriptors){
    CV_Error(CV_StsNotImplemented, "This descriptor do not have dense computation implemented");
}
