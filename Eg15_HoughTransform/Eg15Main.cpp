#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;

//ȫ����������
Mat g_srcImage, g_dstImage, g_midImage;	//ԭʼͼ,Ŀ��ͼ���м�ͼ
vector<Vec4i> g_lines;					//��ŵõ����߶�ʸ������
int g_nThreshould = 100;				//��������trackbarλ�ò���

//�����߱任
void HoughLineDetect()
{
	Mat srcImage = imread("..\\pic\\building.jpg");
	Mat midImage, standardDstImage, progressDstImage;		//��ʱ������Ŀ��ͼ
	
	//��ʾԭʼͼ
	imshow("Origin", srcImage);

	//���б�Ե���,ת���ɻҶ�ͼ
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, standardDstImage, CV_GRAY2BGR);
	//��ʾ��Ե�����ͼ
	imshow("Canny Edge Detect", midImage);

	//���б�׼�����߱任
	vector<Vec2f> standardLines;		//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLines(midImage, standardLines, 1, CV_PI / 180, 150, 0, 0);
	//������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < standardLines.size(); ++i)
	{
		float rho = standardLines[i][0], theta = standardLines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * a);
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * a);
		line(standardDstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
	}
	//��ʾЧ��ͼ
	imshow("Standard Hough Lines Detect", standardDstImage);

	//���л�����ʱ任
	cvtColor(midImage, progressDstImage, CV_GRAY2BGR);
	vector<Vec4i> progresLines;		//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLinesP(midImage, progresLines, 1, CV_PI / 180, 80, 50, 10);
	//������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < progresLines.size(); ++i)
	{
		Vec4i l = progresLines[i];
		line(progressDstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);
	}
	//��ʾЧ��ͼ
	imshow("Progressive Hough Lines Detect", progressDstImage);
}

//�ۼƸ��ʻ���任
void HoughCircleDetect()
{
	Mat srcImage = imread("..\\pic\\Circle.jpg");
	Mat midImage, dstImage;		//��ʱ������Ŀ��ͼ
	imshow("Circle Origin", srcImage);

	//ת��Ϊ�Ҷ�ͼ������ͼ��ƽ��
	cvtColor(srcImage, midImage, COLOR_RGB2GRAY);
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

	//���л���Բ�任
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 2, 10, 200, 100, 0, 0);

	//������ͼ�л��Ƴ�Բ
	for (size_t i = 0; i < circles.size(); ++i)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//����Բ��
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����
		circle(srcImage, center, radius, Scalar(155, 50, 265), 3, 8, 0);
	}

	//��ʾЧ��ͼ
	imshow("Hough Circle Detect", srcImage);
}

static void OnHoughLines(int, void*)
{
	Mat midImage = g_midImage.clone();
	Mat dstImage = g_dstImage.clone();

	//����HoughLinesP����
}


int main()
{
	//HoughLineDetect();
	HoughCircleDetect();

	waitKey();
	return 0;
}