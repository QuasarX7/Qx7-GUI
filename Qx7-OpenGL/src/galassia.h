#ifndef GALASSIA_H_
#define GALASSIA_H_

#include <vector>
#include <random>
using namespace std;

#include "matematica.h"
using namespace Utili;

#include "figura.h"

namespace Grafica {

class Galassia : public Figura{
public:
	Galassia(const Colore& sfondo,const Punto& baricentro, double raggio, size_t numeroStelle=1000, size_t braccia=5);
	virtual ~Galassia() {}
	virtual void disegna() const override;

private:
		double R;
		vector<Punto> stelle;

};

} /* namespace Grafica */

#endif
