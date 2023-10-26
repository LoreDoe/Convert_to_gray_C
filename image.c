#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

// Função para criar uma nova imagem.
Image* create(int rows, int cols, const char type[]) 
{
    // Aloca memória para a estrutura Image.
    Image* image = (Image*)malloc(sizeof(Image));
    if (image == NULL) 
    {
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n");
        exit(1);
    }
  
    // Inicializa os campos da imagem.
    image->rows = rows;
    image->cols = cols;
    strcpy(image->type, type);
  
    // Aloca memória para a matriz de pixels.
    image->pixels = (unsigned char**)malloc(rows * sizeof(unsigned char*));
    if (image->pixels == NULL) 
    {
        fprintf(stderr, "Erro ao alocar memória para os pixels da imagem.\n");
        exit(1);
    }
  
    // Aloca memória para cada linha de pixels.
    for (int i = 0; i < rows; i++) {
        image->pixels[i] = (unsigned char*)malloc(cols * sizeof(unsigned char));
        if (image->pixels[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memória para os pixels da imagem.\n");
            exit(1);
        }
    }
    return image;
}

// Função para carregar uma imagem a partir de um arquivo PPM.
Image* load_from_ppm(const char* filename) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char magic[3];
    int rows, cols, max_val;

    // Lê o cabeçalho do arquivo para obter informações sobre a imagem.
    fscanf(file, "%2s %d %d %d", magic, &cols, &rows, &max_val);
    Image* image = create(rows, cols, magic);
  
    // Lê os valores dos pixels do arquivo e armazena na matriz de pixels da imagem.
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            int r, g, b;
            fscanf(file, "%d %d %d", &r, &g, &b);
            // Calcula o valor de intensidade em tons de cinza e armazena na matriz de pixels
            image->pixels[i][j] = (unsigned char)((r + g + b) / 3);
        }
    }
    fclose(file);
    return image;
}

// Função para escrever a imagem em um arquivo PPM
void write_to_ppm(Image* image, const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo de saída.\n");
        exit(1);
    }
  
    // Escreve o cabeçalho da imagem no arquivo
    fprintf(file, "%s\n", image->type);
    fprintf(file, "%d %d\n", image->cols, image->rows);
    fprintf(file, "255\n");

    // Escreve os valores dos pixels no arquivo
    for (int i = 0; i < image->rows; i++) 
    {
        for (int j = 0; j < image->cols; j++) 
        {
            fprintf(file, "%d ", image->pixels[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void rgb_to_gray(Image* image_rgb, Image* image_gray) 
{
    // Verifica se a imagem de entrada é do tipo P3 (RGB)
    if (strcmp(image_rgb->type, "P3") != 0) {
        fprintf(stderr, "Erro: A imagem de entrada deve ser colorida (P3).\n");
        exit(1);
    }
  
    // Verifica se a imagem de saída é do tipo P2 (níveis de cinza).
    if (strcmp(image_gray->type, "P2") != 0) 
    {
        fprintf(stderr, "Erro: A imagem de saída deve ser em níveis de cinza (P2).\n");
        exit(1);
    }
    // Percorre cada pixel da imagem colorida e realiza a conversão para tons de cinza.
    for (int i = 0; i < image_rgb->rows; i++) 
    {
        for (int j = 0; j < image_rgb->cols; j++) 
        {
            // Obtém os valores das componentes de cores vermelho (R), verde (G) e azul (B) do pixel.
            int r = image_rgb->pixels[i][j];
            int g = image_rgb->pixels[i][j];
            int b = image_rgb->pixels[i][j];
          
            // Calcula o valor de intensidade em tons de cinza usando a fórmula especificada.
            int gray_value = (int)(0.299 * r + 0.587 * g + 0.114 * b);
          
            // Armazena o valor de intensidade em tons de cinza no pixel da imagem em níveis de cinza.
            image_gray->pixels[i][j] = (unsigned char)((r + g + b) / 3);
        }
    }
}