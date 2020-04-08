#include <opencv2/opencv.hpp>

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\sejong_small.jpg");
	CvSize size = cvGetSize(src);
	IplImage* dst1 = cvCreateImage(size, 8, 3);
	IplImage* dst2 = cvCreateImage(size, 8, 3);
	IplImage* dst3 = cvCreateImage(size, 8, 3);
	IplImage* dst4 = cvCreateImage(size, 8, 3);
	IplImage* dst5 = cvCreateImage(size, 8, 3);
	IplImage* dst6 = cvCreateImage(size, 8, 3);

	int w = size.width;
	int h = size.height;

	if (src == nullptr) //
	{
		printf("Image File not found!\n");
		exit(-1);
	}

	//#1
	for(int y = 0 ; y < h ; y++)
		for (int x = 0; x < w; x++)
		{
			CvScalar c = cvGet2D(src, y, x);
			cvSet2D(dst1, h - y - 1, x, c);
		}
	
	//#2
	for(int y=0;y<h;y++)
		for (int x = 0; x < w; x++)
		{
			CvScalar c = cvGet2D(src, y, x);

			if (x < w / 2)
				cvSet2D(dst2, y, x + w / 2, c);
			else
				cvSet2D(dst2, y, x - w / 2, c);
		}
	
	//#3
	for(int y=0;y<h;y++)
		for (int x = 0; x < w; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = f;

			float x2 = x / float(w - 1); //0~1
			float y2 = y / float(h - 1); //0~1

			if (x2 < 0.5 && y2 < 0.5) //왼쪽 상단
			{
				if (x2 + y2 < 0.5) 
				{
					int v = (f.val[0] + f.val[1] + f.val[2]) / 3;
					g = cvScalar(v, v, v);
				}
			}
			
			if (x2 > 0.5 && y2 < 0.5) //오른쪽 상단
			{
				if (x2 - y2 > 0.5)
				{
					int v = (f.val[0] + f.val[1] + f.val[2]) / 3;
					g = cvScalar(v, v, v);
				}
			}

			if (x2 < 0.5 && y2 > 0.5) //왼쪽 하단
			{
				if (x2 - y2 < -0.5)
				{
					int v = (f.val[0] + f.val[1] + f.val[2]) / 3;
					g = cvScalar(v, v, v);
				}
			}

			if (x2 > 0.5 && y2 > 0.5) //오른쪽 하단
			{
				if (x2 + y2 > 1.5)
				{
					int v = (f.val[0] + f.val[1] + f.val[2]) / 3;
					g = cvScalar(v, v, v);
				}
			}
			cvSet2D(dst3, y, x, g);
		}
	//#4
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			float x2 = 2 * x / float(w - 1) - 1;
			float y2 = 2 * y / float(h - 1) - 1;

			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = f;

			if (x2*x2 + y2 * y2 > 1)
			{
				int v = (f.val[0] + f.val[1] + f.val[2]) / 3;
				g = cvScalar(v, v, v);
			}
			cvSet2D(dst4, y, x, g);
		}
	}

	//#5
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			float Cx = w / 2.0f;
			float Cy = h / 2.0f;
			float d = sqrt((x - Cx)*(x - Cx) + (y - Cy)*(y - Cy));

			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = f;

			if ( (int)d % 30 > 20 )
			{
				g = cvScalar(0, 0, 0);
			}
			cvSet2D(dst5, y, x, g);
		}
	}

	//#6
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = f;

			int x2 = x / float(w) * 10; //0~10
			int y2 = y / float(h) * 10; //0~10
			if ((x2 + y2) % 2 == 1)
			{
				g = cvScalar(0, 0, 0);
			}
			cvSet2D(dst6, y, x, g);
		}
	}

	cvShowImage("Image1", dst1);
	cvShowImage("Image2", dst2);
	cvShowImage("Image3", dst3);
	cvShowImage("Image4", dst4);
	cvShowImage("Image5", dst5);
	cvShowImage("Image6", dst6);
	cvWaitKey();
	return 0;
}