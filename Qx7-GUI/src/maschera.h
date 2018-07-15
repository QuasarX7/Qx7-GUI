#ifndef maschera_h
#define maschera_h

#include <string>
using namespace std;

namespace GUI {
    class Maschera{
    public:
        Maschera(const string& stringaMaschera,char carattereOscurato):
        maschera{stringaMaschera},carattereInput{carattereOscurato}{}
        
        virtual ~Maschera(){}
        
        string stringa()const{return maschera;}
        char carattere()const{return carattereInput;}
        
    private:
        char carattereInput;
        string maschera;
        
    };
}

#endif /* maschera_h */
