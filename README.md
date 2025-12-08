### Image-Compressor-C 
Implementação de algoritmo para compressão de imagem PGM em C  
  
******************************************************  

**Aluna**: Hosana Fernandes Gomes  
**Matrícula**: 20251045050585  
**Avaliação 04: Trabalho Final**  
**04.505.23 − 2025.2** − Prof.Daniel Ferreira  
**Compilador**: gcc (MinGW.org GCC-6.3.0-1) 6.3.0  
**S.O**: Windows 11  
  
********************************************************  
  
### Módulos utilizados: 
   
**Leitura**: `pgm.c` e `pgm.h`   
**Decomposição quadtree**: `quadtree.c` e `quadtree.h`    
**Codificação da imagem**: `encoder.c`, `encoder.h`, `encoder_manager.c`, `encoder_manager.h`, `compressionfactor.c`, `compressionfactor.h`    
> * `encoder_manager.c`: chamada das funções de codificação e de construção da quadtree para gerar o bitstream compactado. Serão chamadas no main.c  
> * `compressionfactor.c`: controle de via argv quanto ao nível de compressão que a imagem vai ter
>
	COMPRESSION FACTOR (argv[5]):  
    **altissimo**: o algoritmo gera um bitstream bastante compacto, mas com muita perda de qualidade. a compressão pode ultrapassar 90%.  
    **alto**: idem, porem  com a compressão entre 80-90%.  
    **medio**: o bitstream gerado tem cerca de 70% do valor original. A imagem reconstruída ainda apresenta aspecto pixelado, mas com uma resolução melhor que opções supracitadas. O fator PSNR ainda não é satisfatório.  
    **baixo**: imagem menos compactada (cerca de 60% do valor do tamanho original), mas com boa resolução. Melhor opção para imagens com muita textura

**Decodificação da imagem**: `decoder.c`, `decoder.h`  

********************************************************

### Instalação 
**Pré-requisitos**
* GCC (GNU Compiler Collection) versão 6.0 ou superior, Linux ou Unix-like.
* Git para clonar o repositório.

**Clonar o Repositório**  
git clone [https://github.com/hosanafg/image-compressor-C.git](https://github.com/hosanafg/image-compressor-C.git)  
cd image-compressor-C  
  
  
### Execução
**Compilar**     
gcc main.c pgm.c quadtree.c encoder.c encoder_manager.c decoder.c compressionfactor.c -o encoded_file.exe  
  
O programa opera em dois modos: `encode` e `decode`.  
>  
	*modo 1: encoded*  ./encoded_file.exe encode <imagemEntrada.pgm> <nomearquivoBitstream.qcf> <imagemCodificada.pgm> <niveldecompressao (altissimo, alto, medio ou baixo)>
	*modo 2: decoded*  ./encoded_file.exe decode <nomearquivoBitstream.qcf> <imagemDecodificada.pgm>

********************************************************  
  
[![Licença](https://img.shields.io/badge/Licença-MIT-blue.svg)](LICENSE)
[![Status do Build](https://img.shields.io/badge/Build-Pass-success.svg)](LINK_PARA_BUILD)
