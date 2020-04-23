#include <opencv2/opencv.hpp>

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\flower.jpg");
	CvSize size = cvGetSize(src);

	IplImage* dst = cvCreateImage(size, 8, 3);
	IplImage* blur = cvCreateImage(size, 8, 3);
	IplImage* diff = cvCreateImage(size, 8, 3);


	//restore the original image

	float alpha = 0.0f;
	int kernel = 1;
	while (true)
	{
		cvSmooth(src, blur, CV_GAUSSIAN, 2*kernel+1);

		// compute difference image
		for (int y = 0; y < size.height; y++)
			for (int x = 0; x < size.width; x++)
			{
				CvScalar A = cvGet2D(src, y, x);
				CvScalar B = cvGet2D(blur, y, x);
				//CvScalar D = A - B;
				CvScalar D;
				for (int k = 0; k < 3; k++)
					D.val[k] = (A.val[k] - B.val[k]) / 2 + 128; //-255<D<255 --> 0<D/2+128<255
				cvSet2D(diff, y, x, D);

			}

		for (int y = 0; y < size.height; y++)
			for (int x = 0; x < size.width; x++)
			{
				CvScalar D = cvGet2D(diff, y, x);
				CvScalar B = cvGet2D(blur, y, x);

				//A = B + D
				CvScalar A;
				for (int k = 0; k < 3; k++)
					A.val[k] = B.val[k] + alpha * (D.val[k] - 128) * 2; // ���⼭ D�� ��¥ D�� �ƴ϶� D/2+128�̹Ƿ� D'�� ����.
															// D' = D/2+128
				cvSet2D(dst, y, x, A);
			}
		printf("alpha = %f \n kernel = %d", alpha, kernel);
		cvShowImage("dst", dst);
		int key = cvWaitKey();
		if (key == '1') alpha -= 0.2f;
		if (key == '2') alpha += 0.2f;
		if (key == '3') kernel--;
		if (key == '4') kernel++;
		//Ŀ���� �������� �������, Ŭ���� ū������� ���̰� �������
		if (kernel < 1) kernel = 1;
	}

//	cvShowImage("src", src);
	
//	cvShowImage("blur", blur);
//	cvShowImage("diff", diff);
	return 0;
}