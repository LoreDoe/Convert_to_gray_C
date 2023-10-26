#include <stdio.h>
#include "image.h"

int main() {
    Image* loaded_image = NULL; // Ponteiro para a imagem carregada.
    Image* gray_image = NULL; // Ponteiro para a imagem em tons de cinza.

    int choice; // Variável para armazenar a escolha.
    char input_path[100]; // Caminho do arquivo de entrada.
    char output_path[100]; // Caminho do arquivo de saída.

    do {
        // Exibir opções para escolha.
        printf("Menu de opções:\n");
        printf("1. Carregar imagem\n");
        printf("2. Converter para cinza\n");
        printf("3. Gravar imagem\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Opção 1: Carregar imagem
                printf("Digite o caminho da imagem a ser carregada: ");
                scanf("%s", input_path);
                loaded_image = load_from_ppm(input_path);
                printf("Imagem carregada com sucesso.\n");
                break;
            case 2:
                // Opção 2: Converte a imagem para cinza.
                if (loaded_image != NULL) {
                    gray_image = create(loaded_image->rows, loaded_image->cols, "P2");
                    rgb_to_gray(loaded_image, gray_image);
                    printf("Imagem convertida para cinza.\n");
                } else {
                    printf("Erro: Nenhuma imagem carregada.\n");
                }
                break;
            case 3:
                // Opção 3: Gravar imagem
                if (gray_image != NULL) {
                    printf("Digite o caminho para salvar a imagem em cor cinza: ");
                    scanf("%s", output_path);
                    write_to_ppm(gray_image, output_path);
                    printf("Imagem salva com sucesso.\n");
                } else {
                    printf("Erro: Nenhuma imagem convertida para cinza disponível.\n");
                }
                break;
            case 4:
                // Sair do programa
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 4);

    // Libera a memória alocada para as imagens.
    if (loaded_image != NULL) {
        for (int i = 0; i < loaded_image->rows; i++) {
            free(loaded_image->pixels[i]);
        }
        free(loaded_image->pixels);
        free(loaded_image);
    }

    if (gray_image != NULL) {
        for (int i = 0; i < gray_image->rows; i++) {
            free(gray_image->pixels[i]);
        }
        free(gray_image->pixels);
        free(gray_image);
    }

    return 0;
}