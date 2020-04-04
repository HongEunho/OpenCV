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
			CvScalar o;
			o.val[0] = c.val[2];	//blue
			o.val[1] = c.val[1];	//green
			o.val[2] = c.val[0];	//red;
			cvSet2D(img, y, x, o);
		}
	
	cvShowImage("Image", img);
	cvWaitKey();

	return 0;
}