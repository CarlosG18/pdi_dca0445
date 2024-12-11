#include <iostream>
#include "opencv2/opencv.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <chrono>
#include <random>

#define STEP 5
#define JITTER 3
#define MIN_LIMIAR 0
#define MAX_LIMIAR 300
#define MIN_RAIO 2

cv::Mat image, border, points;

void canny_generate(int, void*){
  cv::Canny(image, border, MIN_LIMIAR, 3*MIN_LIMIAR);
}

int calcularRaioMax(int largura, int altura) {
    // Dimensões da imagem de referência
    const int largura_ref = 2329;
    const int altura_ref = 3500;
    const int soma_dim_ref = largura_ref + altura_ref;

    // Raio máximo de referência
    const float raio_ref = 20.0f;

    // Calcula o raio máximo proporcional
    return raio_ref * (float)(largura + altura) / soma_dim_ref;
}


int main(int argc, char**argv){
  std::vector<int> yrange;
  std::vector<int> xrange;

  int width, height, gray; // variavel para guardar as infos de altura e largura da imagem
  int x, y, coeficient_canny, limiar, MAX_RAIO;
  double minVal, maxVal;
  float raio;
  int faixa = MAX_LIMIAR - MIN_LIMIAR;
  float decremento;

  std::srand(std::time(0));

  cv::Mat original = cv::imread(argv[1], cv::IMREAD_COLOR); // Ler a imagem original em cores
  image= cv::imread(argv[1], cv::IMREAD_GRAYSCALE); // ler a imagem em escala de cinza

  // obtendo a altura e largura da imagem
  width = image.cols;
  height = image.rows;

  MAX_RAIO = calcularRaioMax(width, height);
  //MAX_RAIO = 15;
  raio = MAX_RAIO;
  decremento = (MAX_RAIO - MIN_RAIO)/float(faixa);

  xrange.resize(height / STEP);
  yrange.resize(width / STEP);

  std::iota(xrange.begin(), xrange.end(), 0);
  std::iota(yrange.begin(), yrange.end(), 0);

  for (uint i = 0; i < xrange.size(); i++) {
    xrange[i] = xrange[i] * STEP + STEP / 2;
  }

  for (uint i = 0; i < yrange.size(); i++) {
    yrange[i] = yrange[i] * STEP + STEP / 2;
  }

  points = original.clone();

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(xrange.begin(), xrange.end(), std::default_random_engine(seed));

  for(int k = MIN_LIMIAR; k < MAX_LIMIAR; k+=1){
    canny_generate(k, 0);
    raio -= decremento;
    for (auto i : xrange) {
      std::shuffle(yrange.begin(), yrange.end(), std::default_random_engine(seed));
      for (auto j : yrange) {
        x = i + std::rand() % (2 * JITTER) - JITTER + 1;
        y = j + std::rand() % (2 * JITTER) - JITTER + 1;
        coeficient_canny = border.at<uchar>(y, x); // Índices corretos para acessar o pixel
        if(coeficient_canny != 0){
            cv::Vec3b color = original.at<cv::Vec3b>(x, y); // Obter cor RGB do pixel
            cv::circle(points, cv::Point(y, x), raio, cv::Scalar(color[0], color[1], color[2]), cv::FILLED, cv::LINE_AA);
        }
      }
    }
  }

  cv::waitKey();
  cv::imwrite("cannyborders.png", points);
  return 0;
}