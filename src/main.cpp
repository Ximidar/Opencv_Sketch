#include "cvsource/pencilSketch.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
    int _sigma_s;
    float _sigma_r, _shade_factor, detail_r, detail_s;
    cout <<argc << endl;
    string filepath, filename, filetype;
    if (argc < 3 || argc > 3){
    	cout << "Usage is PaintByNumbers <IMAGE> <OUT NAME> <SIGMA_S> <SIGMA_R> <SHADE VALUE> <detail s> < desail r>" << endl;
    	return -1;
    }
    else{
        filepath = argv[1]; 
        int delimiter = filepath.find_last_of(".");
        filetype = filepath.substr(delimiter + 1);
    	cout << filepath << endl << filetype << endl;

        filename = argv[2];

        // _sigma_s = atoi(argv[3]);

        // _sigma_r = atof(argv[4]);

        // _shade_factor = atof(argv[5]);

        // detail_s = atof(argv[6]);

        // detail_r = atof(argv[7]);

        // cout << filename << endl << _sigma_s << endl << _sigma_r << endl << _shade_factor << endl <<  detail_s << endl << detail_r << endl;
    }


    // load image
    Mat image = imread(filepath,CV_LOAD_IMAGE_COLOR);
    if(!image.data){
    	cout << "Could not load image" << endl;
    	return -1;
    }
    // we should add another variable that increases detail in the image
    pencilSketcher pencil;
    pencilSketcher::filetype type = pencilSketcher::JPG;

    
    //pencil.sketchPencil(image, _sigma_s, _sigma_r, _shade_factor, detail_s, detail_r);
    pencil.sobel_method(image);

    pencil.saveIMG(pencil.pencil_out, filename, type);

    return 0;
}