#include <iostream>
#include <opencv2/opencv.hpp>

struct Point {
    int x;
    int y;

    Point(int value_x, int value_y) : x(value_x), y(value_y) {}
};

int main(int argc, char** argv) {
    cv::Mat image;

    if (argc != 5) {
        std::cout << "Uso: ./regions <P1_x> <P1_y> <P2_x> <P2_y>" << std::endl;
        return -1;
    }

    // Lendo os argumentos da linha de comando
    int P1_x = std::stoi(argv[1]);
    int P1_y = std::stoi(argv[2]);
    int P2_x = std::stoi(argv[3]);
    int P2_y = std::stoi(argv[4]);

    //verificação da região
    if (P1_x >= P2_x || P1_y >= P2_y){
        std::cout << "A região informada não está coerente!" << std::endl;
        return -1;
    }

    image = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);
    if (!image.data) std::cout << "nao abriu bolhas.png" << std::endl;

    cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);
    
    // Criando os pontos
    Point point1(P1_x, P1_y);
    Point point2(P2_x, P2_y);

    for (int i = point1.x; i < point2.x; i++) {
        for (int j = point1.y; j < point2.y; j++) {
            // Certificando-se de que os índices estão dentro dos limites da imagem
            if (j >= 0 && j < image.rows && i >= 0 && i < image.cols) {
                image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
            }
        }
    }
    cv::imshow("janela", image);
    cv::waitKey();
    return 0;
}
