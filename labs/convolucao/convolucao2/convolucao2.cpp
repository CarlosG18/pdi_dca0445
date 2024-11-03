#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "../camera.hpp"
#include <cmath>    // Para abs e fabs

void imprimir_vetor(float* vetor, int dimensao) {
    for (int i = 0; i < dimensao; ++i) {
        for (int j = 0; j < dimensao; ++j) {
            std::cout << std::fixed << std::setprecision(2) << vetor[i * dimensao + j] << " ";
        }
        std::cout << std::endl;
    }
}

float* transform_matriz_for_vetor(float** matriz, int dimensao){
  int tam_vetor = dimensao*dimensao;
  float* vetor = new float[dimensao*dimensao];

  for(int i=0; i < dimensao; i++){
    for(int j=0; j < dimensao; j++){
      int index = i * dimensao + j;
      vetor[index] = matriz[i][j];
    }
  }

  return vetor;
}

float* create_mask(int dimensao,std::string tipo){
  float** matriz = new float*[dimensao*dimensao];
  int limit_inf =(dimensao-1)/2;
  int limit_sup = (dimensao-1)/2;
  int elemento_central_laplacian = 0;
  

  for (int i = 0; i < dimensao; i++) {
        matriz[i] = new float[dimensao];
  }

  for(int i=0; i < dimensao; i++){
    for(int j=0; j < dimensao; j++){
      if(tipo == "media"){
        matriz[i][j] = 1.0/(dimensao*dimensao);
      }else if(tipo == "gauss"){
        float sigma = dimensao / 3.0;
        float x = i - dimensao / 2;
        float y = j - dimensao / 2;
        matriz[i][j] = exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
      }else if(tipo == "horizontal"){
        if (j == 0) {
          matriz[i][j] = -1;
          if(i == (dimensao-1)/2){
            matriz[i][j] = -2;
          }
        } else if (j == dimensao-1) {
          matriz[i][j] = 1;
          if(i == (dimensao-1)/2){
            matriz[i][j] = 2;
          }
        } else {
          matriz[i][j] = 0;
        }
      }else if(tipo == "vertical"){
        if (i == 0) {
          matriz[i][j] = -1;
          if(j == (dimensao-1)/2){
            matriz[i][j] = -2;
          }
        } else if (i == dimensao-1) {
          matriz[i][j] = 1;
          if(j == (dimensao-1)/2){
            matriz[i][j] = 2;
          }
        } else {
          matriz[i][j] = 0;
        }
      }else if(tipo == "laplacian"){
        if(j < limit_inf || j > limit_sup){
          matriz[i][j] = 0;
        }else{
          matriz[i][j] = -1;
          elemento_central_laplacian += 1;
        }
      }
    }
    std::cout << limit_inf << " " << limit_sup << std::endl;
    if(i < (dimensao-1)/2){
      limit_inf -= 1;
      limit_sup += 1;
    }else{
      limit_inf += 1;
      limit_sup -= 1;
    }
  }

  if(tipo == "laplacian"){
    elemento_central_laplacian -= 1;
    matriz[(dimensao-1)/2][(dimensao-1)/2] = elemento_central_laplacian;
  }


  float* vetor = transform_matriz_for_vetor(matriz, dimensao);
  
  // liberando memoria da alocação da matriz
  for (int i = 0; i < dimensao; i++) {
    delete[] matriz[i];
  }
  delete[] matriz;

  return vetor;
}

void printmask(cv::Mat &m) {
  for (int i = 0; i < m.size().height; i++) {
    for (int j = 0; j < m.size().width; j++) {
      std::cout << m.at<float>(i, j) << ",";
    }
    std::cout << std::endl;
  }
}

int main(int, char* argv[]) {
  int dimensao = std::stoi(argv[1]);

  if (dimensao % 2 == 0){
    return -1;
  }

  cv::VideoCapture cap;
  int camera;
  float* media = create_mask(dimensao, "media");
  float* gauss = create_mask(dimensao, "gauss");
  float* horizontal = create_mask(dimensao, "horizontal");
  float* vertical = create_mask(dimensao, "vertical");
  float* laplacian = create_mask(dimensao, "laplacian");
  imprimir_vetor(laplacian, dimensao);

  cv::Mat frame, framegray, frame32f, frameFiltered;
  cv::Mat mask(dimensao, dimensao, CV_32F);
  cv::Mat result;
  double width, height;
  int absolut;
  char key;

  camera = cameraEnumerator();
  cap.open(camera);

  if (!cap.isOpened()) 
    return -1;

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  cv::namedWindow("filtroespacial", cv::WINDOW_NORMAL);
  cv::namedWindow("original", cv::WINDOW_NORMAL);

  mask = cv::Mat(dimensao, dimensao, CV_32F, media);

  absolut = 1;  // calcula absoluto da imagem

  for (;;) {
    cap >> frame;  // captura nova imagem da camera
    cv::cvtColor(frame, framegray, cv::COLOR_BGR2GRAY);
    cv::flip(framegray, framegray, 1);
    cv::imshow("original", framegray);
    framegray.convertTo(frame32f, CV_32F);
    cv::filter2D(frame32f, frameFiltered, frame32f.depth(), mask, cv::Point(1, 1), cv::BORDER_REPLICATE);
    if (absolut) {
      frameFiltered = cv::abs(frameFiltered);
    }

    frameFiltered.convertTo(result, CV_8U);

    cv::imshow("filtroespacial", result);

    key = (char)cv::waitKey(10);
    if (key == 27) break;  // tecla ESC pressionada!
    switch (key) {
      case 'a':
        absolut = !absolut;
        break;
      case 'm':
        mask = cv::Mat(dimensao,dimensao, CV_32F, media);
        printmask(mask);
        break;
      case 'g':
        mask = cv::Mat(dimensao, dimensao, CV_32F, gauss);
        printmask(mask);
        break;
      case 'h':
        mask = cv::Mat(dimensao, dimensao, CV_32F, horizontal);
        printmask(mask);
        break;
      case 'v':
        mask = cv::Mat(dimensao, dimensao, CV_32F, vertical);
        printmask(mask);
        break;
      case 'l':
        mask = cv::Mat(dimensao, dimensao, CV_32F, laplacian);
        printmask(mask);
        break;
    }
  }
  return 0;
}