#include <opencv2/opencv.hpp>

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\lena.png");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);
	
	// 1. Compute Histogram //비효율적인 코드
	int histo[3][256];						//histo[0][128] : blue 128인 점의 갯수
	for (int k = 0; k < 3; k++) //k=0 블루,1 그린, 2 레드
		for (int bri = 0; bri < 256; bri++) //밝기값이 0인것부터 차례대로 검사
		{
			int count = 0;
			for (int y = 0; y < size.height; y++)
				for (int x = 0; x < size.width; x++)
				{
					CvScalar f = cvGet2D(src, y, x);
					if (f.val[0] == bri) //(bri가0이라면) 밝기값이 0인것을 찾으면
						count++; //개수를 센다.
				}
			histo[k][bri] = count; //밝기값이 0인것의 전체 개수를 세어 저장
			printf("k=%d bri=%d count=%d\n", k, bri, histo[k][bri]);
		}

	// 2. Compute Cumulative Histogram
	// 3. Use Cumulative histogram as a transfer function

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	return 0;
}