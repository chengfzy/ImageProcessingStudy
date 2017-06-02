#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//ȫ�ֱ���
const string g_windowName = "���򴰿�";	//���ڱ���
Rect g_rectangle;
bool g_bDrawingBox = false;				//�Ƿ���л���
RNG g_rng(12345);

//��������
void OnMouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& img, Rect box);


//���ݲ�ͬ������¼����в�ͬ�Ĳ���
void OnMouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(Mat*)param;
	switch (event)
	{
	case EVENT_MOUSEMOVE:	//����ƶ�
	{
		if (g_bDrawingBox)
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;
	case EVENT_LBUTTONDOWN:	//�Ҽ�����
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);
	}
	break;
	case EVENT_LBUTTONUP:	//���̧��
	{
		g_bDrawingBox = false;	//�ñ�Ƿ�Ϊfalse
		//�Կ�͸�<0�Ĵ���
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//���ú������л���
		DrawRectangle(image, g_rectangle);
	}
	break;
	default:
		break;
	}
}

//�Զ���ľ��λ��ƺ���
void DrawRectangle(Mat& img, Rect box)
{
	//�����ɫ
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

void ShowHelpText();

int main()
{
	//1. ׼������
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	srcImage = Scalar::all(0);

	//2. �����������ص�����
	namedWindow(g_windowName);
	setMouseCallback(g_windowName, OnMouseHandle, (void*)&srcImage);

	//3. ������ѭ���������л��Ƶı�ʶ��Ϊ��ʱ�����л���
	while (1)
	{
		srcImage.copyTo(tempImage);		//����Դͼ����ʱ����
		//����ʶ��Ϊ��ʱ������л���
		if (g_bDrawingBox)
			DrawRectangle(tempImage, g_rectangle);
		imshow(g_windowName, tempImage);
		//����ESCʱ�����˳�
		if (waitKey(10) == 27)
			break;
	}

	return 0;
}