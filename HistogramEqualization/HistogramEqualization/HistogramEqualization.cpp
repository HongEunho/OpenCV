#include <opencv2/opencv.hpp>

void computeHistogram(IplImage * img, int histo[][256]) //2���� �迭 �޴¹�. �ڿ��� �޴´�.
{
	CvSize size = cvGetSize(img);
	for (int k = 0; k < 3; k++)
		for (int bri = 0; bri < 256; bri++)
			histo[k][bri] = 0;

	for (int y = 0; y < size.height; y++) //ȿ������ �˰���
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
	cvSet(img, cvScalar(0, 0, 0)); //�׸� ��ü �����ѻ��� cvSet, ������ ������ ���� cvSet2D

	//for(int k=0;k<3;k++)
	for(int k=0;k<3;k++)
		for (int bri = 0; bri < 256; bri++)
		{
			int x = bri; //���ΰ�
			int h = histo[k][bri] / scale; //����(����)�� //���� ���̺��� scale�� ����.
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
			cumul[k][bri] = cumul[k][bri - 1] + histo[k][bri]; //����
		}
	}
	for (int k = 0; k < 3; k++)
		for (int bri = 0; bri < 256; bri++)
			printf("k=%d bri=%d count=%d\n", k, bri, cumul[k][bri]);
}

void convertImageWithCumulative(IplImage * src, IplImage * dst, int cumul[][256])
{
	CvSize size = cvGetSize(src);
	int num = size.width * size.height; //��ü ���� ����
	for(int y=0;y<size.height;y++)
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);

			CvScalar g;
			for (int k = 0; k < 3; k++)
			{
				int in = f.val[k];				//0<cumul<w*h
				float rank = cumul[k][in]/float(num); //0<rank<1
				int out = rank*255;		//����� �´� ������ ��ȯ //0<out<255
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
	
	// 1. Compute Histogram //��ȿ������ �ڵ�
	int histo[3][256];						//histo[0][128] : blue 128�� ���� ����
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