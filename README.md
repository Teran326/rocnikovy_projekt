# Ročníkový projekt
## Projekt Lednička
## Cíl: Teploměr by měl měřit danou teplotu v lednici a následně ji zapsat na webserver, ze kterého by bylo možné si dané výsledky stáhnout a vytisknout. 
##      Zaznamenávání teploty a času
### Zdroje: https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html#softapip, http://arduino.esp8266.com/Arduino/versions/2.1.0-rc1/doc/libraries.html, https://jpralves.net/post/2016/11/15/esp8266.html#esp-201
### FrameWork: C/C++
### Konkurence:
### Knihovny: WifiClient, ESP8266WiFi


### Rozdělení do fází:
   1. Fáze: Diagram el. zapojení a předběžný design UI
   2. Fáze: Program zapisující hodnoty
   3. Fáze: Vytvoření web serveru a následný výpis hodnot z programu
   4. Fáze: Úprava UI, sestavení el. obvodu
   5. Fáze: Vytvoření ochranného obalu před chladem a vlhkem
   6. Fáze: Testování, ukončení vývoje

#### Povedlo se mi přiřadit IP k ESP a vytvořit z něj Access Point. Asi to není nejlepší řešení, ale alespoň je snadno přenosný, nemusí se složitě připojovat na router, jelikož jím sám je.
