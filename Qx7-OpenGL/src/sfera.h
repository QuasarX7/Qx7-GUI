#ifndef SFERA_H_
#define SFERA_H_

#include "figura.h"

namespace Grafica {

class Sfera: public Figura {
public:
	Sfera(const Colore& sfondo,const Punto& baricentro, double raggio)
	:Figura(baricentro,sfondo,sfondo),R(raggio){}
	virtual ~Sfera(){}

	virtual void disegna() const override;
private:
	double R;
};

} /* namespace Grafica */

#endif /* SRC_SFERA_H_ */
