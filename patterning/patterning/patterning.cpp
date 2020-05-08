#include <opencv2/opencv.hpp>

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\flower.jpg");
	CvSize size = cvGetSize(src);
	IplImage * blur = cvCreateImage(size, 8, 3);
	IplImage * dst = cvCreateImage(size, 8, 3);

	const int grid = 2;
	const int num = grid*grid;
	int pattern[num] = { 2,1,3,0 };

	cvSmooth(src, blur, CV_BLUR, (grid-1)*2+1);
	cvSet(dst, cvScalar(0, 0, 0));

	for(int y=0;y<size.height;y+=grid) //�� ���� �� ���� �ٲ� ���̶� ��ĭ�� �ǳ� ��.
		for (int x = 0; x < size.width; x += grid)
		{
			CvScalar f = cvGet2D(blur, y, x);
			int bri = (f.val[0] + f.val[1] + f.val[2]) / 3;
			float d = 255.0f / (num + 1); // d = ���� ... 0~51 ��x / 51~102 ��1/ 102~153 ��2...
			int dot = bri / d; // ���� ��⿡�� ��� ���� ���� ����
			if (dot > num) dot = num;
			for (int i = 0; i < dot; i++)
			{
				int u = pattern[i]%grid;
				int v = pattern[i]/grid;
				cvSet2D(dst, y+v, x+u, cvScalar(255, 255, 255)); //������濡 �Ͼ����� ��� ������ 255,255,255
			}
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}