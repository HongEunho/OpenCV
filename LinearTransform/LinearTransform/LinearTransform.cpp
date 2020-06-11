#include <opencv2/opencv.hpp>

void SetScale(float sx, float sy, float M[][3])
{
	M[0][0] = sx;		M[0][1] = 0;	M[0][2] = 0;
	M[1][0] = 0;		M[1][1] = sy;	M[1][2] = 0;
	M[2][0] = 0;		M[2][1] = 0;	M[2][2] = 1;
}

void SetRotate(float theta, float M[][3])
{
	float rad = theta / 180.0f*3.141592;
	M[0][0] = cos(rad);	M[0][1] = -sin(rad);	M[0][2] = 0;
	M[1][0] = sin(rad);	M[1][1] = cos(rad);		M[1][2] = 0;
	M[2][0] = 0;		M[2][1] = 0;			M[2][2] = 1;
}

void SetMultiple(float M[][3], float A[][3], float B[][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			M[i][j] = A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2]*B[2][j];
		}
}

void SetTranslate(float tx, float ty, float M[][3])
{
	M[0][0] = 1;		M[0][1] = 0;	M[0][2] = tx;
	M[1][0] = 0;		M[1][1] = 1;	M[1][2] = ty;
	M[2][0] = 0;		M[2][1] = 0;	M[2][2] = 1;
}

void SetScaleRotateMatrixWithPivot(float px, float py, float s, float theta, float M[][3])
{
	// 1. translate -px, -py;
	float M1[3][3];
	SetTranslate(-px, -py, M1);
	
	// 2-1. Scale
	float M21[3][3];
	SetScale(s, s, M21);

	// 2-2. Rotate theta
	float M22[3][3];
	SetRotate(theta, M22);

	// 3. translate px, py;
	float M3[3][3];
	SetTranslate(px, py, M3);

	float M4[3][3], M5[3][3];

	SetMultiple(M4, M21, M1);
	SetMultiple(M5, M22, M4);
	SetMultiple(M, M3, M5);
}

void SetInverseScaleRotateMatrixWithPivot(float px, float py, float s, float theta, float IM[][3])
{
	float IM1[3][3];
	SetTranslate(px, py, IM1);

	float IM21[3][3];
	SetScale(1 / s, 1 / s, IM21);

	float IM22[3][3];
	SetRotate(-theta, IM22);

	float IM3[3][3];
	SetTranslate(-px, -py, IM3);

	float IM4[3][3], IM5[3][3];
	SetMultiple(IM4, IM22, IM3);
	SetMultiple(IM5, IM21, IM4);
	SetMultiple(IM, IM1, IM5);
}

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\flower.jpg");
	IplImage * dst = cvCreateImage(cvSize(src->width, src->height), 8, 3);

	float sx = 1.5;
	float sy = 0.5;
	float s = 0.5;
	float theta = 30;
	float tx = 100;
	float ty = 50;

	float M1[3][3], M2[3][3], M3[3][3], M4[3][3], M[3][3];
	//SetScale(sx, sy, M1);				// M = M3*M2*M1
	//SetRotate(theta, M2);
	//SetTranslate(tx, ty, M3);

	//SetMultiple(M4, M2, M1);
	//SetMultiple(M, M3, M4);
	for (int theta = 0; theta < 360; theta += 10)
	{/*
		cvSet(dst, cvScalar(0, 0, 0));
		SetScaleRotateMatrixWithPivot(src->width / 2, src->height / 2, s, theta, M);

		for (float y1 = 0; y1 < src->height; y1++)
			for (float x1 = 0; x1 < src->width; x1++)
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
			*/
		float scale = 1.5 + 0.5*sin(theta / 180.0f*3.141592);
		float IM[3][3], IM1[3][3], IM2[3][3], IM3[3][3], IM4[3][3];
		SetInverseScaleRotateMatrixWithPivot(src->width / 2, src->height / 2, scale, theta, IM);
		

		for(float y2=0;y2<dst->height;y2++)
			for (float x2 = 0; x2 < dst->width; x2++)
			{
				float w2 = 1.0f;
				float x1 = IM[0][0] * x2 + IM[0][1] * y2 + IM[0][2] * w2;
				float y1 = IM[1][0] * x2 + IM[1][1] * y2 + IM[1][2] * w2;
				float w1 = IM[2][0] * x2 + IM[2][1] * y2 + IM[2][2] * w2;

				x1 /= w1;
				y1 /= w1;

				if (x1<0 || x1>src->width - 1)continue;
				if (y1<0 || y1>src->height - 1)continue;

				CvScalar c = cvGet2D(src, y1, x1);
				cvSet2D(dst, y2, x2, c);
				
			}
		cvShowImage("dst", dst);
		cvWaitKey(30);
	}
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}