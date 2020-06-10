#include <opencv2/opencv.hpp>

CvScalar myGet2D(IplImage * img, float y, float x)
{
	CvScalar out;

	int i = (int)x;
	int j = (int)y;
	float a = x - i;
	float b = y - j;

	CvScalar I1, I2, I3, I4;
	int i1 = i;
	int i2 = i + 1; if (i2 > img->width - 1)i2 = i1;
	int j1 = j;
	int j2 = j + 1; if (j2 > img->height - 1)j2 = j1;

	I1 = cvGet2D(img, j1, i1);
	I2 = cvGet2D(img, j1, i2);
	I3 = cvGet2D(img, j2, i1);
	I4 = cvGet2D(img, j2, i2);

	for (int k = 0; k < 3; k++)
		out.val[k] = (1 - a)*(1 - b)*I1.val[k]
					+ a * (1 - b)*I2.val[k]
					+ (1 - a)*b*I3.val[k]
					+ a * b*I4.val[k];
	
	return out;
}

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\lena.png");
	IplImage * dst = cvCreateImage(cvSize(800, 800), 8, 3);

	float s = 10;

	int cx = src->width / 2;
	int cy = src->height / 2;

	for(int y2 = 0; y2<dst->height; y2++)
		for (int x2 = 0; x2 < dst->width; x2++)
		{
			float x1 = (x2-cx) / s + cx;			// x2 = s * (x1-cx) + cx
			float y1 = (y2-cy) / s + cy;			// y2 = s * (y1-cy) + cy

			if (x1<0 || x1>src->width - 1)continue;
			if (y1<0 || y1>src->height - 1)continue;

			CvScalar c = myGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, c); 
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	return 0;
}