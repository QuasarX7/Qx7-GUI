#ifndef GALASSIA_H_
#define GALASSIA_H_

#include <vector>
#include <memory>
#include <random>
using namespace std;

#include "matematica.h"
using namespace Utili;

#include "figura.h"

namespace Grafica {

typedef shared_ptr<Punto> pPunto;
typedef shared_ptr<Colore> pColore;
typedef struct Stella{pPunto posizione; pColore colore;};


class Galassia : public Figura{
public:
	Galassia(const Colore& sfondo,const Punto& baricentro, double raggio, size_t numeroStelle=1000, size_t braccia=5);
	virtual ~Galassia() {}
	virtual void disegna() const override;

private:
		double R;
		vector<Stella> stelle;

};

} /* namespace Grafica */

#endif
