#include <opencv2/opencv.hpp>

IplImage * img;
IplImage * pal;
CvScalar color = cvScalar(0, 0, 255);

CvPoint prePt = cvPoint(0, 0);

void myMouse(int event, int x, int y, int flags, void *)
{ 
	if (event == CV_EVENT_LBUTTONDOWN)
		prePt = cvPoint(x, y);

	if (event == CV_EVENT_MOUSEMOVE && flags == CV_EVENT_FLAG_LBUTTON)
	{
		//cvSet2D(img, y, x, color);
		//cvCircle(img, cvPoint(x, y), 3, color, -1);

		cvLine(img, prePt, cvPoint(x, y), color, 3);
		cvShowImage("image", img);
		prePt = cvPoint(x, y);
	}

	if (event == CV_EVENT_RBUTTONDOWN)
	{
		prePt = cvPoint(x, y);
	}
	if (event == CV_EVENT_RBUTTONUP)
	{
		cvRectangle(img, prePt, cvPoint(x, y), color, 3);
		cvShowImage("image", img);
	}
}

void chooseColor(int event, int x, int y, int flags, void *)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		color = cvGet2D(pal, y, x);
		printf("Color = %f %f %f \n", color.val[0], color.val[1], color.val[2]);
	}
}

int main()
{
	img = cvCreateImage(cvSize(500, 500), 8, 3);
	pal = cvLoadImage("c:\\temp\\palette.bmp");
	cvSet(img, cvScalar(255, 255, 255));

	cvShowImage("image", img);
	cvShowImage("palette", pal);
	cvSetMouseCallback("palette", chooseColor);
	cvSetMouseCallback("image", myMouse);
	cvWaitKey();

	return 0;
}