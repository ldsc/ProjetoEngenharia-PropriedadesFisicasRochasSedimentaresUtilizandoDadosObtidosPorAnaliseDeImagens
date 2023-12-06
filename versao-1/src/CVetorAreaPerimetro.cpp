/**
@autor Juliana Avila
@file CVetorAreaPerimetro.cpp
@brief CVetorAreaPerimetro: cria um vetor de poros contidos na imagem, ja convertido, com as informacoes importadas do arquivo gerado pelo ImageJ
*/

#include "CVetorAreaPerimetro.h"
#include <iostream>
#include <fstream>
#include <iomanip> //setw
#include <algorithm> //sort
#include <string>
#include <cmath>
using namespace std;

void CVetorAreaPerimetro::LeituradeDados() {
    string arquivodados;
    cout << "\nEntre com o arquivo de dados exportados do ImageJ" << endl;
    getline (cin, arquivodados);
    ifstream fin (arquivodados.c_str()); //abre arquivo solicitado na construcao do objeto com os dados
    if (!fin) {
        cout << "\nFalha acesso ao arquivo. Encerrando!" << endl;
        exit (0);
            }

    //preenche vetor area e perimetro
    double a;
    double p;
    area.clear(); //zera vetor de area
    perimetro.clear(); //zera vetor de perimetro
    fin.ignore(256, '\n'); //ignora a primeira linha

    while (!fin.eof()) {
        fin >> a;   // numero do poro
        fin >> a;   area.push_back(a);
        fin >> p;   perimetro.push_back(p);
    }

    fin.close(); //fecha arquivo de dados
    sort(area.begin(),area.end());
    sort(perimetro.begin(),perimetro.end());

    //conferindo se deu certo
    ofstream fout;
    system ("mv saida.dat saida.dat~"); //cria novo arquivo e deixa antigo para tras
    fout.open("saida.dat");	//vai para o fim do arquivo
    fout << "\nOs valores de area e perimetro (em pixels) sao(foram ORDENADOS):\n" << endl;
    fout << "\n" << setw(20) << "AREA(pixel2)" << setw(20) << "PERIMETRO(pixel)" << endl;
    for (int i=0; i<area.size(); i++) {
        fout << setw(20) << area[i] << setw(20) << perimetro[i] << endl;
    }
}

void CVetorAreaPerimetro::Conversao() {
     //arquivo de conversao de unidade
      string nomearquivo;
      cout << "\nEntre com o arquivo de conversao (modelo especificado)" << endl;
      getline (cin, nomearquivo);
      ifstream in (nomearquivo.c_str());
      if (!in) {
            cout << "\nArquivo não encontrado" << endl; }

      double ampliacao;
      double fator;
      in.ignore (100, '\n'); //ignora a primeira linha
      while (!in.eof()) {
          in >> ampliacao;
          in >> fator;
          conversao.insert(make_pair(ampliacao, fator));
          }
      in.close();

      //conferindo se deu certo
      ofstream fout;
      fout.open("saida.dat", ios::app);	//vai para o fim do arquivo
      map<double,double>::const_iterator it;
      fout << "\nA conversao utilizada segue a tabela seguinte: " << endl;
      fout << "\n" << setw(20) << "AMPLIACAO" << setw(20) << "FATOR" << endl;
      for(it=conversao.begin(); it!=conversao.end(); it++) {
            fout << setw(20) << it->first << setw(20) << it->second << endl; }

      //pegando o valor da ampliacao e armazenando valor do fator de conversao
      double amp;
      cout << "\nQual foi a ampliacao do microscopio utilizada na lamina?" << endl;
      cin >> amp;
      double fat;
      // precisa verificar se chegou ao fim do map e não encontrou o fator; ocorre quando o usuário seleciona um valor de ampliacao que não esta no arquivo. Neste caso pode pedir para usuário entrar com o fator.
      if (conversao.find(amp) != conversao.end()) {
        map<double,double>::const_iterator iter;
        iter=conversao.find(amp);
        fat=iter->second;
        fout << "\nO fator de conversao é: " << fat << " um/pixel" << endl; }
      else {
        cout << "\nQual é o fator de conversao de pixel para micrometros do microscopio utilizado para essa imagem?" << endl;
        cin >> fat; }

      //converte os valores
      for (int i=0; i<area.size(); i++) {
            area[i]=area[i]*fat*fat; //pow(x,2)
            }
      for (int i=0; i<perimetro.size(); i++) {
            perimetro[i]=perimetro[i]*fat;
            }

      //conferindo
      //fout.open("saida.dat", ios::app);	//vai para o fim do arquivo
      fout << "\nOs valores de area e perimetro (em micrometros) sao:\n" << endl;
      fout << "\n" << setw(20) << "AREA(um2)" << setw(20) << "PERIMETRO(um)" << endl;
      for (int i=0; i<area.size(); i++) {
            fout << setw(20) << area[i] << setw(20) << perimetro[i] << endl;
      }
}

double CVetorAreaPerimetro::AreaTotal() {
    areatotal=0.0;
    for (int i=0; i<area.size(); i++) {
        areatotal+=area[i];
    }

    ofstream fout;
    fout.open("saida.dat", ios::app);	//vai para o fim do arquivo
    fout << "\nA soma das areas é: " << areatotal << " um^2" << endl;

    return areatotal;
}

double CVetorAreaPerimetro::PerimetroTotal() {
     perimetrototal=0.0;
     for (int i=0; i<perimetro.size(); i++) {
        perimetrototal+=perimetro[i];
     }

     ofstream fout;
     fout.open("saida.dat", ios::app);	//vai para o fim do arquivo
     fout << "\nA soma dos perimetros é: " << perimetrototal << " um" << endl;

     return perimetrototal;
     }

void CVetorAreaPerimetro::Calculos() {
      ofstream fout;
      fout.open("saida.dat", ios::app);	//vai para o fim do arquivo
      fout << "\nO valor da superficie especifica é: " << spv << " 1/um" << endl;
      fout << "\nO valor da superficie especifica por volume de grão é: " << svgr << " 1/um"<< endl;

    }
