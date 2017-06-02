#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;		//ԭʼͼ,Ŀ��ͼ,�Ҷ�ͼ,��ģͼ
int g_nFillMode = 1;				//��ˮ����ģʽ
int g_nLowDifference = 20, g_nUpDifference = 20;			//�������ֵ,�������ֵ
int g_nConnectivity = 4;			//��ʾfloodFill������ʶ���Ͱ�λ����ֵͨ
int g_bIsColor = true;				//�Ƿ�Ϊ��ɫͼ�ı�ʶ��
bool g_bUseMask = false;			//�Ƿ���ʾ��Ĥ���ڵĲ���ֵ
int g_nNewMaskVal = 255;			//�µ����»��Ƶ�����ֵ

//�����Ϣ�ص�����
static void OnMouse(int event, int x, int y, int, void*)
{
	//����갴��,�㷵��
	if (event != EVENT_LBUTTONDOWN)
		return;

	//����floodFill����֮ǰ�Ĳ���׼������
	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;		//�շ�Χ����ˮ���
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;			//�շ�Χ����ˮ���
	//��Ƿ���0-7λΪg_nConnectivity, 8-15λΪg_nNewMaskVal����8λ��ֵ,16-23λΪCV_FLOODFILL_FIXED_RANGE����0
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	//�������bgrֵ
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;			//�����ػ��������С�߽��������

	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r* 0.299 + g * 0.587 + b * 0.114);	//���ػ��������ص���ֵ	
	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;	//Ŀ��ͼ�ĸ�ֵ
	int area;

	//2.��ʽ����floodFill����
	if (g_bUseMask)
	{
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
		imshow("mask", g_maskImage);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);		
	}
	imshow("Result", dst);
}


int main()
{
	g_srcImage = imread("..\\pic\\cat.jpg");
	if (!g_srcImage.data)
		cout << "Read Image Error" << endl;

	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);		//����srcImage�ߴ���������Ĥmask

	namedWindow("Result");
	createTrackbar("�������ֵ", "Result", &g_nLowDifference, 255, 0);
	createTrackbar("�������ֵ", "Result", &g_nUpDifference, 255, 0);
	setMouseCallback("Result", OnMouse, 0);


	//ѭ����ѯ����
	while (1)
	{
		//����ʾЧ��ͼ
		imshow("Result", g_bIsColor ? g_dstImage : g_grayImage);

		//��ȡ���̰���
		int c = waitKey();
		//�ж�ESC�Ƿ���,�����±��˳�
		if ((c & 255) == 27)
		{
			cout << "exiting..." << endl;
			break;
		}

		//���ݰ����Ĳ�ͬ,���и��ֲ���
		switch ((char)c)
		{
		case '1':		//1:Ч��ͼ�ڲ�ɫͼ���Ҷ�ͼ֮��ת��
			if (g_bIsColor)
			{
				cout << "����1������,�л���ɫ/�Ҷ�ģʽ,��ǰ����Ϊ��ɫ==>�Ҷ�" << endl;
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIsColor = false;
			}
			else
			{
				cout << "����1������,�л���ɫ/�Ҷ�ģʽ,��ǰ����Ϊ�Ҷ�==>��ɫ" << endl;
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;
			}
			break;
		case '2':		//2.��ʾ/������Ĥ����
			if (g_bUseMask)
			{
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
		case '3':		//3: �ָ�ԭʼͼ��
			cout << "3: �ָ�ԭʼͼ��" << endl;
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
		case '4':		//4:ʹ�ÿշ�Χ����ˮ���
			cout << "4:ʹ�ÿշ�Χ����ˮ���" << endl;
			g_nFillMode = 0;
			break;
		case '5':		//5:ʹ�ý���,�̶���Χ����ˮ���
			cout << "5:ʹ�ý���,�̶���Χ����ˮ���" << endl;
			g_nFillMode = 1;
			break;
		case '6':		//6:ʹ�ý���,������Χ����ˮ���
			cout << "6:ʹ�ý���,������Χ����ˮ���" << endl;
			g_nFillMode = 2;
			break;
		case 7:			//7:������־���ĵ�8λʹ��4λ������ģʽ
			cout << "7:������־���ĵ�8λʹ��4λ������ģʽ" << endl;
			g_nConnectivity = 4;
			break;
		case '8':		//8:������־���ĵ�8λʹ��8λ������ģʽ
			cout << "8:������־���ĵ�8λʹ��8λ������ģʽ" << endl;
			g_nConnectivity = 8;
			break;
		}
	}

	return 0;
}