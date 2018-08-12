#include "momento.h"

using namespace Utili;


string Momento::doppiaCifraNumero(int numero)const{
	stringstream ss;
	if(numero < 10)
		ss <<  "0";
	ss << numero;
	return ss.str();
}

string Momento::triplaCifraNumero(int numero)const{
	stringstream ss;
	if(numero < 10)
		ss <<  "00";
	else if(numero < 100)
		ss <<  "0";
	ss << numero;
	return ss.str();
}
