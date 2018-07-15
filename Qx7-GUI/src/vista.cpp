/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7-GUI.                                          *
 *                                                                          *
 * Qx7-GUI è una libreria software gratuita: puoi ridistribuirla e/o        *
 * modificarla sotto i termini della GNU Lesser General Public License come *
 * pubblicato  dalla Free Software Foundation, o la versione 3 della licenza,
 *  o (a tua scelta) qualsiasi versione successiva.                         *
 *                                                                          *
 * Qx7-GUI è distribuita nella speranza che sia utile,                      *
 * ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di         *
 * COMMERCIABILITÀ O IDONEITÀ PER UN PARTICOLARE SCOPO. Vedi il             *
 * GNU Lesser General Public License per maggiori dettagli.                 *
 *                                                                          *
 * Dovresti aver ricevuto una copia di GNU Lesser General Public            *
 * Licenza insieme a Qx7-GUI. Altrimenti, vedi al sito                      *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7-GUI.                                            *
 *                                                                          *
 *   Qx7-GUI is free software: you can redistribute it and/or modify it     *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Qx7-GUI is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Qx7-GUI.  If not, see                               *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/
/**
 * @file vista.cpp
 * @author Dr. Domenico della Peruta
 * @date 04-05-2018
 * @version 1.0.1, 15-07-2018
 * 
 * @brief File contenente l'implementazione delle metodi della classe Vista.
 * 
 * @namespace GUI
 * @class Vista
 */
#include "vista.h"
using namespace GUI;

Vista::Vista(const string& titoloFinestra,const Area& campo,const Colore& colore,const Colore& sfumatura)
:Componente{0,campo},areaComponenti{},areaPredefinitaVista{OrigineArea{0,0},campo.dimensione()},titolo{titoloFinestra}
{
    coloreSfondo = colore;
    coloreBordoInattivo = colore.combina(sfumatura);
    
    sfondo= Utili::crea<Rettangolo>(
        coloreSfondo,
        coloreBordoInattivo,
        Punto{spessore,spessore},
        static_cast<double>(area.dimensione().altezza()) - 2*spessore,
        static_cast<double>(area.dimensione().lunghezza()) - 2*spessore
    );
    sfondo->bordo(spessore);
    
    
    barraScorrimentoVerticale = Utili::crea<Rettangolo>(
            sfumatura,
            colore,
            Punto{
                area.dimensione().lunghezza()-spessoreBarra,
                0.0
            },
            static_cast<double>(area.dimensione().altezza()),
            spessoreBarra
    );
    barraScorrimentoVerticale->bordo(2.0);
    
    barraScorrimentoOrizzontale = Utili::crea<Rettangolo>(
            sfumatura,
            colore,
            Punto{
                0.0,
                area.dimensione().altezza()-spessoreBarra
            },
            static_cast<double>(area.dimensione().altezza()),
            spessoreBarra
    );
    barraScorrimentoOrizzontale->bordo(2.0);

    cursoreScorrimentoVerticale = Utili::crea<Rettangolo>(
            colore,
            sfumatura,
            Punto{
                area.dimensione().lunghezza()-spessoreBarra+1.0,
                1.0
            },
            0.0,
            spessoreBarra-2.0
    );
    cursoreScorrimentoOrizzontale = Utili::crea<Rettangolo>(
            colore,
            sfumatura,
            Punto{
                1.0,
                area.dimensione().altezza()-spessoreBarra+1.0
            },
            spessoreBarra-2.0,
            0.0
    );
    
    
    //scorrimentoOrizzontale;
    /* SEGNALI */
    click.connetti(this, &Vista::azione);
    coordinateMouse.connetti(this, &Vista::passaggioMouse);
    tasto.connetti(this, &Vista::inputTastiera);
    tastoSpeciale.connetti(this, &Vista::inputTastieraSpeciale);
    
}


Vista::~Vista(){
    /* SEGNALI */
    click.disconnetti();
    coordinateMouse.disconnetti();
    tasto.disconnetti();
    tastoSpeciale.disconnetti();
}

double Vista::proporzioneVerticale() const{
    return area.dimensione().altezza()/(double)areaComponenti.dimensione().altezza();
}

double Vista::proporzioneOrizzontale() const{
    return area.dimensione().lunghezza()/(double)areaComponenti.dimensione().lunghezza();
}

void Vista::disegnaBarraScorrimentoVerticale()const{
    const double proporzione = proporzioneVerticale();
    double y =  - areaComponenti.origine().y()*proporzione;
    cursoreScorrimentoVerticale->posiziona(
        Punto{
            area.dimensione().lunghezza()-spessoreBarra+1.0,
            y
        }
    );
    cursoreScorrimentoVerticale->dimensiona(
            barraScorrimentoVerticale->altezza()*proporzione,
            spessoreBarra-2.0
    );
    
    cursoreScorrimentoVerticale->disegna();
    
    barraScorrimentoVerticale->posiziona(
        Punto{
            area.dimensione().lunghezza()-spessoreBarra,
            0.0
        }
    );
    barraScorrimentoVerticale->dimensiona(
            static_cast<double>(area.dimensione().altezza()),
            spessoreBarra
    );
    barraScorrimentoVerticale->disegna();
    
}

void Vista::disegnaBarraScorrimentoOrizzontale()const{
    const double proporzione = proporzioneOrizzontale();
    double x =  - areaComponenti.origine().x()*proporzione;
    
    cursoreScorrimentoOrizzontale->posiziona(
        Punto{
            x,
            area.dimensione().altezza()-spessoreBarra+1.0
        }
    );
    cursoreScorrimentoOrizzontale->dimensiona(
            spessoreBarra-2.0,
            barraScorrimentoOrizzontale->lunghezza()*proporzione
    );
    cursoreScorrimentoOrizzontale->disegna();
    
    barraScorrimentoOrizzontale->posiziona(
        Punto{
            0.0,
            area.dimensione().altezza()-spessoreBarra
        }
    );
    barraScorrimentoOrizzontale->dimensiona(
            spessoreBarra,
            static_cast<double>(area.dimensione().lunghezza())
    );
    barraScorrimentoOrizzontale->disegna();
    
}
   

void Vista::limiteCursoreVerticale(){
    const int altoBarraCursore = cursoreScorrimentoVerticale->localizzazione().y();
    const int bassoBarraCursore = altoBarraCursore + cursoreScorrimentoVerticale->altezza();
    /* LIMITE INFERIORE */
    if(bassoBarraCursore > area.dimensione().altezza()){
        // [1] effetto calamita
        //      sposta i componenti verso il basso quando dilatando
        //      la finestra la barra arriva al limite inferiore
        // [2] effetto molla
        //      muove la barra verso l'alto quando la vista supera il limite 
        //      inferiore della finestra 
        spostaComponenti(0,bassoBarraCursore-area.dimensione().altezza());
    } 
    
    /* LIMITE SUPERIORE*/
    if(altoBarraCursore <= 0){
        // [1] effetto molla
        //      muove la barra verso il basso quando la vista supera il limite 
        //      superiore della finestra 
        int yCursoreBasso = cursoreScorrimentoVerticale->altezza();
        int dilatazione = yCursoreBassoMax - yCursoreBasso;
        spostaComponenti(0, dilatazione > 0 ? -dilatazione : dilatazione );
        
    }else{
        yCursoreBassoMax= cursoreScorrimentoVerticale->altezza();
    }
}

void Vista::limiteCursoreOrizzontale(){
    const int sinistraBarraCursore = cursoreScorrimentoOrizzontale->localizzazione().x();
    const int destraBarraCursore = sinistraBarraCursore + cursoreScorrimentoOrizzontale->lunghezza();
    /* LIMITE DESTRO */
    if(destraBarraCursore > area.dimensione().lunghezza()){
        spostaComponenti(destraBarraCursore-area.dimensione().lunghezza(),0);
    }
    /* LIMITE SINISTRO*/
    if(sinistraBarraCursore <= 0){
        int xCursoreSinistra = cursoreScorrimentoOrizzontale->lunghezza();
        int dilatazione = xCursoreSinistraMax - xCursoreSinistra;
        spostaComponenti( dilatazione > 0 ? -dilatazione : dilatazione,  0 );
        
    }else{
        xCursoreSinistraMax= cursoreScorrimentoOrizzontale->lunghezza();
    }
}

void Vista::disegna(){
    //aggiorna dimensine area estensione dei componenti
    areaComponenti = estensioneAreaComponenti();
    
    
    if(barraVerticaleAttiva()){
        //corregge posizione del cursore di scorrimento laterale(effetto molla)
        limiteCursoreVerticale();
    
        disegnaBarraScorrimentoVerticale();
    }
    
    if(barraOrizzontaleAttiva()){
        limiteCursoreOrizzontale();
        disegnaBarraScorrimentoOrizzontale();
    }
    
    // disegna componenti interni
    for(size_t i=0; i < numeroFigli(); i++){
        auto componente = dynamic_pointer_cast<Componente>(figlio(i));
        if (componente != nullptr) {
            componente->disegna();
        }
    }
    // reimposta specifiche della figura
    sfondo->posiziona(Punto{spessore,spessore});
    sfondo->dimensiona(
                 area.dimensione().altezza()  -2 * spessore,
                 area.dimensione().lunghezza()-2 * spessore
    );
    infoDebug();
    sfondo->disegna();
    glFlush();
}

void Vista::disegnaMenu(){
    if(menu != nullptr){
        menu->disegna();
    }
}

bool Vista::zonaCursore(pRettangolo cursore,int x,int y){
    return  y > cursore->localizzazione().y() && 
            y < cursore->localizzazione().y() + cursore->altezza() &&
            x > cursore->localizzazione().x() && 
            x < cursore->localizzazione().x() + cursore->lunghezza();
}
   

void Vista::passaggioMouse(const Cursore& mouse,Stato stato){
    Componente::passaggioMouse(mouse,stato);
    int x = mouse.x();
    int y = mouse.y();
    if(cursoreScorrimentoVerticale != nullptr){
        if(barraVerticaleAttiva()){
            if(zonaCursore(cursoreScorrimentoVerticale,x,y)){
                cursoreScorrimentoVerticale->sfondo(coloreBordoInattivo);
                
            }else{
                cursoreScorrimentoVerticale->sfondo(coloreSfondo);
            }
            if(stato == Stato::Attivo && scorrimentoVerticale){//pulsante premuto
                int dy = (int)(((double)(yClic-y))/proporzioneVerticale());
                spostaComponenti(0,dy);
                    
                yClic = y;

            }
        }
    }
    if(cursoreScorrimentoOrizzontale != nullptr){
        if(barraOrizzontaleAttiva()){
            if(zonaCursore(cursoreScorrimentoOrizzontale,x,y)){
                cursoreScorrimentoOrizzontale->sfondo(coloreBordoInattivo);
                
            }else{
                cursoreScorrimentoOrizzontale->sfondo(coloreSfondo);
            }
            if(stato == Stato::Attivo && scorrimentoOrizzontale){//pulsante premuto
                int dx = (int)(((double)(xClic-x))/proporzioneOrizzontale());
                spostaComponenti(dx,0);
                    
                xClic = x;

            }
        }
    }
    
}

void Vista::azione(const Mouse& mouse){
    Componente::azione(mouse);
    xClic = mouse.posizione().x();
    yClic = mouse.posizione().y();
    if(mouse.pulsante() == PulsanteMouse::SINISTRO){
        if(mouse.stato() == StatoPulsante::GIU){
            if(zonaCursore(cursoreScorrimentoVerticale,xClic,yClic))
                scorrimentoVerticale = true;
            if(zonaCursore(cursoreScorrimentoOrizzontale,xClic,yClic))
                scorrimentoOrizzontale = true;
        }else{
            scorrimentoVerticale = false;
            scorrimentoOrizzontale = false;
        }
    }
}

void Vista::inputTastiera(const Tastiera& tastiera){
    Componente::inputTastiera(tastiera);// propagazione a tutti gli elementi associati
    switch (tastiera.carattere()) {
       case 9: // tasto 'tab'
            passaFocusSuccessivo();
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void Vista::inputTastieraSpeciale(const Tastiera& tastiera){
    Componente::inputTastieraSpeciale(tastiera);
}

void Vista::spostaComponenti(int dx, int dy){
       /* spostamento senza condizioni (usato solo dalla metodo stesso) */

	areaPredefinitaVista.origine(
			OrigineArea{
                areaPredefinitaVista.origine().x() + dx,
                areaPredefinitaVista.origine().y() + dy
            }
	);
	for(size_t i=0; i < numeroFigli(); i++){
		pComponente componente = dynamic_pointer_cast<Componente>(figlio(i));
		if(componente != nullptr){
			componente->sposta(
                    OrigineArea{
                        componente->origine().x() + dx,
                        componente->origine().y() + dy
                    }

			);
		}
	}
	areaComponenti = estensioneAreaComponenti();
}

size_t Vista::passaFocusSuccessivo(){
    bool trovato = false;
    for(size_t i=0; i < numeroFigli(); i++){
        if(etichetta(figlio(i)))
            continue;
        auto componente = dynamic_pointer_cast<Componente>(figlio(i));
        if(componente != nullptr){ 
            if(trovato){
                componente->assegnaFocus();
                return componente->ID();
            }
            if(componente->statoFocus()){
                trovato = true;
                if(i == numeroFigli() -1 )
                    i = 0; // se ultimo passa al primo
            }
        
        }
    }
    auto primoComponente = primoComponenteAssociato();
    if(primoComponente != nullptr){
        primoComponente->assegnaFocus();
        return primoComponente->ID();
    }
    throw out_of_range{"Errore focus: nessun elemento presente nella 'Vista'."};
}


size_t Vista::passaFocusPrecedente(){
    bool trovato = false;
    for(size_t i=numeroFigli()-1; i > std::numeric_limits<size_t>::max(); i--){ // [i] = 0 -> [i--] = SIZE_T_MAX
        if(etichetta(figlio(i)))
            continue;
        auto componente = dynamic_pointer_cast<Componente>(figlio(i));
        if(componente != nullptr){
            if(trovato){
                componente->assegnaFocus();
                return componente->ID();
            }
            if(componente->statoFocus()){
                trovato = true;
            }
        }
    }
    auto ultimoComponente = ultimoComponenteAssociato();
    if(ultimoComponente != nullptr){
        ultimoComponente->assegnaFocus();
        return ultimoComponente->ID();
    }
    throw out_of_range{"Errore focus: nessun elemento presente nella 'Vista'."};
}

bool Vista::eventoLocale(const Cursore &mouse){
    int Xmin = 0;
    int Xmax = area.dimensione().lunghezza();
    int Ymin = 0;
    int Ymax = area.dimensione().altezza();
    
    return mouse.x() > Xmin && mouse.x() < Xmax && mouse.y() > Ymin && mouse.y() < Ymax;
    
}


Area Vista::estensioneAreaComponenti()const{
    int xMax = 0;
    int xMin = 0;
    int yMax = 0;
    int yMin = 0;
    
    for(size_t i=0; i < numeroFigli(); i++){
        pComponente componente = dynamic_pointer_cast<Componente>(figlio(i));
        if(componente != nullptr){
            Area zona = componente->zonaOccupata();
            
            int x = zona.origine().x();
            if(x < xMin)
                xMin = x;
            
            int y = zona.origine().y();
            if(y < yMin)
                yMin = y;
            
            x += zona.dimensione().lunghezza();
            if(x > xMax)
                xMax = x;
            
            y += zona.dimensione().altezza();
            if(y > yMax)
                yMax = y;
        }
    }
    // aggiunta della stessa area della vista predefinita
    int x = areaPredefinitaVista.origine().x();
    if(x < xMin)
        xMin = x;

    int y = areaPredefinitaVista.origine().y();
    if(y < yMin)
        yMin = y;

    x += areaPredefinitaVista.dimensione().lunghezza();
    if(x > xMax)
        xMax = x;

    y += areaPredefinitaVista.dimensione().altezza();
    if(y > yMax)
        yMax = y;
    
    return Area{xMin, yMin, yMax-yMin, xMax-xMin};
}
        

string Vista::debug()const{
    stringstream ss;
    ss << "area finestra:   " << area.dimensione().lunghezza() << " x " << area.dimensione().altezza()             << "  coord. schermo  = ("<< area.origine().x() <<  ", "<< area.origine().y() << ")" <<endl;
    ss << "area vista:      " << areaPredefinitaVista.dimensione().lunghezza() << " x " << areaPredefinitaVista.dimensione().altezza() << "  coord. finestra = ("<< areaPredefinitaVista.origine().x() <<  ", "<< areaPredefinitaVista.origine().y() << ")" <<endl;
    ss << "area componenti: " << areaComponenti.dimensione().lunghezza() << " x " << areaComponenti.dimensione().altezza() << "  coord. finestra = ("<< areaComponenti.origine().x() <<  ", "<< areaComponenti.origine().y() << ")" <<endl;
    if( numeroFigli() > 0)
        ss <<endl << "componenti:"<<endl;
    for(size_t i=0; i < numeroFigli(); i++){
        pComponente componente = dynamic_pointer_cast<Componente>(figlio(i));
        if(componente != nullptr){
            Area areaC = componente->zonaOccupata();
            ss << "  [" << i << "]     "  << areaC.dimensione().lunghezza() << " x " << areaC.dimensione().altezza() << "  ("<< areaC.origine().x() <<  ", "<< areaC.origine().y() << ")" <<endl;
        }
    }
    return ss.str();
}

void Vista::infoDebug(){
    pStringa s = Utili::crea<Stringa>(debug(),Punto{10.0,10.0},BIANCO);
    s->disegna();
}
