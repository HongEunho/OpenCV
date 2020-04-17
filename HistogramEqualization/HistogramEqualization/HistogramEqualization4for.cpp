#include <opencv2/opencv.hpp>

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\lena.png");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);
	
	// 1. Compute Histogram //��ȿ������ �ڵ�
	int histo[3][256];						//histo[0][128] : blue 128�� ���� ����
	for (int k = 0; k < 3; k++) //k=0 ���,1 �׸�, 2 ����
		for (int bri = 0; bri < 256; bri++) //��Ⱚ�� 0�ΰͺ��� ���ʴ�� �˻�
		{
			int count = 0;
			for (int y = 0; y < size.height; y++)
				for (int x = 0; x < size.width; x++)
				{
					CvScalar f = cvGet2D(src, y, x);
					if (f.val[0] == bri) //(bri��0�̶��) ��Ⱚ�� 0�ΰ��� ã����
						count++; //������ ����.
				}
			histo[k][bri] = count; //��Ⱚ�� 0�ΰ��� ��ü ������ ���� ����
			printf("k=%d bri=%d count=%d\n", k, bri, histo[k][bri]);
		}

	// 2. Compute Cumulative Histogram
	// 3. Use Cumulative histogram as a transfer function

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	return 0;
}