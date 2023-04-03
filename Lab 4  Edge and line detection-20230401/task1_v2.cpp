#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

struct Parameters{
    int treshold;
    int kernel_size;
    int sigma;
    Mat img;
    Mat gray_scale;
};

void trackBarChangeThreshold(int value, void* values){
    Parameters* params = (Parameters*) values;
    params->treshold = value;

    Mat canny_img(params->img.rows, params->img.cols, CV_8U);
    GaussianBlur(params->gray_scale, canny_img, Size(params->kernel_size, params->kernel_size), params->sigma);

    Canny(canny_img, canny_img, params->treshold, 3 * params->treshold, params->kernel_size);
    imshow("Canny image", canny_img);

    return;
}

void trackBarChangeSigma(int value, void* values){
    Parameters* params = (Parameters*) values;
    params->sigma = value;

    Mat canny_img(params->img.rows, params->img.cols, CV_8U);
    GaussianBlur(params->gray_scale, canny_img, Size(params->kernel_size, params->kernel_size), params->sigma);

    Canny(canny_img, canny_img, params->treshold, 3 * params->treshold, params->kernel_size);
    imshow("Canny image", canny_img);

    return;
}


int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;
    }

    Mat img = imread(argv[1]);
    if(img.data == NULL){
        std::cout << "Image not found!" << std::endl;
        return -1;
    }

    Parameters* params = new Parameters;
    params->treshold = 0;
    params->sigma = 0;
    params->kernel_size = 3;
    params->img = img;

    cvtColor(img, params->gray_scale, COLOR_BGR2GRAY);

    namedWindow("Canny image");

    createTrackbar("Min Threshold: ", "Canny image", nullptr, 100, trackBarChangeThreshold, (void*)params);
    setTrackbarPos("Min Threshold: ", "Canny image", params->treshold);

    createTrackbar("Sigma: ", "Canny image", nullptr, 100, trackBarChangeSigma, (void*)params);
    setTrackbarPos("Sigma: ", "Canny image", params->sigma);

    imshow("Canny image", params->img);
    waitKey(0);
    destroyAllWindows();

    delete(params);

    return 0;
}