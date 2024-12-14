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
    Karakter() {
        isim = "";
        can = 0;
        saldiriGucu = 0;
        savunmaGucu = 0;
    }

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

class Oyuncu : public Karakter { // oyuncu icin bir sinif
private:
    int iksirSayisi;

public:
    Oyuncu(string oyuncuIsim, int hp, int atk, int def, int iksirAdet) {
        isim = oyuncuIsim;
        can = hp;
        saldiriGucu = atk;
        savunmaGucu = def;
        iksirSayisi = iksirAdet;
    }

    void iksirKullan() {
        if (iksirSayisi > 0) {
            can += 30;
            iksirSayisi--;
            cout << isim << " 30lik bir eksir kullanildi " << endl;
        }
        else {
            cout << isim << "'in iksiri kalmadi"<< endl;
        }
    }
};

