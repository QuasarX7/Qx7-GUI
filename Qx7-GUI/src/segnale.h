#ifndef segnale_h
#define segnale_h

#include <functional>
#include <utility>
#include <map>
using namespace std;

namespace GUI{
    
    template <typename... InputMetodo>
    class Segnale
    {
    public:
        
        Segnale() : indice_corrente(0) {}
        
        
        Segnale(Segnale const& ) : indice_corrente(0) {}
        
        
        template <typename T>
        int connetti(T *oggetto, void (T::*metodo)(InputMetodo...)) {
            return connettiSlot([=](InputMetodo... args) {
                (oggetto->*metodo)(args...);
            });
        }
        
        
        template <typename T>
        int connetti(T *oggetto, void (T::*metodo)(InputMetodo...) const) {
            return connettiSlot([=](InputMetodo... args) {
                (oggetto->*metodo)(args...);
            });
        }
        
        
        
        void disconnetto(int id) const {
            slot.erase(id);
        }
        
        void disconnetti() const {
            slot.clear();
        }
        
        // calls all connected functions
        void emetti(InputMetodo... p) {
            for(auto it : slot) {
                it.second(p...);
            }
        }
        
        // assignment creates new Signal
        Segnale& operator=(Segnale const& ) {
            disconnetti();
        }
        
    private:
        
        int connettiSlot(function<void(InputMetodo... )> const& _slot) {
            slot[++indice_corrente] =  _slot;
            return indice_corrente;
        }
        
        
        mutable std::map<int, function<void(InputMetodo... )> > slot;
        mutable int indice_corrente;
        
    };

}

#endif /* segnale_h */
