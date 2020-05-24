#include <opencv2/opencv.hpp>

void buildSAT(IplImage * src, CvScalar** SAT)
{
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	for(int y=0;y<h;y++)
		for (int x = 0; x < w; x++)
		{
			//A = 한칸 왼쪽 사각형 영역
			//B = 한칸 윗쪽 사각형 영역
			//C = A와 B의 중복된 영역
			//SAT[y][x] = A + B - C + I(x,y);
			CvScalar A = cvScalar(0, 0, 0);
			if (x >= 1) A = SAT[y][x - 1];
			CvScalar B = cvScalar(0, 0, 0);
			if (y >= 1) B = SAT[y - 1][x];
			CvScalar C = cvScalar(0, 0, 0);
			if (x >= 1 && y >= 1) C = SAT[y - 1][x - 1];
			CvScalar D = cvGet2D(src, y, x);

			for(int k=0;k<3;k++)
				SAT[y][x].val[k] = A.val[k] + B.val[k] - C.val[k] + D.val[k];
		}
}

void mySmooth(IplImage * src, IplImage * dst, int K)
{
	CvSize size = cvGetSize(src);
	int w = size.width;
	int h = size.height;
	CvScalar** SAT = new CvScalar*[size.height];
	for (int y = 0; y < size.height; y++)
		SAT[y] = new CvScalar[size.width];
	//SAT[y][x]; SAT[height][width]

	// 1. build Summed Area Table
	buildSAT(src, SAT);

	// 2. use SAT to smooth the image
	for(int y=0; y<h; y++)
		for (int x = 0; x < w; x++)
		{
			CvScalar g;
			CvScalar A = cvScalar(0, 0, 0);
			CvScalar B = cvScalar(0, 0, 0);
			CvScalar C = cvScalar(0, 0, 0);
			CvScalar D = cvScalar(0, 0, 0);

			int x1 = x + K;				if (x1 > w - 1) x1 = w - 1;
			int y1 = y + K;				if (y1 > h - 1) y1 = h - 1;
			int x2 = x - K - 1;			if (x2 < -1)x2 = -1;
			int y2 = y - K - 1;			if (y2 < -1)y2 = -1;
			
			A = SAT[y1][x1];
			if (x2 >= 0)				B = SAT[y1][x2];
			if (y2 >= 0)				C = SAT[y2][x1];
			if (x2 >= 0 && y2 >= 0)		D = SAT[y2][x2];

			int W = x1 - x2; //2*K+1
			int H = y1 - y2; //2*K+1
			int area = W * H; //이렇게 해주는 이유는 항상 2*K+1로 유지되진 않기 때문(끝부분)
			for(int k=0;k<3;k++)
				g.val[k] = (A.val[k] - B.val[k] - C.val[k] + D.val[k])/area;

			cvSet2D(dst, y, x, g);
		}

	for (int y = 0; y < h; y++)
		delete[] SAT[y];
	delete[] SAT;
}

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\flower.jpg");

	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	mySmooth(src, dst, 50);

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	return 0;
}