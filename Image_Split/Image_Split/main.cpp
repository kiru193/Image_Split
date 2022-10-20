#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	Mat readimage = imread("AA.bmp");
	int w = 400, h = 400;
	if (readimage.empty() != 0) {
		printf("image was not found\n");
		return 0;
	}
	printf("image col is %d \nimage row is %d\n", readimage.cols, readimage.rows);
	Mat resizeimage = Mat::zeros(w * (readimage.cols / w + 1), h * (readimage.rows / h + 1), CV_8UC3);
	printf("image col is %d \nimage row is %d\n", resizeimage.cols, resizeimage.rows);
	for (int i = 0; i < readimage.cols; i++) {
		for (int m = 0; m < readimage.rows; m++) {
			resizeimage.at<Vec3b>(m, i)[0] = readimage.at<Vec3b>(m, i)[0];
			resizeimage.at<Vec3b>(m, i)[1] = readimage.at<Vec3b>(m, i)[1];
			resizeimage.at<Vec3b>(m, i)[2] = readimage.at<Vec3b>(m, i)[2];
		}
	}
	//imshow("", resizeimage);
	waitKey(0);

	int t_col = readimage.cols / w + 1;
	int t_row = readimage.rows / h + 1;
	for (int j = 0; j < t_col * t_row; j++) {
		//読み込んだ画像を真ん中に突っ込むプログラム
		Mat tempimage = Mat::zeros(512, 512, CV_8UC3);
		//printf("col %d row %d\n", readimage.cols, readimage.rows);
		for (int i = 0; i < 512; i++) {
			for (int m = 0; m < 512; m++) {
				if ((512 - w) / 2 <= i && 512 - (512 - w) / 2 > i && (512 - h) / 2 <= m && 512 - (512 - h) / 2 > m) {
					tempimage.at<Vec3b>(m, i)[0] = resizeimage.at<Vec3b>(m - ((512 - h) / 2) + (h * (j / t_row)), i - ((512 - w) / 2) + (w * (j % t_col)))[0];
					tempimage.at<Vec3b>(m, i)[1] = resizeimage.at<Vec3b>(m - ((512 - h) / 2) + (h * (j / t_row)), i - ((512 - w) / 2) + (w * (j % t_col)))[1];
					tempimage.at<Vec3b>(m, i)[2] = resizeimage.at<Vec3b>(m - ((512 - h) / 2) + (h * (j / t_row)), i - ((512 - w) / 2) + (w * (j % t_col)))[2];

				}
			}
		}
		//imshow("", tempimage);
		waitKey(0);

		//MLAのような16等分するプログラム
		int sepa = 4;
		Mat writeimages = Mat::zeros(512, 512, CV_8UC3);
		String filename;
		printf("please input file name\n");
		cin >> filename;

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
			imwrite(filename + to_string(i) + ".bmp", writeimages);
			waitKey(0);
		}
	}
	//imshow("", readimage);
	//waitKey(0);

	
}
