#include <opencv2/opencv.hpp>

//제곱근 : sqrt()
//제곱 : pow(2,3) 2^3
//sin(angle)
//cos(angle)

int main()
{
	int w = 600;
	int h = 300;
	CvSize size = cvSize(w, h);
	IplImage* img = cvCreateImage(size, 8, 3);

	cvSet(img, cvScalar(255, 255, 255));

	//왼쪽->오른쪽 그라데이션
	//for (int y = 0; y < h; y++)
	//	for (int x = 0; x < w ; x++)
	//	{
	//		// x = 0~w
	//		int x2 = x /float(w)* 255; //0~255;
	//		CvScalar c = cvScalar(0, 0, 0);
	//		c.val[0] = x2;
	//		c.val[2] = 255-x2;
	//		cvSet2D(img, y, x, c);
	//	}

	//원 그라데이션
	/*for(int y=0;y<h;y++)
		for (int x = 0; x < w; x++)
		{
			float Cx = w / 2.0f;
			float Cy = h / 2.0f;
			float d = sqrt((x - Cx)*(x - Cx) + (y - Cy)*(y - Cy));
			CvScalar c = cvScalar(0,0,0);
			c.val[0] = d;
			c.val[2] = 255 - d;
			 
			cvSet2D(img, y, x, c);
		}*/

	//대각선은 x+y가 똑같은 칸 같은색
	//for(int y=0;y<h;y++)
	//	for (int x = 0; x < w; x++)
	//	{
	//		float d = (x + y) / float(w + h) * 255; //d: 0~(w+h)
	//									  //0~255
	//		CvScalar c = cvScalar(0, 0, 0);
	//		c.val[0] = d;
	//		c.val[2] = 255 - d;

	//		cvSet2D(img, y, x, c);
	//	}

	//크기에 상관없이 적용 대각 그라데이션
	//for(int y=0;y<h;y++)
	//	for (int x = 0; x < w; x++)
	//	{
	//		float x2 = x / float(w); //0~1
	//		float y2 = y / float(h); //0~1
	//		float alpha = (x2 + y2)/2.0f; //0~1

	//		CvScalar c = cvScalar(0, 0, 0);
	//		c.val[0] = alpha*255;
	//		c.val[2] = 255 * (1 - alpha);

	//		cvSet2D(img, y, x, c);
	//	}

	//크기에 상관없이 적용가능한 타원(원)
	for(int y=0;y<h;y++)
		for (int x = 0; x < w; x++)
		{
			float x2 = 2 * x / float(w - 1) - 1;
			float y2 = 2 * y / float(h - 1) - 1;
			float alpha = sqrt(x2*x2 + y2 * y2);

			CvScalar c = cvScalar(0, 0, 0);
			c.val[0] = alpha * 255;
			c.val[2] = 255 * (1 - alpha);

			cvSet2D(img, y, x, c);
		}

	cvShowImage("Image", img);
	cvWaitKey();

	return 0;
}