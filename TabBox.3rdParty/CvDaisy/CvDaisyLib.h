#pragma once
#pragma managed(push, off)
#include "cxcore.h"
#pragma managed(pop)
#include "daisy_feature.h"

extern "C" __declspec(dllexport) DaisyDescriptorExtractor* CvDaisyDescriptorExtractorCreate(double rad, int radq, int histq, int thq);

extern "C" __declspec(dllexport) void CvDaisyDescriptorExtractorRelease(DaisyDescriptorExtractor* extractor);

extern "C" __declspec(dllexport) void CvDaisyDescriptorComputeDescriptors(DaisyDescriptorExtractor* extractor, IplImage* image, std::vector<cv::KeyPoint>* keypoints, CvMat* descriptors);

extern "C" __declspec(dllexport) void CvDaisyDescriptorComputeDescriptors2(DaisyDescriptorExtractor* extractor, IplImage* image, CvMat* descriptors);

//extern "C" __declspec(dllexport) void CvDaisyDescriptorComputeDescriptors(DaisyDescriptorExtractor* extractor, IplImage* image, CvMat* descriptors);

extern "C" __declspec(dllexport) int CvDaisyDescriptorExtractorGetDescriptorSize(DaisyDescriptorExtractor* extractor)
{
   return extractor->feature_length();
}

extern "C" __declspec(dllexport) int CvDaisyDescriptorExtractorAddKeyPoint(DaisyDescriptorExtractor* extractor, cv::KeyPoint* keypoint);

extern "C" __declspec(dllexport) void CvDaisyDescriptorExtractorClearKeyPoints(DaisyDescriptorExtractor* extractor);

extern "C" __declspec(dllexport) void CvDaisyDescriptorExtractorVerboseLevel(DaisyDescriptorExtractor* extractor, int level);

extern "C" __declspec(dllexport) int VectorOfKeyPointGetSize(std::vector<cv::KeyPoint>* v);