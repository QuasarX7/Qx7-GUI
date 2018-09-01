/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7-GUI.                                          *
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
 * Licenza insieme a Qx7-GUI. Altrimenti, vedi al sito                      *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7-GUI.                                            *
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
 *   License along with Qx7-GUI.  If not, see                               *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/

/**
 * @file testo.cpp
 * @author Dr. Domenico della Peruta
 * @date 16-12-2017
 * @version 1.0.2, 28-08-2018
 * @brief File contenente l'implementazione della classe Testo.
 *
 * 
 * @namespace Utili
 * @class Testo
 */

#include "testo.h"
using namespace Utili;



Testo::Testo(const string& utf8): testo{utf8}{
    
}

string Testo::latino1()const{
    string out="";
    string ISO_8859_1[]={ // stringhe UTF8 corrispondenti
        "¡","¢","£","¤","¥","¦","§","¨","©","ª","«","¬","\u00AD","®","¯",
        "°","±","²","³","´","µ","¶","·","¸","¹","º","»","¼","½","¾","¿",
        "À","Á","Â","Ã","Ä","Å","Æ","Ç","È","É","Ê","Ë","Ì","Í","Î","Ï",
        "Ð","Ñ","Ò","Ó","Ô","Õ","Ö","×","Ø","Ù","Ú","Û","Ü","Ý","Þ","ß",
        "à","á","â","ã","ä","å","æ","ç","è","é","ê","ë","ì","í","î","ï",
        "ð","ñ","ò","ó","ô","õ","ö","÷","ø","ù","ú","û","ü","ý","þ","ÿ"
    };
    
    for(int indice=0,numeroByte=1; indice < testo.size(); indice += numeroByte){
        u_char byte = testo.at(indice);
        numeroByte = lunghezzaCarattereUTF8(byte);
        if(numeroByte < 0){
            stringstream ss;
            ss << "codifica non UTF8." << endl;
            ss << " - metodo : Testo::latino1()" << endl;
            ss << " - testo  : «"<< testo << "»"<<endl;
            ss << " * indice : " << indice <<endl;
            ss << " * byte   : 0x"<< hex << byte <<endl;
            throw logic_error{ss.str()};
            
        }else if(numeroByte == 1){
            //if((byte >= 33 && byte <= 126) || byte == '\r')
            out += static_cast<char>(byte);
        }else{
            string carattereUTF8 = testo.substr(indice,numeroByte);
            for(int i = 161; i < 256; i++)// "¡" = 161 e "ÿ" = 255
                if(carattereUTF8 == ISO_8859_1[ i-161 ]){//217
                    out += i;
                }
        }
    }
    return out;
    
}


int Testo::lunghezzaCarattereUTF8( unsigned char byte )const{
    //     CODIFICA UTF8                          byte analizzato    byte successivi
    //      |                 |
    //      V                 V
    if ( (byte >> 7) == 0 ) return 1;             // 0xxxxxxx
    else if ( ( byte >> 6 ) == 0b10 ) return 0;   // ...?...    10xxxxxx
    else if ( ( byte >> 5 ) == 0b110 ) return 2;  // 110xxxxx [ 10xxxxxx ]
    else if ( ( byte >> 4 ) == 0b1110 ) return 3; // 1110xxxx [ 10xxxxxx 10xxxxxx ]
    else if ( ( byte >> 3 ) == 0b11110 ) return 4;// 11110xxx [ 10xxxxxx 10xxxxxx 10xxxxxx ]
    
    return -1; // CODIFICA DIVERSA DA UTF8
}

int Testo::byteCarattere(size_t indice,Unità tipo)const{
    if(tipo == Unità::PAROLA){
        stringstream ss;
        ss << "tipo di Indice non previsto (Indice::PAROLA)." << endl;
        ss << " - metodo : Testo::byteCarattere(..)" << endl;
        throw logic_error{ss.str()};
    }
      
    if(indice < testo.size()){
        if(tipo == Unità::BYTE)
            return lunghezzaCarattereUTF8(testo[indice]);
        else if(tipo == Unità::CARATTERE){//indice carattere
            return carattere(indice).byteCarattere(0);
        }
    }
    return -1;
    
}

Testo Testo::frammento(size_t inizio, size_t lunghezza, Unità tipo)const{
    if(lunghezza == 0){
        throw length_error{
            debugFrammentoLength(inizio,lunghezza,"lunghezza nulla.")
        };
    }
    
    if( ( ((long double)inizio) + ((long double)lunghezza) ) >=  std::numeric_limits<size_t>::max())
        throw out_of_range{
            debugFrammentoLength(inizio,lunghezza,"lunghezza frammento superiore a SIZE_T_MAX.")
        };
     
    Testo str{""};
    if(((inizio + lunghezza) <= lunghezzaTesto(tipo)) ){
        if(tipo == Unità::CARATTERE){
            for (size_t i=0; i < numeroCaratteri(); i++) {
                if(i >= inizio && i < (inizio + lunghezza))
                    str += carattere(i);
            }
        }else if(tipo == Unità::BYTE){
            str = testo.substr(inizio,lunghezza);
        
        }else{// tipo == Unità::PAROLA
            auto elenco = scomposizione(true);
            size_t i=0;
            for(auto parola : elenco){
                if(i >= inizio && i < (inizio + lunghezza)){
                    if(i == inizio && separatore(parola)){
                        //  non aggiungi niente
                    }else
                        str += parola;
                }else if(i >= inizio && i >= (inizio + lunghezza)){
                    break;
                }
                if(!separatore(parola)){
                    i++;
                }
                
            }
        } 
    }else{
        throw out_of_range{
           debugFrammentoRange(inizio,lunghezza,tipo)
        };
    }
    return str;
}


string Testo::stampa(Unità tipo){
    if(tipo == Unità::BYTE)
        return "Unità::BYTE";
    else if(tipo == Unità::CARATTERE)
        return "Unità::CARATTERE";
    else
        return "Unità::PAROLA";
}

string Testo::debugFrammentoRange(size_t inizio, size_t lunghezza, Unità tipo)const{
    stringstream ss;
    ss << "indice testo fuori intervallo." << endl;
    ss << " - metodo : Testo::frammento(..)" << endl;
    ss << " - testo: \n«"<< testo << "»"<<endl;
    ss << " + inizio: "<< inizio <<endl;
    ss << " + lunghezza: "<< lunghezza <<endl;
    ss << " + tipo:   " << stampa(tipo) << endl;
    return ss.str();
}

string Testo::debugFrammentoLength(size_t inizio, size_t lunghezza, const string& descrizione)const{
    stringstream ss;
    ss << descrizione << endl;
    ss << " - metodo : Testo::frammento(..)" << endl;
    ss << " - testo: \n«"<< testo << "»"<<endl;
    ss << " + inizio: "<< inizio <<endl;
    ss << " + lunghezza: "<< lunghezza <<endl;
    return ss.str();
}


        
size_t Testo::lunghezzaTesto(Unità tipo)const{
    if(tipo == Unità::BYTE)
        return numeroByte();
    else if(tipo == Unità::CARATTERE)
        return numeroCaratteri();
    else
        return numeroParole();
}

Testo Testo::carattere(size_t idCarattere)const{
    Testo carattere{""};
    if(idCarattere < numeroCaratteri()){
        for (size_t i=0; i < numeroByte(); i++) {
            size_t indice = indiceCarattere(i);
            if(indice == idCarattere){
                carattere += testo.substr(i,byteCarattere(i));
                break;
            }
        }
    }else{
        stringstream ss;
        ss << "indice carattere (UFT8) fuori intervallo." << endl;
        ss << " - metodo : Testo::carattere(..)" << endl;
        ss << " - testo: \n«"<< testo << "»"<<endl;
        ss << " + idCarattere: "<< idCarattere <<endl;
        
        throw out_of_range{ss.str()};
    }
    return carattere;
}


void Testo::aggiungi(const Testo& stringa, size_t indice, Unità tipo){
    if(indice <= lunghezzaTesto(tipo)){
        const string spazio = " ";
        string inizio = "";
        if(indice > 0){
            inizio = frammento(0, indice,tipo).stringa();
            if(tipo == Unità::PAROLA && !separatore(inizio[inizio.size()-1]) )
                inizio += spazio;
        }
        string fine = "";
        if(indice < lunghezzaTesto(tipo)){
            fine = frammento(indice, tipo).stringa();
            if(tipo == Unità::PAROLA && !separatore(fine[0]) )
                fine = spazio + fine;
        }
        testo = inizio + stringa.stringa() + fine;
        
    }else{
        stringstream ss;
        ss << "indice testo fuori intervallo." << endl;
        ss << " - metodo : Testo::aggiungi(..)" << endl;
        ss << " - testo  : \n«"<< testo << "»"<<endl;
        ss << " + indiceCarattere: "<< indice <<endl;
        ss << " + stringa: «"<< stringa.stringa()<< "»" <<endl;
        ss << " + tipo:   " << stampa(tipo) << endl;
        throw out_of_range{ss.str()};
    }
}

size_t Testo::indiceCarattere(size_t indiceByte)const{
    size_t indice =0;
    stringstream ss;
    if(testo.size() > 0){
        if(indiceByte >= testo.size()){
            ss << "indice testo fuori intervallo." << endl;
            ss << " - metodo : Testo::indiceCarattere(..)" << endl;
            ss << " - testo  : \n«"<< testo << "»"<<endl;
            ss << " + indiceByte: "<< indiceByte <<endl;
            throw out_of_range{ss.str()};
        }
        for(size_t i=0; i <= indiceByte; i++){
            int len = byteCarattere(i);
            if(len < 0){
                ss << "carattere con codifica non UTF8." << endl;
                ss << " - metodo : Testo::indiceCarattere(..)" << endl;
                ss << " - testo  : \n«"<< testo << "»"<<endl;
                ss << " + indiceByte: "<< indiceByte <<endl;
                ss << " * i (indice errore): "<< i <<endl;
                throw logic_error{ss.str()};
            }else if(len > 0)
                indice++;
        }
        if(indice == 0){
            ss << "carattere con codifica non UTF8." << endl;
            ss << " - metodo : Testo::indiceCarattere(..)" << endl;
            ss << " - testo  : \n«"<< testo << "»"<<endl;
            ss << " + indiceByte: "<< indiceByte <<endl;
            throw logic_error{ss.str()};
        }
        return indice-1;
    }
    ss << "lungnezza testo nullo." << endl;
    ss << " - metodo : Testo::indiceCarattere(..)" << endl;
    ss << " - testo  : \n«"<< testo << "»"<<endl;
    ss << " + indiceByte: "<< indiceByte <<endl;
    throw length_error{ss.str()};
}

size_t Testo::numeroCaratteri()const{
    if(testo.size() > 0)
        return indiceCarattere(testo.size()-1)+1;
    return 0;
}

Testo Testo::incolonna(size_t numeroCaratteri, Unità tipo)const{
    Testo s{""};
    if(numeroCaratteri > 0){
        if(tipo != Unità::PAROLA){
            size_t lunMax = lunghezzaTesto(tipo);
            for(size_t i=0; i < lunMax; i++){
                if((i % numeroCaratteri == 0) && i > 0)
                    s+="\r\n";
                s += vedi(i,tipo);
            }
        }else{
            auto elenco = scomposizione(true);
            size_t p=0;
            for(Testo elemento : elenco){
                size_t lungParola = elemento.numeroCaratteri();
                if(lungParola <= numeroCaratteri){
                    if(elemento == '\n' || elemento == '\r')
                        p = 0;
                    else
                        p += lungParola;
                    if(p > numeroCaratteri){
                        s+="\r\n";
                        p = lungParola;
                    } 
                    s += elemento;
                }else/*if(lungParola > numeroCaratteri)*/{
                    Testo correzione = elemento.incolonna(numeroCaratteri,Unità::CARATTERE);
                    s += "\r\n" + correzione;
                    //lunghezza ultima riga
                    p = correzione.ultimaRiga().numeroCaratteri();
                }

            }
        }
    }else{
        stringstream ss;
        ss << "lungnezza blocco nullo." << endl;
        ss << " - metodo : Testo::incolonna(..)" << endl;
        ss << " - testo  : \n«"<< testo << "»"<<endl;
        ss << " + numeroCaratteri: "<< numeroCaratteri <<endl;
        ss << " + tipo:   " << stampa(tipo) << endl;
        throw length_error{ss.str()};
    }
    return s;
}

vector<Testo> Testo::righe()const{
    vector<Testo> lista;
    auto elenco = scomposizione(true);
    Testo riga{""};
    auto parola = elenco.begin();
    for(; parola != elenco.end(); ++parola){
        if(*parola == '\n' || *parola == '\r'){
            if(riga.numeroByte() > 0)
                lista.push_back(riga);
            riga = "";
        }else{
            riga += *parola;
        }
    }
    if(riga.numeroByte() > 0)
        lista.push_back(riga);
    return lista;
}




vector<size_t> Testo::trova(const Testo& elemento, Unità tipo)const{
    if(elemento.numeroByte() == 0){
        stringstream ss;
        ss << "lungnezza elemento nullo." << endl;
        ss << " - metodo : Testo::trova(..)" << endl;
        ss << " - testo  : \n«"<< testo << "»"<<endl;
        ss << " + tipo:   " << stampa(tipo) << endl;
        throw length_error{ss.str()};
    }
    vector<size_t> indici;
    
    if(tipo == Unità::BYTE){
        size_t limiteByte = numeroByte();
        size_t lungElemento = elemento.numeroByte();
        for(size_t i=0; i < limiteByte; i++){
            size_t j;
            for(j=0; j < lungElemento; j++){
                if(byte(i+j) != elemento.byte(j))
                    break;
            }
            if(j == lungElemento)
                indici.push_back(i);
        }
        
    }else if(tipo == Unità::CARATTERE){
        size_t limiteCaratteri = numeroCaratteri();
        size_t lungElemento = elemento.numeroCaratteri();
        for(size_t i=0; i < limiteCaratteri; i++){
            size_t j;
            for(j=0; j < lungElemento; j++){
                if(carattere(i+j) != elemento.carattere(j))
                    break;
            }
            if(j == lungElemento)
                indici.push_back(i);
        }
        
    }else{ //if(tipo == Unità::PAROLA)
        auto elenco = scomposizione();
        auto confronto = elemento.scomposizione();
        size_t liminteParole =  elenco.size();
        size_t lungElemento = confronto.size();
        for(size_t i=0; i < liminteParole; i++){
            size_t j;
            for(j=0; j < lungElemento; j++){
                if(elenco.at(i+j) != confronto.at(j))
                    break;
            }
            if(j == lungElemento)
                indici.push_back(i);
        }
    }
    return indici;
}
        


vector<Testo> Testo::scomposizione(bool conSeparatori)const{
    vector<Testo> lista;
    Testo s{""};
    for(size_t i=0; i <= numeroByte(); i++){
        if(!separatore(testo[i]))
            s += testo[i];
        else{
            if(s.numeroByte() > 0){
                lista.push_back(s);
            }
            if(conSeparatori){
                if(testo[i] != '\0')
                    lista.push_back(testo[i]);//separatore (tranne '\0')
                else
                    break;
            }
            s = "";
        }
    }
    return lista;
}

Testo Testo::parola(size_t idParola)const{
    auto elenco = scomposizione();
    size_t i=0;
    for(auto p : elenco){
        if(i++ == idParola)
            return p;
    }
    stringstream ss;
    ss << "indice parole fuori intervallo." << endl;
    ss << " - metodo : Testo::parola(..)" << endl;
    ss << " - testo  : \n«"<< testo << "»"<<endl;
    ss << " + idParola: "<< idParola <<endl;
    throw out_of_range{ss.str()};
    
}
        



void Testo::debug()const{
    cout << "+++ Debug: ++++++++" << endl;
    cout << "[*] byte:"<< endl;
    for(size_t i=0; i < numeroByte(); i++)
        cout << i << ") 0x"<< hex << static_cast<short>(byte(i)) << dec << "\t'"<<  byte(i) << "'"<< endl;
    cout << "[*] caratteri:"<< endl;
    for(size_t i=0; i < numeroCaratteri(); i++)
        cout << i << ") '"<< carattere(i).stringa() << "'\t"<<  carattere(i).numeroByte() << " byte"<< endl;
    cout << "[*] parole:"<< endl;
    auto elenco = scomposizione(/*true*/);
    for(size_t i=0; i < elenco.size() ; i++)
        cout << i << ") '"<< elenco.at(i).stringa() << "'"<< endl;
    cout << "-------------------" << endl;
}


Testo Testo::vedi(size_t indice, Unità tipo)const{
    if(tipo == Unità::BYTE)
        return Testo{static_cast<char>(byte(indice))};
    else if(tipo == Unità::PAROLA)
        return parola(indice);
    else // if(tipo == Unità::CARATTERE)
        return carattere(indice);
}


size_t Testo::elimina(size_t indice, Unità tipo){
    size_t prima = testo.size();
    if(indice < lunghezzaTesto(tipo)){
        Testo inizio{""};
        if(indice > 0){
            inizio = frammento(0, indice,tipo);
        }
        Testo fine{""};
        if(indice+1 < lunghezzaTesto(tipo)){
            fine = frammento(indice+1,tipo);
            if(indice > 0 && tipo == Unità::PAROLA && !separatore(fine.stringa()[0]) )
                fine = " " + fine;
        }
        *this = inizio + fine;
    }else{
        stringstream ss;
        ss << "indice testo fuori intervallo." << endl;
        ss << " - metodo : Testo::elimina(..)" << endl;
        ss << " - testo  : \n«"<< testo << "»"<<endl;
        ss << " + indice: "<< indice <<endl;
        ss << " + tipo:   " << stampa(tipo) << endl;
        throw out_of_range{ss.str()};
    }
    return prima - testo.size();
}
        
