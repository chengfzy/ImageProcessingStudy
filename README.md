# Image Processing Study
Image Processing Study

# Study Content
1. Eg01_HelloOpenCV
	OpenCV�Ļ���Ӧ��:ͼ��ʴ��ģ������Ե���
2. Eg02_SavePicture
	����ͼ���ļ�
3. Eg03_BasicMergePicture
	����ͼ�񣬽��м򵥵Ļ�ϣ���ʾ��������ļ�
4. Eg04_TrackBar
	���ƻ���������������ͼ���Alpha���
5. Eg05_MouseOperator
	������
6. Eg06_MatOperation
	Mat����
7. Eg07_BasicStruct:
	������OpenCV���ݽṹ
8. Eg08_BasicGraphDraw
	���Ƽ�ͼ��
9. Eg09_ReadImagePixel
	����ͼ���е����أ���Ϊ��ɫ�ռ�����������256��ɫ��ԭͼ����64����ɫ
10. Eg10_ROIOperation
	ROI������ͼ��ĵ�������
11. Eg11_MultiChannelBlending
	��ͨ��ͼ����Split,Merge

27. Eg27_AffineTransform
	����任
28. Eg28_LogPolar
	ͼ��任,��������ֱ������任
29. Eg29_Remap
	ͼ��任,Remap
30. Eg30_ReadWriteVideo
	Video�Ķ�д����
31. Eg31_AlphaBlending
	Alpha Blending����ʹ��addWeighted������ʶ�����������Ȼ������������blending���е�����
32. Eg32_Deghost
	ȥ��Ӱ�㷨
33. Eg33_OpticalFlow
	����, Lucas-Kanade, Gunnar Farneback���������
	Ref: http://blog.csdn.net/on2way/article/details/48969649; http://blog.csdn.net/on2way/article/details/48969649
34. Eg34_OperatePixel
	����������أ�ʹ�����ַ�����RGBת���ɻҶ�ͼ�����Ƚ�Ч�ʣ�at<Vec>(r, c): 68 ms, iterator: 56 ms, c pointer[]: 34 ms
35. Eg35_FFT
	DFT��IDFT�㷨
36. Eg36_HoughTransform
	Hough�任ʶ��Բ��ֱ��
37. Eg37_Keypoints
	����KeyPoint��ⷽ��
	Harris-Shi-Tomasi: Ч���п�
	Simple Blob: Ч���ܲ�
	FAST(Features from Accelerated Segments Test): Ч�����У���Harris-Shi-Tomasi��㣬����һ�ѵ�������Ȼ����
	SIFT(Scale Invariant Feature Transform): Ч���ܺã����ṩ��128ά��������ʸ��
	SURF(Speeded Up Robost Features): Ч�������ٶȿ�
38. Eg38_KeypointMatch
	KeyPointƥ�䷽��, Brute Force, FLANN
39. Eg39_CameraCalibration
	���У��: �ο�OpenCV tourials file:///D:/Programs/opencv3.3.0/doc/html/d4/d94/tutorial_camera_calibration.html.	��ͼƬ��δʵ��
40. Eg40_VideoTracking
	Video Tracking, using CamShift algorithm, �ο�OpenCV_dir\samples\cpp\camshiftdemo.cpp��������ͷ�����ò��ԣ��������
41. Eg41_CalcHist
	����ͼ���RGBֱ��ͼ��2άHSֱ��ͼ
42. Eg42_HistCompare
	ֱ��ͼ�Ƚ�: ����ֱ��ͼ�ľ����ԣ�����ӳͼ�����ظ��Ҷ�ֵ�����������ܷ�ӳ����ṹ����˴��ںܶ����С�
	��������ṹ��ͬ����������ͬ��ͼ�����ƶȻ�ܵͣ�����ṹ��ͬ�������������ͼ�����ƶ�ȴ�ܸߡ�
43. Eg43_EMDHistCompare
	EMD(½���ƶ�����)�Ƚ�ֱ��ͼ��Ref Learning OpenCV 3, P390, Example13-2
44. Eg44_BackProjection
	����(BackProjection)����ͶӰ��ֻʹ����HSV�е�Hͨ��
	Ref: https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/Histograms_Matching/calcBackProject_Demo1.cpp
45. Eg45_ImprovedBackProjection
	����(BackProjection)����ͶӰ��ʹ����HSV�е�HSͨ������ʹ��FloodFill��Ϊmask
	Ref: https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/Histograms_Matching/calcBackProject_Demo2.cpp

# Project
1. Prj01_HazeRemoval
	ͼƬȥ���㷨
	Ref: 
		[1] Single Image Haze Removal using Dark Channel Prior, Kaiming He, Jian Sun, and Xiaoou Tang
2. Prj02_CameraCalibration
	���У����