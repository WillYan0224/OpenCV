#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    CommandLineParser parser(argc, argv, "{@input | lena.jpg | input image}");
    Mat src = imread("C:/Users/lc472/Documents/cpp_project/h_opencv/data/sample1.jpg");
    if (src.empty())
    {
        cout << "Could not open or find the image!/n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    Point2f srcTri[3];
    srcTri[0] = Point2f(0.f, 0.f);
    srcTri[1] = Point2f(src.cols - 1.f, 0.f);
    srcTri[2] = Point2f(0.f, src.rows - 1.f);
    Point2f dstTri[3];
    dstTri[0] = Point2f(0.f, src.rows * 0.33f);
    dstTri[1] = Point2f(src.cols * 0.3f, src.rows * 0.3f);
    dstTri[2] = Point2f(src.cols * 0.0f, src.rows * 1.0f);
    Mat warp_mat = getAffineTransform(srcTri, dstTri);
    Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());
    
    warpAffine(src, warp_dst, warp_mat, warp_dst.size());
    Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
    double angle = -50.0;
    double scale = 0.6;
    Mat rot_mat = getRotationMatrix2D(center, angle, scale);
    Mat warp_rotate_dst;
    warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
    imshow("Source image", src);
    imshow("Warp", warp_dst);
	imshow("Warp + Rotate", warp_rotate_dst);
    // resize up
    Mat resize_up;
    cv::resize(warp_dst, resize_up, Size(1200, 800), INTER_LINEAR);
    imshow("Resized Up image by defining height and width", resize_up);

	waitKey();
    return 0;
}