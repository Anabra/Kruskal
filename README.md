# Kruskal - dokumentáció


Feladat
=======

Adott egy élsúlyozott, írányítatlan gráf. határozzuk meg a minimális költségű
feszítőfáját!

Elemzés
=======

Az algoritmus
-------------

A Kruskal algoritmust fogjuk használni a feladat megoldásához. Ehhez szükségünk
lesz egy lineáris rendező algoritmusra, valamint a union-find adatszerkezetre.
Rendezési algoritmusnak a radix rendezést vélasztjuk, amely a counting sort-ot
fogja használni.

Ezeket az algoritmusokat általánosan fogjuk implementálni, tetszőleges T típusra
alkalmazhatóak lesznek (néhány megszórítás mellett).


Az adatszerkezet
----------------

Az algoritmus megvalósításához egy általános célú gráf típust fogunk használni.
A gráfban tetszőleges típussal címkézhetők mind az élek, mind a csúcsok (néhány
megszorítás mellett).

Ami az adatszerkezet funkcionalitását illeti, lehetőségünk lesz csúcsonként,
illetve élenként felépíteni a gráfot, valamint lekérdezni egy adott csúcsból
a kimenő és beérkező éleket, és a hozzájuk tartozó csúcsokat is.
Ezen műveletek költsége egyenesen arányos az adott csúcsból kiinduló élek
számával.

Továbbá lehetőségünk van a gráf csúcsain végigiterálni, és lekérdezni az összes
élét.

_Megjegyzés_: A Kruskal algoritmus implementálásához nincs is szükségünk gráf
adatszerkezetre, elegendő lenne egy megfelelő él reprezentáció.


Tervezés
========

A feladatot C++14-ben fogjuk megvalósítani.

`disjoint_set<T>`
----------------

A fentebbi típussal fogjuk megvalósítani a union-find adatszerkezetet.
Az osztály interface-e három függvényt biztosít a számunkra:

  - `T    find      (const T&);`
  - `void merge     (const T&, const T&);`
  - `bool connected (const T&, const T&);`

Ezek a union-find szokásos műveletei. Amit érdemes megjegyezni, az az, hogy az
implementációnál path-shrinking-et és union-by-rank megvalósítást alkalmaztunk,
aminek következtében mindegyik művelet közel konstans<sup id="a1">[1](#f1)</sup> műveletigényű.

Ahhoz, hogy tetszőleges típust tudjunk tárolni ebben az adatszerkezetben,
biztosítanunk kell azt, hogy a `T` típusra specializálva legyen a `std::hash<T>`
osztály. Ezáltal készíthetünk egy leképezést a `T` típus elemei és az egész
számok között a `std::unordered_map<T, int>` osztály segítségével.
Ez biztosítani fogja, hogy a belső reprezentáció egész számokkal tudjon dolgozni,
miközben a felhasználó tetszőleges típust megadhat a publikus függvények
paramétereként.

__Fontos:__ Kizárólag olyan típus lehet a `T` paraméter amely rendelkezik
`std::hash<T>` specializációval.

<b id="f1">1)</b> A futásidő egyeneses arányos az egyértékű Ackermann
függvény inverzével: __O(A<sup>-1</sup>(n))__, ahol __n__ a halmazban lévő
elemek száma . [↩](#a1)



`radix_sort(vector<T>& vec, ToInt f)`
----------------------------------------

A `radix_sort` teljes mértékben a `countint_sort`-ra alapszik. Ennek a
függvénynek csupán annyi a feladata, hogy a megadott `f` függvény segítségével
leképezze a tetszőleges `T` típust egy egész számra (base10), majd meghatározza
a __n__-et, leghosszabb számot hosszát, és meghívja a `counting_sort`-ot
__n__-szer, mindig eggyel odébb tolva a rendezendő helyiértéket.


`counting_sort(vector<T>& vec, int base, ToInt f, NthDigit nth)`
----------------------------------------------------------------

A szokásos algoritmust implementáljuk, annyi különbséggel, hogy itt tetszőleges
`T` típust tudunk rendezni, amely leképezhető egy egész számra. Továbbá az
eljárás paraméterezhető még a számrendszer alapjával, és az __n__. számjegyet
lekérdező függvénnyel.



`Graph <NodeLabel, EdgeLabel>`
------------------------------

Célunk egy hatékony, általános célú gráf adatszerkezet megvalósítása. A gráfot
úgynevezett környezetekkel fogjuk ábrázolni. Minden csúcshoz hozzárendelünk
környezetet, amely tartalmazni fogja a beérkező és kimutató éleket. Ez fogja
biztosítani a környező csűcsok gyors elérését. Ezeket a `NodeLabel` - `Context`
párokat egy `std::unordered_map`-ben fogjuk tárolni, amely így nemcsak gyors
lesz, de kényelmessé teszi az adatszerkezet használatát. a környezetek
segítségével effektív törlést biztosíthatunk, hiszen, ha törlünk egy csúcsot,
akkor egyől ismerni fogjuk azokat a csúcsokat, amelyeket frissíten kell.

Az éleket is tárolni fogjuk egy `std::unordered_set`-ben. Ez fogja biztosítani
az élek gyors elérését.

A gráfot egy konstans iterátorral járhatjuk be, amely mindössze annyiban
különbözik az `std::unordered_map` konstan iterátorától, hogy ez kizárólag
a kulcshoz ad hozzáférést, tehát a csak a csúcsok címkéit fogja látni a
felhasználó, a hozzájuk rendelt környezeteket nem.


__Fontos:__ Kizárólag olyan típus lehet a `NodeLabel` és `EdgeLabel` paraméter
amely rendelkezik `std::hash<T>` specializációval.



Fordítás és futtatás
====================

A `main.cpp` fájlt fordítsuk a c++14 szabványa szerint. A fordított program
egy paramétert várt, amely az input fájl neve. Az eredményt a konzolra írja ki,
valamint egy `output.txt` nevű fájlba.
