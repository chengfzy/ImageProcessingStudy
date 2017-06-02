#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

const string windowName = "���Ի��ʾ��";	//������

const int g_nMaxAlphaValue = 100;	//Alpha�����ֵ
int g_nAlphaValueSlider;			//��������Ӧ�ı���
double g_dAlphaValue;
double g_dBetaValue;


//ȫ�ֱ���
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void OnTrackbar(int, void*)
{
	//�����ǰalphaֵ��Ӧ�����ֵ�ı���
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	//betaֵ
	g_dBetaValue = 1.0 - g_dAlphaValue;
	//����alpha��betaֵ�������Ի��
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0, g_dstImage);
	//��ʾЧ��
	imshow(windowName, g_dstImage);
}


int main()
{
	//����ͼ��
	g_srcImage1 = imread("..\\pic\\spring01.jpg");
	if (!g_srcImage1.data)
		cout << "ͼƬ1������!" << endl;
	g_srcImage2 = imread("..\\pic\\spring02.jpg");
	if (!g_srcImage2.data)
		cout << "ͼƬ2������!" << endl;
		 
	namedWindow(windowName);

	char trackbarName[50];
	sprintf(trackbarName, "͸��ֵ%d", g_nMaxAlphaValue);
	createTrackbar(trackbarName, windowName, &g_nAlphaValueSlider, g_nMaxAlphaValue, OnTrackbar);
	
	//����ڻص���������ʾ
	OnTrackbar(g_nAlphaValueSlider, 0);

	waitKey(0);
	return 0;
}
