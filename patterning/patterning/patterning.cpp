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

	for(int y=0;y<size.height;y+=grid) //한 점당 네 점을 바꿀 것이라 한칸씩 건너 뜀.
		for (int x = 0; x < size.width; x += grid)
		{
			CvScalar f = cvGet2D(blur, y, x);
			int bri = (f.val[0] + f.val[1] + f.val[2]) / 3;
			float d = 255.0f / (num + 1); // d = 구간 ... 0~51 점x / 51~102 점1/ 102~153 점2...
			int dot = bri / d; // 지금 밝기에서 몇개의 점을 찍어야 할지
			if (dot > num) dot = num;
			for (int i = 0; i < dot; i++)
			{
				int u = pattern[i]%grid;
				int v = pattern[i]/grid;
				cvSet2D(dst, y+v, x+u, cvScalar(255, 255, 255)); //검은배경에 하얀점을 찍기 때문에 255,255,255
			}
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}