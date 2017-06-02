#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	//1.�������ʾͼ��
	Mat girl = imread("..\\pic\\girl.jpg");
	namedWindow("����ͼ");
	imshow("����ͼ", girl);

	//2.����ͼ����
	Mat image = imread("..\\pic\\dota.jpg");
	Mat logo = imread("..\\pic\\dota_logo.jpg");
	namedWindow("ԭ��ͼ");
	imshow("ԭ��ͼ", image);
	namedWindow("Logo");
	imshow("Logo", logo);
	//����һ��Mat���ڴ��ͼ���ROI
	Mat imageROI;
	imageROI = image(Rect(800, 350, logo.cols, logo.rows));
	//��logo�ӵ�ԭͼ��
	addWeighted(imageROI, 0.5, logo, 0.3, 0, imageROI);
	//��ʾЧ��
	namedWindow("ԭ��+logoͼ");
	imshow("ԭ��+logoͼ", image);

	//3.������ļ�
	imwrite("..\\pic\\Eg03Out.jpg", image);
	
	waitKey(0);
	return 0;
}