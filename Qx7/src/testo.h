/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
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
 * @file testo.h
 * @author Dr. Domenico della Peruta
 * @date 16-12-2017
 * @version 1.0.2, 28-08-2018
 * 
 * @brief File contenente l'intestazione della classe Testo.
 *
 * La classe Testo appartiene allo spazio dei nomi 'Utili', cioè l'insieme
 * delle classi generali che semplificano alcune operazioni di manipolazione
 * e sviluppo software in C++.
 * 
 * @namespace Utili
 * @class Testo
 * @enum Unità
 */
#ifndef testo_h
#define testo_h

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;


namespace Utili {
    /**
     * Enumerazione che specifica il tipo di indice della classe Testo.
     */
    enum class Unità{
        BYTE,      ///< indice alla struttua del codifica
        CARATTERE, ///< indice ai singoli caratteri
        PAROLA     ///< indice alle singole parole
    };
    /**
     * Classe che gestisce un 'Testo' di caratteri e parole Unicode (UTF8).
     * 
     * A differenza della classe standard dello C++ (string), essa opera sui 
     * songoli caratteri Unicode e sulle parole del Testo.
     */
    class Testo{
    public:
        /**
         * Costruttore a zero argomenti o con una stringa.
         * @param utf8 stringa standard C++
         */
        Testo(const string& utf8="");
        
        /**
         * Costruttore di copia.
         * @param copia
         */
        Testo(const Testo& copia){testo=copia.testo;}
        /**
         * Costruttore con carattere.
         * @param c tipo char
         */
        Testo(char c){testo =""; testo+=c;}
        
        /**
         * Il testo (UTF8) viene convertito nella codifica ISO 8859-1 (Latino 1).
         * Cioè in una codifica particolare dell'estensione ASCII di lunghezza fissa (1 byte)
         * che contiene tutti i caratteri delle lingue europee occidentali.
         * 
         * @throw logic_error eccezione lanciata se il testo contiene caratteri non Unicode.
         * @return stringa standard composta da soli caratteri "Latino 1", gli 
         * altri caratteri Uniconde (UTF8) non vengono aggiunti.
         */
        string latino1()const;
        
        /**
         * @return stringa standard
         */
        string stringa()const{return testo;}
        
        /**
         * Analizza la lunghezza in byte di ogni singolo carattere Unicode
         * del testo.
         * @param indice  di default è riferito ai singoli byte della codifica, indica il 
         * carattere della sequenza di testo da analizzare.
         * @param tipoIndice  di default è Unità::BYTE, ed indica la posizione in byte del carattere da analizzare;
         * se è Unità::CARATTERE, si riferisce al sequenza di caratteri UTF8.
         * @throw logic_error generato se si usa tipoIndice=Unità::PAROLA
         * @return lunghezza in byte del carattere, di valore -1 se l'indice è fuori la stringa, 
         * di valore 0 se riferito a un byte non di "testa" della codifica UTF8 
         * (nel caso si usi Unità::BYTE).
         */
        int byteCarattere(size_t indice,Unità tipoIndice=Unità::BYTE)const;
        
        /**
         * Lunghezza codifica in numero di byte.
         * @return size_t
         */
        size_t numeroByte()const{return testo.size();}
        
        /**
         * Numero di caratteri Unicode (UTF8).
         * @return size_t
         */
        size_t numeroCaratteri()const;
        
        
        /**
         * Numero di parole, cioè di stringhe separate da caratteri di spaziatura o separazione.
         * @return 
         */
        size_t numeroParole()const{return scomposizione().size();}
        
        /**
         * Lunghezza del testo.
         * @param tipo di unità di lunghezza: Unità::BYTE, Unità::CARATTERE o Unita::PAROLA.
         * @return 
         */
        size_t lunghezzaTesto(Unità tipo)const;
        
        /**
         * Scompone il testo in una sequenza di parole, separate da spazi, 
         * caratteri di fine riga o di tabilazione.
         * 
         * @param eSeparatori, di default è false, se posto a true, l'elento 
         * conterrà anche separatamente i singoli caratteri di separazione.
         * 
         * @return Lista sequenziale standard (vector<..>) di parole o caratteri
         * di tipo Testo.
         */
        vector<Testo> scomposizione(bool eSeparatori=false)const;
        
        /**
         * @fn Testo& operator=(const Testo& t)
         * @brief Metodo operatore di assegnazione, implementato in linea.
         * @param t
         * @return 
         */
        /**
         * @fn Testo& operator=(const string& s)
         * @brief Metodo operatore di assegnazione con stringa standard, implementato in linea.
         * @param s
         * @return 
         */
        /**
         * @fn Testo& operator=(char c)
         * @brief Metodo operatore di assegnazione con tipo carattere 'char', implementato in linea.
         * 
         * @param c
         * @return 
         */
        Testo& operator=(const Testo& t){testo = t.testo;return *this;}
        Testo& operator=(const string& s){testo = s;return *this;}
        Testo& operator=(char c){testo = "";testo += c;return *this;}
        /**
         * @fn Testo& operator+=(const Testo& t)
         * @brief Metodo operatore di concatenamento, implementato in linea.
         * 
         * @param t
         * @return 
         */
        /**
         * @fn Testo& operator+=(const string& s)
         * @brief Metodo operatore di concatenamento con stringa standard, implementato in linea.
         * 
         * @param s
         * @return 
         */
        /**
         * @fn Testo& operator+=(char c)
         * @brief Metodo operatore di concatenamento con tipo carattere 'char', implementato in linea.
         * 
         * @param c
         * @return 
         */
        Testo& operator+=(const Testo& t){testo += t.testo;return *this;}
        Testo& operator+=(const string& s){testo += s;return *this;}
        Testo& operator+=(char c){testo += c;return *this;}
        /**
         * @fn Testo operator+(const Testo& t1,const Testo& t2)
         * @brief Metodo oparatore esterno di concatenamento tra due oggetti di Testo, 
         *        implementato in linea.
         * @param inizio
         * @param lunghezza
         * @param tipo
         * @return 
         */
        /**
         * @fn Testo operator+(const Testo& t,const string& s)
         * @brief Metodo oparatore esterno di concatenamento tra un oggetto di Testo e una 
         *        stringa standard, implementato in linea.
         * @param inizio
         * @param lunghezza
         * @param tipo
         * @return 
         */
        /**
         * @fn Testo operator+(const string& s,const Testo& t)
         * @brief Metodo oparatore esterno di concatenamento tra una stringa standard e un 
         *        oggetto di Testo, implementato in linea.
         * @param inizio
         * @param lunghezza
         * @param tipo
         * @return 
         */
        friend Testo operator+(const Testo& t1,const Testo& t2)
        {Testo t = t1; return t += t2;}
        friend Testo operator+(const Testo& t,const string& s)
        {Testo t1 = t; return t1 += s;}
        friend Testo operator+(const string& s,const Testo& t)
        {Testo t1 = s; return t1 += t;}
        
        /**
         * @fn bool operator ==(const Testo& t1,const Testo& t2)
         * @brief Metodo operatore di confronto di uguagianza tra due testi, implementato in linea.
         * @param inizio
         * @param lunghezza
         * @param tipo
         * @return 
         */
        /**
         * @fn bool operator !=(const Testo& t1,const Testo& t2)
         * @brief Metodo operatore di confronto di disuguagianza tra due testi, implementato in linea.
         * 
         * @param inizio
         * @param lunghezza
         * @param tipo
         * @return 
         */
        /**
		 * @fn bool operator ==(const Testo& t1,const string& t2)
		 * @brief Metodo operatore di confronto di uguagianza tra un testo e una stringa, implementato in linea.
		 *
		 * @param inizio
		 * @param lunghezza
		 * @param tipo
		 * @return
		 */
        /**
		 * @fn bool operator ==(const string& t1,const Testo& t2)
		 * @brief Metodo operatore di confronto di uguagianza tra una stringa e un testo, implementato in linea.
		 *
		 * @param inizio
		 * @param lunghezza
		 * @param tipo
		 * @return
		 */
        /**
		 * @fn bool operator !=(const Testo& t1,const string& t2)
		 * @brief Metodo operatore di confronto di disuguagianza tra un testo e una stringa, implementato in linea.
		 *
		 * @param inizio
		 * @param lunghezza
		 * @param tipo
		 * @return
		 */
		/**
		 * @fn bool operator !=(const string& t1,const Testo& t2)
		 * @brief Metodo operatore di confronto di disuguagianza tra una stringa e un testo, implementato in linea.
		 *
		 * @param inizio
		 * @param lunghezza
		 * @param tipo
		 * @return
		 */
        friend bool operator ==(const Testo& t1,const Testo& t2)
        {return t1.testo == t2.testo;}
        friend bool operator !=(const Testo& t1,const Testo& t2)
        {return !(t1 == t2);}
        friend bool operator ==(const Testo& t1,const string& t2)
		{return t1.testo == t2;}
        friend bool operator ==(const string& t1,const Testo& t2)
        {return t2 == t1;}
		friend bool operator !=(const Testo& t1,const string& t2)
		{return !(t1 == t2);}
		friend bool operator !=(const string& t1,const Testo& t2)
		{return !(t1 == t2);}
        /**
         * Metodo operatore di flusso stream d'inserimento, implementato in linea.
         * @param inizio
         * @param lunghezza
         * @param tipo
         * @return 
         */
        friend ostream& operator<<(ostream& os, const Testo& t)
        {os << t.stringa(); return os;}
        

        
        /**
         * Seleziona una parte del testo.
         * <pre>
         * Es.:
         * Testo t{"Questa è una frase di esempio..."};
         * Testo s = t.frammento(2, 3, Unità::PAROLA); 
         * cout << s.stringa() << endl;
         * ....
         * [output video]
         * 
         * Unità::PAROLA
         * 
         *            lunghezza
         *          |<--- 3 ---->| 
         * Questa è "una frase di" esempio...
         *    0   1   2    3   4      5   <-- indice 
         * 
         * </pre>
         * 
         * @param inizio indice di parte da selezionale.
         * @param lunghezza delle testo
         * @param tipo unità di misura su cui si base la lunghezza e l'indice di inizio.
         * @throw length_error
         * @throw out_of_range
         * @return 
         */
        Testo frammento(size_t inizio, size_t lunghezza,Unità tipo =Unità::CARATTERE)const;
        /**
         * Seleziona tutta la parte di testo successiva a un dato indice.
         * 
         * @see <code>frammentoTesto(size_t , size_t, Unità)</code>
         * @param inizio
         * @param tipo unità di misura su cui si base l'indice di inizio.
         * @throw length_error
         * @throw out_of_range
         * @return 
         */
        Testo frammento(size_t inizio, Unità tipo =Unità::CARATTERE)const
        {return frammento(inizio, lunghezzaTesto(tipo)-inizio, tipo);}
        
        /**
         * Aggiungi del Testo ad un dato indice. L'indice può essere riferito alla sequenza di 
         * byte del testo, alla succesione dei caratteri oppire, come nell'esempio seguente,
         * a una successione di parole.
         * 
         * <code>
         * Es.:<br>
         * Testo t{"Questa è una frase di esempio..."};<br>
         * Testo s = "NON"; <br>
         * t.aggiungi(s, 1, Unità::PAROLA);<br>
         * cout << s.stringa() << endl;<br>
         * ....<br>
         * [output video]<br>
         * <br>
         * Unità::PAROLA<br>
         * <br>
         *           
         * Questa NON è una frase di esempio...<br>
         *    0    1  2  3    4    5   6   <-- indice <br>
         * <br>
         * </code>
         * 
         * @throw out_of_range
         * @param stringa
         * @param indice è riferito al tipo di unità
         * @param tipo
         */
        void aggiungi(const Testo& stringa, size_t indice, Unità tipo =Unità::CARATTERE);
        /**
         * Aggiunge una stringa standard ad un dato indice.
         * 
         * @see <code>void aggiungi(const Testo& stringa, size_t indice, Unità tipo)</code>
         * @throw out_of_range
         * @param stringa
         * @param indice
         * @param tipo
         */
        void aggiungi(const string& stringa, size_t indice, Unità tipo =Unità::CARATTERE)
        {aggiungi(Testo{stringa}, indice,tipo);}
        /**
         * Aggiunge un carattere di tipo 'char' a un dato indice. L'indice di default è in byte.
         * 
         * @see <code>void aggiungi(const Testo& stringa, size_t indice, Unità tipo)</code>
         * @throw out_of_range
         * @param carattere
         * @param indice
         * @param tipo
         */
        void aggiungi(char carattere, size_t indice, Unità tipo =Unità::BYTE)
        {aggiungi(Testo{carattere}, indice,tipo);}
        
        /**
         * Accoda una stringa di tipo 'Testo' al testo.
         * 
         * @param stringa
         */
        void aggiungi(const Testo& stringa){*this += stringa;}
        /**
         * Accoda una stringa standard C++ al Testo.
         * @param stringa
         */
        void aggiungi(const string& stringa)
        {aggiungi(Testo{stringa});}
        
        /**
         * Permette di vedere un sincolo elemento del testo conoscendo la sua posizione, di default è un carattere, 
         * ma se specifichiamo il tipo di unità dell'indice, può essere rispettivamente anche un byte o una parola.
         * @param indice
         * @param tipo riferito sia all'indice che al valore di ritorno.
         * @throw out_of_range
         * @return l'elemento sia esso byte, carattere o parola, è espresso in 'Testo'.
         */
        Testo vedi(size_t indice, Unità tipo =Unità::CARATTERE)const;
        /**
         * Permette di trovare tutte le posizioni in cui un dato elemento compare nel testo. 
         * Di default l'unità dell'indice è il carattere UTF8 (Unità::CARATTERE).
         * 
         * @param elemento
         * @param tipo di unità dell'indice
         * @throw length_error nel caso di lunghezza nulla dell'elemento da cercare
         * @return vettore degli indici incui compare l'elemento da cercare
         */
        vector<size_t> trova(const Testo& elemento, Unità tipo =Unità::CARATTERE)const;
        /**
         * @see vector<size_t> trova(const Testo& elemento, Unità tipo)
         * @param elemento
         * @param tipo
         * @throw length_error
         * @return 
         */
        vector<size_t> trova(const string& elemento, Unità tipo =Unità::CARATTERE)const
        {return trova(Testo{elemento},tipo);}
        /**
         * Permette di trovare tutte le posizioni in cui un dato carattere 'char' compare nel testo. 
         * Di default l'unità dell'indice è il byte (Unità::BYTE).
         * 
         * @see <code>vector<size_t> trova(const Testo& elemento, Unità tipo)</code>
         * @param elemento
         * @param tipo
         * @throw length_error
         * @return 
         */
        vector<size_t> trova(char elemento, Unità tipo =Unità::BYTE)const
        {return trova(Testo{elemento},tipo);}
        /**
         * Permette di eliminare un elemento dal testo, di default indica un elemento di tipo 
         * carattere unicode (UTF8).
         * @param indice
         * @param tipo si riferisce sia all'unità dell'indice che al tipo di elemento da eliminare
         * @return numero di byte eliminati
         */
        size_t elimina(size_t indice, Unità tipo =Unità::CARATTERE);
        /**
         * Elimina tutto il testo.
         */
        void elimina(){testo = "";}
        /**
         * Crea un testo formattato in un blocco di lunghezza più o meno omogenea.
         * La formattazione predefinita è di tipo 'Unità::PAROLA' in cui le parole non sono 
         * spezzate tranne se non sono più lunghe del 'numeroCaratteri'. Se il tipo è 
         * 'Unità::Carattere', ogni riga del blocco avrà lo stesso numero di caratteri Unicode, 
         * eccetto l'ultima riga; se di tipo 'Unità::Byte', la lunghezza sarà riferita al numero 
         * di byte.
         * 
         * @param numeroCaratteri
         * @param tipo specifica la lunghezza della formattazione del blocco.
         * @throw length_error se la lunghezza è nulla
         * @return 
         */
        Testo incolonna(size_t numeroCaratteri, Unità tipo =Unità::PAROLA)const;
        /**
         * Elenco delle righe del testo.
         * @return 
         */
        vector<Testo> righe()const;
        /**
         * Ultima riga del testo.
         * @return 
         */
        Testo ultimaRiga()const{return righe()[righe().size()-1];};
        
        /**
         * Stampa dati per il debug del testo.
         */
        void debug()const;
        
        /**
         * Permette la stampa dell'Unità nel testo di debug.
         * @param tipo
         * @return 
         */
        static string stampa(Unità tipo);
        
    protected:
        /**
         * Trova il carattere Unicode (UTF8) nel testo.
         * @param idCarattere indice della sola sequenza dei caratteri UTF8.
         * @throw out_of_range
         * @return 
         */
        Testo carattere(size_t idCarattere)const;
        
        /**
         * Trova il byte della sequenza di codifica del testo.
         * @param idByte indice dei byte del testo
         * @return 
         */
        u_char byte(size_t idByte)const
        {return testo.at(idByte);}
        
        /**
         * Trova una parola (vista come un insieme di caratteri separati da uno spazio o da un carattere di tabulazione) 
         * @param idParola indice di sequenza delle parole.
         * @throw out_of_range
         * @return 
         */
        Testo parola(size_t idParola)const;
        
        /**
         * Permette la conversionde dell'indice dei byte della codifica del testo, nell'indice
         * dei caratteri UTF8 (multi byte).
         * @throw logic_error
         * @throw out_of_range 
         * @throw length_error
         */
        size_t indiceCarattere(size_t indiceByte)const;
        
    private:
        int lunghezzaCarattereUTF8(unsigned char byte)const;
        /**
         * Verifica se un carattere di testo è un separatore di "parole".
         * 
         * @param c carattere o Testo
         * @return 
         */
        template<typename C>
        bool separatore(C c)const
        {return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\0';}
        
        /**
         * Testo di errore indice fuori intervallo  del metodo frammento
         * @param inizio
         * @param lunghezza
         * @param tipo
         * @return 
         */
        string debugFrammentoRange(size_t inizio, size_t lunghezza, Unità tipo)const;
        /**
         * Testo di errore lunghezza dell'intervallo del metodo frammento.
         * @param inizio
         * @param lunghezza
         * @param descrizione
         * @return 
         */
        string debugFrammentoLength(size_t inizio, size_t lunghezza, const string& descrizione)const;
        
        
    protected:
        string testo;
    };
}

#endif /* testo_h */

