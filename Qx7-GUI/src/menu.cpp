#include "menu.h"
using namespace GUI;

VoceMenu::VoceMenu(int ID,const string& etichetta)
:identificativo{ID},titolo{etichetta}
{
}

void VoceMenu::disegna(){
    glutAddMenuEntry(titolo.c_str(), identificativo);
}



Menu::Menu(const string& etichetta)
:titolo{etichetta}
{
}

void Menu::assegnaGenitore(pOggetto genitore){
    Oggetto::assegnaGenitore(genitore);
    pMenu menuPrincipale;
    if( ( menuPrincipale = dynamic_pointer_cast<Menu>(genitore) ) != nullptr){
        azione = menuPrincipale->azione;
    }
}  

void Menu::disegna(){
    if(azione != nullptr){
        creaSottomenu();
        creaMenu();
        glutAttachMenu(GLUT_RIGHT_BUTTON);
        
    }else{
        throw logic_error{"Errore Menu::disegna(): azione non definita."};
    }
}

void Menu::creaSottomenu(){
    pMenu sottoMenu;
    for(size_t i=0; i < numeroFigli(); i++){
        if(( sottoMenu = dynamic_pointer_cast<Menu>(figlio(i)) ) != nullptr){
            sottoMenu->creaMenu();
        }
    }
}

void Menu::creaMenu(){
    //crea menu principale
    identificativo = glutCreateMenu(azione);
        
    pMenu sottoMenu;
    pVoceMenu voceMenu;
    for(size_t i=0; i < numeroFigli(); i++){
        if(( voceMenu = dynamic_pointer_cast<VoceMenu>(figlio(i)) ) != nullptr){
            //aggiungi voce del menu principale
            voceMenu->disegna();
        }else if(( sottoMenu = dynamic_pointer_cast<Menu>(figlio(i)) ) != nullptr){
            //aggiungi sottomenu creato dal metodo (precedente) Menu::creaSottomenu()
            glutAddSubMenu(sottoMenu->nome().c_str(),sottoMenu->identificativo);
        }
    }
}
        
