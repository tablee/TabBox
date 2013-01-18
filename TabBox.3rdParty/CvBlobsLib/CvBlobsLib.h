#pragma once

#include "cxcore.h"
#include "BlobExtraction.h"
#include "Blob.h"

#ifndef CVAPI
    #define CVAPI(rettype) extern "C" __declspec(dllexport) rettype __cdecl
#endif

extern "C" __declspec(dllexport) CBlob** CvGetBlobs(IplImage* inputImage,
					int threshold,
				    IplImage* maskImage,
				    bool borderColor,
				    bool findMoments,
					int* numberOfDetectedBlobs);

extern "C" __declspec(dllexport) void CvClearBlob(CBlob* blob);

extern "C" __declspec(dllexport) BlobFeatures* CvGetBlobFeatures(CBlob* blob);

extern "C" __declspec(dllexport) void CvBlobFeaturesRelease(BlobFeatures* features);

extern "C" __declspec(dllexport) CvPoint* CvGetBlobEdges(CBlob* blob, int *numberOfEdges);

extern "C" __declspec(dllexport) void CvFillBlob(CBlob* blob, IplImage* imatge, CvScalar color, int offsetX, int offsetY);