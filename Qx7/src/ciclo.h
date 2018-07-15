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
 * @file ciclo.h
 * @author Dr. Domenico della Peruta
 * @date 05-01-2018
 * @version 2.0.0, 17-03-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Ciclo.
 * 
 * @namespace Utili
 * @class Ciclo
 */
#ifndef ciclo_h
#define ciclo_h

#include <thread>
#include <chrono>
using namespace std;

namespace Utili {
    
            
    typedef std::chrono::milliseconds Tempo;
    typedef std::chrono::seconds Vita;
    typedef std::function<void(void)> Funzione;
    
    
    
    /**
     * Costante di riferimento STANDARD, per l'aggiornamento delle finestre e delle 
     * "azioni" di movimento 
     * @see <code>void Figura::anima(const vector<Azione*>& azioni)</code>
     */
    const Tempo INTERVALLO_DI_AGGIORNAMENTO_GRAFICO = 100ms;
    
 
    /**
     * Classe che permette di avviare o fermare l'esecuzione ciclica di un funzione.
     */
    class Ciclo{
    public:
        /**
         * Costruttore
         * @param attività      Funzione associata all'attività periodica
         * @param periodo       durata di un periodo in millisecondi
         */
        Ciclo(const Funzione& attività, const Tempo& periodo)
        :azione{attività},durataPeriodo{periodo},durataCiclo{0s}{}
        /**
         * Avvia attività ciclica.
         * 
         * @param limite        eventuale limite temporale del ciclo in secondi
         */
        void avvia(const Vita& limite = 0s)
        {
            avvio = true;
            
            attivitàPeriodica = thread([=](){
                while (avvio == true) {
                    this_thread::sleep_for(durataPeriodo);
                    azione();
                }
            });
            cronometro = thread([=](){
                while(avvio){
                    this_thread::sleep_for(1s);
                    durataCiclo++;
                    if(limite > 0s)
                        if(durataCiclo > limite)
                            break;
                }
                avvio = false;
            });
            attivitàPeriodica.join();
            cronometro.join();
        }
        /**
         * Ferma l'attività ciclica.
         */
        void ferma(){
            avvio = false;
        }
       
        /**
         * Durata del ciclo in secondi.
         * 
         * @return 
         */
        Vita vita()const{return durataCiclo;};
        
    private:
        thread attivitàPeriodica,cronometro;
        bool avvio = false;
        Funzione azione;
        
        Tempo durataPeriodo;
        Vita durataCiclo;
        
    };
}

#endif /* ciclo_h */
