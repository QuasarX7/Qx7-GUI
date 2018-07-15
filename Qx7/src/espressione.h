/****************************************************************************
 * Copyright (C) 2018 by Dott. Domenico della Peruta                        *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7.                                              *
 *                                                                          *
 * Qx7 è una libreria software gratuita: puoi ridistribuirlo e/o modificarlo*
 * sotto i termini della GNU Lesser General Public License come pubblicato  *
 * dalla Free Software Foundation, o la versione 3 della licenza, o         *
 * (a tua scelta) qualsiasi versione successiva.                            *
 *                                                                          *
 * Qx7 è distribuita nella speranza che sia utile,                          *
 * ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di         *
 * COMMERCIABILITÀ O IDONEITÀ PER UN PARTICOLARE SCOPO. Vedi il             *
 * GNU Lesser General Public License per maggiori dettagli.                 *
 *                                                                          *
 * Dovresti aver ricevuto una copia di GNU Lesser General Public            *
 * Licenza insieme a Qx7. Altrimenti, vedi al sito                          *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7.                                                *
 *                                                                          *
 *   Qx7 is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Qx7 is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Qx7.  If not, see                                   *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/

/**
 * @file espressione.h
 * @author Dr. Domenico della Peruta
 * @date 21-04-2018
 * @version 1.0.1, 15-07-2018
 * 
 * @brief File creato per l'implementazione della classe Espressione. Contiene 
 * metodi e classi interne al namespace NotazionePolacca implementate in linea,
 * usati per il calcolo di un espressione generica mediante l'argoritmo della 
 * notazione polacca inversa postfissa.
 * 
 * @namespace NotazionePolacca racchiude le seguenti classi interne
 * @class Simbolo
 * @class Operatore
 * @class Valore
 * @class Variabile
 * @class TabellaVariabili
 * @class NotazioneInfissa
 * @class NotazioneInversaPostfissa
 * @class CalcolaEspressione
 * 
 * @namespace Utili
 * @class Espressione
 */
#ifndef _POLACCA_H_
#define _POLACCA_H_

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <iterator>
#include <cmath>
#include <limits>
#include <iostream>
#include <sstream>
#include <iostream>
using namespace std;

#include "parser.h"
using namespace Utili;


/**
 * Lo spazio dei nomi "NotazionePolacca" raccoglie tutte le classi, i metodi e le variabili
 * usate per implementare la classe Espressione, tramite l'argoritmo che fa uso della 
 * notazione polacca inversa.
 */
namespace NotazionePolacca{
    /* COSTANTI */
    const int NO_ERRORE                 =    0;
    const int ERRORE_GENERICO           =   -1;
    const int ERRORE_PARSE              =   -2;
    const int ERRORE_PARENTESI          =   -4;
    const int USO_NON_CORRETTO_OPERANDO =   -8;
    const int ERRORE_SINTASSI           =  -16;

    const unsigned int MAX_LUNG_SIMBOLO =   32;

    const double INDEFINITO = std::numeric_limits<double>::quiet_NaN();
        
    
    
    typedef double (*funzione_di_calcolo)(double []); ///< puntatore alle funzioni di calcolo
    
    enum class TipoSimbolo{
        TIPO_OPERATORE,
        TIPO_VALORE,
        TIPO_VARIABILE
    }; 
    
    /**
     * Un simbolo e' il minimo elemento della notazione polacca postfissa puo' essere un operatore, un valore oppure una variabile
     */
    class Simbolo{
    public:
        /**
         * Costruttore.
         * @param tipo
         */
        Simbolo(TipoSimbolo tipo):_tipo{tipo} {}
        /**
         * Distruttore.
         */
        virtual ~Simbolo(){}
        /**
         * Verifica se il simbolo è un operatore.
         * @return 
         */
        bool eOperatore() const { return _tipo == TipoSimbolo::TIPO_OPERATORE; }
        /**
         * Verifica se il simbolo è un valore
         * @return 
         */
        bool eValore() const    { return _tipo == TipoSimbolo::TIPO_VALORE; }
        /**
         * Verifica se il simbolo è una variabile
         * @return 
         */
        bool eVariabile() const { return _tipo == TipoSimbolo::TIPO_VARIABILE; }

        /**
         * Conversione del simbolo nel valore (se esiste) associato.
         */
        virtual operator double() const{return vedi();};
        /**
         * Metodo da implementare nelle classi derivate.
         * @return 
         */
        virtual double vedi() const = 0;
        
    protected:   
        TipoSimbolo _tipo;        // E' il tipo di simbolo
    };

    /**
     * Puntatore "intelligente" all' oggetto Simbolo.
     */
    typedef shared_ptr<Simbolo> pSimbolo;

    /**
     * Questa classe definisce un operatore o una funzione
     */
    class Operatore: public Simbolo{
    public:
        /**
         * Costruttore. 
         * @param _operazione
         * @param _priorita
         * @param _funzione
         * @param _operandi
         */
        Operatore(const string& _operazione, int _priorita, funzione_di_calcolo _funzione, int _operandi=1);
        /**
         * Costruttore di copia
         * @param copia
         * @param genitore
         */
        Operatore(const Operatore& copia);
        
        /**
         * Tipo di operazione.
         * @return 
         */
        const string& tipoOperazione() const { return operazione; }
        /**
         * Numero di operandi associati all'operazione.
         * @return 
         */
        int numeroOperandi() const { return operandi; }
        /**
         * Priorità dell'operazione nel calcolo dell'espressione.
         * @return 
         */
        int valorePriorita() const { return priorita; }
        /**
         * Parentesi aperta.
         * @return 
         */
        bool parentesiAperta() const { return parentesi_aperta; }
        /**
         * Parentesi chiusa.
         * @return 
         */
        bool parentesiChiusa() const { return parentesi_chiusa; }
        /**
         * Verifica se è una funzione
         * @return 
         */
        bool eFunzione() const { return funzione; }
        funzione_di_calcolo funzioneDiCalcolo() const { return m_funzione; }
        /**
         * Verifica se è un operatore somma o differenza.
         * 
         * @return 
         */
        bool eSommaODifferenza() const
        {return (operazione == "+" || operazione == "-");}
        
        /**
         * Metodo da non utilizzare, usato solo per ragioni di polimorfismo...
         * 
         * @return 
         */
        virtual double vedi() const override{throw std::bad_cast{};}
        /**
         * Informazioni di debug.
         * @return 
         */
        virtual string debug()const;
    protected:
        string  operazione;
        int     priorita;
        int     operandi;
        bool    parentesi_aperta;
        bool    parentesi_chiusa;
        bool    funzione;
        funzione_di_calcolo m_funzione;

    
    };
    
    typedef shared_ptr<Operatore> pOperatore;
    
    /**
     * Classe che definisce un valore costante.
     */
    class Valore : public Simbolo{
    public:
        /**
         * Costruttore. Es.: Valore a{10}, a2{-4.2};
         * @param x
         */
        Valore(double valoreNumerico): Simbolo{TipoSimbolo::TIPO_VARIABILE}, valore{valoreNumerico} {}
        /**
         * Costruttore di copia.
         * @param v
         */
        Valore(const Valore& v): Simbolo{TipoSimbolo::TIPO_VARIABILE}, valore{v.valore}{}
        /**
         * Valore numerico.
         * @return 
         */
        virtual double vedi() const override{return valore;}
        /**
         * Assegna valore numerico.
         * @param x
         */
        virtual void assegna(double valoreNumerico){valore = valoreNumerico;}
        /**
         * Operatore di assegnazione standard.
         * @param rv
         * @return 
         */
        virtual Valore& operator=(const Valore& rv);
        
        /**
         * Informazioni di debug.
         * @return 
         */
        virtual string debug()const;
        
    protected:
        double valore;
    
    };
    
    /**
     * Puntatore intelligente a Valore.
     */
    typedef shared_ptr<Valore> pValore;


    /**
     * Definisce una variabile, con nome e valore.
     * es. costruttori Variabile a(),b("pippo",25),b2(b);
     */
    class Variabile : public Valore{

    public:
        /**
         * Costruttore.
         * @param nominativo
         * @param valore
         */
        Variabile(const string& nominativo, double valore);

        /**
         * Costruttore di copia.
         * @param v
         */
        Variabile(const Variabile& copia) : Valore(copia),_nome{copia._nome}
        {_tipo = TipoSimbolo::TIPO_VARIABILE;}
        /**
         * Nome della variabile.
         * @return 
         */
        virtual string nome() const {return _nome;}

        /**
         * Operatore di assegnazione di un oggetto Valore.
         * @param v
         * @return 
         */
        Variabile& operator=(const Valore& v)override;
        /**
         * Operatore di assegnazione di un oggetto Variabile.
         * @param rv
         * @return 
         */
        Variabile& operator=(const Variabile& v);
        /**
         * Assegna valore numerico.
         * @param x
         */
        virtual void assegna(double x)  override{valore=x;}
        /**
         * Informazioni di debug.
         * @return 
         */
        virtual string debug()const  override;
     
    private:
        
        template <class ForwardIterator>
        void minuscolo(ForwardIterator start,ForwardIterator end){
            while(start!=end){
                *start=std::tolower(*start);
                ++start;
            }
        }
        
    protected:
        string  _nome;   ///< nome della variabile
        
        
    };
    
    /**
     * Definisce un puntatore shared_ptr a un oggetto Variabile
     */
    typedef shared_ptr<Variabile> pVariabile;

    
    /**
     * Classe interna che gestisce una tabella delle 'Variabili'.
     */
    class TabellaVariabili{
    
    public:
        /**
         * Costruttore.
         */
        TabellaVariabili(){}
        /**
         * Distruttore.
         */
        virtual ~TabellaVariabili(){}
        
            // inserisce una nuova var, se ritorna 1 c'era gia'
        /**
         * Inserisce o aggiorna il valore di una variabile.
         * 
         * @param nuovaVariabile
         * @return se true esiste già una variabile
         */
        bool aggiungi(pVariabile variabile);

        /**
         * Cerca una variabile.
         * 
         * @param name
         * @return 
         */
        pVariabile cerca(const string& name);
        
    private:
        map<string,pVariabile> tabella;

        
    };
    
    /**
     * Puntatore "intelligente" a TabellaVariabili
     */
    typedef shared_ptr<TabellaVariabili> pTabellaVariabili;
    /**
     * Puntatore "intelligente" a Parser
     */
    typedef shared_ptr<Parser> pParser;


    /**
     * Classe interna che legge una stringa di testo che rappresenta un espressione algebrica e genera una
     * lista si simboli in notazione infissa
     */
    class NotazioneInfissa{
    public:
        /**
         * Costruttore.
         * @param espressione
         */
        NotazioneInfissa(const string& espressione);
        /**
         * Distruttore.
         */
        virtual ~NotazioneInfissa(){}
        /**
         * Errori.
         * @return 
         */
        int errori() const { return _errore; }
        /**
         * Numero dei simboli.
         * @return 
         */
        int dimensione() const { return lista_infissa.size(); }
        /**
         * Tabella delle variabili.
         * @return 
         */
        pTabellaVariabili vediTabellaVariabili() const { return tabella_variabili; }
        /**
         * Lista dei simbolo della notazione infissa.
         * @return 
         */
        list<pSimbolo> lista()const{return lista_infissa;}

    private:

        /**
         * Verifica se la prossima sequenza di caratteri è un operatore.
            
         * @return restituisce l'operatore trovato o nullptr
         */
        const pOperatore verificaPresenzaOperatore() const;
        /**
         * Verifica se la prossima sequenza di caratteri è un valore.
         * @return 
         */
        bool eValore() const;
        /**
         * Se la prossima sequenza di caratteri è una variabile.
         * @return 
         */
        bool eVariabile() const;
        /**
         * Ottiene un numero, crea il simbolo e lo inserisce in lista_infissa.
         */
        void generaNumero();
        /**
         * Ottiene una variabile, crea il simbolo e lo inserisce in lista_infissa.
         */
        void generaVariabile();
        /**
         * Popola la lista di simboli.
         * @return 
         */
        int creaListaSimboli();

        /**
         * Verifica la correttezza della formula.
         * 
         * @param operatoreCorrente
         * @param operatorePrecedente
         * @return 
         */
        int verificaFormula(pOperatore operatoreCorrente, pOperatore operatorePrecedente) const;
        
        
    protected:
        static const vector<pOperatore> operatori; ///< lista di tutti gli operandi consentiti
        
        int _errore;
        char separatore_decimale;
        
        list<pSimbolo> lista_infissa;   // lista infissa
        pTabellaVariabili tabella_variabili;
        pParser  _parser;
        string sorgente;
    
    };
    
    /**
     * Puntatore "intelligente" a NotazioneInfissa
     */
    typedef shared_ptr<NotazioneInfissa> pNotazioneInfissa;


    /**
     * Classe interna che legge una stringa di testo che rappresenta un espressione algebrica e genera una
     * lista si simboli in notazione polacca inversa postfissa
     */
    class NotazioneInversaPostfissa{
    public:
        /**
         * Costruttore.
         * @param espressione
         */
        NotazioneInversaPostfissa(const string& espressione);
        /**
         * Distruttore.
         */
        virtual ~NotazioneInversaPostfissa() {}
        /**
         * Tabella delle variabili.
         * @return 
         */
        pTabellaVariabili tabellaVariabili() const { return notazione_infissa->vediTabellaVariabili(); }
        /**
         * Tipo di errore.
         * @return 
         */
        int errore() const { return _errore; }

        /**
         * Lista dei simboli per l'accesso in lettura.
         * @return 
         */
        const list<pSimbolo> lista()const{return lista_postfissa;}
        /**
         * Lista dei simboli per l'accesso in scrittura.
         * @return 
         */
        list<pSimbolo> lista(){return lista_postfissa;}
            
    private:
        /**
         * Crea la notazione polacca inversa postfissa a partire da una notazione infissa.
         * @return 
         */
        int creaNotazioneInversa();
        /**
         * Svuota lo stack e ordina gli operandi nella lista per priorità.
         * @param ultimoSimbolo
         */
        void precedenzaCalcoli(pSimbolo ultimoSimbolo);
        /**
         * Svuota lo stack e aggiorna la lista fino all'incontro con una parentesi apererta.
         */
        void eliminaParentesi();
        
    protected:
        list<pSimbolo> lista_postfissa;  ///< lista di simboli postfissa
        stack<pSimbolo> stack_simboli;  ///< stack dei simboli usato per la manipolazione
        
        pNotazioneInfissa notazione_infissa;
        int _errore;
            
    };
    
    /**
     * Puntatore "intelligente" a NotazioneInversaPostfissa
     */
    typedef shared_ptr<NotazioneInversaPostfissa> pNotazioneInversaPostfissa;

    
    
    /**
     * Questa classe calcola il valore di una lista di simboli in notazione inversa post 
     * fissa.
     */
    class CalcolaEspressione{
    public:
        /**
         * Costruttore.
         * @param notazioneInversaPostfissa
         */
        CalcolaEspressione(const string& espressione);
        /**
         * Distruttore
         */
        virtual ~CalcolaEspressione(){}
        /**
         * Assegna una variabile.
         * @param variabile
         */    
        void assegna(const Variabile& variabile);
        /**
         * Calcola espressione.
         * @return 
         */
        double risultato();
        /**
         * Tipo di errore.
         * @return 
         */
        int errore() const { return _errore; }
    private:
        void calcola(pOperatore operatore);
        
    protected: 
            stack<pSimbolo> stack;
            pNotazioneInversaPostfissa notazioneInversaPostfissa;
            int _errore;
            
    };

    typedef shared_ptr<CalcolaEspressione> pCalcolaEspressione;

    
}


namespace Utili{
    
    using namespace NotazionePolacca;

    /**
     * La Classe Espressione è la classe fondamentale che converte una espressione in notazione
     * polacca e ne calcola il risultato.
     * <pre>
     * es.
     * <code>
     *      Espressione<float> e("2^(-a/2)");
     *      e.assegna("a",-3);
     *      cout << "Il valore e' : " << e.esegui() << endl;
     * </code>
     * </pre>
     */
    class Espressione{
    public:
        /**
         * Costruttore
         * @param espressione
         */
        Espressione(const string& espressione);
        /**
         * Distruttore
         */
        virtual ~Espressione(){}
        
        /**
         * Assegna un valore a una variabile.
         * @param Va
         */
        void assegna(const string& nome,double valore)
        {assegna(Variabile(nome,valore));}

        int errore() const { return tipo_errore; }
        /**
         * Risultato dell'espressione.
         * @return può essere o un valore reale, se assegnate tutte le variabili, oppure NaN (valore indefinito)
         * @throw std::invalid_argument
         */
        double esegui();
        
            
    private:
        /**
         * @see <code>void assegna(const string& nome,double valore)</code>
         * @param variabile
         */
        void assegna(const Variabile& variabile);
        
        int tipo_errore;
        pCalcolaEspressione calcola;
            

    };

};

    /*
       + ------------------------------------------------------------------ + 
       |                                                                    |
       |                  IMPLEMENTAZIONE METODI IN LINEA                   |
       |                                                                    |
       + ------------------------------------------------------------------ +
    */





                        /* Classe Operatore */

inline Operatore::Operatore(const string& _operazione, int _priorita, funzione_di_calcolo _funzione, int _operandi)
:Simbolo{TipoSimbolo::TIPO_OPERATORE}, 
 operazione{_operazione}, priorita{_priorita},operandi{_operandi},parentesi_aperta{false},parentesi_chiusa{false},funzione{false},m_funzione{_funzione}
{  
    if (operazione.rfind('(') != string::npos){
        parentesi_aperta=true;
        
        if (operazione[0] != '(') 
            funzione=true;
            
    }else if (operazione[0] == ')')
                parentesi_chiusa=true;
}

inline Operatore::Operatore(const Operatore& M)
: Simbolo{TipoSimbolo::TIPO_OPERATORE}, 
  operazione{M.operazione},priorita{M.priorita},operandi{M.operandi}{
    parentesi_aperta = M.parentesi_aperta;
    parentesi_chiusa = M.parentesi_chiusa;
    funzione  = M.funzione;
    m_funzione= M.m_funzione;
}

inline string Operatore::debug()const{
    stringstream ss;
    ss << "Operatore [0x"<< this<<"]: \"" << operazione << "\"";
    return ss.str();
}

                         /* Classe Valore */

inline Valore& Valore::operator=(const Valore& rv){
    if(this == &rv) return *this;
    valore = rv.valore;
    return *this;
}

inline string Valore::debug()const{
    stringstream ss; ss << "Valore [0x"<< this<<"]:  = " << valore << std::endl;
    return ss.str();
}


                         /* Classe Variabile */


inline Variabile::Variabile(const string& nominativo, double valore) : Valore{valore},_nome{nominativo} {
    minuscolo(_nome.begin(),_nome.end());
    _tipo = TipoSimbolo::TIPO_VARIABILE;
}

inline Variabile& Variabile::operator=(const Valore& v){
    if(this == &v) return *this;
    valore = v.vedi();
    return *this;
}

inline Variabile& Variabile::operator=(const Variabile& v) {
    if(this == &v) return *this;
    if(_nome.compare(v._nome) != 0) 
        throw std::logic_error{"Impossibile assegnare una variabile di tipo diverso.."};
    valore = v.vedi();
    return *this;
}


inline string Variabile::debug()const{
    stringstream ss;
    ss << "Variabile [0x"<< this<<"]: \"" << _nome << "\" = " << valore << std::endl;
    return ss.str();
}



                    /* Classe  TabellaVariabili */

inline bool TabellaVariabili::aggiungi(pVariabile nuovaVariabile){
    auto voceTabella = tabella.find(nuovaVariabile->nome());
    if (voceTabella != tabella.end()){
        // la variabile esiste gia' la aggiorna al nuovo valore
        auto variabileEsistente = (*voceTabella).second;
        *variabileEsistente = *nuovaVariabile;
        return true;
    }
    tabella[nuovaVariabile->nome()] = nuovaVariabile;
    return false;
}

inline pVariabile TabellaVariabili::cerca(const string& name){
    string nomeMinuscolo("");
    for(auto carattere = name.begin(); carattere != name.end(); ++carattere)
        nomeMinuscolo += std::tolower(*carattere);
    
    auto variabile = tabella.find(nomeMinuscolo);
    if (variabile != tabella.end())
        return (*variabile).second;
    return nullptr;
}


                    /* Classe  NotazioneInfissa */

inline const vector<shared_ptr<Operatore> > NotazioneInfissa::operatori{
    make_shared<Operatore>( // POTENZA
        "^",
        4,// La potenza ha la gerachia maggiore
        [](double v[]){
            double v0=v[0],v1=v[1];
            double r=pow(v1,v0);
            return r;
        },
        2
    ), 
            
    make_shared<Operatore>( // MOLTIPLICAZIONE
        "*",
        3,
        [](double v[]){
            return v[1] * v[0];
        },
        2
    ),
    make_shared<Operatore>( // DIVISIONE
        "/",
        3,
        [](double v[]){
            return (v[1] / v[0]);
        },
        2
    ),
    make_shared<Operatore>( // SOMMA
        "+",
        2,[](double v[]){
            return (v[1] + v[0]);
        },
        2
    ),
    make_shared<Operatore>( // SOTTREAZIONE
        "-",
        2,
        [](double v[]){
            return v[1] - v[0];
        },
        2
    ), 
    make_shared<Operatore>(
        ")",
        1,
        nullptr // la parentesi e' trattata dall'algoritmo!
    ), 
    make_shared<Operatore>(
        "(",
        1,
        nullptr
    ),
    make_shared<Operatore>( // LOGARITMO NATURALE
        "ln(",
        1,
        [](double v[]){
            return log(v[0]);
        }
    ),
    make_shared<Operatore>( // ESPONENZIALE
        "exp(",
        1,
        [](double v[]){
            return exp(v[0]);
        }
    ),
    make_shared<Operatore>( // SENO
        "sen(",
        1,
        [](double v[]){
            return sin(v[0]);
        }
    ),
    make_shared<Operatore>( // COSENO
        "cos(",
        1,
        [](double v[]){
            return cos(v[0]);
        }
    ),
    make_shared<Operatore>( // TANGENTE
        "tan(",
        1,
        [](double v[]){
            return tan(v[0]);
        }
    ),
    make_shared<Operatore>( // ARCOTANGENTE
        "arctan(",
        1,
        [](double v[]){
            return atan(v[0]);
        }
    ),
    make_shared<Operatore>( // RADICE QUADRATA
        "sqrt(",
        1,
        [](double v[]){
            return sqrt(v[0]);
        }
    )
};



inline NotazioneInfissa::NotazioneInfissa(const string& espressione) :  sorgente{espressione}{
    // individua il separatore decimale utilizzato
    separatore_decimale= (atof("0,5") > std::numeric_limits<float>::epsilon()) ? ',' : '.';
    for(auto c = sorgente.begin();c!=sorgente.end();++c)
        if (*c == ',') *c = '.'; // perche' il parser accetta sempre il punto

    _parser= std::make_shared<Parser>(sorgente.c_str());
    tabella_variabili= make_shared<TabellaVariabili>();

    _parser->saltaSpazio();
    _errore=creaListaSimboli();
}

inline const pOperatore NotazioneInfissa::verificaPresenzaOperatore() const{
    for(auto operatore: operatori){
        if(operatore != nullptr)
            if(_parser->eLaStringa(operatore->tipoOperazione()))
                return operatore;
    }
    return nullptr;
}

inline bool NotazioneInfissa::eValore() const{
    return isdigit(_parser->carattereAttuale()) || _parser->carattereAttuale()=='.';
}

inline bool NotazioneInfissa::eVariabile() const{
    return std::isalpha(_parser->carattereAttuale());
}

inline void NotazioneInfissa::generaNumero(){
    string numero{_parser->estraeNumeroDecimale()};
    
    // controlla la presenza del giusto separatore decimale
    for(auto c = numero.begin(); c != numero.end(); ++c)
        if (*c==',' || *c=='.') 
            *c = separatore_decimale;
    
    double valore(static_cast<double>( atof(numero.c_str())) );
    pSimbolo simbolo = make_shared<Valore>(valore);
    lista_infissa.push_back(simbolo);
}

inline void NotazioneInfissa::generaVariabile(){
    // legge il nome della variabile dalla formula
    string nomeVariabile = _parser->estraeNomeVariabile();
    
    // cerca la variabile nella tabella_variabile, se non esiste la crea
    pVariabile variabile = tabella_variabili->cerca(nomeVariabile);
    if (variabile == nullptr) {
        variabile = make_shared<Variabile>(nomeVariabile,INDEFINITO);
        tabella_variabili->aggiungi(variabile);
    }
    lista_infissa.push_back(variabile);
}

inline int NotazioneInfissa::creaListaSimboli(){
    pOperatore operatore = nullptr;
    pOperatore precedenteOperatore = nullptr;
    
    int numeroParentesi=0; // verifica le parentesi
    bool parentesiAperta = true; // verifica la parentesi aperta
    
    bool ultimoSimboloNumero=false;
            
    // Analizza il testo
    while (!_parser->fine() && !_parser->errore()){
        precedenteOperatore = operatore; 
        operatore = verificaPresenzaOperatore(); 
        
        if (operatore != nullptr){ // E' UN OPERATORE
            if (!parentesiAperta || !operatore->eSommaODifferenza()){
                
                /* cerca errori */
                
                if (operatore->parentesiAperta() && ultimoSimboloNumero)
                    return ERRORE_SINTASSI;
                
                if (precedenteOperatore != nullptr){
                    int erroreOperatore = verificaFormula(operatore,precedenteOperatore);
                    if (erroreOperatore != NO_ERRORE) 
                        return erroreOperatore;
                }
                // se il precedente simbolo era un numero e ora c'è una parentesi aperta c'è
                // certamente un errore
                if (ultimoSimboloNumero && operatore->parentesiAperta())
                    return USO_NON_CORRETTO_OPERANDO;
                
                /* aggiorna lista e parser*/
                _parser->verificaSuccessivo(operatore->tipoOperazione());
                lista_infissa.push_back(dynamic_pointer_cast<Simbolo>(operatore));
                
                /* aggiorna stato parentesi */
                if (operatore->parentesiAperta()){
                    ++numeroParentesi;
                    parentesiAperta=true;
                }
                if (operatore->parentesiChiusa())
                    --numeroParentesi;
            }else{
                /* altrimenti e' un segno aritmetico in questo caso aggiungiamo 
                   uno zero 
                   infatti (-A) = (0-A) */
                lista_infissa.push_back(make_shared<Valore>(0.0));
                
                /* aggiorna lista e parser*/
                _parser->verificaSuccessivo(operatore->tipoOperazione());
                lista_infissa.push_back(dynamic_pointer_cast<Simbolo>(operatore));
                
            }
            ultimoSimboloNumero=false;
            continue;
        }
        parentesiAperta=false;
        _parser->saltaSpazio();
        
        if (eValore()){
            generaNumero();
            ultimoSimboloNumero=true;
            continue;
        }
        
        if (eVariabile()){
            generaVariabile();
            ultimoSimboloNumero=true;
            continue;
        }
        
        return ERRORE_SINTASSI;
    }
    
    if (_parser->errore()) 
        return ERRORE_PARSE;
    
    if (numeroParentesi != 0) 
        return ERRORE_PARENTESI;
    return 0;
}

inline int NotazioneInfissa::verificaFormula(pOperatore operatoreCorrente, pOperatore operatorePrecedente) const{
    if (operatoreCorrente->eSommaODifferenza() && operatorePrecedente->eSommaODifferenza())
        // +1 è ammesso ++ NO!
        return USO_NON_CORRETTO_OPERANDO;
    if (operatorePrecedente->parentesiAperta()){
        // (* or (/ or (^ are not allowed
        std::string p(operatoreCorrente->tipoOperazione());
        if (p=="*" || p=="/" || p=="^" || p==")")
            return USO_NON_CORRETTO_OPERANDO;
    }
    if ((operatorePrecedente->parentesiChiusa() && operatoreCorrente->parentesiAperta()) ||
            (operatorePrecedente->parentesiAperta() && operatoreCorrente->parentesiChiusa()) )
        // ...)(...   oppure  ...()...
        return USO_NON_CORRETTO_OPERANDO;

    return NO_ERRORE;
}




                    /* Classe  NotazioneInversaPostfissa */


inline NotazioneInversaPostfissa::NotazioneInversaPostfissa(const string& origin) 
: notazione_infissa{std::make_shared<NotazioneInfissa>(origin)} {
        int erroreN = notazione_infissa->errori();
        if (erroreN == NO_ERRORE) 
            _errore = creaNotazioneInversa();
        else 
            _errore = erroreN;
}

inline int NotazioneInversaPostfissa::creaNotazioneInversa(){
    for(pSimbolo simbolo: notazione_infissa->lista()){
        if (!simbolo->eOperatore()){
            // se è una variabile o un valore la mette nella lista postfissa
            lista_postfissa.push_back(simbolo);
            continue;       
        } else {// se invece e' un operatore
            
            pOperatore operatore= dynamic_pointer_cast<Operatore>(simbolo);
            // se e' una parentesi o una funzione
            if (operatore->parentesiAperta()){
                // mette il simbolo nello stack
                stack_simboli.push(simbolo);
                continue;
            }
            // se �una parentesi chiusa...
            if (operatore->parentesiChiusa()){
                // togliamo i simboli dallo stack fino a quando troviamo una parentesi
                // aperta o una funzione.
                eliminaParentesi();
                continue;
            }
            precedenzaCalcoli(simbolo);
        }
    }
    
    // si svuola lo stack alla ricerca di operazioni da eseguire....
    while (!stack_simboli.empty()){
        pSimbolo s = stack_simboli.top();
        lista_postfissa.push_back(s);
        stack_simboli.pop();
    }
    return 0;
}

inline void NotazioneInversaPostfissa::precedenzaCalcoli(pSimbolo ultimoSimbolo){
    pOperatore ultimoOperando = dynamic_pointer_cast<Operatore>(ultimoSimbolo);
    pOperatore operando = nullptr;
    int prioritaOperando = ultimoOperando->valorePriorita();
    
    // svuota lo stack e ordina gli operandi nella lista per priorità
    while(!stack_simboli.empty()){
            shared_ptr<Simbolo> simbolo = stack_simboli.top(); // legge un simbolo dallo stack
            operando = dynamic_pointer_cast<Operatore>(simbolo);
            if (operando->valorePriorita() < prioritaOperando) break;
            stack_simboli.pop();
            lista_postfissa.push_back(simbolo);      // aggiunge il simbolo a post
    }
    stack_simboli.push(ultimoSimbolo);
}

inline void NotazioneInversaPostfissa::eliminaParentesi(){
            while (!stack_simboli.empty()){
                pSimbolo simbolo = stack_simboli.top(); // legge un simbolo dallo stack
                stack_simboli.pop(); // lo elimina dallo stack
                pOperatore operando = dynamic_pointer_cast<Operatore>(simbolo);
                // se trovo una parentesi aperta esco dal ciclo
                if (operando->parentesiAperta()){
                        // se è una funzione la aggiungo alla lista postfissa
                        if (operando->eFunzione()) lista_postfissa.push_back(simbolo);
                        break; // esce dal ciclo
                } else {
                    lista_postfissa.push_back(simbolo);
                }
            }
        }


                       /* Classe CalcolaEspressione */


inline CalcolaEspressione::CalcolaEspressione(const string& espressione):  _errore(0){
    notazioneInversaPostfissa = make_shared<NotazioneInversaPostfissa>(espressione);
    if (notazioneInversaPostfissa == nullptr){
        _errore=ERRORE_GENERICO;
    }
        
}

inline void CalcolaEspressione::assegna(const Variabile& variabile){
    shared_ptr<Variabile> dv=std::make_shared<Variabile>(variabile);
    notazioneInversaPostfissa->tabellaVariabili()->aggiungi(dv);
}

inline double CalcolaEspressione::risultato(){
    while (!stack.empty()) stack.pop();
    _errore=0;
    if(!notazioneInversaPostfissa->lista().empty()){
        for (pSimbolo simbolo : notazioneInversaPostfissa->lista()){

                if (simbolo->eOperatore()){
                        calcola(dynamic_pointer_cast<Operatore>(simbolo));
                }else {
                        stack.push(simbolo);
                }
                if (_errore) return 0.0;
        }
        
    }else{
        _errore = ERRORE_SINTASSI;
        return 0.0;
    }
    shared_ptr<Simbolo> s = stack.top();
    stack.pop();
    return static_cast<double>(*s);
}

inline void CalcolaEspressione::calcola(pOperatore operatore){
    size_t numeroOperandi = operatore->numeroOperandi();
    if (stack.size() < numeroOperandi){
            _errore=ERRORE_GENERICO;
            return;
    }
    // estrazione operandi dallo stack
    double* operandi = new double[numeroOperandi];
    for (auto i=0; i < numeroOperandi; ++i){
            pSimbolo s = stack.top();
            stack.pop();
            operandi[i] = s->vedi();
    }
    // calcolo risultato 
    funzione_di_calcolo funzione = operatore->funzioneDiCalcolo();
    double risultato = (*funzione)(operandi);
    delete [] operandi;
    
    pSimbolo  valoreRisultato = make_shared<Valore>(risultato);
    // il risultato viene messo nello stack
    stack.push(valoreRisultato);
}




                    /* Classe Espressione */
inline Utili::Espressione::Espressione(const string& espressione)
: tipo_errore{1}, calcola{nullptr}{
    calcola = make_shared<CalcolaEspressione>(espressione);
    if (calcola != nullptr) 
        tipo_errore = calcola->errore();
    else 
        tipo_errore=ERRORE_GENERICO;
        
}
            
inline void Utili::Espressione::assegna(const Variabile& variabile){
    if(!tipo_errore){
        if(calcola != nullptr) 
            calcola->assegna(variabile);
    }
}
inline double Utili::Espressione::esegui(){
    double risultato;
    risultato = 0.0;
    if (!tipo_errore && calcola != nullptr){
            risultato = calcola->risultato();
            tipo_errore = calcola->errore();
            
            if (tipo_errore == NO_ERRORE) 
                return risultato;
    }
    switch(tipo_errore){
        case ERRORE_GENERICO: 
            throw std::invalid_argument{"Espressione: errore..."};
        case ERRORE_PARSE:    
            throw std::invalid_argument{"Espressione: errore di analesi."};
        case ERRORE_PARENTESI:
            throw std::invalid_argument{"Espressione: errore parentesi."};
        case USO_NON_CORRETTO_OPERANDO: 
            throw std::invalid_argument{"Espressione: errore uso non corretto degli operandi."};
        case ERRORE_SINTASSI: 
            throw std::invalid_argument{"Espressione: errore sintassi."};

    };
    return 0.0;
}



#endif
