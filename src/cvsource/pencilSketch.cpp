#include "pencilSketch.h"

pencilSketcher::pencilSketcher(){
	debug = false;
}

pencilSketcher::~pencilSketcher(){

}

//Alter Pencil takes in a source image and splits into a grayscale pencil sketch and a
//colorized pencil sketch.
void pencilSketcher::alterPencil(Mat src, int shade_factor){
	 edgePreservingFilter(src,src,1,shade_factor,0.7f);

     //convert to gray for shade
     cvtColor( src, src, CV_BGR2GRAY );

     addWeighted( src, 1, out, 0.3, 0, pencil_out);


}

void pencilSketcher::filter_background(Mat src, Mat &out){

}

void pencilSketcher::sketchPencil(Mat &src,int sigma_s, float sigma_r, float shade_factor, float detail_s, float detail_r){

	

	//alter the image to have a pencil look
   // pencilSketcher::detailEnhance(src, detail_s, detail_r);

	//alterPencil(src, pencil_8bit, pencil_out, sigma_s, sigma_r, shade_factor);
    dog(src);
    dog_out.copyTo(pencil_8bit);
	//alter background
	//filter_background(pencil_out, pencil_out);



    debug = true;
	if(debug){

    	namedWindow("pencil 1", WINDOW_AUTOSIZE);
    	imshow("pencil 1", blob_out);

    	waitKey(0);
	}
}

void pencilSketcher::detailEnhance(Mat src, float sigma_s, float sigma_r){
        cv::detailEnhance(src, enhance_out, sigma_s, sigma_r);
}

void pencilSketcher::saveIMG(Mat src, string filename,  filetype type){
    cout << "Attempting to save " << filename << endl;

	vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(90);

    
    imwrite(filename,src );
}

//difference of gaussians
void pencilSketcher::dog(Mat &src){
    Mat dog1, dog2;
    cv::GaussianBlur(src, dog1, Size(9,9), 0);
    cv::GaussianBlur(src, dog2, Size(29,29), 0);
    absdiff(dog1, dog2, dog_out);

    bitwise_not(dog_out, dog_out);

}

void pencilSketcher::blob_detect_and_delete(Mat src, Mat altered){

    SimpleBlobDetector::Params params;
    vector<KeyPoint> keypoints;


    // Change thresholds
    params.minThreshold = 0;
    params.maxThreshold = 255;
     
    // Filter by Area.
    params.filterByArea = true;
    params.minArea = 50;
     
    // Filter by Circularity
    params.filterByCircularity = false;
    params.minCircularity = 0.1;
     
    // Filter by Convexity
    params.filterByConvexity =false;
    params.minConvexity = 0.87;
     
    // Filter by Inertia
    params.filterByInertia = false;
    params.minInertiaRatio = 0.01;
 

 
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
 
    // SimpleBlobDetector::create creates a smart pointer. 
    // So you need to use arrow ( ->) instead of dot ( . )
    detector->detect( altered, keypoints);

    Mat im_with_keypoints;
    drawKeypoints( src, keypoints, blob_out, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );



    //cout << keypoints << endl;
}

void pencilSketcher::sobel_method(Mat &src){
    Mat src_gray;
    Mat grad;
    char* window_name = "Sobel Method";
    int scale = 1;
    int delta = 1;
    int ddepth = CV_16S;

    int c;

    
    

    GaussianBlur( src, src, Size(9,9), 0, 0, BORDER_DEFAULT );

        /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );

        /// Create window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

        /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    // Gradient X
    
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    // Gradient Y
    
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

        /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 1, abs_grad_y, 1, 0, grad );

    //invert the image
    bitwise_not ( grad, out );

    //GaussianBlur( grad, out, Size(3,3), 0, 0, BORDER_DEFAULT );
    

    alterPencil(src, 100);
       

    imshow( window_name, pencil_out );

    waitKey(0);


}