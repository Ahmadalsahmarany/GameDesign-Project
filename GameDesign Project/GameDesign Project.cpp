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

void gosterCanBar(string isim, int mevcutCan, int maksimumCan) {
    int barUzunlugu = 20; // Sağlık barının genişliği
    int doluUzunluk = (mevcutCan * barUzunlugu) / maksimumCan;

    cout << isim << " [";
    for (int i = 0; i < doluUzunluk; i++) cout << "#"; // Dolu kısmı
    for (int i = doluUzunluk; i < barUzunlugu; i++) cout << " "; // Boş kısmı
    cout << "] " << mevcutCan << "/" << maksimumCan << endl;
}

void baslangicEkrani() {
    cout << "==============================" << endl;
    cout << "   SIRA TABANLI SAVAS OYUNU   " << endl;
    cout << "==============================" << endl;
    cout << "Zorluk seviyesini secin (1 = Kolay, 2 = Orta, 3 = Zor): ";
}


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
    baslangicEkrani(); // Başlangıç ekranı göster

    int zorluk;
    cin >> zorluk;
    cout << endl;

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
    cout << endl;
    dusmanlar[1] = new Ejder();
    cout << endl;
    dusmanlar[2] = new Titan();
    cout << endl;



    cout << "Savas Basliyor " << endl;

    int mevcutDusman = 0;

    while (oyuncu.hayattaMi() && mevcutDusman < 3) {
        cout << endl;
        gosterCanBar(oyuncu.getIsim(), oyuncu.getCan(), oyuncuCan);
        gosterCanBar(dusmanlar[mevcutDusman]->getIsim(), dusmanlar[mevcutDusman]->getCan(),100);
        cout << endl;

        // Oyuncunun Sırası
        cout << "Islev sec 1) Saldir 2) Iksir Kullan: ";
        int secim;
        cin >> secim;
        cout << endl;

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

    for (int i = 0; i < 3; i++) {
        delete dusmanlar[i];
    }

    return 0;
}

