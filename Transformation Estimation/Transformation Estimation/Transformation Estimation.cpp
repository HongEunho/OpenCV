#include <opencv2/opencv.hpp>
#include "MatrixInverse.h"

void TransformEstimation(float M[][3], float P[][3], float Q[][3])
{
	// Q = M P
	// M = Q P^-1

	float invP[3][3];
	InverseMatrixGJ(P, invP, 3);

	for(int i=0; i<3; i++)
		for (int j = 0; j < 3; j++)
		{
			M[i][j] = 0.0f;
			for (int k = 0; k < 3; k++)
				M[i][j] += Q[i][k] * invP[k][j];
		}
}

void DoAffineTransform(IplImage * src, IplImage * dst, float M[][3])
{
	for(int y1=0; y1<src->height; y1++)
		for (int x1 = 0; x1 < src->width; x1++)
		{
			float w1 = 1;
			float x2 = M[0][0] * x1 + M[0][1] * y1 + M[0][2] * w1;
			float y2 = M[1][0] * x1 + M[1][1] * y1 + M[1][2] * w1;
			float w2 = M[2][0] * x1 + M[2][1] * y1 + M[2][2] * w1;
			x2 /= w2;
			y2 /= w2;

			if (x2<0 || x2>dst->width - 1)continue;
			if (y2<0 || y2>dst->height - 1)continue;
			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}
}

void DoInverseAffineTransform(IplImage * src, IplImage * dst, float M[][3])
{
	for (int y2 = 0; y2 < dst->height; y2++)
		for (int x2 = 0; x2 < dst->width; x2++)
		{
			float w2 = 1;
			float x1 = M[0][0] * x2 + M[0][1] * y2 + M[0][2] * w2;
			float y1 = M[1][0] * x2 + M[1][1] * y2 + M[1][2] * w2;
			float w1 = M[2][0] * x2 + M[2][1] * y2 + M[2][2] * w2;
			x2 /= w1;
			y2 /= w1;

			if (x1<0 || x1>src->width - 1)continue;
			if (y1<0 || y1>src->height - 1)continue;
			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}
}

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\lena_triangle.png");
	IplImage * dst = cvCreateImage(cvGetSize(src), 8, 3);

	int num = 3;
	CvPoint p[3] = { cvPoint(100,350), cvPoint(400,350), cvPoint(250,100) };
	CvPoint q[3] = { cvPoint(400,400), cvPoint(400,100), cvPoint(100,200) };

	float P[3][3];
	float Q[3][3];

	for (int j = 0; j < 3; j++)
	{
		P[0][j] = p[j].x;
		P[1][j] = p[j].y;
		P[2][j] = 1;
		Q[0][j] = q[j].x;
		Q[1][j] = q[j].y;
		Q[2][j] = 1;
	}
	float M[3][3];
	//TransformEstimation(M, P, Q); //P->Q
	TransformEstimation(M, Q, P);	//Q->P
	//DoAffineTransform(src, dst, M); //정변형
	DoInverseAffineTransform(src, dst, M); //역변형


	for (int i = 0; i < num; i++)
	{
		cvCircle(src, p[i], 10, cvScalar(0, 0, 255), -1);
		cvCircle(dst, q[i], 10, cvScalar(255, 0, 0), -1);
	}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	return 0;
}