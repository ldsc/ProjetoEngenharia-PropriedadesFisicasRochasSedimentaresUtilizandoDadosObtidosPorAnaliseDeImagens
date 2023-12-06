/**
@autor Juliana Avila
@file CPermeabilidadeKC.h
@brief CPermeabilidadeKC: calcula a permeabilidade a partir da area e do periodo
*/

#ifndef CPermeabilidadeKC_h
#define CPermeabilidadeKC_h

#include <cmath>
#include <fstream>
#include <vector>
#include "CVetorAreaPerimetro.h"

class CPermeabilidadeKC {

public:
       CVetorAreaPerimetro image;
       double kkc;

public:
       //construtores e destrutor
       //construtor default
       CPermeabilidadeKC() {}

       //destrutor
       ~CPermeabilidadeKC(){};

        double PermeabilidadeKC(CVetorAreaPerimetro image) {return kkc=(((1.0/(5.0*(image.svgr*image.svgr)))*((image.porosidade*image.porosidade*image.porosidade)/((1.0-image.porosidade)*(1.0-image.porosidade))))/0.00098717);}

        double operator()(CVetorAreaPerimetro image) {return kkc; }

       void SaidadeCalculo();

};
#endif
