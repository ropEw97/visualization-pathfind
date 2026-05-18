## Slučaj upotrebe: Čuvanje mape
Kratak opis: Korisnik bira opciju za čuvanje mape.
Aplikacija informacije o trenutnoj konfiguraciji mape upisuje u datoteku na disku.
Trenutno stanje mape je nakon toga zapamćeno i može se ponovo učitati iz datoteke.

Akteri:
  - Korisnik

Preduslovi: Aplikacija je pokrenuta i čeka na sledeću komandu korisnika.

Postuslovi: Stanje mape je trajno sačuvano u datoteci ili je prikazana poruka o grešci.

Osnovni tok:
- 1. Korisnik bira dugme "Save map".
- 2. Aplikacija proverava da li su na mapi postavljene oznake za početak i cilj.
  - 2.1. Ukoliko oznake za početak i cilj nisu postavljene potrebno je obavestiti korisnika.
    - 2.1.1. Aplikacija prikazuje poruku da je potrebno postaviti oznake za početak i cilj.
    - 2.1.2. Prelazi se na korak 7.
- 3. Aplikacija dohvata informacije o trenutno postavljenim objektima na mapi.
- 4. Aplikacija prikazuje dijalog za čuvanje nove datoteke.
  - 4.1. Korisnik bira ime nove datoteke u kojoj će biti sačuvana mapa.
    - 4.1.1. Ukoliko već postoji datoteka sa datim imenom korisnik može izabrati da prepiše nove podatke preko nje.
  - 4.2. Ukoliko korisnik zatvori dijalog bez biranja datoteke:
    - 4.2.1. Prelazi se na korak 7.
- 5. Aplikacija upisuje informacije o mapi u datoteku.
- 6. Aplikacija prikazuje poruku da je mapa uspešno sačuvana.
- 7. Aplikacija čeka na sledeću komandu korisnika.

Alternativni tokovi:
  - A1: Greška pri pisanju u datoteku. Ukoliko za vreme koraka 5 dođe do greške, mapa neće
  biti sačuvana. Aplikacija će nastaviti rad od koraka 7. 

Podtokovi: /

Specijalni zahtevi: /

Dodatne informacije: Aplikacija u datoteci za svaku oznaku sa mape čuva poziciju na mapi
i tip oznake.


## Slučaj upotrebe: Generisanje lavirinta
Kratak opis: Korisnik pritiskom na dugme lavirint pokrece algoritam koji generise lavirint i iscrtava ga na scenu.

Akteri: Korisnik.

Preduslovi: Aplikacija je pokrenuta.

Postuslovi: Algoritam je izgenerisao prepreke na sceni i pozicionirao start i cilj.

Osnovni tok: 
- 1. Igrac bira dugme "Lavirint" iz glavnog menija.
- 2. Poziva se metod klase Canvas za ciscenje scene.
- 3. Poziva se metod klase Canvas za generisanje lavirinta.
	- 3.1. Pokrece se algoritam za generisanje lavirinta.
	- 3.2. Iscrtavanu se prepreke.
	- 3.3. Pozicioniraju se start i cilj na prvo slobodno mesto.

Alternativni tokovi:
- A1: Neocekivani izlaz iz aplikacije. Ukoliko u bilo kojem toraku korisnik iskljuci   aplikaciju, sva eventualno zapamcenja podesavanja na msceni se ponistavaju i aplikacija zavrsava rad. Slucaj upotrebe se zavrsava.

Podtokovi:/

Specijalni zahtevi:/

Dodatne informacije:/


## Slučaj upotrebe: Pokretanje algoritma
Kratak opis: Korisnik pritiskom na boks sa algoritmima bira algoritam pretrage koji će se izvršavati. Nakon toga počinje izvršavanje zadatog algoritma.

Akteri: Korisnik.

Preduslovi: Izabrani su početak i cilj. Aplikacija je pokrenuta. 

Postuslovi: Prikazani svi putevi razmatrani u toku pretrage i posebno naznačen najkraći put od početka do cilja.

Osnovni tok:
- 1. Korisnik bira algoritam iz boksa "Algorithm".
- 2. Aplikacija proverava da li su na mapi postavljene oznake za početak i cilj.
    - 2.1.1. Aplikacija prikazuje poruku da je potrebno postaviti oznake za početak i cilj.
    - 2.1.2. Prelazi se na korak 7.
- 3. Dohvataju se informacije o mapi.
- 4. Aplikacija pokreće odgovarajući algoritam.
- 5. Sve dok traje pretraga(dok se ne stigne do cilja):
    - 5.1. Aplikacija čuva informacije o putu koji prelazi.
    - 5.2. Čuva informaciju o najkraćem putu.
- 6. Iscrtavaju se svi obiđeni putevi, a najkraći put se posebno označava.
- 7. Aplikacija čeka na sledeću komandu korisnika.

Alternativni tokovi:

  - A1: Neočekivani izlaz iz aplikacije. Ukoliko u bilo kojem toraku korisnik isključi aplikaciju, sva eventualno zapamćena podešavanja na sceni se poništavaju i aplikacija završava rad. Slučaj upotrebe se završava.
  - A2: Prepreke su tako postavljene da je nemoguće naći put od početka do cilja.
    
Podtokovi:/

Specijalni zahtevi:/ 

Dodatne informacije:/


## Slučaj upotrebe: Pozicioniranje starta
Kratak opis: Korisnik vri pozicioniranje starta pritiskom na dugme start iz glavnog menija,
a onda i pomeranjem nacrtanog starta na sceni pomoću miša.

Akteri: Korisnik.

Preduslovi: Aplikacija je pokrenuta.

Postuslovi: Start je pozicioniran na sceni.

Osnovni tok: 
- 1. Korisnik bira dugme "Start" iz glavnog menija.
- 2. Poziva se metod klase Canvas za crtanje starta.
- 3. Korisnik pomera start na eljeno mesto na sceni.
- 4. Poziva se metod klase Canvas koji pamti poziciju starta.

Alternativni tokovi:

- A1: Neoekivani izlaz iz aplikacije. Ukoliko u bilo kojem koraku korisnik iskljui aplikaciju, sva eventualno zapamena podeavanja na sceni se ponitavaju i aplikacija zavrava rad. Sluaj upotrebe se zavrava.

Podtokovi:/

Specijalni zahtevi:/

Dodatne informacije:/

