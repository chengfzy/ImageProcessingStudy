#include <opencv2/opencv.hpp>
#include <time.h>
using namespace cv;
using namespace std;

void WriteFile()
{
	//��ʼ��
	FileStorage fs("test.yaml", FileStorage::WRITE);	//can be .yaml, .xml, .txt, .doc

	//��ʼд���ļ�
	fs << "frameCount" << 5;
	time_t rawTime;
	time(&rawTime);
	fs << "calibrationDate" << asctime(localtime(&rawTime));
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 1);
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	fs << "features" << "[";
	for (int i = 0; i < 3; ++i)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;

		fs << "{" << "x" << x << "y" << y << "lbp" << "[:";
		for (int j = 0; j < 8; ++j)
			fs << ((lbp >> j) & 1);
		fs << "]" << "}";
	}
	fs << "]";
	fs.release();
}

void ReadFile()
{
	//�ı�console������ɫ
	system("color 6F");

	//��ʼ��
	FileStorage fs("test.yaml", FileStorage::READ);

	//��һ�ַ���,��FileNode����
	int frameCount = (int)fs["frameCount"];
	
	//�ڶ��ַ���,ʹ��FileNode�����>>
	std::string date;
	fs["calibrationDate"] >> date;
	Mat cameraMatrix, distCoeffs;
	fs["cameraMatrix"] >> cameraMatrix;
	fs["distCoeffs"] >> distCoeffs;

	cout << "frameCount: " << frameCount << endl << "calibration date: " << date << endl
		<< "camera matrix: " << cameraMatrix << endl << "distortion coeffs: " << distCoeffs << endl;

	//ʹ��FileNodeIterator��������
	FileNode features = fs["features"];
	int idx = 0;
	vector<uchar> lbpval;
	for (FileNodeIterator it = features.begin(); it != features.end(); ++it, ++idx)
	{
		cout << "features #" << idx << ": ";
		cout << "x = " << (int)(*it)["x"] << ", y = " << (int)(*it)["y"] << ", lbp: (";
		//����Ҳ����ʹ��filenode >> vector�������������׵ض���ֵ����
		(*it)["lbp"] >> lbpval;
		for (int i = 0; i < (int)lbpval.size(); ++i)
			cout << " " << (int)lbpval[i];
		cout << ")" << endl;
	}
	fs.release();
}

int main()
{
	WriteFile();
	ReadFile();

	system("pause");
	return 0;
}