// This is the main DLL file.

#include "CvBlobsLib.h"
#include <iostream>
#include <fstream>
using namespace std;

__declspec(dllexport) CBlob** CvGetBlobs(IplImage* inputImage,
					int threshold,
				    IplImage* maskImage,
				    bool borderColor,
				    bool findMoments,
					int* numberOfDetectedBlobs)
{
	vector<CBlob*> blobVector = vector<CBlob*>();
	BlobAnalysis(inputImage, threshold, maskImage, borderColor, findMoments, blobVector);
	*numberOfDetectedBlobs = blobVector.size();
	CBlob** blobs = new CBlob*[*numberOfDetectedBlobs];
	std::copy(blobVector.begin(), blobVector.end(), blobs);
	return blobs;
}

__declspec(dllexport) void CvClearBlob(CBlob* blob)
{
	blob->~CBlob();
}

__declspec(dllexport) BlobFeatures* CvGetBlobFeatures(CBlob* blob)
{	
	return blob->GetFeatures();
}

__declspec(dllexport) void CvBlobFeaturesRelease(BlobFeatures* features)
{
   delete features;
}

__declspec(dllexport) CvPoint* CvGetBlobEdges(CBlob* blob, int *numberOfEdges)
{
	*numberOfEdges = blob->Edges->total;
	CvPoint* edges = new CvPoint[blob->Edges->total];
	return (CvPoint*)cvCvtSeqToArray(blob->Edges, edges);
}

__declspec(dllexport) void CvFillBlob(CBlob* blob, IplImage* image, CvScalar color, int offsetX, int offsetY)
{
		blob->FillBlob(image, color, offsetX, offsetY);
}