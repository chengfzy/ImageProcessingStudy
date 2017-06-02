#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image(600, 600, CV_8UC3);

	while (true)
	{
		int count = theRNG().uniform(3, 103);
		vector<Point> points;	//��ֵ

		//������ɵ�����
		for (int i = 0; i < count; ++i)
		{
			Point point;
			point.x = theRNG().uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = theRNG().uniform(image.rows / 4, image.cols * 3 / 4);
			points.push_back(point);
		}
		//���Ƴ������ɫ�ĵ�
		image = Scalar::all(0);
		for (int i = 0; i < count; ++i)
		{
			circle(image, points[i], 3, Scalar(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255)),
				FILLED, LINE_AA);
		}

		if (0)		//��С����ľ��ΰ�Χ
		{
			//�Ը�����2D�㼯,Ѱ����С����İ�Χ����
			RotatedRect box = minAreaRect(Mat(points));
			Point2f vertex[4];
			box.points(vertex);

			//���Ƴ���С����İ�Χ����
			for (int i = 0; i < 4; ++i)
				line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		}
		else    //��С�����Բ��Χ
		{
			Point2f center;
			float radius = 0;
			minEnclosingCircle(Mat(points), center, radius);
			//���Ƴ���С����İ�ΧԲ
			circle(image, center, radius, Scalar(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255)),
				2, LINE_AA);

		}

		imshow("Image", image);

		char key = (char)waitKey();
		if (key == 27)
			break;
	}

	return 0;
}