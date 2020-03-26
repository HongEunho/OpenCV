#include <opencv2/opencv.hpp>


int main()
{
	IplImage* img;
	img = cvLoadImage("c:\\flower.jpg");

	if (img != nullptr)
	{
		cvSaveImage("c:\\eclipse\\flower.bmp", img);
	}

	if (img == nullptr) //null pointer
	{
		printf("File not found~!\n"); //이 4줄 반드시 추가
		exit(-1);
	}

	printf("w=%d h=%d \n", img->width, img->height);

	//cvNamedWindow("Image1");
	//cvNamedWindow("Image2");

	cvShowImage("Image", img);

	while (true)
	{
		char key = cvWaitKey();
		printf("%c \n", key);
		if (key == 'q')
			break;
	}
	

	return 0;
}