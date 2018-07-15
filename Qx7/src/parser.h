/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7.                                          *
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
 * @file parser.h
 * @author Dr. Domenico della Peruta
 * @date 20/05/2013
 * @version 1.0.1, 03/04/2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Parser.
 * 
 * @namespace Utili
 * @class Parser
 */
#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <sstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

namespace Utili{
    
/**
 * La classe Parser effettua il parsing di un testo, cioè ne analiza in modo sequenziale 
 * il contenuto
 */
class Parser{
public:
    /**
     * Costruttore
     * 
     * @param linea stringa di caratteri stile C
     */
    Parser(const char* linea) : indice(0),errore_codice(0),eof(false) {
                dimensione=strlen(linea);
                buffer=new char[dimensione+1];
                strcpy(buffer,linea);
                carattere=leggeCarattere();
                saltaSpazio();
    }
    /**
     * Distruttore
     */
    virtual ~Parser(){delete [] buffer;}
    /**
     * Carattere del testo sottoanalisi.
     * @return 
     */
    char carattereAttuale() const { return carattere; }
    /**
     * Controlla fine analisi del testo
     * @return true il testo è finito
     */
    inline bool fine();
    /**
     * Legge un carattere.
     * @return 
     */
    inline char leggeCarattere();

    /**
     * Estrae un nome di una variabile dal testo, Es.: "casa", "k12", "a0".
     * Per variabile si intente una stringa che non inizia con una cifra. 
     * @return 
     */
    inline string estraeNomeVariabile();
    /**
     * Estrae un numero naturale senza segno.
     * 
     * @return 
     */
    inline string estraeNumeroNaturale();
    /**
     * Estrae un numero in virgola mobile senza segno.
     * @return 
     */
    inline string estraeNumeroDecimalePositivo(); 
    /**
     * Estrae un numero intero.
     * @return 
     */
    inline string estraeNumeroIntero();
    /**
     * Estrae un numero in virgola mobile.
     * @return 
     */
    inline string estraeNumeroDecimale();

    /**
     * Ritorna true se il carattere attuale e' + o -
     * 
     * @param c
     * @return 
     */
    inline static bool eUnSegno(const char c);  
    /**
     * Ritorna true se e' una lettera o un numero.
     * @param c
     * @return 
     */
    inline static bool eUnaLetteraOUnNumero(const char c);
    /**
     * Restituisce true se il carattere e' spazio o tab
     * @param c
     * @return 
     */
    inline static bool eUnoSpazio(const char c);             
    /**
     * Restituisce true se legge esattamente string 's'
     * @param s
     * @return 
     */
    inline bool eLaStringa(const string& s) const;
    /**
     * Verifica se il prossimo carattere è una cifra.
     * @return 
     */
    inline bool laProssimaEUnaCifra() const;
    /**
     * Salta un carattere
     * @param salta_spazio  se true non valuta la presenza degli spazi vuoti e valuta il 
     *                      carattere successivo
     */
    inline void saltaCarattere(bool salta_spazio); 
    /**
     * Salta spazi e tab fino al primo carattere da leggere
     */
    inline void saltaSpazio();
    /**
     * Verifica che il prossimo char sia 'c' altrimenti genera un errore, 
     * se la verifica va a buon fine va avanti col parsing.
     * @param c
     */
    inline void verificaSuccessivo(char c); 
    /**
     * verifica che la prossima stringa sia 'c'
     * @param s
     */
    inline void verificaSuccessivo(string s);

    /**
     * Descrive il verificarsi di un errore.
     * @param s
     */
    void errore(string s) {
        sollevaErrore("Errore parser causato da: "+ s);
    }
    /**
     * Accede al tipo di errore;
     * @return 
     */
    int errore() const { return errore_codice; }

    /**
     * Converte una stringa in un tipo diverso
     * @param strValue
     * @return 
     */
    template<typename T>
    inline static T converti(const string& strValue);
        // converte una stringa in un float
    /**
     * Converte una stringa numerica in un valore in virgola mobile semplice.
     * @param 
     * @return 
     */  
    inline static float convertiInFloat(const string&);
    /**
     * Converte una stringa numerica in un valore in virgola mobile a doppia precisione.
     * @param 
     * @return 
     */  
    inline static double convertiInDouble(const string&);

private:
    char*   buffer;
    unsigned int indice,dimensione;
    int     errore_codice;
    string  info_errore;
    char    carattere;
    bool    eof;

    /**
     * Solleva un errore.
     * @param s
     */
    void sollevaErrore(string s) {
        errore_info(s);
        errore_codice = -1;
    }
    /**
     * Segnala un errore.
     * @param s
     */
    void errore_info(string s) {
            //std::cout << "error : " << s << std::endl;
            info_errore=s;
    }


};


                    /* IMPLEMENTAZIONE */

inline bool Parser::fine(){
        return eof;
}

inline char Parser::leggeCarattere(){
        char c;
        if ((c=buffer[indice])!=0) {
                ++indice;
                carattere=c;
                return c;
        } else {
                eof=true;
                return static_cast<char>(0);
        }
}

inline bool Parser::eUnoSpazio(const char c){
        return ((c==' ' || c=='\t' || c=='\n') ? true:false);
}

inline void Parser::saltaSpazio(){
        while (eUnoSpazio(carattere)) carattere=leggeCarattere();
}
inline void Parser::saltaCarattere(bool salta_spazio){
        carattere=leggeCarattere();
        if (salta_spazio) saltaSpazio();
}


inline void Parser::verificaSuccessivo(const char c){
        string spazio("  ");
        if (carattere!=c) errore(spazio+c+spazio);
        else {
            carattere=leggeCarattere();
            saltaSpazio();
        }
}

inline void Parser::verificaSuccessivo(string s){
    string spazio(" ");
    string::iterator p;
    for (p=s.begin();p!=s.end() && !errore_codice;p++){
        if (carattere != *p) {
            errore(spazio + s + spazio);
        }else{
            carattere=leggeCarattere();
        }
    }
    saltaSpazio();
}


inline bool Parser::eUnaLetteraOUnNumero(const char c){
    return std::isalpha(c) || std::isdigit(c);
}

inline bool Parser::eUnSegno(const char c){
    if (c=='+' || c=='-') return true; else return false;
}

inline bool Parser::eLaStringa(const string& s) const{
    if (eof) return false;
    unsigned int p=indice-1;
    string::const_iterator i;
    bool res=true;
    for (i=s.begin();i != s.end() && res;++i)
        if (buffer[p++]!=*i) res=false;
    return res;
}

inline bool Parser::laProssimaEUnaCifra() const{
        unsigned int p=indice-1;
        char c;
        while ((c=buffer[p++])!=0)
        {
                if (eUnoSpazio(c) || eUnSegno(c)) continue;
                if (c>='0' && c<='9') return true;else return false;
        }
        return false;
}

inline string Parser::estraeNomeVariabile(){
        std::string token("");
        if (!std::isalpha(carattere)) errore("Nome variabile");
        if (errore_codice) return token;
        while (eUnaLetteraOUnNumero(carattere)){
                token+=std::toupper(carattere);
                carattere=leggeCarattere();
        }
        saltaSpazio();
        return token;
}


inline string Parser::estraeNumeroNaturale(){
        string value("");
        if (!std::isdigit(carattere)) errore("Integer");
        if (errore_codice) return value;
        while (std::isdigit(carattere)) {
                value+=carattere;
                carattere=leggeCarattere();
        }
        saltaSpazio();
        return value;
}

inline string Parser::estraeNumeroIntero(){
        string value("");
        char s=carattere;
        if (eUnSegno(s)) {
                value+=s;
                verificaSuccessivo(s);
        }
        value+=estraeNumeroNaturale();
        return value;
}

inline std::string Parser::estraeNumeroDecimalePositivo(){
        std::string value("");
        if (!std::isdigit(carattere) && carattere!='.') errore("Float");
        if (errore_codice) return value;
        while (std::isdigit(carattere)) {
                value+=carattere;
                carattere=leggeCarattere();
        }
        if (carattere=='.') {
                verificaSuccessivo('.');
                value+='.';
                if (!std::isdigit(carattere)) errore("Float");
                if (errore_codice) return value;
                while (std::isdigit(carattere)) {
                        value+=carattere;
                        carattere=leggeCarattere();
                }
        }
        saltaSpazio();
        if (carattere=='e' || carattere=='E') {
                carattere='E';
                verificaSuccessivo('E');
                value+='E';
                if (eUnSegno(carattere)) {
                        value+=carattere;
                        saltaCarattere(true);
                } else value+='+';
                value+=estraeNumeroIntero();
        }
        return value;
}

inline std::string Parser::estraeNumeroDecimale(){
        std::string value("");
        char s=carattere;
        if (eUnSegno(s)) {
                value+=s;
                verificaSuccessivo(s);
        }
        value+=estraeNumeroDecimalePositivo();
        return value;
}

inline float Parser::convertiInFloat(const string& str_val){
        return atof(str_val.c_str());
}

inline double Parser::convertiInDouble(const string& str_val){
        return static_cast<double>(atof(str_val.c_str()));
}

template<typename T>
inline T Parser::converti(const string& strValue){
        T ret_val;
        istringstream os(strValue);
        os >> ret_val;
        return ret_val;
}


}; // fine namespace Utili

#endif
