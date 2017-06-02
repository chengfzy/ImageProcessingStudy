#include <opencv2/opencv.hpp>
using namespace cv;

const int gWindowWidth = 600;			//���ڴ�С
const String gAtomWindowName = "ԭ��ͼ";	//���ڱ���
const String gRookWindowName = "���ͼ";

//������Բ
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;
	ellipse(img, Point(gWindowWidth / 2, gWindowWidth / 2), Size(gWindowWidth / 4, gWindowWidth / 6),
		angle, 0, 360, Scalar(255, 129, 0), thickness, lineType);
}

//����ʵ��Բ
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;
	circle(img, center, gWindowWidth / 32, Scalar(0, 255, 255), thickness, lineType);
}

//���ư������
void DrawPolygon(Mat img)
{
	int lineType = 8;

	//����һЩ��
	Point rookPoints[1][20];
	rookPoints[0][0] = Point(gWindowWidth / 4, 7 * gWindowWidth / 8);
	rookPoints[0][1] = Point(3 * gWindowWidth / 4, 7 * gWindowWidth / 8);
	rookPoints[0][2] = Point(3 * gWindowWidth / 4, 13 * gWindowWidth / 16);
	rookPoints[0][3] = Point(11 * gWindowWidth / 16, 13 * gWindowWidth / 16);
	rookPoints[0][4] = Point(19 * gWindowWidth / 32, 3 * gWindowWidth / 8);
	rookPoints[0][5] = Point(3 * gWindowWidth / 4, 3 * gWindowWidth / 8);
	rookPoints[0][6] = Point(3 * gWindowWidth / 4, gWindowWidth / 8);
	rookPoints[0][7] = Point(26 * gWindowWidth / 40, gWindowWidth / 8);
	rookPoints[0][8] = Point(26 * gWindowWidth / 40, gWindowWidth / 4);
	rookPoints[0][9] = Point(22 * gWindowWidth / 40, gWindowWidth / 4);
	rookPoints[0][10] = Point(22 * gWindowWidth / 40, gWindowWidth / 8);
	rookPoints[0][11] = Point(18 * gWindowWidth / 40, gWindowWidth / 8);
	rookPoints[0][12] = Point(18 * gWindowWidth / 40, gWindowWidth / 4);
	rookPoints[0][13] = Point(14 * gWindowWidth / 40, gWindowWidth / 4);
	rookPoints[0][14] = Point(14 * gWindowWidth / 40, gWindowWidth / 8);
	rookPoints[0][15] = Point(gWindowWidth / 4, gWindowWidth / 8);
	rookPoints[0][16] = Point(gWindowWidth / 4, 3 * gWindowWidth / 8);
	rookPoints[0][17] = Point(13 * gWindowWidth / 32, 3 * gWindowWidth / 8);
	rookPoints[0][18] = Point(5 * gWindowWidth / 16, 13 * gWindowWidth / 16);
	rookPoints[0][19] = Point(gWindowWidth / 4, 13 * gWindowWidth / 16);

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };
	fillPoly(img, ppt, npt, 1, Scalar(255, 255, 255), lineType);
}

//������
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img, start, end, Scalar(0, 0, 0), thickness, lineType);
}

int main()
{
	//�����հ׵�Matͼ��
	Mat atomImage = Mat::zeros(gWindowWidth, gWindowWidth, CV_8UC3);
	Mat rookImage = Mat::zeros(gWindowWidth, gWindowWidth, CV_8UC3);

	//1. ���ƻ�ѧ�е�ԭ��ʾ��ͼ
	//1.1 �Ȼ��Ƴ���Բ
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);
	//1.2 ����Բ��
	DrawFilledCircle(atomImage, Point(gWindowWidth / 2, gWindowWidth / 2));
	
	//2.�������ͼ
	//2.1. �Ȼ��Ƴ���Բ
	DrawPolygon(rookImage);
	//2.2. ���ƾ���
	rectangle(rookImage, Point(0, 7 * gWindowWidth / 8), Point(gWindowWidth, gWindowWidth), Scalar(0, 255, 255), -1, 8);
	//2.3. ����һЩ�߶�
	DrawLine(rookImage, Point(0, 15 * gWindowWidth / 16), Point(gWindowWidth, 15 * gWindowWidth / 16));
	DrawLine(rookImage, Point(gWindowWidth / 4, 7 * gWindowWidth / 8), Point(gWindowWidth / 4, gWindowWidth));
	DrawLine(rookImage, Point(gWindowWidth / 2, 7 * gWindowWidth / 8), Point(gWindowWidth / 2, gWindowWidth));
	DrawLine(rookImage, Point(3 * gWindowWidth / 4, 7 * gWindowWidth / 8), Point(3 * gWindowWidth / 4, gWindowWidth));

	//3. ��ʾ���Ƴ���ͼ��
	imshow(gAtomWindowName, atomImage);
	moveWindow(gAtomWindowName, 0, 200);
	imshow(gRookWindowName, rookImage);
	moveWindow(gRookWindowName, gWindowWidth, 200);

	waitKey(0);
	return 0;
}