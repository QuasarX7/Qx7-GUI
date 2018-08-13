#ifndef SRC_CAMPO_DATA_H_
#define SRC_CAMPO_DATA_H_

#include <memory>
using namespace std;

#include "data.h"
using namespace Utili;

#include "campo_numerico.h"


namespace GUI {

typedef shared_ptr<Data> pData;

class CampoData;
typedef shared_ptr<CampoData> pCampoData;

class CampoData: public CampoNumerico {
public:
	/**
	 * Costruttore.
	 * @param ID
	 * @param posizione
	 */
	CampoData(size_t ID, const OrigineArea& posizione):
		CampoNumerico{ID,posizione,(size_t)10,'/',Maschera{"__/__/____",'_'}} {}
	/**
	 * Distruttore
	 */
	virtual ~CampoData(){}
	/**
	 * Numero di giorni dal 01/01/0001 alla data inserita. La data 01/01/0001 è pari a 1 gg, se
	 * la data è nulla o incompleta, il valore restituito è 0.
	 * @return
	 */
	virtual double valore()const override{return _data != nullptr ? _data->valore(UnitàTemporale::GIORNO) : 0.0;}
	/**
	 * Data inserita.
	 * @return
	 */
	pData data()const{return _data;}


protected:
		/* SLOT */
	virtual void inputTastiera(const Tastiera& tastiera)override; ///< segnale input tastiera (tasto)


	pData _data = nullptr;
};

} /* namespace GUI */

#endif /* SRC_CAMPO_DATA_H_ */
