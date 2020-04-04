#include <opencv2/opencv.hpp>

//CvScalar, CvPoint, CvSize : structures
//cvScalar(..), cvPoint(..), cvSize(..) : functions
//cvGet2D(..), cvSet2D(..)

int main()
{
	//c = cvScalar(b, g, r);
	//CvScalar f = cvScalar(0, 0, 255);
	//CvPoint p = cvPoint(100,200);
	//CvSize size = cvSize(300,200);

	IplImage* img = cvLoadImage("c:\\temp\\flower.jpg");
	if (img == nullptr)
	{
		printf("Not found image!");
		exit(-1);
	}
	cvShowImage("Image", img); //반드시 적용후에 해야함.
	cvWaitKey();

	CvSize size = cvGetSize(img);
	int w = size.width;
	int h = size.height;
	printf("size: w=%d, h=%d\n", w, h);
	int x = 200;
	int y = 200;
	CvScalar c = cvGet2D(img, y, x);
	printf("color: r=%f g=%f b=%f\n", c.val[2], c.val[1], c.val[0]);
	c = cvScalar(0, 0, 255);
	for(int i=0;i<20;i++)
		for (int j = 0; j < 20; j++)
		{
			cvSet2D(img, y + j, x + i, c);
			cvShowImage("Image", img); //반드시 적용후에 해야함.
			cvWaitKey(10);
		}
	

	//cvShowImage("Image", img); //반드시 적용후에 해야함.
	cvWaitKey();

	return 0;
}