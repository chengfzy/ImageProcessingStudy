#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;

const string g_szOriginWindowName = "Origin";
const string g_szResultWindowName = "Result";

Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_nMaxThresh = 255;
Mat g_srcCopyImage = g_srcImage.clone();
Mat g_thresoldImage;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;


void OnThreshChange(int, void*)
{
	//��ͼ����ж�ֵ��,������ֵ
	threshold(g_grayImage, g_thresoldImage, g_nThresh, 255, THRESH_BINARY);
	//Ѱ������
	findContours(g_thresoldImage, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	
	//����ÿ������,Ѱ����͹��
	vector<vector<Point>> hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); ++i)
	{
		convexHull(Mat(g_vContours[i]), hull[i], false);
	}

	//������������͹��
	Mat drawing = Mat::zeros(g_thresoldImage.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); ++i)
	{
		Scalar color = Scalar(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	imshow(g_szResultWindowName, drawing);
}


int main()
{
	g_srcImage = imread("..\\pic\\cat.jpg");
	
	//��ԭͼת���ɻҶ�ͼ������ģ������
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	//����ԭͼ���ڲ���ʾ
	namedWindow(g_szOriginWindowName, WINDOW_AUTOSIZE);
	imshow(g_szOriginWindowName, g_srcImage);

	//����������
	createTrackbar("Threshold", g_szOriginWindowName, &g_nThresh, g_nMaxThresh, OnThreshChange);
	OnThreshChange(0, 0);

	waitKey();
	return 0;
}