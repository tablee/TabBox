//***********************************************************//
//* Blob analysis package  8 August 2003                    *//
//* Version 1.0                                             *//
//* Input: IplImage* binary image                           *//
//* Output: attributes of each connected region             *//
//* Author: Dave Grossman                                   *//
//* Email: dgrossman@cdr.stanford.edu                       *//
//* Acknowledgement: the algorithm has been around > 20 yrs *//
//***********************************************************//

#pragma once
#include <vector>
#include "blob.h"
#include "cxcore.h"

using namespace std;

//! Extreu els blobs d'una imatge
bool  BlobAnalysis(IplImage* inputImage, int threshold, IplImage* maskImage,
				  bool borderColor, bool findmoments, vector<CBlob*> &RegionData );

 
// FUNCIONS AUXILIARS

//! Fusiona dos blobs
void Subsume(vector<CBlob*> &RegionData, int, int*, CBlob*, CBlob*, bool, int, int );
//! Reallocata el vector auxiliar de blobs subsumats
int *NewSubsume(int *SubSumedRegion, int elems_inbuffer);
//! Retorna el perimetre extern d'una run lenght
double GetExternPerimeter( int start, int end, int row, int width, int height, IplImage *maskImage );

