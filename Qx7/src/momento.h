#ifndef SRC_MOMENTO_H_
#define SRC_MOMENTO_H_

#include <sstream>
#include <string>
using namespace std;

namespace Utili {

enum class UnitàTemporale{
	ANNO,MESE,GIORNO,ORA,MINUTO,SECONDO,MILLI_SECONDO
};

/**
 * La classe astratta Momento identifica una posizione temporale in cui si verifica
 * un evento generico. Da essa derivano la classe Data e Orario
 */
class Momento {
public:
	virtual ~Momento(){}

	virtual float valore(UnitàTemporale tipo)override const =0;

	float differenza(const Momento& confronto, UnitàTemporale tipo)const{
		return valore(tipo) - confronto.valore(tipo);
	}

	friend bool operator==(const Momento& a, const Momento& b)
	{return a.valore(UnitàTemporale::SECONDO) == b.valore(UnitàTemporale::SECONDO);}

	friend bool operator!=(const Momento& a, const Momento& b)
	{return !(a == b);}

	friend bool operator<(const Momento& a, const Momento& b)
	{return a.valore(UnitàTemporale::SECONDO) < b.valore(UnitàTemporale::SECONDO);}


	friend bool operator>(const Momento& a, const Momento& b)
	{return b < a;}

	friend bool operator<=(const Momento& a, const Momento& b)
	{return (a == b) && (a < b);}

	friend bool operator>=(const Momento& a, const Momento& b)
	{return (a == b) && (a > b);}
protected:
	Momento(){}

	string doppiaCifraNumero(int numero)const;
	string triplaCifraNumero(int numero)const;
};



} /* namespace Utili */

#endif /* SRC_MOMENTO_H_ */
