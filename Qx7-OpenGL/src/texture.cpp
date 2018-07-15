/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7-OpenGL.                                       *
 *                                                                          *
 * Qx7-OpenGL è una libreria software gratuita: puoi ridistribuirla e/o     *
 * modificarla sotto i termini della GNU Lesser General Public License come *
 * pubblicato  dalla Free Software Foundation, o la versione 3 della licenza,
 *  o (a tua scelta) qualsiasi versione successiva.                         *
 *                                                                          *
 * Qx7-OpenGL è distribuita nella speranza che sia utile,                   *
 * ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di         *
 * COMMERCIABILITÀ O IDONEITÀ PER UN PARTICOLARE SCOPO. Vedi il             *
 * GNU Lesser General Public License per maggiori dettagli.                 *
 *                                                                          *
 * Dovresti aver ricevuto una copia di GNU Lesser General Public            *
 * Licenza insieme a Qx7-OpenGL. Altrimenti, vedi al sito                   *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7-OpenGL.                                         *
 *                                                                          *
 *   Qx7-OpenGL is free software: you can redistribute it and/or modify it  *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Qx7-OpenGL is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Qx7-OpenGL.  If not, see                            *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/

#include "texture.h"
using namespace Grafica;

Texture::Texture(const string& file){
    if(file.find(".bmp") != string::npos || file.find(".BMP") != string::npos){
        caricaImmagineBitMap(file);
    }else{
        stringstream ss;
        ss << "Errore Texture::Texture(...): file \"" << file << "\" non è un immagine."<<endl;
        throw runtime_error{ss.str()};
    }
}

Texture::~Texture(){
    if(dati != nullptr)
        delete[] dati;
    
}

void Texture::caricaImmagineBitMap(const string &nomeFile){
    ifstream file(nomeFile.c_str());
    if (!file.is_open()){
        stringstream ss;
        ss << "Errore Texture::caricaImmagineBitMap(...): file \"" << nomeFile << "\" non aperto."<<endl;
        throw runtime_error{ss.str()};
    }
    
    const size_t DIM_HEADER = 54;
    char header[DIM_HEADER];
    file.seekg(0, ios::beg);
    file.read(header, DIM_HEADER);
    
    if ( header[0] != 'B' || header[1] != 'M' ){
        stringstream ss;
        ss << "Errore Texture::caricaImmagineBitMap(...): file \"" << nomeFile << "\" non di è tipo bitmap (.bmp)."<<endl;
        throw logic_error{ss.str()};
    }
    
    unsigned int posizioneDati     = *reinterpret_cast<int*>(&header[0x0A]);
    unsigned int dimDatiImmagine   = *reinterpret_cast<int*>(&header[0x22]);
    lunghezzaImmagine = *reinterpret_cast<int*>(&header[0x12]);
    altezzaImmagine   = *reinterpret_cast<int*>(&header[0x16]);
    
    if (dimDatiImmagine == 0)
        dimDatiImmagine = lunghezzaImmagine * altezzaImmagine * 3;
    
    if (posizioneDati == 0)
        posizioneDati = DIM_HEADER;
    
    if(dati != nullptr)
        delete[] dati;
    
    dati = new char[dimDatiImmagine];
    file.seekg(posizioneDati, ios::beg);
    file.read(dati, dimDatiImmagine);
    
    file.close();
    
}


void Texture::applicaImmagine(){
    glGenTextures(1, &textureID);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lunghezzaImmagine, altezzaImmagine, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, dati);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    delete[] dati;
    dati=nullptr;
}
