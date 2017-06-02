#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//����Mat����
void CreateMat()
{
	//1. ʹ��Mat()���캯��
	Mat m1(2, 2, CV_8UC3, Scalar(0, 0, 255));
	cout << "m1 = " << endl << m1 << endl << endl;

	//2. ��C++��ͨ�����캯�����г�ʼ��
	int sz[3] = { 2, 2, 2 };
	Mat m2(3, sz, CV_8UC3, Scalar::all(0));

	//3. Ϊ�Ѵ��ڵ�IplImageָ�봴����Ϣͷ
	IplImage* img = cvLoadImage("..\\pic\\spring01.jpg", 1);
	// ERROR!!!
	//Mat m3(img);		//ת��IplImage* ==> Mat

	//4. ����Create()����
	Mat m4;
	m4.create(4, 4, CV_8UC(2));
	cout << "m4 = " << endl << m4 << endl << endl;

	//5. ����Matlabʽ�ĳ�ʼ����ʽ
	Mat m5a = Mat::eye(4, 4, CV_64F);
	cout << "m5a = " << endl << m5a << endl << endl;
	Mat m5b = Mat::ones(2, 2, CV_32F);
	cout << "m5b = " << endl << m5b << endl << endl;
	Mat m5c = Mat::zeros(3, 3, CV_8UC1);
	cout << "m5c = " << endl << m5c << endl << endl;

	//6. ��С����ʹ�ö��ŷָ�ʽ��ʼ��
	Mat m6 = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "m6 = " << endl << m6 << endl << endl;

	//7.Ϊ�Ѵ��ڵĶ��󴴽�����Ϣͷ
	Mat m7 = m6.row(1).clone();
	cout << "m7 = " << endl << m7 << endl << endl;

}

//��ʽ�����
void OutputMat()
{
	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));

	//1. OpenCVĬ�Ϸ��
	cout << "r (Ĭ�Ϸ��) = " << endl << r << ";" << endl << endl;

	//2. Python���
	cout << "r (Python���) = " << endl << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;

	//3.���ŷָ�CSV
	cout << "r (CVS���) = " << endl << format(r, Formatter::FMT_CSV) << ";" << endl << endl;

	//4.Numpy���
	cout << "r (Numpy���) = " << format(r, Formatter::FMT_NUMPY) << ";" << endl << endl;

	//5. C���
	cout << "r (C���) = " << format(r, Formatter::FMT_C) << ";" << endl << endl;

	//6. Matlab���
	cout << "r (Matlab���) = " << format(r, Formatter::FMT_MATLAB) << ";" << endl << endl;

}

//������������������ݽṹ
void OutputOtherStruct()
{
	//1. ����������ά��
	Point2f p(6, 2);
	cout << "��ά�� p = " << p << endl;

	//2.����������ά��
	Point3f p3f(8, 2, 0);
	cout << "��ά�� p3f = " << p3f << endl;

	//3. ������������Mat��vector
	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	cout << "����Mat��vector v = " << Mat(v) << endl;

	//4. ��������vector��
	vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); ++i)
		points[i] = Point2f(i * 5, i % 7);
	cout << "��ά������ points = " << points << endl;
}

int main()
{
	CreateMat();
	OutputMat();
	OutputOtherStruct();

	system("pause");
	return 0;
}