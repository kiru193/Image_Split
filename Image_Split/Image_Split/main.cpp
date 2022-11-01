#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	Mat readimage = imread("AA.bmp");
	struct image {
		int width = 200;
		int hight = 200;
		int tip_x = 56;
		int tip_y = 56;
	}image;
	
	int w = 200, h = 200;
	if (readimage.empty() != 0) {
		printf("image was not found\n");
		return 0;
	}
	printf("image col is %d \nimage row is %d\n", readimage.cols, readimage.rows);
	Mat resizeimage = Mat::zeros(image.hight * (readimage.rows / image.hight + 1),image.width * (readimage.cols / image.width + 1), CV_8UC3);
	printf("image col is %d \nimage row is %d\n", resizeimage.cols, resizeimage.rows);
	
	for (int i = 0; i < readimage.cols; i++) {
		for (int m = 0; m < readimage.rows; m++) {
			resizeimage.at<Vec3b>(m, i)[0] = readimage.at<Vec3b>(m, i)[0];
			resizeimage.at<Vec3b>(m, i)[1] = readimage.at<Vec3b>(m, i)[1];
			resizeimage.at<Vec3b>(m, i)[2] = readimage.at<Vec3b>(m, i)[2];
		}
	}

	//imshow("", resizeimage);
	//waitKey(0);

	String filename;
	printf("please input file name\n");
	cin >> filename;

	int t_col = readimage.cols / image.width + 1;
	int t_row = readimage.rows / image.hight + 1;
	for (int j = 0; j < t_col * t_row; j++) {
		//読み込んだ画像を指定個所に突っ込むプログラム
		Mat tempimage = Mat::zeros(512, 512, CV_8UC3);
		//printf("col %d row %d\n", readimage.cols, readimage.rows);
		printf("%d %d\n", image.tip_y + image.hight * (j / t_col + 1), image.tip_x + image.width * (j % t_col + 1));
		for (int i = 0; i < image.hight; i++) {
			for (int m = 0; m < image.width; m++) {
				if (image.tip_y + image.hight * (j / t_col + 1) < 512 && image.tip_x + image.width * (j % t_col + 1) < 512) {
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col) + i, image.tip_x + image.width * (j % t_col) + m)[0] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[0];
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col) + i, image.tip_x + image.width * (j % t_col) + m)[1] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[1];
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col) + i, image.tip_x + image.width * (j % t_col) + m)[2] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[2];
				}
				else if(image.tip_y + image.hight * (j / t_col + 1) < 512 && image.tip_x + image.width * (j % t_col + 1) > 512){
					//printf("%d %d\n", image.tip_y + image.hight * (j / t_col - t_col) + i,image.tip_x + image.width * (j % t_row - 2) + m);
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col) + i, image.tip_x + image.width * (j % t_col - t_col/2) + m)[0] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[0];
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col) + i, image.tip_x + image.width * (j % t_col - t_col/2) + m)[1] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[1];
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col) + i, image.tip_x + image.width * (j % t_col - t_col/2) + m)[2] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[2];
				}
				else if (image.tip_y + image.hight * (j / t_col + 1) > 512 && image.tip_x + image.width * (j % t_col + 1) < 512) {
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col - t_col / 2) + i, image.tip_x + image.width * (j % t_col) + m)[0] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[0];
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col - t_col / 2) + i, image.tip_x + image.width * (j % t_col) + m)[1] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[1];
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col - t_col / 2) + i, image.tip_x + image.width * (j % t_col) + m)[2] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[2];
				}
				else {
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col - t_col / 2) + i, image.tip_x + image.width * (j % t_col - t_col / 2) + m)[0] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[0];
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col - t_col / 2) + i, image.tip_x + image.width * (j % t_col - t_col / 2) + m)[1] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[1];
					tempimage.at<Vec3b>(image.tip_y + image.hight * (j / t_col - t_col / 2) + i, image.tip_x + image.width * (j % t_col - t_col / 2) + m)[2] = resizeimage.at<Vec3b>(image.hight * (j / t_col) + i, image.width * (j % t_col) + m)[2];
				}
			}
		}
		/*
		for (int i = 0; i < 512; i++) {
			for (int m = 0; m < 512; m++) {
				if (m + image.hight * (j / t_row) + image.hight < 512 && i + image.width * (j % t_col) + image.width < 512) {
					if (image.tip_x<i && image.tip_x + image.width>i && image.tip_y < m && image.tip_y + image.hight > m) {
						tempimage.at<Vec3b>(m + image.hight * (j / t_row), i + image.width * (j % t_col))[0] = resizeimage.at<Vec3b>(m + image.tip_x + (image.hight * (j / t_row)), i + image.tip_y + (image.width * (j % t_col)))[0];
						tempimage.at<Vec3b>(m + image.hight * (j / t_row), i + image.width * (j % t_col))[1] = resizeimage.at<Vec3b>(m + image.tip_x + (image.hight * (j / t_row)), i + image.tip_y + (image.width * (j % t_col)))[1];
						tempimage.at<Vec3b>(m + image.hight * (j / t_row), i + image.width * (j % t_col))[2] = resizeimage.at<Vec3b>(m + image.tip_x + (image.hight * (j / t_row)), i + image.tip_y + (image.width * (j % t_col)))[2];
					}
				}
				
			}
			
		}
		*/
		
		imshow("", tempimage);
		waitKey(0);

		//MLAのような16等分するプログラム
		int sepa = 4;
		Mat writeimages = Mat::zeros(512, 512, CV_8UC3);

		for (int i = 0; i < sepa * sepa; i++) {
			for (int m = 0; m < writeimages.cols; m++) {
				for (int n = 0; n < writeimages.rows; n++) {
					if ((m - i) % sepa != 0 || (n - i / sepa) % sepa != 0) {
						writeimages.at<Vec3b>(n, m)[0] = 0;
						writeimages.at<Vec3b>(n, m)[1] = 0;
						writeimages.at<Vec3b>(n, m)[2] = 0;
					}
					else {
						writeimages.at<Vec3b>(n, m)[0] = tempimage.at<Vec3b>(n, m)[0];
						writeimages.at<Vec3b>(n, m)[1] = tempimage.at<Vec3b>(n, m)[1];
						writeimages.at<Vec3b>(n, m)[2] = tempimage.at<Vec3b>(n, m)[2];
					}
				}
			}
			//imshow("", writeimages);
			imwrite(filename + to_string(j) +"_"+ to_string(i) + ".bmp", writeimages);
			waitKey(0);
		}
	}
	//imshow("", readimage);
	//waitKey(0);

	
}
