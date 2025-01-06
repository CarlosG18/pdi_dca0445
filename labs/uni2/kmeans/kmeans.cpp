#include <cstdlib>
#include <opencv2/opencv.hpp>

void calcularKMeans(const cv::Mat& img, int nClusters, int nRodadas, const std::string& outputPrefix) {
    cv::Mat rotulos, centros;

    // Prepara a matriz de amostras
    cv::Mat samples(img.rows * img.cols, 3, CV_32F);
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            for (int z = 0; z < 3; z++) {
                samples.at<float>(y + x * img.rows, z) = img.at<cv::Vec3b>(y, x)[z];
            }
        }
    }

    // Executa o KMeans
    cv::kmeans(samples, nClusters, rotulos,
               cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10000, 0.0001),
               nRodadas, cv::KMEANS_PP_CENTERS, centros);

    // Cria a imagem rotulada
    cv::Mat rotulada(img.size(), img.type());
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            int indice = rotulos.at<int>(y + x * img.rows, 0);
            rotulada.at<cv::Vec3b>(y, x)[0] = (uchar)centros.at<float>(indice, 0);
            rotulada.at<cv::Vec3b>(y, x)[1] = (uchar)centros.at<float>(indice, 1);
            rotulada.at<cv::Vec3b>(y, x)[2] = (uchar)centros.at<float>(indice, 2);
        }
    }

    // Exibe e salva a imagem resultante
    std::string outputPath = outputPrefix + "_k" + std::to_string(nClusters) + ".jpg";
    cv::imwrite(outputPath, rotulada);
    std::cout << "Imagem salva: " << outputPath << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Uso: kmeans entrada.jpg saida_prefixo max_clusters\n";
        return 0;
    }

    int maxClusters = std::atoi(argv[3]);
    if (maxClusters < 2) {
        std::cerr << "Erro: o número máximo de clusters deve ser pelo menos 2." << std::endl;
        return -1;
    }

    int nRodadas = 5; // Número de rodadas do KMeans

    // Lê a imagem de entrada
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Erro: não foi possível carregar a imagem." << std::endl;
        return -1;
    }

    // Executa o KMeans para cada número de clusters no intervalo
    for (int nClusters = 2; nClusters <= maxClusters; nClusters++) {
        calcularKMeans(img, nClusters, nRodadas, argv[2]);
    }

    return 0;
}
