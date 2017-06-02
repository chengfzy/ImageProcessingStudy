// ��ӳ��
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage, dstImage;
	Mat mapX, mapY;

	srcImage = imread("..\\pic\\1.jpg");
	if (!srcImage.data)
		cout << "Read Image Error" << endl;

	//������ԭʼͼһ����Ч��ͼ,x��ӳ��ͼ,y��ӳ��ͼ
	dstImage.create(srcImage.size(), srcImage.type());
	mapX.create(srcImage.size(), CV_32FC1);
	mapY.create(srcImage.size(), CV_32FC1);

	//����ÿһ�����ص�,�ı�mapX��mapY��ֵ
	for (int j = 0; j < srcImage.rows; ++j)
		for (int i = 0; i < srcImage.cols; ++i)
		{
			mapX.at<float>(j, i) = static_cast<float>(i);
			mapY.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}

	//������ӳ�����
	remap(srcImage, dstImage, mapX, mapY, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//��ʾЧ��ͼ
	imshow("Result", dstImage);

	waitKey();
	return 0;
}