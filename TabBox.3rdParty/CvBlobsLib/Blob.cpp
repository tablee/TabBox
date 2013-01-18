#include <limits.h>
#include <vector>
#include "blob.h"
#include "cv.h"

using namespace std;

CBlob::CBlob()
{
	Label = -1;		// Flag indicates null region

	Exterior = 0;
	Area = 0.0f;
	Perimeter = 0.0f;
	Parent = -1;
	Minx = LONG_MAX;
	Maxx = 0;
	Miny = LONG_MAX;
	Maxy = 0;
	u10 = 0;
	u01 = 0;
	u20 = 0;
	u02 = 0;
	u11 = 0;
	Mean = 0;
	StdDev = 0;
	ExternPerimeter = 0;


	m_storage = cvCreateMemStorage(0);
	Edges = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2,
		sizeof(CvContour),
		sizeof(CvPoint),m_storage);
}

CBlob::~CBlob()
{
	cvClearSeq(Edges);
	cvReleaseMemStorage( &m_storage );
}

void CBlob::CopyEdges( CBlob &destination ) const
{
	CvSeqReader reader;
	CvSeqWriter writer;
	CvPoint edgeactual;

	cvStartReadSeq( Edges, &reader);
	cvStartAppendToSeq( destination.Edges, &writer );

	for( int i=0; i<Edges->total; i++)
	{
		CV_READ_SEQ_ELEM( edgeactual ,reader);
		CV_WRITE_SEQ_ELEM( edgeactual , writer );
	}

	cvEndWriteSeq( &writer );
}

void CBlob::ClearEdges()
{
	cvClearSeq( Edges );
}

BlobFeatures* CBlob::GetFeatures()
{
	BlobFeatures *Features = new BlobFeatures();

	Features->CentroidX = u10;
	Features->CentroidY = u01;
	Features->Exterior= Exterior;
	Features->Area= Area;
	Features->Perimeter= Perimeter;
	Features->ExternPerimeter= ExternPerimeter;
	Features->Parent= Parent;
	// Moments
	Features->u10= u10;
	Features->u01= u01;
	Features->u20= u20;
	Features->u02= u02;
	Features->u11= u11;
	Features->Angle = 0.5 *atan2(2.0*u11,(u20-u02));
	
	// Bounding rect
	Features->MinX= Minx;
	Features->MaxX= Maxx;
	Features->MinY= Miny;
	Features->MaxY= Maxy;

	Features->Mean= Mean;
	Features->StdDev= StdDev;
	return Features;
}

void CBlob::FillBlob( IplImage *image, CvScalar color, int offsetX /*=0*/, int offsetY /*=0*/) const					  
{
	
	//verifiquem que existeixi el blob i que tingui cantonades
	if( Edges == NULL || Edges->total == 0 ) return;
	
	CvPoint edgeactual, pt1, pt2;
	CvSeqReader reader;
	vector<CvPoint> vectorEdges = vector<CvPoint>( Edges->total );
	vector<CvPoint>::iterator itEdges, itEdgesSeguent;
	bool dinsBlob;
	int yActual;
	
	// passem els punts del blob a un vector de punts de les STL
	cvStartReadSeq( Edges, &reader);
	itEdges = vectorEdges.begin();
	while( itEdges != vectorEdges.end() )
	{
		CV_READ_SEQ_ELEM( edgeactual ,reader);
		*itEdges = edgeactual;
		itEdges++;
	}
	// ordenem el vector per les Y's i les X's d'esquerra a dreta
	std::sort( vectorEdges.begin(), vectorEdges.end(), comparaCvPoint() );

	// recorrem el vector ordenat i fem linies entre punts consecutius
	itEdges = vectorEdges.begin();
	itEdgesSeguent = vectorEdges.begin() + 1;
	dinsBlob = true;
	while( itEdges != (vectorEdges.end() - 1))
	{
		yActual = (*itEdges).y;

		if( ( (*itEdges).x != (*itEdgesSeguent).x ) &&
			( (*itEdgesSeguent).y == yActual )
		  )
		{
			if( dinsBlob )
			{
				pt1 = *itEdges;
				pt1.x += offsetX;
				pt1.y += offsetY;

				pt2 = *itEdgesSeguent;
				pt2.x += offsetX;
				pt2.y += offsetY;

				cvLine( image, pt1, pt2, color );
			}
			dinsBlob =! dinsBlob;
		}
		itEdges++;
		itEdgesSeguent++;
		if( (*itEdges).y != yActual ) dinsBlob = true;
	}
	vectorEdges.clear();
}
