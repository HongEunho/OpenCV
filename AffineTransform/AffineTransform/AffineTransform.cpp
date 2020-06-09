#include <opencv2/opencv.hpp>

void SetScale(float sx, float sy, float M[][3])
{
	M[0][0] = sx;			M[0][1] = 0;		M[0][2] = 0;
	M[1][0] = 0;			M[1][1] = sy;		M[1][2] = 0;
	M[2][0] = 0;			M[2][1] = 0;		M[2][2] = 1;
}

void SetRotate(float theta, float M[][3])
{
	float rad = theta / 180.0f * 3.141592;
	M[0][0] = cos(rad);			M[0][1] = -sin(rad);		M[0][2] = 0;
	M[1][0] = sin(rad);			M[1][1] = cos(rad);			M[1][2] = 0;
	M[2][0] = 0;				M[2][1] = 0;				M[2][2] = 1;
}

void SetTranslate(float tx, float ty, float M[][3])
{
	M[0][0] = 1;			M[0][1] = 0;		M[0][2] = tx;
	M[1][0] = 0;			M[1][1] = 1;		M[1][2] = ty;
	M[2][0] = 0;			M[2][1] = 0;		M[2][2] = 1;
}

void SetMultiply(float M[][3], float A[][3], float B[][3]) //M = A*B
{
	int dim = 3;
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
		{/*M[i][j] = A[i][0] * B[0][j]
							+ A[i][1] * B[1][j]
							+ A[i][2] * B[2][j];*/
			M[i][j] = 0.0f;
			for (int k = 0; k < dim; k++)
				M[i][j] += A[i][k] * B[k][j];
		}
}

void SetInverse(float IM[][2], float M[][2])
{
	float det = M[0][0] * M[1][1] - M[0][1] * M[1][0];

	IM[0][0] = M[1][1] / det;				IM[0][1] = -M[0][1] / det;
	IM[1][0] = -M[1][0] / det;				IM[1][1] = M[0][0] / det;
}

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\flower.jpg");
	IplImage * dst = cvCreateImage(cvSize(800, 800), 8, 3);

	float sx = 1.5;
	float sy = 0.5;
	float tx = 100;
	float ty = 50;
	float theta = 30;

	float M1[3][3], M2[3][3], M3[3][3];
	SetScale(sx, sy, M1);
	SetRotate(theta, M2);
	SetTranslate(tx, ty, M3);

	float M[3][3];					// M = M3 * M2 * M1
									// M4 =     M2 * M1
									// M = M3 * M4
	float M4[3][3];
	SetMultiply(M4, M2, M1);
	SetMultiply(M, M3, M4);
/*
	for(float y1=0;y1<src->height;y1++)
		for (float x1 = 0; x1 < src->width; x1++)
		{
			float w1 = 1;

			float x2 = M[0][0] * x1 + M[0][1] * y1 + M[0][2] * w1;
			float y2 = M[1][0] * x1 + M[1][1] * y1 + M[1][2] * w1;
			float w2 = M[2][0] * x1 + M[2][1] * y1 + M[2][2] * w1;

			x2 = x2 / w2;
			y2 = y2 / w2;

			if (x2<0 || x2>dst->width - 1)continue;
			if (y2<0 || y2>dst->height - 1)continue;

			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}
	*/	

		//¿ªº¯Çü
	float IM[3][3];
	//SetInverse(IM, M);
	float IM1[3][3], IM2[3][3], IM3[3][3];
	SetScale(1 / sx, 1 / sy, IM1);
	SetRotate(-theta, IM2);
	SetTranslate(-tx, -ty, IM3);
										// M = M3*M2*M1
										// IM = IM1*IM2*IM3
										// IM4 = IM2*IM3
	float IM4[3][3];
	SetMultiply(IM4, IM2, IM3);
	SetMultiply(IM, IM1, IM4);			// IM = IM1 * IM4


	for (float y2 = 0; y2 < dst->height; y2++)
		for (float x2 = 0; x2 < dst->width; x2++)
		{
			float w2 = 1.0f;
			float x1 = IM[0][0] * x2 + IM[0][1] * y2 + IM[0][2] * w2;
			float y1 = IM[1][0] * x2 + IM[1][1] * y2 + IM[1][2] * w2;
			float w1 = IM[2][0] * x2 + IM[2][1] * y2 + IM[2][2] * w2;
			x1 = x1 / w1;
			y1 = y1 / w1;
			if (x1<0 || x1>src->width - 1)continue;
			if (y1<0 || y1>src->height - 1)continue;
			CvScalar c = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c);
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}