#include <opencv2/opencv.hpp>

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\flower.jpg");
	CvSize size = cvGetSize(src);
	IplImage * dst = cvCreateImage(size, 8, 3);

	// neighborhood processing
	const int k = 4 ;
	const int num = (2 * k + 1) * (2 * k + 1);
	for(int y=k;y<size.height-k;y++)
		for (int x = k; x < size.width-k; x++)
		{
			//G[x,y] = S(u=-k~k) S(v=-k~k) * 1/(2k+1)*F[x+u, y+v]
			CvScalar f[num];
			int index = 0;
			for (int u = -k; u <= k; u++)
				for (int v = -k; v <= k; v++)
				{
					f[index] = cvGet2D(src, y + v, x + u);
					index++;
				}

			CvScalar g = cvScalar(0, 0, 0);
			for (int i = 0; i < num; i++)
				for(int k=0;k<3;k++)
					g.val[k] += f[i].val[k]/(float)num;
			cvSet2D(dst, y, x, g);

		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}