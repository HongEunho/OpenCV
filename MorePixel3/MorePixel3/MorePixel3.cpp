#include <opencv2/opencv.hpp>

CvScalar transf(CvScalar f)
{
	CvScalar g = f;	//기울기가 1 y절편 0
	return g;
}

CvScalar adjustBriAndCont(CvScalar f, float a, float b)
{
	//g = a*f + b;
	CvScalar g;
	g.val[0] = a * f.val[0] + b;
	g.val[1] = a * f.val[1] + b;
	g.val[2] = a * f.val[2] + b;
	return g;
}

int main()
{
	IplImage * src = cvLoadImage("c:\\temp\\flower.jpg");
	CvSize size = cvGetSize(src);

	IplImage * dst = cvCreateImage(size,8,3);

	float a = 1.0f;
	float b = 0.0f;
	while (true)
	{
		printf("a= %f b= %f\n", a, b);
		for (int y = 0; y < size.height; y++)
			for (int x = 0; x < size.width; x++)
			{
				CvScalar f = cvGet2D(src, y, x);
				//CvScalar g = transf(f);					//point processing
				CvScalar g = adjustBriAndCont(f, a, b);
				cvSet2D(dst, y, x, g);
			}

		//cvShowImage("source", src);
		cvShowImage("destination", dst);

		int key = cvWaitKey();
		switch (key)
		{
		case '1': b += 10; break;
		case '2': b -= 10; break;
		case '3': a += 0.1f; break;
		case '4': a -= 0.1f; break;
		case 'q': return 0; break;
		default: break;
		}
	}
	

	return 0;
}