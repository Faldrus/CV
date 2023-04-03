#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;

int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

void CannyThreshold(int, void*){
    //Blur the image
    GaussianBlur(src_gray, detected_edges, Size(kernel_size, kernel_size), 0, 0, cv::BORDER_DEFAULT);
    //Apply Canny edge detection
    //Arguments: (source image, output(can be same of input), value entered by user, 3 times lower threshold(recommended by Canny), kernel size)
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
    //Fill images with zeros(black image)
    dst=Scalar::all(0);
    //Maps only the areas of image identified as edges
    src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;
    }

    src = imread(argv[1]);
    if(src.data == NULL){
        std::cout << "Image not found!" << std::endl;
        return -1;
    }
    
    dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    namedWindow(window_name, WINDOW_AUTOSIZE);

    //Create a trackbar to enter the lower threshold
    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

    CannyThreshold(0, 0);

    waitKey(0);
    destroyAllWindows();

    return 0;
}