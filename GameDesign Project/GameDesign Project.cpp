#include <iostream>
#include <string>
using namespace std;

class Karakter { // ana karakterin sinifi
protected:
    string isim; // Karakterin ismi
    int can; // Karakterin sağlık puanı
    int saldiriGucu; // Karakterin saldırı gücü
    int savunmaGucu; // Karakterin savunma gücü

public:
    Karakter() { // Varsayılan yapıcı (default constructor)
        isim = "";
        can = 0;
        saldiriGucu = 0;
        savunmaGucu = 0;
    }

    Karakter(string karakterIsim, int hp, int atk, int def) { // Parametreli yapıcı (constructor)
        isim = karakterIsim;
        can = hp;
        saldiriGucu = atk;
        savunmaGucu = def;
    }

    virtual void saldir(Karakter& target) { // Karakterin saldırı yapmasını sağlar
        cout << isim << " " << target.isim << "'e saldiriyor" << endl;
        target.hasarAl(saldiriGucu);
    }

    void hasarAl(int hasar) { // Karakterin aldığı hasarı hesaplar
        int gercekHasar = hasar - savunmaGucu;
        can -= gercekHasar;
        cout << isim << " " << gercekHasar << " hasar aldi" << endl;
    }

    bool hayattaMi() { // Karakterin hayatta olup olmadığını kontrol eder
        return can > 0;
    }

    string getIsim() { // Karakterin ismini döner
        return isim;
    }

    int getCan() { // Karakterin mevcut canını döner
        return can;
    }
};

void gosterCanBar(string isim, int mevcutCan, int maksimumCan) { // Sağlık barını gösterir
    int barUzunlugu = 20; // Sağlık barının genişliği
    int doluUzunluk = (mevcutCan * barUzunlugu) / maksimumCan; // Dolu kısmı hesapla

    cout << isim << " [";
    for (int i = 0; i < doluUzunluk; i++) cout << "#"; // Dolu kısmı yazdır
    for (int i = doluUzunluk; i < barUzunlugu; i++) cout << " "; // Boş kısmı yazdır
    cout << "] " << mevcutCan << "/" << maksimumCan << endl;
}

void baslangicEkrani() { // Oyunun başlangıç ekranını gösterir
    cout << "==============================" << endl;
    cout << "   SIRA TABANLI SAVAS OYUNU   " << endl;
    cout << "==============================" << endl;
    cout << "Zorluk seviyesini secin (1 = Kolay, 2 = Orta, 3 = Zor): ";
}

class Oyuncu : public Karakter { // oyuncu icin bir sinif
private:
    int iksirSayisi; // Oyuncunun sahip olduğu iksir sayısı

public:
    Oyuncu(string oyuncuIsim, int hp, int atk, int def, int iksirAdet) { // Oyuncu için yapıcı
        isim = oyuncuIsim;
        can = hp;
        saldiriGucu = atk;
        savunmaGucu = def;
        iksirSayisi = iksirAdet;
    }

    void iksirKullan() { // Oyuncunun iksir kullanma özelliği
        if (iksirSayisi > 0) {
            can += 30;
            iksirSayisi--;
            cout << isim << " 30lik bir eksir kullanildi " << endl;
        }
        else {
            cout << isim << "'in iksiri kalmadi" << endl;
        }
    }
};

class Goblin : public Karakter { // Goblin sınıfı, Karakter sınıfından türetilmiştir
public:
    Goblin() { // Goblin için yapıcı
        isim = "Goblin";
        can = 30;
        saldiriGucu = 10;
        savunmaGucu = 2;
        cout << "Bir Goblin ortaya cikti" << endl;
    }

    void saldir(Karakter& hedef) override { // Goblinin saldırı metodu
        cout << isim << " " << hedef.getIsim() << "'e saldiriyor" << endl;
        hedef.hasarAl(saldiriGucu);
    }
};

class Ejder : public Karakter { // Ejder sınıfı, Karakter sınıfından türetilmiştir
public:
    Ejder() { // Ejder için yapıcı
        isim = "Ejder";
        can = 60;
        saldiriGucu = 15;
        savunmaGucu = 5;
        cout << "Bir Ejder ortaya cikti" << endl;
    }

    void saldir(Karakter& hedef) override { // Ejderin saldırı metodu
        cout << isim << " " << hedef.getIsim() << "'e saldiriyor" << endl;
        hedef.hasarAl(saldiriGucu);
    }
};

class Titan : public Karakter { // Titan sınıfı, Karakter sınıfından türetilmiştir
public:
    Titan() { // Titan için yapıcı
        isim = "Titan";
        can = 80;
        saldiriGucu = 20;
        savunmaGucu = 10;
        cout << "bir Titan ortaya cikti" << endl;
    }

    void saldir(Karakter& hedef) override { // Titanın saldırı metodu
        cout << isim << " " << hedef.getIsim() << "'e saldiriyor" << endl;
        hedef.hasarAl(saldiriGucu);
    }
};

int main() {
    baslangicEkrani(); // Başlangıç ekranı göster

    int zorluk;
    cin >> zorluk;

    int oyuncuCan; // Oyuncunun başlangıç canı
    if (zorluk == 1) { // Kolay seviye
        oyuncuCan = 120;
    }
    else if (zorluk == 2) { // Orta seviye
        oyuncuCan = 100;
    }
    else { // Zor seviye
        oyuncuCan = 80;
    }

    Oyuncu oyuncu("Kahraman Ahmet", oyuncuCan, 15, 5, 3); // Oyuncu nesnesi oluştur

    // Düşman Tipleri
    Karakter* dusmanlar[3];
    dusmanlar[0] = new Goblin();
    cout << endl;
    dusmanlar[1] = new Ejder();
    cout << endl;
    dusmanlar[2] = new Titan();
    cout << endl;

    cout << "Savas Basliyor " << endl;

    int mevcutDusman = 0; // Mevcut düşman indeksi

    while (oyuncu.hayattaMi() && mevcutDusman < 3) { // Oyun döngüsü
        cout << endl;
        gosterCanBar(oyuncu.getIsim(), oyuncu.getCan(), oyuncuCan); // Oyuncunun sağlık barını göster
        gosterCanBar(dusmanlar[mevcutDusman]->getIsim(), dusmanlar[mevcutDusman]->getCan(), 100); // Düşmanın sağlık barını göster

        // Oyuncunun Sırası
        cout << "Islev sec 1) Saldir 2) Iksir Kullan: ";
        int secim;
        cin >> secim;
        cout << endl;

        if (secim == 1) { // Oyuncu saldırır
            oyuncu.saldir(*dusmanlar[mevcutDusman]);
        }
        else if (secim == 2) { // Oyuncu iksir kullanır
            oyuncu.iksirKullan();
        }
        else {
            cout << "Gecersiz. Tekrar deneyin" << endl;
            continue;
        }

        if (!dusmanlar[mevcutDusman]->hayattaMi()) { // Düşman yenildiyse
            cout << dusmanlar[mevcutDusman]->getIsim() << " yenildi!\n";
            mevcutDusman++;

            if (mevcutDusman < 3) {
                cout << "Yeni bir car savasa katildi" << endl;
            }

            continue;
        }

        dusmanlar[mevcutDusman]->saldir(oyuncu); // Düşman saldırır

        if (!oyuncu.hayattaMi()) { // Oyuncu yenildiyse
            cout << "Maalesef kaybettiniz. " << endl;
            break;
        }
    }

    for (int i = 0; i < 3; i++) { // Belleği temizle
        delete dusmanlar[i];
    }

    return 0; // Program sonu
}
