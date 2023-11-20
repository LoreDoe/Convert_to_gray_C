#ifndef IMAGE_H
#define IMAGE_H

// Define a estrutura Image.
typedef struct Image 
{
    int rows; // Número de linhas da imagem.
    int cols; // Número de colunas da imagem.
    char type[3]; // Tipo da imagem.
    unsigned char** pixels; // Matriz de pixels da imagem.
} Image;

// Função para criar uma nova imagem.
Image* create(int rows, int cols, const char type[]);

// Função para carregar uma imagem de um arquivo PPM
Image* load_from_ppm(const char* filename);

// Função para escrever uma imagem em um arquivo PPM
void write_to_ppm(Image* image, const char* filename);

// Função para converter uma imagem RGB em tons de cinza
void rgb_to_gray(Image* image_rgb, Image* image_gray);

#endif 
