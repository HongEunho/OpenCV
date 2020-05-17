#include <opencv2/opencv.hpp>
//6���� bool lbutton, rbutton, mbutton, ctrl, shift, alt;
// flags �ִ� 32���� on/off ������ ���� �� �ִ� bit switch
IplImage* img;
IplImage* pal;
CvScalar color = cvScalar(0, 0, 255);
void myMouse(int event, int x, int y, int flags, void *)
{
	// event 0 : CV_EVENT_MOUSEMOVE;
	// event 1 : CV_EVENT_LBUTTONDOWN
	// event 4 : CV_EVENT_LBUTTONUP

//	if(flags == CV_EVENT_FLAG_SHIFTKEY) //shift �� ������ ���
//	if(flags == CV_EVENT_FLAG_LBUTTON) //lbutton�� ������ �ִ� ��츸
	//if(flags % 2 == 1) //lbutton�� ������ �ִ� ��� ��� (lbutton���� 2��0�� 1�̹Ƿ� Ȧ����)
	//if ((flags & CV_EVENT_FLAG_SHIFTKEY) != 0) �ؿ��ٰ� ���� ��
	if((flags & CV_EVENT_FLAG_SHIFTKEY) == CV_EVENT_FLAG_SHIFTKEY) //shift�� ���� �ִ� ���
		//��Ʈ�����ڴ� �������ں��� ������ ���� ������ ��ȣ �ʼ�
		printf("Mouse (%d, %d) : %d : %d \n", x, y, event, flags);

	int myFlag = CV_EVENT_FLAG_LBUTTON + CV_EVENT_FLAG_SHIFTKEY;
	//if (flags == myFlag)
	if((flags & myFlag) == myFlag) //�����ϰ� �ִٸ� -> &
		printf("Shift Click \n");

//	if (event == CV_EVENT_FLAG_LBUTTON)
	if((flags & CV_EVENT_FLAG_LBUTTON) == CV_EVENT_FLAG_LBUTTON)
	{
		cvSet2D(img, y, x, color);
		cvShowImage("image", img);
	}
}

void myMouse2(int event, int x, int y, int flags, void*)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		CvScalar c = cvGet2D(pal, y, x);
		printf("Color = (%f %f %f) \n", c.val[0], c.val[1], c.val[2]);
		color = c;
	}
}
int main()
{
	img = cvLoadImage("c:\\temp\\flower.jpg");
	pal = cvLoadImage("c:\\temp\\palette.bmp");

	cvLine(img, cvPoint(100, 100), cvPoint(200, 300), cvScalar(0, 0, 255), 10);
	cvRectangle(img, cvPoint(100, 100), cvPoint(200, 300), cvScalar(0, 255, 0), -1); //-1�� ��ä�� (���� �ȵ�)
	cvCircle(img, cvPoint(150, 200), 100, cvScalar(255, 0, 0), -1);

	cvShowImage("image", img);
	cvShowImage("pal", pal);
	cvSetMouseCallback("image", myMouse);
	cvSetMouseCallback("pal", myMouse2);
	cvWaitKey();



	return 0;
}