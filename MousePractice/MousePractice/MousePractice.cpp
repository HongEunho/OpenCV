#include <opencv2/opencv.hpp>
//6가지 bool lbutton, rbutton, mbutton, ctrl, shift, alt;
// flags 최대 32개의 on/off 정보를 담을 수 있는 bit switch
IplImage* img;
IplImage* pal;
CvScalar color = cvScalar(0, 0, 255);
void myMouse(int event, int x, int y, int flags, void *)
{
	// event 0 : CV_EVENT_MOUSEMOVE;
	// event 1 : CV_EVENT_LBUTTONDOWN
	// event 4 : CV_EVENT_LBUTTONUP

//	if(flags == CV_EVENT_FLAG_SHIFTKEY) //shift 만 눌렸을 경우
//	if(flags == CV_EVENT_FLAG_LBUTTON) //lbutton이 눌려져 있는 경우만
	//if(flags % 2 == 1) //lbutton이 눌려져 있는 모든 경우 (lbutton값만 2의0승 1이므로 홀수임)
	//if ((flags & CV_EVENT_FLAG_SHIFTKEY) != 0) 밑에줄과 같은 뜻
	if((flags & CV_EVENT_FLAG_SHIFTKEY) == CV_EVENT_FLAG_SHIFTKEY) //shift가 눌려 있는 경우
		//비트연산자는 논리연산자보다 순위가 낮기 때문에 괄호 필수
		printf("Mouse (%d, %d) : %d : %d \n", x, y, event, flags);

	int myFlag = CV_EVENT_FLAG_LBUTTON + CV_EVENT_FLAG_SHIFTKEY;
	//if (flags == myFlag)
	if((flags & myFlag) == myFlag) //포함하고 있다면 -> &
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
	cvRectangle(img, cvPoint(100, 100), cvPoint(200, 300), cvScalar(0, 255, 0), -1); //-1은 꽉채움 (선은 안됨)
	cvCircle(img, cvPoint(150, 200), 100, cvScalar(255, 0, 0), -1);

	cvShowImage("image", img);
	cvShowImage("pal", pal);
	cvSetMouseCallback("image", myMouse);
	cvSetMouseCallback("pal", myMouse2);
	cvWaitKey();



	return 0;
}