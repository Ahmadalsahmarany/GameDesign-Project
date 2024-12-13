#include <iostream>
#include <string>
using namespace std;

class Karakter { // ana karakterin sinifi
protected:
    string isim;
    int can;
    int saldiriGucu;
    int savunmaGucu;

public:
    Karakter(string karakterIsim, int hp, int atk, int def) {
        isim = karakterIsim;
        can = hp;
        saldiriGucu = atk;
        savunmaGucu = def;
    }

    virtual void saldir(Karakter& target) { //saldiri metodu
        cout << isim << " " << target.isim << "'e saldiriyor"<< endl;
        target.hasarAl(saldiriGucu);
    }

    void hasarAl(int hasar) { // alinan hasarin metodu

        int gercekHasar = hasar - savunmaGucu;
        can -= gercekHasar;
        cout << isim << " " << gercekHasar << " hasar aldi"<< endl;
       
    }

    bool hayattaMi() {
        return can > 0;
    }

    string getIsim() {
        return isim;
    }

    int getCan() {
        return can;
    }
};
