/**
@autor Juliana Avila
@file CHistograma.h
@brief CHistograma: plota graficos
*/

#ifndef CHistograma_h
#define CHistograma_h

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> //sqrt e M_PI
#include "CVetorAreaPerimetro.h"
#include "CGnuplot.h"
#include "CPermeabilidadeKC.h"

class CHistograma {

public:
        std::vector<double> raio;
        //double M_PI;
        CVetorAreaPerimetro image;

public:
       //construtor e destrutor
       //construtor default
       CHistograma(): raio(0.0) {}

       //construtor de copia
       //CHistograma(const CHistograma& hist) {raio=hist.raio;}
       //construtor sobrecarregado
       //CHistograma(std::vector<double> _raio): raio(_raio) {}

       //destrutor
       ~CHistograma(){};

       void Raio(CVetorAreaPerimetro& image);
       void DistribuicaoPoros();
       void VPorosoAcumulativo(CVetorAreaPerimetro& image);

};
#endif
