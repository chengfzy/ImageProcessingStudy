#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

Mat g_grayImage, g_dstImage;
const string g_szWindowName = "Image Threshold";
int g_nThresholdValue = 100;
int g_nThresholdType = 3;

//��ֵ�ص�����
void OnThreshold(int, void*)
{
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	imshow(g_szWindowName, g_dstImage);
}

int main()
{
	Mat srcImage = imread("..\\pic\\1.jpg");
	if (!srcImage.data)
		cout << "Read Image Error" << endl;

	//����һ��ԭͼ�ĻҶ�ͼ
	cvtColor(srcImage, g_grayImage, COLOR_RGB2GRAY);
	
	//�������ڲ���ʾԭʼͼ
	namedWindow(g_szWindowName, WINDOW_AUTOSIZE);

	//������������������ֵ
	createTrackbar("Mode", g_szWindowName, &g_nThresholdType, 4, OnThreshold);
	createTrackbar("Parameters", g_szWindowName, &g_nThresholdValue, 255, OnThreshold);

	//��ʼ���Զ������ֵ�ص�����
	OnThreshold(0, 0);

	waitKey();
	return 0;
}