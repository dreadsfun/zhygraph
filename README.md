# Szakdolgozat

cím: *Interaktív kezelőfelület C++ nyelven implementált grafikus alkalmazásokhoz*

## Bevezetés

* Ezt elég lesz majd csak a végén leírni. Kb. 1-2 oldal elegendő ide.
* Mit mutat majd be a dolgozat, és milyen problémát old meg.
* 1-2 oldal

## Problémakör

* Ez indokolja a dolgozat létjogosultságát. Itt kell azt is megmutatni, hogy nem triviális problémáról van szó, és hogy pont ilyen még nincs.
* Grafikus megjelenítő rendszerek
* Szkriptnyelvek (Python, Lua, JavaScript, LISP)
* Alternatív megoldások. Keresni olyan grafikus motorokat, keretrendszereket, amelyekben van hasonló beágyazott nyelves megoldás. (Például játékmotorok, Unity, Blender)
* 5-6 oldal

## Program felépítése, alkalmazott technológiák

* Ez mutatja meg, hogy a program egészében hogy áll össze, hogy épül fel.
* Tesztelésre érdemes kitérni, például egységtesztek a funkciók ellenőrzéséhez.
* Architektúrális ábrák
* Interakcióhoz ábra a host és a beágyazott nyelv között.
* Nézeti csővezeték, beavatkozási pont, renderelési folyamat, mainloop.
* 5-6 oldal

## Renderelési folyamat optimalizálása

* Az eredeti probléma megadása
* Láthatósági problémához
* Térpartícionálás
* Algoritmusok
* Oktális fák
* Shader-ek
* Modell renderelési eszközök, vertex-, index-, attribútum bufferek
* kb. 10 oldal

## Asset management

* redundancia csökkentése
* szálbiztonság
* gargabe collecting
* kb. 5 oldal

## Szkriptnyelv beágyazása

* Hogyan illeszthető egymáshoz a C++ és a Python
* kb. 5 oldal

## Implementáció, API

* Milyen interfészek vannak
* Forráskód szerkezete
* API jellegű leírás (kvázi, mint ha fejlesztőknek szólna)
* Fejlesztői tutorial féle, hogy hogy lehet használni úgy, hogy a belsejébe már nem nagyon kell belenézni.
* A Python-os interfészt részletezni.
* GitHub repo elérhetősége
* kb. 5 oldal

## Tesztek, eredmények

* Meg kell mutatni, hogy a szoftver valóban használható.
* Ide jöhetnek a képernyőképek majd.
* Teljesítmény vizsgálatával kapcsolatos dolgok. (Pl.: Szkript használatából eredő overhead)
* Grafikonokkal ábrázolni a natív és szkriptes implementáció közötti különbségeket.
* kb. 4 oldal

## Összegzés

* Ezt elég lesz majd csak a végén leírni. Kb. 1-2 oldal elegendő ide.
* Mit mutatott be a dolgozat, és hogy lehet értékelni az eredményeket összességében.
* További fejlesztési, kutatási irányok, alkalmazási lehetőségek.
* 1-2 oldal

## Hivatkozások

* OpenGL
* Blender
* Algoritmusok (octtree, hierarchikus transzformációk)
* kb. 2 oldal

