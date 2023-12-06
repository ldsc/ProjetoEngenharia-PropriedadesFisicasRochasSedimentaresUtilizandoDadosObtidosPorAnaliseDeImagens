/**
@autor Juliana Avila
@file main.cpp
@brief main: implementa as classes
*/

#include <iostream>
#include "CVetorAreaPerimetro.h"
#include "CPermeabilidadeKC.h"
#include "CHistograma.h"

using namespace std;

int main() {
       CVetorAreaPerimetro image; //pede o arquivo com os dados de area e perimetro
       image.LeituradeDados(); //preenche e mostra os vetores area e perimetro em pixel
       image.Conversao(); //pede o arquivo de conversao, le e mostra ele na tela
                          //pergunta a ampliacao da imgem, converte e mostra na tela os vetores de area e perimetro convertidos
       image.AreaTotal(); //calcula a soma das areas dos poros
       image.PerimetroTotal(); //calcula a soma dos perimetros dos poros
       cout << "\nQual o valor de porosidade encontrado no experimento? (ImageJ) (frac)" << endl;
       cin >> image.porosidade;
       image.Spv(image.perimetrototal, image.areatotal); //calcula superficie especifica do poro total
       image.Svgr(image.spv); //calcula area especifica do poro total
       image.Calculos();

       CPermeabilidadeKC perme;
       perme.PermeabilidadeKC(image); //calcula permeabilidade
       perme.SaidadeCalculo(); //mostra na tela os valores calculados acima

       CHistograma hist; //cria o vetor de raio a partir do vetor area da classe CVetorAreaPerimetro
       hist.Raio(image);
       hist.DistribuicaoPoros(); //plota um histograma com os tamanhos do poro
       hist.VPorosoAcumulativo(image); //plota um grafico de poros pela acumulacao do volume (area)
}
