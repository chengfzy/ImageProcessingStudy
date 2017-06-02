#include <opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//����ȫ�ֺ���
void colorReduce(Mat& inputImage, Mat& outputImage, int div, int method)
{
	switch (method)
	{
	case 0:	//��ָ���������
	{
		//1. ��ָ���������
		outputImage = inputImage.clone();
		int rowNumber = outputImage.rows;	//����
		int colNumber = outputImage.cols * outputImage.channels();	//����*ͨ����=ÿһ��Ԫ�صĸ���

		//˫��ѭ�����������е�����ֵ
		for (int i = 0; i < rowNumber; ++i)
		{
			uchar* data = outputImage.ptr<uchar>(i);	//��ȡ��i�е��׵�ַ
			for (int j = 0; j < colNumber; ++j)
			{
				data[j] = data[j] / div * div + div / 2;
			}
		}
	}
	break;
	case 1:		//�õ�������������
	{
		outputImage = inputImage.clone();		
		for (Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); it != outputImage.end<Vec3b>(); ++it)
		{
			(*it)[0] = (*it)[0] / div*div + div / 2;
			(*it)[1] = (*it)[1] / div*div + div / 2;
			(*it)[2] = (*it)[2] / div*div + div / 2;
		}
	}
	break;
	case 2:		//��̬��ַ����
	{
		outputImage = inputImage.clone();
		int rowNumber = outputImage.rows;	//����
		int colNumber = outputImage.cols;	//����

		//��ȡ��ɫͼ������
		for (int i = 0; i < rowNumber; ++i)
		{
			for (int j = 0; j < colNumber; ++j)
			{
				outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;		//Blue Channel
				outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;		//Green Channel
				outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;		//Red Channel
			}
		}
	}
	break;
	}
}


//test for color reduce
void testColorReduce(Mat& srcImage, Mat& dstImage, int method)
{
	//3.��¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());

	//4.������ɫ�ռ���������
	colorReduce(srcImage, dstImage, 32, method);

	//5.��������ʱ�䲢���
	time0 = (static_cast<double>(getTickCount()) - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ: " << time0 << "s" << endl;
}


int main()
{
	//1. ����ԭʼͼ����ʾ
	Mat srcImage = imread("..\\pic\\1.jpg");
	imshow("ԭʼͼ��", srcImage);

	//2.��ԭʼͼ�Ĳ����κ��ⴴ��Ч��ͼ
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	testColorReduce(srcImage, dstImage, 0);		//ָ��
	testColorReduce(srcImage, dstImage, 1);		//������
	testColorReduce(srcImage, dstImage, 2);		//��̬��ַ


	//6.��ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);

	waitKey(0);
	return 0;
}