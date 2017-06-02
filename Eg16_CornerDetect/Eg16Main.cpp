#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;


Mat g_srcImage, g_tempImage, g_grayImage;
int g_nThreshould = 30;			//��ǰ��ֵ
int g_nMaxThreshould = 175;		//�����ֵ

//Harris�ǵ���
void OnCornerHarris(int, void*)
{
	Mat dstImage;
	Mat normImage;			//��һ�����ͼ
	Mat scaledImage;		//���Ա任���8λ�޷������ε�ͼ

	//��ʼ��
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_tempImage = g_srcImage.clone();

	//���нǵ���
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	//��һ����ת��
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);
	//����⵽�Ľǵ���Ƴ���
	for (int j = 0; j < normImage.rows; ++j)
	{
		for (int i = 0; i < normImage.cols; ++i)
		{
			if ((int)normImage.at<float>(j, i) > g_nThreshould + 80)
			{
				circle(g_tempImage, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}

	imshow("Harris Result", g_tempImage);
	imshow("Scaled Result", scaledImage);
}

int main()
{
	g_srcImage = imread("..\\pic\\car.jpg");
	if (!g_srcImage.data)
		cout << "Read Image Error" << endl;
	imshow("Origin", g_srcImage);

	g_tempImage = g_srcImage.clone();
	//��һ�ŻҶ�ͼ
	cvtColor(g_tempImage, g_grayImage, COLOR_RGB2GRAY);

	//�������ں͹�����
	namedWindow("Harris Result");
	createTrackbar("Threshould", "Harris Result", &g_nThreshould, g_nMaxThreshould, OnCornerHarris);
	OnCornerHarris(0, 0);

	waitKey();
	return 0;
}