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

class Goblin : public Karakter {
public:
    Goblin() {
        isim = "Goblin";
        can = 30;
        saldiriGucu = 10;
        savunmaGucu = 2;
        cout << "Bir Goblin ortaya cikti"<<endl;
    }

    void saldir(Karakter& hedef) override {
        cout << isim << " " << hedef.getIsim() << "'e saldiriyor" << endl;
        hedef.hasarAl(saldiriGucu);
    }
};

class Ejder : public Karakter {
public:
    Ejder() {
        isim = "Ejder";
        can = 60;
        saldiriGucu = 15;
        savunmaGucu = 5;
        cout << "Bir Ejder ortaya cikti" << endl;
    }

    void saldir(Karakter& hedef) override {
        cout << isim << " " << hedef.getIsim() << "'e saldiriyor" << endl;
        hedef.hasarAl(saldiriGucu);
    }
};

class Titan : public Karakter {
public:
    Titan() {
        isim = "Titan";
        can = 80;
        saldiriGucu = 20;
        savunmaGucu = 10;
        cout << "bir Titan ortaya cikti" << endl;
    }

    void saldir(Karakter& hedef) override {
        cout << isim << " " << hedef.getIsim() << "'e saldiriyor" << endl;
        hedef.hasarAl(saldiriGucu);
    }
};
int main() {

    int zorluk;
    cout << "Zorluk secin (1 = Kolay, 2 = Orta, 3 = Zor): ";
    cin >> zorluk;

    int oyuncuCan;
    if (zorluk == 1) {
        oyuncuCan = 120;
    }
    else if (zorluk == 2) {
        oyuncuCan = 100;
    }
    else {
        oyuncuCan = 80;
    }

    Oyuncu oyuncu("Kahraman Ahmet", oyuncuCan, 15, 5, 3);

    // Düşman Tipleri
    Karakter* dusmanlar[3];
    dusmanlar[0] = new Goblin();
    dusmanlar[1] = new Ejder();
    dusmanlar[2] = new Titan();

    cout << "Savas Basliyor " << endl;

    int mevcutDusman = 0;

    while (oyuncu.hayattaMi() && mevcutDusman < 3) {
        cout << endl << "Oyuncu Can: " << oyuncu.getCan() << endl;
        cout << dusmanlar[mevcutDusman]->getIsim() << " Can: " << dusmanlar[mevcutDusman]->getCan() << endl;

        // Oyuncunun Sırası
        cout << "Islev sec 1) Saldir 2) İksir Kullan: ";
        int secim;
        cin >> secim;

        if (secim == 1) {
            oyuncu.saldir(*dusmanlar[mevcutDusman]);
        }
        else if (secim == 2) {
            oyuncu.iksirKullan();
        }
        else {
            cout << "Gecersiz. Tekrar deneyin" << endl;
            continue;
        }

        if (!dusmanlar[mevcutDusman]->hayattaMi()) {
            cout << dusmanlar[mevcutDusman]->getIsim() << " yenildi!\n";
            mevcutDusman++;

            if (mevcutDusman < 3) {
                cout << "Yeni bir car savasa katildi" << endl;
            }

            continue;
        }

        dusmanlar[mevcutDusman]->saldir(oyuncu);

        if (!oyuncu.hayattaMi()) {
            cout << "Maalesef kaybettiniz. " << endl;
            break;
        }
    }

    if (oyuncu.hayattaMi()) {
        cout << "Tebrikler, Kazandiniz" << endl;
    }

    for (int i = 0; i < 3; i++) {
        delete dusmanlar[i];
    }

    return 0;
}



