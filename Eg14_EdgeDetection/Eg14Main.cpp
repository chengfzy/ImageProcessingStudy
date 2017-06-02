#include <opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//ԭͼ,ԭͼ�ĻҶ�ͼ,Ŀ��ͼ
Mat g_srcImage, g_srcGrayImage, g_dstImage;

//Canny��Ե�����ر���
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;		//trackbarλ�ò���

//Sobel��Ե�����ر���
Mat g_sobelGradientX, g_sobelGradientY;
Mat g_sobelAbsGradientX, g_sobelAbsGradientY;
int g_sobelKernelSize = 1;			//trackbarλ�ò���


//������Canny��Ե���
void CannyBasic()
{
	Mat srcImage = imread("..\\pic\\Orange.jpg");
	Mat srcCopy = srcImage.clone();

	imshow("Origin", srcImage);
	//�߽�canny�÷�:ת���ɻҶ�ͼ,����,��canny,��󽫵õ��ı�Ե��Ϊ����,����ԭͼ��Ч��ͼ��,�õ���ɫ�ı�Եͼ
	Mat dstImage, edge, gray;
	//1.������srcͬ���ͺʹ�С�ľ���
	dstImage.create(srcImage.size(), srcImage.type());
	//��ԭͼת���ɻҶ�ͼ
	cvtColor(srcImage, gray, COLOR_RGB2GRAY);
	//��ʹ��3X3�ں˽���
	blur(gray, edge, Size(3, 3));
	//����Canny����
	Canny(edge, edge, 3, 9, 3);
	//��dstImage������Ԫ������Ϊ0
	dstImage = Scalar::all(0);
	//ʹ��Canny��������ı�Եͼedge��Ϊ����,����ԭͼscrImage����Ŀ��ͼdstImage��
	srcCopy.copyTo(dstImage, edge);
	//��ʾЧ��ͼ
	imshow("Canny Detect Result", dstImage);
}


//Canny��Ե���
static void OnCanny(int, void*)
{
	//��ʹ��3X3�ں˽���
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));
	//����Canny����
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, 3 * g_cannyLowThreshold, 3);
	//��dstImage������Ԫ������Ϊ0
	g_dstImage = Scalar::all(0);
	//ʹ��Canny��������ı�Եͼedge��Ϊ����,����ԭͼscrImage����Ŀ��ͼdstImage��
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);
	//��ʾЧ��ͼ
	imshow("Canny Edge Detect", g_dstImage);
}

//Sobel��Ե���
static void OnSobel(int, void*)
{
	//��X�����ݶ�
	Sobel(g_srcImage, g_sobelGradientX, CV_16S, 1, 0, 2 * g_sobelKernelSize + 1, 1, 0, BORDER_DEFAULT);	
	convertScaleAbs(g_sobelGradientX, g_sobelAbsGradientX);	//�������ֵ,�������ת����8λ

	//��Y�����ݶ�
	Sobel(g_srcImage, g_sobelGradientY, CV_16S, 0, 1, 2 * g_sobelKernelSize + 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradientY, g_sobelAbsGradientY);	//�������ֵ,�������ת����8λ

	//�ϲ��ݶ�
	addWeighted(g_sobelAbsGradientX, 0.5, g_sobelAbsGradientY, 0.5, 0, g_dstImage);

	//��ʾЧ��ͼ
	imshow("Sobel Edge Detect", g_dstImage);
}

//Scharr��Ե���
void ScharrEdgeDetect()
{
	//Scharr�˲���ر���
	Mat gradientX, gradientY;
	Mat absGradientX, absGradientY;

	//��X�����ݶ�
	Scharr(g_srcImage, gradientX, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(gradientX, absGradientX);	//�������ֵ,�������ת����8λ

	//��Y�����ݶ�
	Scharr(g_srcImage, gradientY, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(gradientY, absGradientY);	//�������ֵ,�������ת����8λ

																//�ϲ��ݶ�
	addWeighted(absGradientX, 0.5, absGradientY, 0.5, 0, g_dstImage);

	//��ʾЧ��ͼ
	imshow("Scharr Edge Detect", g_dstImage);
}

//Laplace�任
void LaplaceDetect()
{
	Mat src, srcGray, dst, absDst;

	//ʹ�ø�˹�˲���������
	GaussianBlur(g_srcImage, src, Size(3, 3), 0);
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(src, srcGray, COLOR_RGB2GRAY);
	//ʹ��Laplace����
	Laplacian(srcGray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//�������ֵ,�������ת����8λ
	convertScaleAbs(dst, absDst);
	imshow("Laplace Detect", absDst);
}

int main()
{	
	//CannyBasic();

	g_srcImage = imread("..\\pic\\Orange.jpg");
	if (!g_srcImage.data)
		cout << "Read Image Error" << endl;
	
	imshow("Origin", g_srcImage);

	//������srcͬ���ͺʹ�С�ľ���dst
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	//��ԭͼת���ɻҶ�ͼ
	cvtColor(g_srcImage, g_srcGrayImage, COLOR_RGB2GRAY);

	//Canny
	namedWindow("Canny Edge Detect");
	createTrackbar("Parameters: ", "Canny Edge Detect", &g_cannyLowThreshold, 120, OnCanny);
	OnCanny(0, 0);

	//Sobel
	namedWindow("Sobel Edge Detect");
	createTrackbar("Parameters: ", "Sobel Edge Detect", &g_sobelKernelSize, 3, OnSobel);
	OnSobel(0, 0);

	//Scharr
	ScharrEdgeDetect();
	
	//Laplace
	LaplaceDetect();


	waitKey();
	return 0;
}