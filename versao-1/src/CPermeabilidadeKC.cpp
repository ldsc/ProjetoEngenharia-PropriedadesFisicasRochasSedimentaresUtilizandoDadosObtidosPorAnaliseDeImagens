/**
@autor Juliana Avila
@file CPermeabilidadeKC.cpp
@brief CPermeabilidadeKC: calcula a permeabilidade a partir da area e do periodo
*/

#include "CPermeabilidadeKC.h"
#include <iostream>

using namespace std;

void CPermeabilidadeKC::SaidadeCalculo() {
      ofstream fout;
      fout.open("saida.dat", ios::app);	//vai para o fim do arquivo
      fout << "\nO valor da permeabilidade (modelo Kozeny-Carman): " << kkc << " mD" << endl;
      cout << "\nO valor da permeabilidade (modelo Kozeny-Carman): " << kkc << " mD" << endl;
      }
