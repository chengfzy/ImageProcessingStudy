#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	//���������,��������������
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	//����һЩMat����
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstWarpImage, dstWarpRotateImage;

	//����Դͼ����һЩ��ʼ��
	srcImage = imread("..\\pic\\1.jpg");
	if (!srcImage.data)
		cout << "Read Image Error" << endl;
	imshow("Origin", srcImage);

	dstWarpImage = Mat::zeros(srcImage.size(), srcImage.type());

	//����Դͼ���Ŀ��ͼ���ϵ�������Լ������任
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));
	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));

	//��÷���任
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	//��Դͼ��Ӧ�øո���õķ���任
	warpAffine(srcImage, dstWarpImage, warpMat, dstWarpImage.size());
	imshow("Warp", dstWarpImage);

	//��ͼ��������ź�����ת:������ͼ���е�˳ʱ����ת50��,��������Ϊ0.6����ת����
	Point center = Point(dstWarpImage.cols / 2, dstWarpImage.rows / 2);
	double angle = -30.0;
	double scale = 0.6;
	//ͨ���������תϸ����Ϣ�����ת����
	rotMat = getRotationMatrix2D(center, angle, scale);
	//��ת�����ź��ͼ��
	warpAffine(dstWarpImage, dstWarpRotateImage, rotMat, dstWarpImage.size());
	imshow("Warp and Rotation", dstWarpRotateImage);

	waitKey();
	return 0;
}