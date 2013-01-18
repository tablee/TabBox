// This is the main DLL file.

#include "CvDaisyLib.h"
#include <iostream>
#include <fstream>
using namespace std;

__declspec(dllexport) DaisyDescriptorExtractor* CvDaisyDescriptorExtractorCreate(double rad, int radq, int histq, int thq)
{
	return new DaisyDescriptorExtractor(rad, radq, histq, thq);
}

__declspec(dllexport) void CvDaisyDescriptorExtractorRelease(DaisyDescriptorExtractor* extractor)
{
	extractor->~DaisyDescriptorExtractor();
}

__declspec(dllexport) void CvDaisyDescriptorComputeDescriptors(DaisyDescriptorExtractor* extractor, IplImage* image, std::vector<cv::KeyPoint>* keypoints, CvMat* descriptors)
{	
	cout<<"CvDaisyDescriptorComputeDescriptors\n";
	cout<<"C++ Address "<<(int)extractor<<" "<<(int)image<<" "<<(int)keypoints<<"["<<(int)keypoints->size()<<"] "<<(int)descriptors<<std::endl;
	cout<<"Empty:"<<((keypoints->empty())?"TRUE":"FALSE")<<std::endl;
	if (keypoints->size() <= 0) return;
	cout<<"keypoints->size() > 0\n";
	cv::Mat img = cv::cvarrToMat(image);
	if(img.channels() == 1)
	{
		cout<<"img.channels() == 1\n";
		cv::Mat result = cv::cvarrToMat(descriptors);
		extractor->compute(img, *keypoints, result);
	}
	else //opponent DAISY
	{
		cout<<"img.channels() != 1\n";
	}
}

__declspec(dllexport) void CvDaisyDescriptorComputeDescriptors2(DaisyDescriptorExtractor* extractor, IplImage* image, CvMat* descriptors)
{	
	cout<<"CvDaisyDescriptorComputeDescriptors\n";
	cout<<"C++ Address "<<(int)extractor<<" "<<(int)image<<" "<<(int)&(extractor->keypoints())<<"["<<(int)extractor->keypoints().size()<<"] "<<(int)descriptors<<std::endl;
	cout<<"Empty:"<<((extractor->keypoints().empty())?"TRUE":"FALSE")<<std::endl;
	if (extractor->keypoints().size() <= 0) return;
	cout<<"keypoints->size() > 0\n";
	cv::Mat img = cv::cvarrToMat(image);
	if(img.channels() == 1)
	{
		cout<<"img.channels() == 1\n";
		cv::Mat result = cv::cvarrToMat(descriptors);
		extractor->compute(img, result);
	}
	else //opponent DAISY
	{
		cout<<"img.channels() != 1\n";
	}
}

__declspec(dllexport) int CvDaisyDescriptorExtractorAddKeyPoint(DaisyDescriptorExtractor* extractor, cv::KeyPoint* keypoint)
{
	//cout<<"CvDaisyDescriptorExtractorAddKeyPoint "<<(*keypoint).pt.x<<","<<(*keypoint).pt.y<<std::endl;
	return extractor->add_point(*keypoint);
}

__declspec(dllexport) void CvDaisyDescriptorExtractorVerboseLevel(DaisyDescriptorExtractor* extractor, int level)
{
	extractor->SetVerboseLevel(level);
}

__declspec(dllexport) void CvDaisyDescriptorExtractorClearKeyPoints(DaisyDescriptorExtractor* extractor)
{
	//cout<<"CvDaisyDescriptorExtractorClearKeyPoints"<<std::endl;
	extractor->clear_point();
}

__declspec(dllexport) int VectorOfKeyPointGetSize(std::vector<cv::KeyPoint>* v)
{
   return v->size();
}