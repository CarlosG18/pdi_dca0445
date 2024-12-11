#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat image;
    cv::Rect rect(20, 50, 30, 30);

    image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (!image.data) std::cout << "nao abriu!" << std::endl;

    // obtendo os quadrantes
    cv::Mat q1 = image(cv::Rect(0,0,image.cols/2,image.rows/2));
    cv::Mat q2 = image(cv::Rect(image.cols/2,0,image.cols/2,image.rows/2));
    cv::Mat q3 = image(cv::Rect(0,image.rows/2,image.cols/2,image.rows/2));
    cv::Mat q4 = image(cv::Rect(image.rows/2,image.cols/2,image.cols/2,image.rows/2));

    cv::Mat RowUp, RowDown, FinalImage;

    cv::hconcat(q4, q3, RowUp); // concatena horizontalmente duas matrizes (images)
    cv::hconcat(q2, q1, RowDown); // concatena horizontalmente duas matrizes (images)
    cv::vconcat(RowUp, RowDown, FinalImage); // concatena verticalmente duas matrizes (images)
    
    cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

    cv::imshow("janela", FinalImage);
    cv::waitKey();
    return 0;
}
