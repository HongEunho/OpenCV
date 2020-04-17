#include <opencv2/opencv.hpp>

void computeHistogram(IplImage * img, int histo[][256]) //2차원 배열 받는법. 뒤에꺼 받는다.
{
	CvSize size = cvGetSize(img);
	for (int k = 0; k < 3; k++)
		for (int bri = 0; bri < 256; bri++)
			histo[k][bri] = 0;

	for (int y = 0; y < size.height; y++) //효율적인 알고리즘
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(img, y, x);
			for (int k = 0; k < 3; k++)
				histo[k][(int)f.val[k]]++;
		}

	/*for (int k = 0; k < 3; k++)
		for (int bri = 0; bri < 256; bri++)
			printf("k=%d bri=%d count=%d\n", k, bri, histo[k][bri]);*/
}

void drawHistogram(int histo[][256], float scale)
{
	CvSize size = cvSize(256, 300);
	IplImage * img = cvCreateImage(size, 8, 3);
	cvSet(img, cvScalar(0, 0, 0)); //그림 전체 동일한색은 cvSet, 한점만 설정할 때는 cvSet2D

	//for(int k=0;k<3;k++)
	for(int k=0;k<3;k++)
		for (int bri = 0; bri < 256; bri++)
		{
			int x = bri; //가로값
			int h = histo[k][bri] / scale; //세로(높이)값 //원래 높이보다 scale배 줄임.
			if (h > size.height - 1) h = size.height - 1;
			for (int y = size.height - 1; y > size.height - 1 - h; y--)
			{
				CvScalar f = cvGet2D(img, y, x);
				f.val[k] = 255;
				cvSet2D(img, y, x, f);
			}
		}

	cvShowImage("img", img);
	cvWaitKey();
}

void computeCumulative(int histo[][256], int cumul[][256])
{
	for (int k = 0; k < 3; k++)
	{
		cumul[k][0] = histo[k][0];
		for (int bri = 1; bri < 256; bri++)
		{
			cumul[k][bri] = cumul[k][bri - 1] + histo[k][bri]; //누적
		}
	}
	for (int k = 0; k < 3; k++)
		for (int bri = 0; bri < 256; bri++)
			printf("k=%d bri=%d count=%d\n", k, bri, cumul[k][bri]);
}

void convertImageWithCumulative(IplImage * src, IplImage * dst, int cumul[][256])
{
	CvSize size = cvGetSize(src);
	int num = size.width * size.height; //전체 점의 개수
	for(int y=0;y<size.height;y++)
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);

			CvScalar g;
			for (int k = 0; k < 3; k++)
			{
				int in = f.val[k];				//0<cumul<w*h
				float rank = cumul[k][in]/float(num); //0<rank<1
				int out = rank*255;		//등수에 맞는 색으로 변환 //0<out<255
				g.val[k] = out;
			}
			cvSet2D(dst, y, x, g);
		}
}

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\histogram1.jpg");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);
	
	// 1. Compute Histogram //비효율적인 코드
	int histo[3][256];						//histo[0][128] : blue 128인 점의 갯수
	computeHistogram(src, histo);
	drawHistogram(histo, 15);

	// 2. Compute Cumulative Histogram
	int cumul[3][256];
	computeCumulative(histo, cumul);
	drawHistogram(cumul, size.width*size.height/300.0f);

	// 3. Use Cumulative histogram as a transfer function
	convertImageWithCumulative(src, dst, cumul);

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	cvSaveImage("c:\\temp\\histoEq.jpg", dst);
	return 0;
}