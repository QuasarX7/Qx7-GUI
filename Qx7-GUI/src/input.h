#ifndef input_h
#define input_h

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "matematica.h"
using namespace Utili;

namespace GUI {
    
    typedef Posizione<int> Cursore;
    
    enum StatoPulsante{
        GIU = GLUT_DOWN,
        SU = GLUT_UP
    };
    
    enum PulsanteMouse{
        SINISTRO = GLUT_LEFT_BUTTON,
        CENTRO = GLUT_MIDDLE_BUTTON,
        DESTRO = GLUT_RIGHT_BUTTON,
        SCORRI_SU = 3,
        SCORRI_GIU = 4,
        NON_DEFINITO = -1
        
    };
    
    class Mouse{
    public:
        Mouse(PulsanteMouse pulsante, StatoPulsante stato, const Cursore& posizione):
        statoPulsante{stato}, pulsanteMouse{pulsante}, coordinate{posizione}
        {}
        /**
         * Stato del pulsante: <code>GIU</code> o <code>GU</code>
         * @return <code>enum StatoPulsante</code>
         */
        StatoPulsante stato()const{return statoPulsante;}
        /**
         * Pulsante del mouse premuto.
         * @return <code>enum PulsanteMouse</code>
         */
        PulsanteMouse pulsante()const{return pulsanteMouse;}
        /**
         * Coordinate del cursore mouse.
         * @return tipo <code>Cursore</code> (<code>Posizione<int></code>)
         */
        Cursore posizione()const{return coordinate;}
    private:
        StatoPulsante statoPulsante;
        PulsanteMouse pulsanteMouse;
        Cursore coordinate;
    };
    
    class Tastiera{
    public:
        Tastiera(unsigned char tasto, const Cursore& posizione):
        tastoTastiera{tasto},coordinate{posizione}
        {}
        Cursore posizione()const{return coordinate;}
        unsigned char carattere()const{return tastoTastiera;}
    private:
        unsigned char tastoTastiera;
        Cursore coordinate;
    };
}

#endif /* input_h */
