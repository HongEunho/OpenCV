#include <opencv2/opencv.hpp>

CvScalar gammaCorrection(CvScalar in, float gamma)
{
	CvScalar out;

	//sqrt(2.0f) = 1.414...
	//pow(a,b) : a^b
	//sqrt(2.0f) = pow(2, 0.5f)
	
	/*out.val[0] = pow(in.val[0], gamma);
	out.val[1] = pow(in.val[1], gamma);
	out.val[2] = pow(in.val[2], gamma);*/
	for (int k = 0; k < 3; k++)
	{
		//감마함수를 쓰려면 0~1범위로 지정해놨다가 다시 복원을 해줘야함. (함수 그림 참고)
		out.val[k] = pow(in.val[k]/255.0f, gamma)*255.0f;
	}
	return out;
}

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\lena.png");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);

	float gamma = 1.0f;

	//1 key : gamma down
	//2 key : gamma up

	while (true)
	{
		for (int y = 0; y < size.height; y++)
			for (int x = 0; x < size.width; x++)
			{
				CvScalar f = cvGet2D(src, y, x);
				CvScalar g = gammaCorrection(f, gamma);
				cvSet2D(dst, y, x, g);
			}
		//cvShowImage("src", src);
		cvShowImage("dst", dst);
		int key = cvWaitKey();
		if (key == '1') gamma -= 0.1f;
		else if (key == '2')gamma += 0.1f;
		else if (key == 'q')break;
	}
	

	

	return 0;
}