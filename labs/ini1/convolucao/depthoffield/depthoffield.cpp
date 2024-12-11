#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    // Carregar o vídeo
    cv::VideoCapture cap;
    double width, height;
    cv::Mat frame, framegray, frameFiltered, frame32f, image_final;
    cv::Mat mask(3, 3, CV_32F);
    cv::Mat maximos8U, maximosColor;
    cv::Mat resultado;

    float laplacian[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    mask = cv::Mat(3, 3, CV_32F, laplacian);

    cap.open(argv[1]);
    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir o vídeo!" << std::endl;
        return -1;
    }

    //obtendo as dimensões do video
    width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    // Inicializar a matriz de máximos do laplaciano
    cv::Mat maximos = cv::Mat(height, width, CV_32F, cv::Scalar(0));

    while (cap.read(frame)) { // Capturar o frame
        if (frame.empty()) {
            std::cerr << "Erro: Frame vazio!" << std::endl;
            break;
        }

        // Converter o frame para tons de cinza
        cv::cvtColor(frame, framegray, cv::COLOR_BGR2GRAY);
        framegray.convertTo(frame32f, CV_32F);

        // Fazer a convolução com a máscara 3x3 laplaciana
        cv::filter2D(frame32f, frameFiltered, frame32f.depth(), mask, cv::Point(1, 1), cv::BORDER_REPLICATE);

        // Comparar com o valor da matriz dos máximos do laplaciano
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (frameFiltered.at<float>(i, j) > maximos.at<float>(i, j)) {
                    maximos.at<float>(i, j) = frameFiltered.at<float>(i, j);
                }
            }
        }

        // Converter maximos para o mesmo tipo e número de canais de frame antes de somar
        
        maximos.convertTo(maximos8U, CV_8U);
        cv::cvtColor(maximos8U, maximosColor, cv::COLOR_GRAY2BGR); // Converte para 3 canais

        cv::imshow("Resultado", maximosColor);

        if (cv::waitKey(30) >= 0) break;
    }

    if (cv::imwrite("output_image.jpg", maximosColor)) {
        std::cout << "Imagem salva com sucesso como 'output_image.jpg'" << std::endl;
    } else {
        std::cerr << "Erro ao salvar a imagem!" << std::endl;
    }

    return 0;
}
