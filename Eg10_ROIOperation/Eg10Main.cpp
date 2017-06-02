#include <opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//���ø���Ȥ����ROIʵ��ͼ�����
bool ROI_AddImage()
{
	//1.����ͼ��
	Mat srcImage = imread("..\\pic\\dota.jpg");
	Mat logoImage = imread("..\\pic\\dota_logo.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡsrcImage����!" << endl;
		return false;
	}
	if (!logoImage.data)
	{
		cout << "��ȡlogoImage����!" << endl;
		return false;
	}


	//2.����һ��Mat���Ͳ��趨ROI
	Mat imageROI = srcImage(Rect(200, 250, logoImage.cols, logoImage.rows));

	//3.���������������ǻҶ�ͼ
	Mat mask = imread("..\\pic\\dota_logo.jpg", 0);

	//4.����Ĥ���Ƶ�ROI
	logoImage.copyTo(imageROI, mask);

	//5.��ʾ���
	imshow("����ROIʵ��ͼ�����", srcImage);

	return true;
}

//ͼ�����Ի��addWeighted()
void LinearBlending()
{
	//1.��ȡͼ��
	Mat srcImage1 = imread("..\\pic\\mogu.jpg");
	Mat srcImage2 = imread("..\\pic\\rain.jpg");
	Mat dstImage;

	//2.ͼ���ϼ�Ȩ
	double alphaValue = 0.5;
	double betaValue = 1.0 - alphaValue;
	addWeighted(srcImage1, alphaValue, srcImage2, betaValue, 0, dstImage);

	//3.��ʾ
	imshow("ԭͼ", srcImage1);
	imshow("���Ի��", dstImage);
}

//����Ȥ����ROI��ʵ���Զ�����������Ի��
bool ROI_LinearBlending()
{
	//1.����ͼ��
	Mat srcImage = imread("..\\pic\\dota.jpg");
	Mat logoImage = imread("..\\pic\\dota_logo.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡsrcImage����!" << endl;
		return false;
	}
	if (!logoImage.data)
	{
		cout << "��ȡlogoImage����!" << endl;
		return false;
	}

	//2.����һ��Mat���Ͳ������趨ROI����
	Mat imageROI = srcImage(Range(250, 250 + logoImage.rows), Range(200, 200 + logoImage.cols));

	//3.��logo�ӵ�ԭͼ��
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0, imageROI);
	

	//4.��ʾ���
	imshow("ROI����ͼ����", srcImage);
	return true;
}

int main()
{
	ROI_AddImage();
	LinearBlending();

	ROI_LinearBlending();

	waitKey(0);
	return 0;
}