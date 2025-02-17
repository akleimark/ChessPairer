ChessPairer

ChessPairer är en applikation för att hantera och administrera schacktävlingar. Den låter användare skapa turneringar, lägga till spelare och generera lottningar enligt olika system såsom Schweizer-systemet och Berger-tabellen.

Funktioner

Skapa och hantera schacktävlingar

Stöd för både FIDE-registrerade och oregistrerade spelare

Automatiserad lottning enligt Schweizer- eller Berger-systemet

Databaslagring med SQLite

Grafiskt gränssnitt byggt med Qt 5

Import och export av turneringsdata

Installation

Förutsättningar

För att bygga och köra applikationen behöver du följande:

C++ (minst C++17)

Qt 5 (för GUI och databashantering)

CMake (för att bygga projektet)

SQLite (för databashantering)

Bygg och kör

mkdir build && cd build
cmake ..
make
./ChessPairer

Användning

Skapa en ny turnering

Öppna applikationen

Klicka på "Ny turnering"

Fyll i turneringsnamn, start- och slutdatum, antal ronder och lottningstyp

Klicka på "Skapa"

Lägg till spelare

Gå till fliken "Spelare"

Klicka på "Lägg till spelare"

Ange namn, FIDE-ID (om tillgängligt) och rating

Klicka på "Spara"

Generera lottning

Navigera till fliken "Ronder"

Klicka på "Generera lottning"

Systemet skapar automatiskt matcher enligt valt lottningstyp

Teknisk Information

ChessPairer är byggt med C++ och använder Qt 5 för sitt gränssnitt och databasinteraktion. Databasen hanteras med SQLite, och applikationen följer en Model-View-Controller (MVC)-arkitektur.

Bidra

Om du vill bidra till projektet:

Forka detta repo

Skapa en ny branch (git checkout -b feature-namn)

Gör dina ändringar och commit (git commit -m 'Lade till ny funktion')

Push till din branch (git push origin feature-namn)

Skapa en Pull Request

Licens

ChessPairer är öppen källkod och distribueras under MIT-licensen.
