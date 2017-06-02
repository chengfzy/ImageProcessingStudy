#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//��ͨ�����
bool MultiChannelBlending()
{
	//1.����ͼ��
	Mat srcImage = imread("..\\pic\\dota.jpg");
	Mat logoImage = imread("..\\pic\\dota_logo.jpg", 0);
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

	//2.��һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	vector<Mat> channels;
	split(srcImage, channels);

	//3.��ԭͼ����ɫͨ�����÷��ظ�imageBlueChannel
	Mat imageBlueChannel = channels.at(0);

	//4.����ɫͨ�����·�������logoͼ���м�Ȩ�������õ���Ͻ��
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage,
		0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//5.������ͨ�����ºϳ�һ����ͨ��
	merge(channels, srcImage);

	//6.��ʾЧ��ͼ
	imshow("��Ϸԭ��+logo��ɫͨ��", srcImage);

	return true;
}


int main()
{
	MultiChannelBlending();

	waitKey(0);
	return 0;
}