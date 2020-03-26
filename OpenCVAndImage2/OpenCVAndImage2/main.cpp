#include <opencv2/opencv.hpp>

int main()
{
	IplImage* img[2];
	img[0] = cvLoadImage("c:\\temp\\flower.jpg");
	img[1] = cvLoadImage("c:\\temp\\flower2.jpg");
	for (int i = 0; i < 2; i++)
		if (img[i] == nullptr) //꼭 해줄것
		{
			printf("%d-th Image File not found!\n", i + 1);
			exit(-1);
		}
	int c = 0;
	while (true)
	{
		cvShowImage("Image1", img[c]);
		char key = cvWaitKey();
		switch (key)
		{
		case '1':
			c = 0;
			break;
		case '2':
			c = 1;
			break;
		case 'q':
			return 0;
		default:break;
		}
		
	}
	

	

	//cvReleaseImage(&img1); //이미지 메모리 해제
	//cvReleaseImage(&img2);
	//cvDestroyWindow("Image1"); //창 닫기
	//cvDestroyWindow("Image2");

	return 0;
}