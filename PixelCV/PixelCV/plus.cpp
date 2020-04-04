#include <opencv2/opencv.hpp>


int main()
{
	
	IplImage* img1 = cvLoadImage("c:\\temp\\flower.jpg");
	IplImage* img2 = cvLoadImage("c:\\temp\\flower2.jpg");

	CvSize size1 = cvGetSize(img1);
	CvSize size2 = cvGetSize(img2);
	printf("s1: %d %d\n", size1.width, size1.height);
	printf("s2: %d %d\n", size2.width, size2.height);
	int w = size1.width; if (w > size2.width) w = size2.width;
	int h = size1.height; if (h > size2.height) h = size2.height;
	//int w = (size1.width < size2.width) ? size1.width : size2.width;
	//int h = (size1.height < size2.height) ? size1.height: size2.height;

	cvShowImage("Image1", img1);
	cvShowImage("Image2", img2);
	cvWaitKey();

	for(int x=0;x<w;x++)
		for (int y = 0; y < h; y++)
		{
			CvScalar c1 = cvGet2D(img1, y, x);
			CvScalar c2 = cvGet2D(img2, y, x);

			CvScalar c;  // c = (c1 + c2)/2;
			c.val[0] = (c1.val[0] + c2.val[0])/2;
			c.val[1] = (c1.val[1] + c2.val[1])/2;
			c.val[2] = (c1.val[2] + c2.val[2])/2;
			cvSet2D(img1, y, x, c);
		}
	cvShowImage("Image", img1);
	cvWaitKey();

	return 0;
}