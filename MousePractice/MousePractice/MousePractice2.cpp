#include <opencv2/opencv.hpp>

IplImage * img;
IplImage * buf;
CvPoint pt1, pt2;
CvScalar color;
void myMouse(int event, int x, int y, int flags, void *)
{
	
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		pt1 = cvPoint(x, y);
		pt2 = cvPoint(x, y);
		color = cvScalar(rand() % 256, rand() % 256, rand() % 256);
		cvCopy(img, buf);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		pt2 = cvPoint(x, y);
		cvRectangle(img, pt1, pt2, color, 3);
		cvShowImage("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE)
	{
		if ((flags & CV_EVENT_FLAG_LBUTTON) == CV_EVENT_FLAG_LBUTTON)
		{
			// ���� ���� ��� �����.
			// cvRectangle(img, pt1, pt2, cvScalar(255, 255, 255), 3);
			// ���� ���� �� �����
			// cvSet(img, cvScalar(255, 255, 255));

			// ���� ���·� ������. (���� = �׸� --> ���� �׸�(���� �簢�������� ���)�� �����ϰ� �ǵ��� �ش�.)
			cvCopy(buf, img);
			// ���� �׸���
			pt2 = cvPoint(x, y);
			cvRectangle(img, pt1, pt2, color, 3);
			cvShowImage("img", img);
		}
	}
}

int main()
{
	img = cvCreateImage(cvSize(500, 500), 8, 3);
	buf = cvCreateImage(cvGetSize(img), 8, 3);
	cvSet(img, cvScalar(255, 255, 255));


	cvShowImage("img", img);

	cvSetMouseCallback("img", myMouse);
	cvWaitKey();

	return 0;
}