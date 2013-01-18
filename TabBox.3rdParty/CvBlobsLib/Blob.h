#pragma once
//***********************************************************//
//* Blob analysis package  8 August 2003                    *//
//* Version 1.0                                             *//
//* Input: IplImage* binary image                           *//
//* Output: attributes of each connected region             *//
//* Author: Dave Grossman                                   *//
//* Modifications: Francesc Pinyol and Ricard Borras		*//
//* Email: dgrossman@cdr.stanford.edu                       *//
//* Email: fpinyol@cvc.uab.es rborras@cvc.uab.es            *//
//* Acknowledgement: the algorithm has been around > 20 yrs *//
//***********************************************************//


#include "cxcore.h"
#include <functional>
#include <vector>
#include <algorithm>

//! Factor de conversi?de graus a radians

struct BlobFeatures
{
	double CentroidX;
	double CentroidY;
	int Exterior;
	double Area;
	double Perimeter;
	double ExternPerimeter;
	int Parent;
	// Moments
	double u10;
	double u01;
	double u20;
	double u02;
	double u11;
	double Angle;
	// Bounding rect
	double MinX;
	double MaxX;
	double MinY;
	double MaxY;

	double Mean;
	double StdDev;
};

class CBlob
{
public:

	CBlob();
	~CBlob();

	BlobFeatures* GetFeatures();

	void ClearEdges();	
	void CopyEdges( CBlob &destination ) const;
	void FillBlob( IplImage *image, CvScalar color, int offsetX = 0, int offsetY = 0 ) const;

	int Label;
	
	int Exterior;
	double Area;
	double Perimeter;
	double ExternPerimeter;
	int Parent;
	// Moments
	double u10;
	double u01;
	double u20;
	double u02;
	double u11;
	// Bounding rect
	double Minx;
	double Maxx;
	double Miny;
	double Maxy;

	double Mean;
	double StdDev;

	CvMemStorage *m_storage;
	CvSeq *Edges;

	struct comparaCvPoint : public std::binary_function<CvPoint, CvPoint, bool> 
	{
			bool operator()(CvPoint a, CvPoint b) 
		{ 
			if( a.y == b.y ) 
				return a.x < b.x;
			else 
				return a.y < b.y; 
		}
	};
};




