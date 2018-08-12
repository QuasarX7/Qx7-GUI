#ifndef SRC_CAMPO_ORARIO_H_
#define SRC_CAMPO_ORARIO_H_

#include <memory>
#include "orario.h"
using namespace Utili;

#include "campo_numerico.h"

namespace GUI {

typedef shared_ptr<Orario> pOrario;

class CampoOrario;
typedef shared_ptr<CampoOrario> pCampoOrario;

class CampoOrario : public CampoNumerico{
public:
	CampoOrario(size_t ID, const OrigineArea& posizione):
		CampoNumerico{ID,posizione,(size_t)5,Maschera{"__:__",'_'}}{}
	virtual ~CampoOrario(){}
	/**
	 * Valore orario espresso in secondi
	 * @return
	 */
	virtual double valore()const override{return _orario != nullptr ? _orario->valore(UnitàTemporale::SECONDO) : 0.0;}
	/**
	 * Ora inserita.
	 * @return
	 */
	pOrario orario()const{return _orario;}

protected:
		virtual void inputTastiera(const Tastiera& tastiera)override; ///< segnale input tastiera (tasto)

		pOrario _orario = nullptr;
};

} /* namespace GUI */

#endif /* SRC_CAMPO_ORARIO_H_ */
