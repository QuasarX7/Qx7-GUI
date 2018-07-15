#ifndef menu_h
#define menu_h

#include <GLUT/glut.h>

#include <vector>
#include <memory>
using namespace std;

#include "componente.h"
using namespace Utili;

namespace GUI {
    
    class VoceMenu;
    typedef shared_ptr<VoceMenu> pVoceMenu;
    

    class VoceMenu: public Oggetto{
    public:
        VoceMenu(int ID,const string& etichetta);
        virtual ~VoceMenu(){}
        /**
         * Implementa il metodo GLUT <code>glutAddMenuEntry("nome voce",ID)</code> che permette
         * di disegnale le singole voci.
         */
        void disegna();
    private:
        string titolo;
        int identificativo;
        
    };
    
    typedef void (* ComportamentoMenu)(int idVoceMenu);
    
    class Menu;
    typedef shared_ptr<Menu> pMenu;

    
    class Menu: public Oggetto{
    public:
        Menu(const string& etichetta);
        Menu(ComportamentoMenu comportamento):Menu{""}{azione=comportamento;} // menu principale
        
        virtual ~Menu(){}
        
        
        virtual void disegna();
        void aggiungiVoce(int ID,const string& etichetta){voci.push_back(Oggetto::crea<VoceMenu>(shared_from_this(),ID,etichetta));}
        
        string nome()const{return titolo;}
    
        virtual void assegnaGenitore(pOggetto genitore)override;
        
        int ID()const{return identificativo;}
        
        
    private:
        void creaSottomenu();
        void creaMenu();
        
        string titolo;
        int identificativo = -1;
        ComportamentoMenu azione;
        
        vector<pVoceMenu> voci{};
        
    };
    
    
    
        
        
        
}

#endif /* menu_h */
