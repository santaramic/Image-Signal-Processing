#include <iostream>
#include <algorithm>
#include "opencv2\core.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\highgui.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat ori_img = imread("C:/bird.jpg");

	int range = 256; 
	int *pixel = new int[range]();
	for (int i = 0; i < range; i++)
		pixel[i] = i;	
	int *count_b = new int[range]();	
	int *count_g = new int[range]();	
	int *count_r = new int[range]();	

	for (int y = 0; y < ori_img.size().height; y++)
	{
		for (int x = 0; x < ori_img.size().width; x++)
		{
			for (int i = 0; i < range; i++)
			{
				if (pixel[i] == ori_img.at<Vec3b>(y, x)[0])
					count_b[i] += 1;	
				if (pixel[i] == ori_img.at<Vec3b>(y, x)[1])
					count_g[i] += 1;	
				if (pixel[i] == ori_img.at<Vec3b>(y, x)[2])
					count_r[i] += 1;
			}
		}
	}

	Mat ori_B_img(ori_img.size().height, ori_img.size().width, CV_8UC1, Scalar(0));
	Mat ori_G_img(ori_img.size().height, ori_img.size().width, CV_8UC1, Scalar(0));
	Mat ori_R_img(ori_img.size().height, ori_img.size().width, CV_8UC1, Scalar(0));

	for (int y = 0; y < ori_img.size().height; y++)
	{
		for (int x = 0; x < ori_img.size().width; x++)
		{
			ori_B_img.at<uchar>(y, x) = ori_img.at<Vec3b>(y, x)[0];
			ori_G_img.at<uchar>(y, x) = ori_img.at<Vec3b>(y, x)[1];
			ori_R_img.at<uchar>(y, x) = ori_img.at<Vec3b>(y, x)[2];
		}
	}

	int *ori_b_max = max_element(count_b, count_b + range); 
	int *ori_g_max = max_element(count_g, count_g + range); 
	int *ori_r_max = max_element(count_r, count_r + range);

	Mat ori_hist_b(int(*ori_b_max), range, CV_8UC1, Scalar(0));	
	Mat ori_hist_g(int(*ori_g_max), range, CV_8UC1, Scalar(0));	
	Mat ori_hist_r(int(*ori_r_max), range, CV_8UC1, Scalar(0));	

	for (int i = 0; i < range; i++)
	{
		int c = 0;
		for (int j = 0; j < int(*ori_b_max); j++)
		{
			if (count_b[i] >= c)
			{
				ori_hist_b.at<uchar>(int(*ori_b_max) - 1 - j, i) = 255;
			}
			c++;
		}
	}

	for (int i = 0; i < range; i++)
	{
		int c = 0;
		for (int j = 0; j < int(*ori_g_max); j++)
		{
			if (count_g[i] >= c)
			{
				ori_hist_g.at<uchar>(int(*ori_g_max) - 1 - j, i) = 255;
			}
			c++;
		}
	}

	for (int i = 0; i < range; i++)	
	{
		int c = 0;
		for (int j = 0; j < int(*ori_r_max); j++)
		{
			if (count_r[i] >= c)
			{
				ori_hist_r.at<uchar>(int(*ori_r_max) - 1 - j, i) = 255;
			}
			c++;
		}
	}

	resize(ori_hist_b, ori_hist_b, Size(512, 256));
	resize(ori_hist_g, ori_hist_g, Size(512, 256));
	resize(ori_hist_r, ori_hist_r, Size(512, 256));

	int *b_sum_plain = new int[range]();	// 이 버퍼를 정의한 이유: 픽셀 빈도수의 누적값에 대한 버퍼 정의, B채널
	int *g_sum_plain = new int[range]();	// 이 버퍼를 정의한 이유: 픽셀 빈도수의 누적값에 대한 버퍼 정의, G채널
	int *r_sum_plain = new int[range]();	// 이 버퍼를 정의한 이유: 픽셀 빈도수의 누적값에 대한 버퍼 정의, R채널

	int *b_regul = new int[range]();	// 이 버퍼를 정의한 이유: 정규화 될 값에 대한 버퍼 정의, B채널
	int *g_regul = new int[range]();	// 이 버퍼를 정의한 이유: 정규화 될 값에 대한 버퍼 정의, G채널
	int *r_regul = new int[range]();	// 이 버퍼를 정의한 이유: 정규화 될 값에 대한 버퍼 정의, R채널

	int sum_b = 0;
	int sum_g = 0;
	int sum_r = 0;
	for (int i = 0; i < range; i++)	// 이 for문은 무엇에 관한것인가? : 픽셀 순서대로 정규화된값을 대체
	{
		sum_b += count_b[i];
		sum_g += count_g[i];
		sum_r += count_r[i];

		b_regul[i] = round((sum_b * 255) / (ori_img.size().height * ori_img.size().width));	
		g_regul[i] = round((sum_g * 255) / (ori_img.size().height * ori_img.size().width));
		r_regul[i] = round((sum_r * 255) / (ori_img.size().height * ori_img.size().width));
	}

	Mat eq_img(ori_img.size().height, ori_img.size().width, CV_8UC3, Scalar(0, 0, 0));

	for (int y = 0; y < ori_img.size().height; y++)
	{
		for (int x = 0; x < ori_img.size().width; x++)
		{
			eq_img.at<Vec3b>(y, x)[0] = b_regul[ori_img.at<Vec3b>(y, x)[0]];	
			b_sum_plain[eq_img.at<Vec3b>(y, x)[0]] += 1;	
			eq_img.at<Vec3b>(y, x)[1] = g_regul[ori_img.at<Vec3b>(y, x)[1]];	
			g_sum_plain[eq_img.at<Vec3b>(y, x)[0]] += 1;	
			eq_img.at<Vec3b>(y, x)[2] = r_regul[ori_img.at<Vec3b>(y, x)[2]];	
			r_sum_plain[eq_img.at<Vec3b>(y, x)[0]] += 1;
		}
	}

	int *max_eq_b = max_element(b_sum_plain, b_sum_plain + range);
	Mat eq_hist_b(int(*max_eq_b), range, CV_8UC1, Scalar(0));

	for (int i = 0; i < range; i++)	
	{
		int c = 0;
		for (int j = 0; j < int(*max_eq_b); j++)
		{
			if (b_sum_plain[i] >= c)
			{
				eq_hist_b.at<uchar>(int(*max_eq_b) - 1 - j, i) = 255;
			}
			c++;
		}
	}


	resize(eq_hist_b, eq_hist_b, Size(512, 256));


	imshow("ori_hist_b", ori_hist_b);
	imshow("eq_hist_b", eq_hist_b);
	imshow("ori_hist_g", ori_hist_g);
	imshow("ori_hist_r", ori_hist_r);
	imshow("ori_B_img", ori_B_img);
	imshow("ori_G_img", ori_G_img);
	imshow("ori_R_img", ori_R_img);
	imshow("ori_color_img", ori_img);
	imshow("eq_img", eq_img);
	waitKey(0);

	delete[] pixel;
	delete[] count_b;
	delete[] count_g;
	delete[] count_r;
	delete[] ori_b_max;
	delete[] ori_g_max;
	delete[] ori_r_max;


	return 0;

}
