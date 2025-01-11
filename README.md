# Proiect Librarie
 Acest proiect C++ reprezinta gestionarea unui meniu de produse: carti si cd-uri si a interactiunii cu clientii, inclusiv cumpararea de produse, gestionarea stocurilor si calcularea sumei cheltuite de fiecare client.

## Caracteristici principale
- Gestionarea produselor: adaugarea de produse: carti si cd-uri, fiecare cu un pret, stoc si un TVA specific.
- Gestionarea clientilor: adaugarea clientilor, cumpararea produselor si calculul sumei totale cheltuite.
- Clasa template Inventar: gestioneaza cartile cumparate de catre fiecare client.
- Meniu: permite utilizatorului sa gestioneze interactiunile cu clientii prin intermediul consolei.

## Structura proiectului
### Clase principale:
1. Produs
   -Clasa de baza pentru produse = CLASA ABSTRACTA
2. Carte
   -Derivata din Produs
3. CD
   -Derivata din Produs
4. Client
   -clasa de baza pentru clienti
5. Meniu
   -centralizeaza interactiunile utilizatorului.
   -permite adaugarea, vizualizarea produselor si efectuarea de achizitii.

### Utilizare
- Adaugare produse. (carti si cd-uri)
- Adaugare clienti.
- Adaugare produse pentru clienti. (achizitii)
- Vizualizare sume cheltuite de fiecare client.
- Verificare stoc ramas pentru fiecare client.
- Cautare produs in functie de titlu.
- Sortarea cartilor librariei in functie de pret.
