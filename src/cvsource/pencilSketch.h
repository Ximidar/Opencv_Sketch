#ifndef PENCILSKETCH_H
#define PENCIL_SKETCH_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

class pencilSketcher{
public:

	//Public Variables
	enum filetype {PNG, JPG};

	Mat pencil_8bit ;
	Mat pencil_out ;
	Mat enhance_out;
	Mat dog_out;
	Mat blob_out;
	Mat out;
	bool debug;

	//Constructor/Deconstructor
	pencilSketcher();
	~pencilSketcher();

	//Public Functions
	void sketchPencil(Mat &src, int sigma_s, float sigma_r, float shade_factor, float detail_s, float detail_r);
	void sobel_method(Mat &src);
	

	void saveIMG(Mat src, string filename,  filetype type);

private:

	//Private Functions
	void alterPencil(Mat src, int shade_factor);
	void filter_background(Mat src, Mat &out);
	void detailEnhance(Mat src, float sigma_s, float sigma_r);

	//difference of gaussians
	void dog(Mat &src);

	//blob detection
	void blob_detect_and_delete(Mat src, Mat altered);



};

#endif