#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

const string g_szOriginWindowName = "Origin";
const string g_szResultWindowName = "Result";
Mat g_srcImage, g_grayImage, g_dstImage;
int g_nThresh = 50;				//��ֵ
int g_nMaxThresh = 255;			//��ֵ���ֵ


void OnContoursChange(int, void*)
{
	Mat thresholdImage;
	vector<vector<Point>> vContours;
	vector<Vec4i> vHierarchy;

	//ʹ��threshold����Ե
	threshold(g_grayImage, thresholdImage, g_nThresh, 255, THRESH_BINARY);

	//�ҳ�����
	findContours(thresholdImage, vContours, vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//����αƽ�����+��ȡ���κ�Բ�α߽��
	vector<vector<Point>> polyContours(vContours.size());
	vector<Rect> rectBound(vContours.size());
	vector<Point2f> center(vContours.size());
	vector<float> radius(vContours.size());

	//�������в���
	for (unsigned int i = 0; i < vContours.size(); ++i)
	{
		approxPolyDP(Mat(vContours[i]), polyContours[i], 3, true);
		rectBound[i] = boundingRect(Mat(polyContours[i]));
		minEnclosingCircle(polyContours[i], center[i], radius[i]);
	}

	//���ƶ��������+��Χ�ľ��ο�+Բ�ο�
	Mat drawing = Mat::zeros(thresholdImage.size(), CV_8UC3);
	for (unsigned int i = 0; i < vContours.size(); ++i)
	{
		Scalar color = Scalar(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255));
		drawContours(drawing, polyContours, i, color, 1, LINE_AA, vector<Vec4i>(), 0, Point());
		rectangle(drawing, rectBound[i].tl(), rectBound[i].br(), color, 2, LINE_AA, 0);
	}

	imshow(g_szResultWindowName, drawing);
}

int main()
{
	g_srcImage = imread("..\\pic\\cat.jpg");
	if (!g_srcImage.data)
		cout << "Read Image Error" << endl;

	//�õ�ԭͼ�ĻҶ�ͼ�񲢽���ƽ��
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	//����ԭʼͼ���ڲ���ʾ
	namedWindow(g_szOriginWindowName, WINDOW_AUTOSIZE);
	imshow(g_szOriginWindowName, g_srcImage);

	createTrackbar("Threshold", g_szOriginWindowName, &g_nThresh, g_nMaxThresh, OnContoursChange);
	OnContoursChange(0, 0);

	waitKey();
	return 0;
}