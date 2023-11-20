#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

// Função para criar uma nova imagem.
Image* create(int rows, int cols, const char type[]) 
{
    // Aloca memória para a estrutura Image.
    Image* image = (Image*)malloc(sizeof(Image)); // Alocação dinâmica de memória para a estrutura Image.
    if (image == NULL) // Verificação de erro na alocação de memória.
    {
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n"); // Mensagem de erro em caso de falha na alocação.
        exit(1);
    }
  
    // Inicializa os campos da imagem.
    image->rows = rows; // Inicialização do número de linhas da imagem.
    image->cols = cols; // Inicialização do número de colunas da imagem.
    strcpy(image->type, type); // Cópia do tipo de imagem para a estrutura.
  
    // Aloca memória para a matriz de pixels.
    image->pixels = (unsigned char**)malloc(rows * sizeof(unsigned char*)); // Alocação dinâmica de memória para as linhas da matriz.
    if (image->pixels == NULL) // Verificação de erro na alocação de memória.
    {
        fprintf(stderr, "Erro ao alocar memória para os pixels da imagem.\n"); // Mensagem de erro em caso de falha na alocação.
        exit(1); // Encerra o programa com código de erro 1.
    }
  
    // Aloca memória para cada linha de pixels.
    for (int i = 0; i < rows; i++) {
        image->pixels[i] = (unsigned char*)malloc(cols * sizeof(unsigned char)); // Alocação dinâmica de memória para as colunas da matriz.
        if (image->pixels[i] == NULL) // Verificação de erro na alocação de memória.
        { 
            fprintf(stderr, "Erro ao alocar memória para os pixels da imagem.\n"); // Mensagem de erro em caso de falha na alocação.
            exit(1); // Encerra o programa com código de erro 1.
        }
    }
    return image; // Retorna a imagem criada.
}

// Função para carregar uma imagem a partir de um arquivo PPM.
Image* load_from_ppm(const char* filename) 
{
    FILE* file = fopen(filename, "r"); // Abertura do arquivo em modo de leitura.
    if (file == NULL) // Verifica se houve erro na abertura do arquivo.
    {
        fprintf(stderr, "Erro ao abrir o arquivo.\n"); // Se houver erro na abertura do arquivo, exibe uma mensagem de erro.
        exit(1); // Encerra o programa com código de erro 1.
    }

    char magic[3]; // Array para armazenar o tipo da imagem.
    int rows, cols, max_val; // Variáveis para armazenar o número de linhas, colunas e valor máximo dos pixels.

    // Lê o cabeçalho do arquivo para obter informações sobre a imagem.
    fscanf(file, "%2s %d %d %d", magic, &cols, &rows, &max_val); // Lê os valores do cabeçalho (tipo da imagem, número de colunas, número de linhas, valor máximo).
    Image* image = create(rows, cols, magic); // Cria uma nova imagem com base nas informações do cabeçalho.
  
    // Lê os valores dos pixels do arquivo e armazena na matriz de pixels da imagem.
    for (int i = 0; i < rows; i++) // Loop para percorrer as linhas da imagem.
    {
        for (int j = 0; j < cols; j++) // Loop para percorrer as colunas da imagem.
        {
            int r, g, b;
            fscanf(file, "%d %d %d", &r, &g, &b); // Lê os valores de RGB de um pixel.
            // Calcula o valor de intensidade em tons de cinza e armazena na matriz de pixels
            image->pixels[i][j] = (unsigned char)((r + g + b) / 3); // Calcula a média dos valores RGB para obter o valor de tons de cinza.
        }
    }
    fclose(file); // Fecha o arquivo após a leitura. 
    return image; // Retorna a imagem criada.
}

// Função para escrever a imagem em um arquivo PPM
void write_to_ppm(Image* image, const char* filename) 
{
    FILE* file = fopen(filename, "w"); // Abertura do arquivo em modo de escrita.
    if (file == NULL) // Verifica se houve erro na abertura do arquivo.
    {
        fprintf(stderr, "Erro ao criar o arquivo de saída.\n"); // Se houver erro na criação do arquivo, exibe uma mensagem de erro.
        exit(1); // Encerra o programa com código de erro 1.
    }
  
    // Escreve o cabeçalho da imagem no arquivo
    fprintf(file, "%s\n", image->type); // Escreve o tipo da imagem no arquivo.
    fprintf(file, "%d %d\n", image->cols, image->rows); // Escreve o número de colunas e linhas no arquivo.
    fprintf(file, "255\n"); // Escreve o valor máximo dos pixels no arquivo (255 para imagens PPM).

    // Escreve os valores dos pixels no arquivo
    for (int i = 0; i < image->rows; i++) // Loop para percorrer as linhas da imagem.
    {
        for (int j = 0; j < image->cols; j++) // Loop para percorrer as colunas da imagem.
        {
            fprintf(file, "%d ", image->pixels[i][j]); // Escreve o valor do pixel no arquivo.
        }
        fprintf(file, "\n"); // Adiciona uma quebra de linha após cada linha de pixels.
    }
    fclose(file); // Fecha o arquivo após a escrita.
}

// Função para converter uma imagem RGB para tons de cinza.
void rgb_to_gray(Image* image_rgb, Image* image_gray) 
{
    // Verifica se a imagem de entrada é do tipo P3 (RGB)
    if (strcmp(image_rgb->type, "P3") != 0) 
    {
        fprintf(stderr, "Erro: A imagem de entrada deve ser colorida (P3).\n"); // Se a imagem não for do tipo RGB, exibe uma mensagem de erro.
        exit(1); // Encerra o programa com código de erro 1.
    }
  
    // Verifica se a imagem de saída é do tipo P2 (níveis de cinza).
    if (strcmp(image_gray->type, "P2") != 0) 
    {
        fprintf(stderr, "Erro: A imagem de saída deve ser em níveis de cinza (P2).\n"); // Se a imagem de saída não for do tipo P2, exibe uma mensagem de erro.
        exit(1); // Encerra o programa com código de erro 1.
    }
    // Percorre cada pixel da imagem colorida e realiza a conversão para tons de cinza.
    for (int i = 0; i < image_rgb->rows; i++) // Loop para percorrer as linhas da imagem RGB.
    {
        for (int j = 0; j < image_rgb->cols; j++) // Loop para percorrer as colunas da imagem RGB.
        {
            // Obtém os valores das componentes de cores vermelho (R), verde (G) e azul (B) do pixel.
            int r = image_rgb->pixels[i][j]; // Valor da componente vermelha do pixel.
            int g = image_rgb->pixels[i][j]; // Valor da componente verde do pixel.
            int b = image_rgb->pixels[i][j]; // Valor da componente azul do pixel.
          
            // Calcula o valor de intensidade em tons de cinza usando a fórmula especificada.
            int gray_value = (int)(0.299 * r + 0.587 * g + 0.114 * b); // Fórmula para converter RGB para tons de cinza.
          
            // Armazena o valor de intensidade de tons de cinza no pixel da imagem em cinza.
            image_gray->pixels[i][j] = (unsigned char)((r + g + b) / 3); // Calcula a média dos valores RGB para obter o valor de tons de cinza.
        }
    }
}
