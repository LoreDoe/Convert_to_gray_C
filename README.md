# Convert_to_gray_C

O Convert_to_gray_C é um programa em C que permite carregar imagens no formato PPM (Portable Pix Map), convertê-las para cinza e salvá-las novamente no formato PPM.

## Requisitos

- Um ambiente de desenvolvimento C (como GCC).
- Sistema operacional Unix/Linux (o código pode ser adaptado para Windows, se necessário).
- Poderá também ser utilizado um ambiente online como o Replit.

## Passo-a-Passo para Executar o Programa

Siga as etapas para executar o programa:

1. **Compilar o programa:**

   Abra um terminal no diretório onde os arquivos `image.c`, `image.h` e `main.c` estão localizados. Use o `Makefile` fornecido para compilar o programa. Basta executar o comando `make`:

   ```bash
   make

Isso compilará o programa e gerará um executável chamado image_processor.

Executar o programa:

Após a compilação, você pode executar o programa usando o seguinte comando:
./image_processor

Interagir com o programa:

O programa irá exibir um menu de opções. Você pode escolher as seguintes opções:

1. Carregar imagem: Esta opção permite que você carregue uma imagem no formato PPM. Digite o caminho do arquivo de imagem quando solicitado. O programa irá carregar a imagem para a memória.

2. Converter para cinza: Após carregar uma imagem, você pode escolher esta opção para converter a imagem carregada em uma imagem em tons de cinza. O programa realizará a conversão.

3. Gravar imagem: Após converter a imagem para tons de cinza, você pode escolher esta opção para salvar a imagem em um novo arquivo PPM. Digite o caminho do arquivo de saída quando solicitado.

4. Sair: Esta opção encerra o programa.

Encerrar o programa:

Quando você terminar de usar o programa, selecione a opção "4" no menu para sair.
