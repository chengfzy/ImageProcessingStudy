#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//ͼ��ʴ
Mat Erosion(const Mat& srcImage)
{
	//���и�ʴ����
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	return dstImage;
}


// ͼ��ģ��
Mat Blur(const Mat& srcImage)
{
	Mat dstImage;
	blur(srcImage, dstImage, Size(7, 7));
	return dstImage;
}


//Canny ��Ե���
Mat EdgeDetect(const Mat& srcImage)
{
	Mat grayImage, blurImage, edge;
	//1. ת���ɻҶ�ͼ��
	cvtColor(srcImage, grayImage, ColorConversionCodes::COLOR_RGB2GRAY);
	//2. ʹ��3*3�ں�������
	blur(grayImage, blurImage, Size(3, 3));
	//3. ����Canny����
	Canny(srcImage, edge, 3, 9.3);
	return edge;
}


int main()
{
	cout << "version: " << CV_VERSION << endl;

	Mat srcImage = imread("..\\pic\\cat.jpg");		//read image
	imshow("ԭͼ", srcImage);						//show in window

	//1.��ʴ
	imshow("Ч��ͼ-��ʴ", Erosion(srcImage));
	//2.ͼ��ģ��
	imshow("��ֵ�˲�", Blur(srcImage));
	//3.Cannyͼ���Ե���
	imshow("Canny��Ե���", EdgeDetect(srcImage));
	

	waitKey(0);							//wait and close
}