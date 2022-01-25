#include <iostream>
#include "opencv2\core.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\highgui.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat ori_img = imread("C:/bird.jpg");

	int height = ori_img.size().height;
	int width = ori_img.size().width;
	int channels = 3;

	int filter_size = 7;
	int padding_factor = (filter_size / 2) * 2;
	int padding_height = height + padding_factor;
	int padding_width = width + padding_factor;

	int *padding_img_buf = new int[padding_height * padding_width * channels]();

	for (int c = 0; c < channels; c++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				padding_img_buf[((y + (filter_size / 2)) * padding_width + x + (filter_size / 2)) * channels + c] = ori_img.at<Vec3b>(y, x)[c];
				// 원본이미지를 패딩 버퍼에 넣어주는 반복문, 패딩테두리만 남기고 모두 넣어준다.
				// 39 >> 42 >> 45 >> ... >> 74 >> 78...
				// 40 >> 43 >> ....
			}
		}
	}

	Mat padding_buf_img(padding_height, padding_width, CV_8UC3, Scalar(0, 0, 0));
	// opencv로 보기위한 mat
	// 1. 패딩높이, 2.패딩너비, 3. 몇 채널인지, 4. 초기화 방법

	for (int c = 0; c < channels; c++)
	{
		for (int y = 0; y < padding_height; y++)
		{
			for (int x = 0; x < padding_width; x++)
			{
				padding_buf_img.at<Vec3b>(y, x)[c] = padding_img_buf[(y * padding_width + x) * channels + c];
				// 값이 들어간 패딩버퍼를 출력하여 확인한다.
				// 새로 선언한 Mat에다가 padding_img_buf를 그대로 넣어주는것이다.
				// 0부터 그대로 넣어주면 되므로 이제 padding_value를 더할 필요는 없음.
			}
		}
	}


	float **gau_filter_2D = new float*[filter_size];
	for (int i = 0; i < filter_size; i++)
	{
		gau_filter_2D[i] = new float[filter_size];
	}

	double m = 0;
	for (int j = -(filter_size / 2); j < (filter_size / 2) + 1; j++)
	{
		for (int i = -(filter_size / 2); i < (filter_size / 2) + 1; i++)
		{
			gau_filter_2D[j + (filter_size / 2)][i + (filter_size / 2)] = exp(-(pow(j, 2) + pow(i, 2)) / 2 * 0.0001);
			m += exp(-(pow(j, 2) + pow(i, 2)) / 2 * 0.001);
			cout << gau_filter_2D[j + (filter_size / 2)][i + (filter_size / 2)] << endl;
		}
	}


	/*float gau_filter_2D_stc[5][5] = 
	{ { 0., 0., 0., 0., 0. },
	{ 0., 0., 0., 0., 0. },
	{ 0., 0., 0., 0., 0. },
	{ 0., 0., 0., 0., 0. }, 
	{ 0., 0., 0., 0., 0. }, };
	double n = 0;
	for (int j = -(filter_size / 2); j < (filter_size / 2) + 1; j++)
	{
		for (int i = -(filter_size / 2); i < (filter_size / 2) + 1; i++)
		{
			gau_filter_2D_stc[j + 1][i + 1] = exp(-(pow(j, 2) + pow(i, 2)) / 2 * 0.0001);
			n += exp(-(pow(j, 2) + pow(i, 2)) / 2 * 0.001);
			cout << gau_filter_2D_stc[j + 1][i + 1] << endl;
		}
	}
	*/

	Mat gau_img(height, width, CV_8UC3, Scalar(0, 0, 0));		// 가우시안이 적용된 이미지를 확인하기위한 Mat
	for (int c = 0; c < channels; c++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				double sum = 0;	// 주석
				for (int j = 0; j < filter_size; j++)
				{
					for (int i = 0; i < filter_size; i++)
					{
						sum += padding_buf_img.at<Vec3b>(y + j, x + i)[c] * gau_filter_2D[j][i] / m;
						// sum 자체를(0,0)부터 차례로 double n으로 나누어서 넣어주는것이다.
					}
				}
				gau_img.at<Vec3b>(y, x)[c] = sum;
				//이제 좌표를 슬라이딩하면서 새로운 mat에 넣어주는 과정
			}
		}
	}




	cout << "완성" << endl;

	imshow("Pading_img", padding_buf_img);
	imshow("original_img", ori_img);
	imshow("gau_img", gau_img);
	waitKey(0);


	for (int i = 0; i < filter_size; i++)
		delete[] gau_filter_2D[i];
	delete[] gau_filter_2D;
	delete[] padding_img_buf;

	return 0;
}
