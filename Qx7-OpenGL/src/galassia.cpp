#include "galassia.h"

using namespace Grafica;

Galassia::Galassia(const Colore& sfondo,const Punto& baricentro, double raggio, size_t numeroStelle, size_t braccia)
:Figura(baricentro,sfondo,sfondo),R(raggio){

	for(auto i = 0; i < numeroStelle; i++) {
		const float distanzaBraccia = 2 * π / braccia;
		const float offsetMaxBraccia = 0.8f;
		const float fattoreRotazioneBraccio = 5;
		const float randomOffsetXY = 0.02f;

		// coordinate polari casuali
		float distanza = R * pow(casuale<float>(), 2);   // da 0 a R con spostamento quadratico verso il centro
		float angolo = casuale<float>() * 2 * π; // da 0 a 180°
		//raggruppa le stelle lungo le braccia
		float offsetBraccia = casuale<float>() * offsetMaxBraccia;
		offsetBraccia -=  offsetMaxBraccia / 2;
		offsetBraccia *=  (R / distanza);
		//spostamento quadratico verso il centro del braccio
		float quadraturaOffsetBraccia = pow(offsetBraccia, 2);
		offsetBraccia =  (offsetBraccia < 0) ? -quadraturaOffsetBraccia : quadraturaOffsetBraccia;
		//curvatura del braccio
		float rotazioneBraccio = distanza/R * fattoreRotazioneBraccio;

		angolo = (int)(angolo / distanzaBraccia) * distanzaBraccia + offsetBraccia + rotazioneBraccio;

		// conversione delle coordinate polari in cartesiane
		float x = cos(angolo) * distanza;
		float y = sin(angolo) * distanza;

		float randomOffsetX = casuale<float>() * randomOffsetXY;
		float randomOffsetY = casuale<float>() * randomOffsetXY;

		x += randomOffsetX;
		y += randomOffsetY;

		stelle.push_back(Punto{x, y});
	}
}
void Galassia::disegna()const{
    glPushMatrix();
    trasforma(Vettore{posizione.x(),posizione.y(),posizione.z()});

    glBegin(GL_POINTS);
    coloreSfondo.disegna();
    for(Punto stella: stelle){
    	glVertex3d(stella.x(),stella.y(),0.0);
    }
    glEnd();

    glPopMatrix();
}
