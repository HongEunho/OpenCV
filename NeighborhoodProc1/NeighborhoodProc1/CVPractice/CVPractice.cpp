#include <opencv2/opencv.hpp>

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\saltpepper.jpg");
	CvSize size = cvGetSize(src);
	IplImage * dst = cvCreateImage(size, 8, 3);

	const int K = 1;
	const int NUM = (2 * K + 1) * (2 * K + 1);

	//median
	for(int y=K;y<size.height-K;y++)
		for (int x = K; x < size.width-K; x++)
		{
			CvScalar f[NUM];
			int index = 0;
			for (int v = -K; v <= K; v++)
				for (int u = -K; u <= K; u++)
				{
					f[index] = cvGet2D(src, y + v, x + u);
					index++; 
				}
			// f[0], f[1], f[2], f[3],,,,,f[8];
			// Á¤·Ä
			for (int k = 0; k < 3; k++)
			{
				for (int j = 0; j < NUM; j++)
				{
					for (int i = j + 1; i < NUM; i++)
						if (f[j].val[k] > f[i].val[k])
						{
							int temp = f[i].val[k];
							f[i].val[k] = f[j].val[k];
							f[j].val[k] = temp;
						}
				}
			}

			CvScalar g = f[NUM/2];
			cvSet2D(dst, y, x, g);
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	return 0;
}