# Compressão de imagem em C   
Este projeto consiste na implementação de um sistema de compressão e descompressão de imagens no formato **PGM (Portable Graymap)** utilizando a estrutura de dados **Quadtree** e codificação customizada em binário (`.bit`). Desenvolvido como projeto final para a disciplina de Laboratório de Programação - IFCE.
  
**Avaliação 04: Trabalho Final**  
**Equipe**: Hosana Fernandes Gomes    
**04.505.23 − 2025.2** − Prof.Daniel Ferreira  
**Compilador**: gcc (MinGW.org GCC-6.3.0-1) 6.3.0  
**S.O**: Windows 11  
    

## Funcionalidades
* **Compressão Baseada em Limiar:** Divide a imagem recursivamente em quadrantes dependendo do nível de textura e do fator de compressão escolhido.
* **Codificação Eficiente:** Gera um arquivo binário compactado compacto (`.bit`).
* **Decodificação/Reconstrução:** Reconstrói a imagem original a partir do arquivo `.bit`, gerando um novo arquivo PGM


### Módulos utilizados: 
O projeto está dividido de forma modular para facilitar a manutenção e organização do fluxo de dados

* **Leitura e Manipulação:** `pgm.c` / `pgm.h`
* **Decomposição:** `quadtree.c` / `quadtree.h`
* **Codificação:** `encoder.c` / `encoder.h`, `encoder_manager.c` / `encoder_manager.h`
* **Qualidade:** `bib/compressionfactor.h` (gerencia limiares e fatores de compressão)
* **Decodificação:** `decoder.c` / `decoder.h`   


## Fatores de Compressão

O comportamento do algoritmo de compressão é determinado pelo argumento de qualidade (argv[5]) passado no terminal:

| Nível | Threshold (Limiar) | Impacto no Tamanho | Qualidade Visual | Indicação de Uso |
| :--- | :---: | :---: | :---: | :--- |
| **Alto** | `30` | Redução de 80% a 90% | Baixa (Mais perdas) | Imagens simples com pouca variação de cor. |
| **Médio** | `15` | Redução de ~70% | Média (Aspecto pixelado) | Meio-termo entre economia de espaço e fidelidade. |
| **Baixo** | `8` | Redução de ~60% | Alta (Boa resolução) | **Melhor opção** para imagens com muita textura. |

**Decodificação da imagem**: `decoder.c`, `decoder.h`  


## Instalação e Compilação do código

### Pré-requisitos
* Compilador GCC (GNU Compiler Collection).
* Ferramenta `make` (opcional, para sistemas Linux/Unix ou MinGW no Windows).

```bash
# 1. Clonar o Repositório
git clone [https://github.com/hosanafg/image-compressor-C.git](https://github.com/hosanafg/image-compressor-C.git)
cd image-compressor-C

# 2. Compilar
## Manualmente (Powershell)
gcc main.c pgm.c quadtree.c encoder.c encoder_manager.c decoder.c -o encoded_file.exe

## Manualmente (Linux / MacOS)
gcc main.c pgm.c quadtree.c encoder.c encoder_manager.c decoder.c -o encoded_file
```

## Modos de execução
### 1. Encode
Gera o arquivo binário comprimido e uma prévia da imagem codificada.
```bash
/encoded_file.exe encode <imagem_entrada.pgm> <saida_bitstream.bit> <preview_codificada.pgm> <fator_qualidade>
```
**exemplo:**
```bash
./encoded_file.exe encode img01.pgm img01.bit img01_decode.pgm baixo
```
### 2. Decode
Reconstrói uma imagem PGM a partir do arquivo comprimido `.bit.`  
```bash  
./encoded_file.exe decode <saida_bitstream.bit> <imagem_reconstruida.pgm>  
```
**exemplo**
```bash
./encoded_file.exe decode saida.bit resultado_final.pgm  
```  
  
[![Licença](https://img.shields.io/badge/Licença-MIT-blue.svg)](LICENSE)
[![Status do Build](https://img.shields.io/badge/Build-Pass-success.svg)](LINK_PARA_BUILD)
