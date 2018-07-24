/*
 * sfera.cpp
 *
 *  Created on: 21 lug 2018
 *      Author: Ninja
 */

#include "sfera.h"

using namespace Grafica;
void Sfera::disegna() const {
	glPushMatrix();
		trasforma(Vettore{posizione.x(),posizione.y(),posizione.z()});
	    glLineWidth(spessoreBordo);

	    glBegin(GL_POINTS);
	    coloreSfondo.disegna();
	    //glutWireSphere(R,20,20);
	    for(auto beta=0.0; beta <= 180.0; beta += 5.0){
			for(auto alfa=-180.0; alfa <= 180.0; alfa += 5.0){
				glVertex3d(R*sin(beta)*cos(alfa),R*sin(beta)*sin(alfa),R*cos(beta));
			}
	    }
	    glEnd();

	glPopMatrix();
}



