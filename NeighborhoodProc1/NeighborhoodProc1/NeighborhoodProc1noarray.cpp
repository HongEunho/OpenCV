#include <opencv2/opencv.hpp>

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\flower.jpg");
	CvSize size = cvGetSize(src);
	IplImage * dst = cvCreateImage(size, 8, 3);

	// neighborhood processing
	const int K = 10;
	const int num = (2 * K + 1) * (2 * K + 1);
	for(int y=K;y<size.height-K;y++)
		for (int x = K; x < size.width-K; x++)
		{
			//G[x,y] = S(u=-k~k) S(v=-k~k) * 1/(2k+1)*F[x+u, y+v]
			CvScalar f;
			CvScalar g = cvScalar(0, 0, 0);
			
			for (int u = -K; u <= K; u++)
				for (int v = -K; v <= K; v++)
				{
					f = cvGet2D(src, y + v, x + u);
					for (int k = 0; k < 3; k++)
						g.val[k] += f.val[k] / (float)num;
				}
				
			cvSet2D(dst, y, x, g);

		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}