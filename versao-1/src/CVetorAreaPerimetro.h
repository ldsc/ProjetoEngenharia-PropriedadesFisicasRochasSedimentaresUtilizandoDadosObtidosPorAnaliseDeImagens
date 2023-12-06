/**
@autor Juliana Avila
@file CVetorAreaPerimetro.h
@brief CVetorAreaPerimetro: cria um vetor de poros contidos na imagem, ja convertido, com as informacoes importadas do arquivo gerado pelo ImageJ
*/

#ifndef CVetorAreaPerimetro_h
#define CVetorAreaPerimetro_h

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

class CVetorAreaPerimetro {

public: //main nao acessa qnd e privado
        std::vector<double> area;
        std::vector<double> perimetro;
        std::map<double,double> conversao;
        double areatotal;
        double perimetrototal;
        double spv;
        double svgr;
        double porosidade;

public:
       //construtores e destrutor
       //construtor default
       CVetorAreaPerimetro():area(0.0), perimetro(0.0), areatotal(0.0), perimetrototal(0.0), spv(0.0), svgr(0.0) {}

       //construtor de copia
       //CVetorAreaPerimetro(const CVetorAreaPerimetro& image) {
                                //area=image.area; perimetro=image.perimetro; conversao=image.conversao; areatotal=image.areatotal; perimetrototal=image.perimetrototal;}
       //construtor sobrecarregado
       //CImagemBinarizada(std::vector<int> _area, std::vector<double> _perimetro, map<double,double> _conversao, double _so, double _areatotal, double _perimetrototal):
                                 //area(_area), perimetro(_perimetro), conversao(_conversao), areatotal(_areatotal), perimetrototal(_perimetrototal) {}
       //destrutor
       ~CVetorAreaPerimetro(){};

       void LeituradeDados();
       void Conversao(); //usar arquivo para conversao do tipo especificado
       double AreaTotal();
       double PerimetroTotal();

       double Spv(double perimetrototal, double areatotal) {return spv=((4.0*perimetrototal)/(M_PI*areatotal));}

       double Svgr(double spv) {return svgr=(spv*(porosidade/(1.0-porosidade)));}

       void Calculos();

       friend class CHistograma;
       friend class CPermeabilidadeKC;

};
#endif

