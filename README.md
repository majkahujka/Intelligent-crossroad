# Intelligent-crossroad
Slovensky:

Projekt pre ESP32, ktorý monitoruje reálny čas a intenzitu svetla. Monitorovanie reálneho času sa prevádzkuje pomocou komunikácie s NTP serverom. Na monitorovanie intenzity svetla sa používa odporový snímač so zabudovaným fototranzistorom.

English: 
A project for ESP32 that monitors real-time and light intensity. Real-time monitoring is operated via communication with an NTP server. A resistive sensor with a built-in phototransistor is used to monitor light intensity.

Popis práce: 
Doska ESP32 je nadradená doska, ktorá komunikuje s aplikáciu vytvorenou v prostredí Blynk. K doske ESP32 je pripojený senzor svetla, ktorý má v sebe zabudovaný fototranzistor, ktorý pri zmene intenzity svetla mení na výstupe úroveň napätia od 0-3.3V. Túto hodnotu meriame na ADC prevodníku a následne je prepočítaná na percentá, ktoré si posielame do aplikácie, aby sme mohli byť informovaní. Doska ESP32 má v sebe integrované dva stavy pomocou ktorých spíname výstupne piny, ktorými prepíname riadiacu logiku v Arduino Mega. Arduino Mega má možnosť riadenia až 54 výstupných pinov, ktorými sa riadia svetla simulujúce križovatku. Keďže doska ESP32 má 3.3V riadiacu logiku a Arduino Mega 5V ich prepojenie nie je možne realizovať iba na digitálnom čítaní pinov, preto Arduino Mega si číta analógovú hodnotu, ak jeho hodnota presiahne 500 berieme ju ako za logickú jednotku. Svetelná križovatka má dva hlavne stavy: Buď je noc alebo deň. Počas dňa sa križovatka riadi ako klasická križovatka v meste, po dosiahnutí 20 hodiny sa križovatka prepína do nočného stavu kedy sa predpokladá, že premávka je znížená a len blikajú oranžové svetlá. Druhý komunikačný stav z ESP32 sa využíva na zapínanie verejného osvetlenia. Po nameraní nízkej hodnoty okolitého svetla sa vyšle signál, ktorý rozsvieti verejné svetlo. Zvolili sme riadenie podľa snímača intenzít svetla, lebo je to inteligentná forma riadenia oproti len nastavovaniu pevne fixného času. 
