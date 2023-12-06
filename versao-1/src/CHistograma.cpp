/**
@autor Juliana Avila
@file CHistograma.cpp
@brief CHistograma: plota graficos
*/

#include "CHistograma.h"
#include "CGnuplot.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

void CHistograma::Raio(CVetorAreaPerimetro& image) {
    //preenche o vetor raio com seus valores acessando o vetor area do CVetorAreaPerimetro
      for (int i=0; i<image.area.size(); i++) {
        raio.push_back(sqrt(image.area[i]/M_PI));
                                        }
      //conferindo se deu certo e mostrando na tela o vetor criado
      ofstream fout;
      fout.open("saida.dat", ios::app);	//vai para o fim do arquivo
      fout << "\nO vetor de raio criado a partir dos dados da area é:" << endl;
      fout << setw(30) << "RAIO(um)" << endl;
      for (int i=0; i<raio.size(); i++) {
        fout << setw(30) << raio[i] << endl;
                                         }
}


void CHistograma::DistribuicaoPoros() {
 //criando histograma
    vector<int> histograma (5,0);
    for (int i=0; i<raio.size(); i++) {
        if      (raio[i]<=1.0)                      histograma[0]+=1;
        else if (raio[i]>=1.0 && raio[i]<10.0)      histograma[1]+=1;
        else if (raio[i]>=10.0 && raio[i]<100.0)    histograma[2]+=1;
        else if (raio[i]>=100.0 && raio[i]<1000.0)  histograma[3]+=1;
        else                                        histograma[4]+=1;
    }
     vector<double> hist_x (5,0);
     hist_x[0]=0.1;
     hist_x[1]=1.0;
     hist_x[2]=10.0;
     hist_x[3]=100.0;
     hist_x[4]=1000.0;

      ofstream hout;
      hout.open("histograma.dat");	//vai para o fim do arquivo
      for (int i=0; i<histograma.size(); i++) {
        hout << setw(10) << histograma[i] << setw(10) << i << " = " << hist_x[i] << endl;
                                         }
      CGnuplot gdp; // Construtor (grafico distribuicao tamanho de poros)
      gdp.set_style("histograms");
      gdp.XLabel("Raio de poros (um)"); // Rotulo eixo x
      gdp.YLabel("Frequencia"); // Rotulo eixo y
      gdp.YAutoscale();
      gdp << "set term png\n"; // terminal é arquivo png
      gdp << "set out \"frequencia_raio.png\"\n"; // nome do arquivo
      gdp.plotfile_x("histograma.dat", 1, ""); // 1:xtic(2)
      gdp << "xtic(2)\n";
      //gdp.PlotVector(raio, "Distribuicao de tamanho de poros");
      //cin.get();
}

void CHistograma::VPorosoAcumulativo(CVetorAreaPerimetro& image) {
      //cria vetor area acumulada
      vector<double> areaA;
      areaA.push_back(image.area[0]);
      for (int i=1; i<image.area.size(); i++) {
        areaA.push_back(areaA[i-1]+image.area[i]);
      }

      //cria vetor area acumulada normalizada (%)
      vector<double> areaAN;
      for (int i=0; i<areaA.size(); i++) {
        areaAN.push_back((areaA[i]/image.areatotal)*100.0);
      }

      //conferindo se deu certo
      ofstream fout;
      fout.open("saida.dat", ios::app);
      fout << "\nO vetor de area tratado é:" << endl;
      fout << setw(30) << "\nAREA ACUMULADA NORMALIZADA(um2)" << endl;
      for (int i=0; i<areaAN.size(); i++) {
        fout << setw(30) << areaAN[i] << endl;
      }
     //arquivo com os valores do grafico
      ofstream raio_area;
      raio_area.open("raio_area.dat");
      for (int i=0; i<areaAN.size(); i++)
        raio_area << setw(30) << raio[i] << setw(30) << areaAN[i] << endl;
      raio_area.close();

      //plotando com gnuplot
      CGnuplot gva; // Construtor (grafico volume acumulado)
      gva.Style("linespoints");
      gva.XLabel("Raio de poros (um)"); // Rotulo eixo x
      gva.YLabel("Fracao acumulatica de volume poroso (%)"); // Rotulo eixo y
      gva.set_xlogscale(10);
      gva.XAutoscale();
      gva.YRange(0, 100);
      gva << "set term png\n"; // terminal é arquivo png
      gva << "set out \"vporoso_acumulado.png\"\n"; // nome do arquivo
      gva.plotfile_xy("raio_area.dat", 1,2);
      //gva.PlotVector(raio, areaAN, "Distribuicao acumulativa de tamanho de poros1");
      //cin.get();
 }
