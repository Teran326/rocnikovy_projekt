# Ročníkový projekt
## Projekt Lednička
## Cíl: Teploměr by měl měřit danou teplotu v lednici a následně ji zapsat na webserver, ze kterého by bylo možné si dané výsledky stáhnout a vytisknout. 
##      Zaznamenávání teploty a času
### Zdroje: [Arduino libraries](http://arduino.esp8266.com/Arduino/versions/2.1.0-rc1/doc/libraries.html), [ESP sheets](https://jpralves.net/post/2016/11/15/esp8266.html#esp-201), [How to use the javascript fetch api to get data](https://www.geeksforgeeks.org/how-to-use-the-javascript-fetch-api-to-get-data/), [Fetch post and header examples](https://www.freecodecamp.org/news/javascript-fetch-api-tutorial-with-js-fetch-post-and-header-examples/)
### Framework:
### Knihovny: 


### Rozdělení do fází:
   1. Fáze: Diagram el. zapojení
   2. Fáze: Program zapisující hodnoty
   3. Fáze: Vytvoření web serveru a následný výpis hodnot z programu
   4. Fáze: Sestavení el. obvodu
   5. Fáze: Vytvoření ochranného obalu před chladem a vlhkem
   6. Fáze: Testování, ukončení vývoje

#### Povedlo se mi přiřadit IP k ESP a vytvořit z něj Access Point. Asi to není nejlepší řešení, ale alespoň je snadno přenosný, nemusí se složitě připojovat na router, jelikož jím sám je.
#### Na stránku se přiřazují hodnoty trimru (prozatím není zapojený teploměr, takže to musí stačit)
#### Místo AP jsem nakonec udělal WebServer, bohužel nemůžu najít knihovny ESPmDNS.h a SPIFFS.h
#### Přidání měření teploty
#### Vytvoření REST API a práce na JS pro výpis dat
#### Hledání zdrojů o REST API
