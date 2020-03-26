#include <opencv2/opencv.hpp>


int main()
{
	

	IplImage* img = cvLoadImage("c:\\temp\\flower.jpg");
	if (img == nullptr)
	{
		printf("Not found image!");
		exit(-1);
	}

	cvShowImage("Image", img); //반드시 적용후에 해야함.
	cvWaitKey();

	CvSize size = cvGetSize(img);
	for(int x=0; x<size.width; x++)
		for (int y = 0; y < size.height; y++)
		{
			CvScalar c = cvGet2D(img, y, x);
			c.val[0] = 0;	//blue
			c.val[1] = 0;	//green
			c.val[2];	//red;
			cvSet2D(img, y, x, c);
		}
	 
	cvShowImage("Image", img);
	cvWaitKey();

	return 0;
}