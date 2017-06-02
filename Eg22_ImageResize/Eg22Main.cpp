#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	const string szWindowName = "Resize Image";

	Mat srcImage = imread("..\\pic\\1.jpg");
	if (!srcImage.data)
		cout << "Read Image Error" << endl;

	namedWindow(szWindowName, WINDOW_AUTOSIZE);
	imshow(szWindowName, srcImage);

	Mat tmpImage = srcImage;
	Mat dstImage = srcImage;
	
	int key = 0;

	//��ѯ��ȡ������Ϣ
	while (1)
	{
		key = waitKey();
		switch (key)
		{
		case 27:		//ESC
		case 'q':		//Q
			return 0;
			break;

		case 'a':		//A: pyrUP
			pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "A: pyrUp" << endl;
			break;
		case 'w':		//W: resize
			resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "W: resize" << endl;
			break;
		case 'd':		//D: pyrDown
			pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "D: pyrDown" << endl;
			break;
		case 's':
			resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "S: resize" << endl;
			break;
		}

		imshow(szWindowName, dstImage);
		tmpImage = dstImage;		//��dstImage����tmpImage,������һ��ѭ��
	}

	return 0;
}