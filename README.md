**Image-Compressor-C**  
  
******************************************************  

**Aluna**: Hosana Fernandes Gomes  
**Matrícula**: 20251045050585  
**Avaliação 04: Trabalho Final**  
**04.505.23 − 2025.2** − Prof.Daniel Ferreira  
**Compilador**: gcc (MinGW.org GCC-6.3.0-1) 6.3.0  
**S.O**: Windows 11  
  
********************************************************  
  
**Módulos utilizados:** 
   
**Leitura**: pgm.c e pgm.h 
**Decomposição quadtree**: quadtree.c e quadtree.h  
**Codificação da imagem**: encoder.c, encoder.h, encoder_manager.c, encoder_manager.h, compressionfactor.c, compressionfactor.h  
        *@ encoder_manager.c*: chamada das funções de codificação e de construção da quadtree para gerar o bitstream compactado  
        *@ compressionfactor.c*: controle de via argv quanto ao nível de compressão que a imagem vai ter  
                *altissimo*: o algoritmo gera um bitstream bastante compacto, mas com muita perda de qualidade. a compressão pode ultrapassar 90%.  
                *alto*: idem, porem  com a compressão entre 80-90%.  
                *medio*: o bitstream gerado tem cerca de 70% do valor original. A imagem reconstruída ainda apresenta aspecto pixelado, mas com uma resolução melhor que opções supracitadas. O fator PSNR ainda não é satisfatório.  
                *baixo*: imagem menos compactada (cerca de 60% do valor do tamanho original), mas com boa resolução. Melhor opção para imagens com muita textura  
