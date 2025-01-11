#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <exception>

using namespace std;

class Produs {  ///CLASA ABSTRACTA
protected:
    string titlu;
    string autor;
    double pret;
    int stoc;
public:
    Produs():titlu(""), autor(""), pret(0), stoc(0) {}
    Produs(string titlu, string autor, double pret, int stoc) : titlu(titlu), autor(autor), pret(pret), stoc(stoc) {}

    virtual void afisare(ostream &out) const {
        out << "Titlu: " << titlu << '\n';
        out << "Autor: " << autor << '\n';
        out << "Pret: " << pret << '\n';
        out << "Stoc: " << stoc << '\n';
    }

    friend ostream& operator<<(ostream &out, const Produs &p) {
        p.afisare(out);
        return out;
    }
    friend istream& operator>>(istream &in, Produs &p) {
        cout << "Titlu: ";
        in.ignore();
        getline(in, p.titlu);

        cout << "Autor: ";
        getline(in, p.autor);

        cout << "Pret: ";
        in >> p.pret;
        cout << "Stoc: ";
        in >> p.stoc;
        return in;
    }
    virtual ~Produs() {}

    const string &getTitlu() const {return titlu;}  ///!!!
    int getStoc() const {return stoc;}
    void scadeStoc() {
        stoc--;
    }
    virtual double PretFinal() const = 0; ///functie pur virtuala
};

class Carte: public Produs {    ///de tip BUILDER
private:
    int nr_pagini;
    string format;
friend class CarteBuilder;
public:
    Carte() = default;  ///pt builder
    Carte(const string &titlu, const string &autor, double pret, int stoc, int nr_pagini, const string &format) ///referinta constanta pt parametrii de tip string
    : Produs(titlu, autor, pret, stoc), nr_pagini(nr_pagini) , format(format) {}
    Carte(const Carte &c):Produs(c), nr_pagini(c.nr_pagini), format(c.format) {}

    Carte& operator=(const Carte& c) {
        if(this != &c){
            Produs::operator=(c);
            nr_pagini = c.nr_pagini;
            format = c.format;
        }
        return *this;
    }

    void afisare(ostream &out) const override{
        Produs::afisare(out);
        out << "Nr Pagini: " << nr_pagini << '\n';
        out << "Format: " << format << '\n';
        out << "\n";
    }

    friend ostream& operator<<(ostream &out, const Carte& c) {
        c.afisare(out);
        return out;
    }

    friend istream& operator>>(istream &in, Carte& c) {
        in >> (Produs&) c;  ///citirea atributelor comune din Produs
        cout << "Nr Pagini: ";
        in >> c.nr_pagini;
        cout << "Format: ";
        in >> c.format;
        return in;
    }

    double PretFinal()const override {
        return pret + (pret * (4/100));   ///Am presupus ca TVA-ul pt carti este 4%
    }
    virtual ~Carte() override{}
};
///operator < non-membru
bool operator<(const Carte& c1, const Carte& c2) {
    return c1.PretFinal() < c2.PretFinal(); ///pt sortarea in functie de pret
}

class CarteBuilder {
    private:
    Carte carte;
    public:
    CarteBuilder() = default;

    CarteBuilder& titlu(const string &t) {
        carte.titlu = t;
        return *this;
    }
    CarteBuilder& autor(const string &a) {
        carte.autor = a;
        return *this;
    }
    CarteBuilder& pret(double p) {
        carte.pret = p;
        return *this;
    }
    CarteBuilder& stoc(int s) {
        carte.stoc = s;
        return *this;
    }
    CarteBuilder& nr_pagini(int np) {
        carte.nr_pagini = np;
        return *this;
    }
    CarteBuilder& format(string f) {
        carte.format = f;
        return *this;
    }
    Carte &build() {    ///!!!
        return carte;
    }
};

class CD: public Produs {
private:
    string gen, album;
    int nr_melodii;

public:
    CD(const string &titlu, const string &autor, const string &album, double pret, int stoc, int nr_melodii, const string &gen) ///!!!
        :Produs(titlu, autor, pret, stoc), gen(gen), album(album), nr_melodii(nr_melodii) {}
    CD(const CD &c):Produs(c), gen(c.gen), album(c.album),nr_melodii(c.nr_melodii) {}

    CD& operator=(const CD& c) {
        if(this != &c){
            Produs::operator=(c);
            nr_melodii = c.nr_melodii;
            gen = c.gen;
            album = c.album;
        }
        return *this;
    }

    ///METODA 1
    void afisare(ostream &out) const override{
        Produs::afisare(out);
        out << "Numar melodii : " << nr_melodii << '\n';
        out << "Gen : " << gen << '\n';
        out << "Album : " << album << '\n';
        out << "\n";
    }
    friend ostream& operator<<(ostream &out, const CD& c) {
        c.afisare(out);
        return out;
    }

    friend istream& operator>>(istream &in, CD& c) {
        in >> (Produs&) c;
        cout << "Numar melodii : ";
        in >> c.nr_melodii;
        cout << "Gen : ";
        in >> c.gen;
        cout << "Album : ";
        in.ignore();
        getline(in, c.album);
        return in;
    }
    double PretFinal() const override {
        return pret + (pret * (7/100));  ///TVA-ul pt CD-uri = 7%
    }
    virtual ~CD() override{}
};

///
class Client {
private:
    int index;
    static int contor;
    string nume;
    string prenume;
    string nr_telefon;
    string email;
    double suma_produse;

public:
    Client(string nume, string prenume, string nr_telefon, string email) : nume(nume), prenume(prenume), nr_telefon(nr_telefon), email(email), suma_produse(0) {
        index = contor++;
    }

    ///operator supraincarcat ca functie membra
    Client &operator+=(Produs* produse) {   ///suma produselor achizitionate de un client
        suma_produse += produse -> PretFinal();
        return *this;
    }

    void afisare() const{
        cout << "Nume: " << nume;
        cout << "\nPrenume: " << prenume;
        cout << "\nNumar de telefon: " << nr_telefon;
        cout << "\nEmail: " << email;
        cout << "\nBani cheltuiti: " << suma_produse;
        cout << "\n";
    }

    friend ostream& operator<<(ostream &out, const Client& c) {
        c.afisare();
        return out;
    }

    friend istream& operator>>(istream &in, Client& c) {
        cout << "Nume: ";
        in >> c.nume;
        cout << "Prenume: ";
        in >> c.prenume;
        cout << "Numar de telefon: ";
        in >> c.nr_telefon;
        cout << "Email: ";
        in >> c.email;
        return in;
    }
    virtual ~Client() {}

    int getIndex() const{return index;}
    int getSumaClient() const{return suma_produse;}
    const string &getNume() const{return nume;}
    const string &getPrenume() const{return prenume;}
    const string &getTelefon() const {return nr_telefon;}
};
int Client::contor = 1;

///
class Meniu {   ///SINGLETON
private:
    vector<Produs*> produse;
    vector<Client*> clienti;
    Meniu() = default;

    public:
    Meniu(const Meniu&) = delete;
    Meniu& operator=(const Meniu&) = delete;
    static Meniu& get_app() {
        static Meniu app;
        return app;
    }

    void afisareOptiuni();
    void run();
    Carte adaugareCarte();  ///clasa builder
    void adaugareCD();
    void adaugareClient();
    void adaugareProdusClient();
    void afisareCarti();
    void afisareCDuri();
    void afisareClienti();
    void sortare_carti_pret();
    void cautareProdusTitlu();
};

void Meniu::afisareOptiuni() {
    cout << "1. Adauga carte\n";
    cout << "2. Adauga CD\n";
    cout << "3. Adauga Client\n";
    cout << "4. Afiseaza carti\n";
    cout << "5. Afiseaza CD-uri\n";
    cout << "6. Afiseaza Clienti\n";
    cout << "7. Sortare carti dupa pret\n";
    cout << "8. Adaugare produs client\n";
    cout << "9. Cautare produs dupa titlu\n";
    cout << "Optiunea ta:\n";
}

Carte Meniu::adaugareCarte() {
    CarteBuilder b;

    string titlu, autor, format;
    double pret;
    int stoc, nr_pagini;

    cout << "Titlu: ";
    cin.ignore();
    getline(cin, titlu);
    cout << "Autor: ";
    getline(cin, autor);
    cout << "Pret: ";
    cin >> pret;
    cout << "Stoc: ";
    cin >> stoc;
    cout << "Nr Pagini: ";
    cin >> nr_pagini;
    cout << "Format: ";
    cin >> format;

    b.titlu(titlu)
    .autor(autor)
    .pret(pret)
    .stoc(stoc)
    .nr_pagini(nr_pagini)
    .format(format);

    Carte carte = b.build();
    ///UPCASTING AUTOMAT => carte devine produs
   // Carte* carte =  new Carte(titlu, autor, pret, stoc, nr_pagini, format);
    produse.push_back(&carte);   ///pentru a putea avea produsele si in vectorul produse
    cout << "Cartea a fost inregistrata cu succes!\n";
}

void Meniu::sortare_carti_pret() {
    vector <Carte*> carti;
    for(Produs* produs : produse) {
        if(Carte* c = dynamic_cast <Carte*> (produs)) {
            carti.push_back(c);
        }
    }
    sort(carti.begin(), carti.end(), [](Carte* a, Carte* b) {
        return a->PretFinal() < b->PretFinal();
    });
    cout << "Cartile au fost sortate dupa pret!\n";
}

void Meniu::cautareProdusTitlu() {
    string titlu;
    cout << "Introduceti titlul produsului cautat: \n";
    cin.ignore();
    getline(cin, titlu);

    bool gasit = 0;
    for(Produs* produs : produse) {
        if(produs->getTitlu() == titlu) {
            gasit = 1;
            if(dynamic_cast<Carte *>(produs)) { ///pt ca primeam eroare la G actions
                cout << "Carte gasita!\n";
            }
            else if(dynamic_cast<CD *>(produs)) {
                cout << "CD gasit!\n";
            }
        }
    }
    if(!gasit) {
        cout << "Produsul nu a fost gasit!\n";
    }
}

void Meniu::adaugareCD() {
    string titlu, autor, gen, album;
    double pret;
    int stoc, nr_melodii;

    cout << "Titlu: ";
    cin.ignore();
    getline(cin, titlu);
    cout << "Autor: ";
    getline(cin, autor);
    cout << "Pret: ";
    cin >> pret;
    cout << "Stoc: ";
    cin >> stoc;
    cout << "Nr Melodii: ";
    cin >> nr_melodii;
    cout << "Gen: ";
    cin >> gen;
    cout << "Album: ";
    cin.ignore();
    getline(cin, album);

    CD* cd = new CD(titlu, autor, album, pret, stoc, nr_melodii, gen);
    produse.push_back(cd);
    cout << "CD-ul a fost inregistrat cu succes!\n";
}

void Meniu::adaugareClient() {
    string nume, prenume, nr_telefon, email;

    cout << "Introduceti numele clientului: ";
    cin >> nume;
    cout << "Introduceti prenumele clientului: ";
    cin >> prenume;
    cout << "Introduceti numarul de telefon al clientului: ";
    cin >> nr_telefon;
    cout << "Introduceti adresa de email a clientului: ";
    cin.ignore();
    getline(cin, email);

    Client *client = new Client(nume, prenume, nr_telefon, email);
    clienti.push_back(client);
    cout << "Clientul a fost inregistrat cu succes!\n";
}

void Meniu::afisareCarti() {
    bool ok = 0;
    cout << "Carti inregistrate: \n";
    for(Produs* produs: produse) {
        if(Carte* carte = dynamic_cast<Carte*>(produs)) {
            cout << *carte;
            ok = 1;
        }
    }
    if(!ok) {
        cout << "Nu au fost inregistrate carti!\n";
    }
}

void Meniu::afisareCDuri() {
    bool ok = 0;
    cout << "CD-uri inregistrate: \n";
    for(Produs* produs: produse) {
        if(CD* cd = dynamic_cast<CD*>(produs)) {
            cout << *cd;
            ok = 1;
        }
    }
    if(!ok) {
        cout << "Nu au fost inregistrate CD-uri!\n";
    }
}

void Meniu::afisareClienti() {
    if(clienti.empty()) {
        cout << "Nu au fost inregistrati clienti!\n";
        return;
    }
    cout << "Clienti inregistrati:\n";
    for(auto i = clienti.begin(); i != clienti.end(); i++) {
        const auto& client = *i;
        client -> afisare();
        cout << '\n';
    }
}

void Meniu::adaugareProdusClient() {
    if(clienti.empty()) {
        cout << "Nu exista clienti inregistrati!\n";
        return;
    }

    cout <<"Selecteaza indexul clientului:\n";
    for(size_t i = 0; i < clienti.size(); i++) {    ///eroare la github actions
        cout << i + 1 <<". " << *clienti[i] << '\n';
    }

    int index;
    cin >> index;
    Client* c = clienti[index - 1];

    if(produse.empty()) {
        cout << "Nu exista produse in stoc! \n";
        return;
    }

    cout << "Selecteaza indexul produsului dorit: \n";
    for(size_t i = 0; i < produse.size(); i++) {
        cout << i + 1 <<". " << *produse[i] << '\n';
    }

    int index_produs;
    cin >> index_produs;
    Produs* produs = produse[index_produs - 1];
    if(produs -> getStoc() > 0) {
        produs -> scadeStoc();
        *c += produs;    ///adaugam produsul clientului
        cout << "Clientul a cumparat produsul! Achizitie reusita!";
    }
    cout << "Suma cheltuita de clientul " << index << " este: " << c -> getSumaClient() << '\n';
}

class wrongInput:public exception {
public:
    const char* what() const noexcept override {return "Alegere gresita!";}
};
///Daca o fct. e marcata cu noexcept => ea nu va arunca nicio exceptie!

void Meniu::run() {
        while(true) {
            int optiune;
            afisareOptiuni();
            cin >> optiune;

            try {
                switch (optiune) {
                    case 1: adaugareCarte(); break;
                    case 2: adaugareCD(); break;
                    case 3: adaugareClient(); break;
                    case 4: afisareCarti(); break;
                    case 5: afisareCDuri(); break;
                    case 6: afisareClienti(); break;
                    case 7: sortare_carti_pret(); break;
                    case 8: adaugareProdusClient(); break;
                    case 9: cautareProdusTitlu(); break;
                    default: throw wrongInput();
                }
            }
            catch(exception& e) {
                cout << "Eroare: " << e.what() << '\n';
               // run();
            }
        }
};

int main()
{
    Meniu &m = Meniu::get_app();
    m.run();
    return 0;
}