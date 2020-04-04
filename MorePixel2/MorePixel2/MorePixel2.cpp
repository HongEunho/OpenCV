#include <opencv2/opencv.hpp>

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\lena.png");

	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	////Copy & Gray
	//for(int y=0;y<size.height;y++)
	//	for (int x = 0; x < size.width; x++)
	//	{ 
	//		CvScalar f = cvGet2D(src, y, x);
	//		int v = (f.val[0] + f.val[1] + f.val[2])/3;

	//		CvScalar g = cvScalar(v,v,v); // ????? image filtering
	//		cvSet2D(dst, y, x, g);
	//	}

	//부분 그레이
	/*for(int y=0;y<size.height;y++)
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = f;
			
			if ((x > size.width/ 2 && y<size.height/2) ||
				(x<size.width/2 && y>size.height/2))
			{
				int v = (f.val[0] + f.val[1] + f.val[2]) / 3;
				g = cvScalar(v, v, v);
			}
			cvSet2D(dst, y, x, g);
		}*/

	//좀더 간단한 코드
	for (int y = 0; y < size.height; y++)
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = f;

			int x2 = x / float(size.width) * 2; //0~2
			int y2 = y / float(size.height) * 2; //0~2
			if ((x2+y2)%2 == 1)
			{
				int v = (f.val[0] + f.val[1] + f.val[2]) / 3;
				g = cvScalar(v, v, v);
			}
			cvSet2D(dst, y, x, g);
		}

	cvShowImage("Source", src);
	cvShowImage("Destination", dst);
	cvWaitKey();
	return 0;
}