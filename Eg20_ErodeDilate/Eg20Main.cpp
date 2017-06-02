#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;


Mat g_srcImage, g_dstImage;

int g_nElementShape = MORPH_RECT;		//Ԫ�ؽṹ����״
int g_nMaxIterationNum = 10;
int g_nErodeDilateNum = 9;
int g_nOpenCloseNum = 9;
int g_nTopBlackHatNum = 2;


//Erode & Dilate
static void OnErodeDilate(int, void*)
{
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;		//ƫ����
	int absoluteOffset = offset > 0 ? offset : -offset;

	//�Զ����
	Mat element = getStructuringElement(g_nElementShape, Size(absoluteOffset * 2 + 1, absoluteOffset * 2 + 1),
		Point(absoluteOffset, absoluteOffset));

	//����
	if (offset < 0)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);
	imshow("Erode & Dilate", g_dstImage);
}

//Open & Close
static void OnOpenClose(int, void*)
{
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;		//ƫ����
	int absoluteOffset = offset > 0 ? offset : -offset;

	//�Զ����
	Mat element = getStructuringElement(g_nElementShape, Size(absoluteOffset * 2 + 1, absoluteOffset * 2 + 1),
		Point(absoluteOffset, absoluteOffset));

	//����
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, element);
	imshow("Open & Close", g_dstImage);
}

//TopHat & BlackHat
static void OnTopBlackHat(int, void*)
{
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;		//ƫ����
	int absoluteOffset = offset > 0 ? offset : -offset;

	//�Զ����
	Mat element = getStructuringElement(g_nElementShape, Size(absoluteOffset * 2 + 1, absoluteOffset * 2 + 1),
		Point(absoluteOffset, absoluteOffset));

	//����
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	imshow("TopHat & BlackHat", g_dstImage);
}


int main()
{
	g_srcImage = imread("..\\pic\\cat.jpg");
	imshow("Origin", g_srcImage);

	//Erode & Dilate
	namedWindow("Erode & Dilate");
	createTrackbar("Iteration Num", "Erode & Dilate", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, OnErodeDilate);

	//Open & Close
	namedWindow("Open & Close");
	createTrackbar("Iteration Num", "Open & Close", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, OnOpenClose);

	//TopHat & BlackHat
	namedWindow("TopHat & BlackHat");
	createTrackbar("Iteration Num", "TopHat & BlackHat", &g_nTopBlackHatNum, g_nMaxIterationNum * 2 + 1, OnTopBlackHat);

	//��ѯ��ȡ������Ϣ
	while (1)
	{
		int c;
		//ִ�лص�����
		OnErodeDilate(g_nErodeDilateNum, 0);
		OnOpenClose(g_nOpenCloseNum, 0);
		OnTopBlackHat(g_nTopBlackHatNum, 0);

		//��ȡ����
		c = waitKey();
		if (c == 'q' || c == 27)		//Q��ESC,�����˳�
			break;
		if (c == 49)		//1:��Բ
			g_nElementShape = MORPH_ELLIPSE;
		else if (c == 50)
			g_nElementShape = MORPH_RECT;
		else if (c == 51)
			g_nElementShape = MORPH_CROSS;
		else if (c == ' ')	//�ո�:�ھ���,��Բ,ʮ���νṹԪ����ѭ��
			g_nElementShape = (g_nElementShape + 1) % 3;
	}
	
	return 0;
}