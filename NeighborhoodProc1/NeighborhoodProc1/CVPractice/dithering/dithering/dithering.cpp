#include <opencv2/opencv.hpp>

float getDistance(CvScalar a, CvScalar b)
{
	float d = 0.0f;
	//|a-b|
	for (int k = 0; k < 3; k++)
	{
		d += (a.val[k] - b.val[k])*(a.val[k] - b.val[k]);
	}
	return sqrt(d);
}

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\flower.jpg");
	CvSize size = cvGetSize(src);
	IplImage * dst = cvCreateImage(size, 8, 3);

	const int num = 2;
	CvScalar pal[num] = {
						cvScalar(0,0,0),
						cvScalar(255, 255, 255),
						 };

	for (int y = 0; y < size.height; y++)
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;

			float min_d = FLT_MAX;
			int min_idx = 0;
			for (int i = 0; i < num; i++)
			{
				float d = getDistance(f, pal[i]);
				if (d < min_d)
				{
					min_d = d;
					min_idx = i;
				}
			}
			g = pal[min_idx];
			cvSet2D(dst, y, x, g);

			CvScalar d; // d = f-g
			for (int k = 0; k < 3; k++)
				d.val[k] = f.val[k] - g.val[k];

			if (x < size.width - 1)
			{
				CvScalar f1 = cvGet2D(src, y, x + 1);
				for (int k = 0; k < 3; k++) f1.val[k] += 7.0 / 16 * d.val[k];
				cvSet2D(src, y, x + 1, f1);
			}
			if (y < size.height - 1 && x>0)
			{
				CvScalar f2 = cvGet2D(src, y + 1, x - 1);
				for (int k = 0; k < 3; k++) f2.val[k] += 3.0 / 16 * d.val[k];
				cvSet2D(src, y + 1, x - 1, f2);
			}
			if (y < size.height - 1)
			{
				CvScalar f3 = cvGet2D(src, y + 1, x);
				for (int k = 0; k < 3; k++) f3.val[k] += 5.0 / 16 * d.val[k];
				cvSet2D(src, y + 1, x, f3);
			}
			if (y < size.height - 1 && x < size.width - 1)
			{
				CvScalar f4 = cvGet2D(src, y + 1, x + 1);
				for (int k = 0; k < 3; k++) f4.val[k] += 1.0 / 16 * d.val[k];
				cvSet2D(src, y + 1, x + 1, f4);
			}
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}