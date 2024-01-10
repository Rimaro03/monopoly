# Monopoly
Progetto finale del corso di Laboratorio di Programmazione, UniPD, A.A. 2023-24.
Il progetto è stato svolto dal gruppo composto da: Davide Tonolotto, Filippo Battisti, Leonardo Ongaro.

## Note all'attenzione del docente
### 1. Implementazione dei comandi eseguibili dall'utente
   Il nostro gruppo ha deciso di implementare i comandi lato utente richiesti nella consegna, nel seguente modo:
   - `show`: stampa le informazioni sulla partita: tavola da gioco, lista delle proprietà acquistate dai giocatori e lista dei saldi dei giocatori
   - `show table`: stampa solamente la tavola da gioco
   - `show list`: stampa le proprietà possedute da ogni giocatore
   - `show balances`: stampa i giocatori con i loro saldi.  

In caso sia stato inserito un comando invalido, il programma lo ignora.

## Descrizione delle costanti :
Il progetto dispone di un header di costanti chiamato `rules.h`, allinterno sono presenti:
#### Interi :
   - PLAYER_COUNT : Il numero di giocatori
   - BOARD_SIZE : Il numero di caselle per lato
   - BOXES_PER_ROW : Il numero di caselle per lato esclusa quella in comune
   - BOX_COUNT : Il numero di caselle totali nel tabellone
   - START_PASS_BONUS : Il bonus per il passaggio dal via
   - START_BALANCE : Il quantitativo di fiorini dato a inizio partita
   - ECONOMIC_BOXES_COUNT : Il numero di caselle economiche
   - STANDARD_BOXES_COUNT : Il numero di caselle standard
   - LUXURY_BOXES_COUNT : Il numero di caselle di lusso
   - MAX_BOT_GAME_TURNS : Il numero massimo di turni per una partita di bot
#### Array di interi :
Ad ogniuno di questi array si accede tramite la classe della casella (economico = 0, standard = 1, lusso = 2)
   - TERRAIN_COST : I prezzi dei terreni
   - HOUSE_COST : I prezzi della costruzione di una casa
   - HOTEL_COST : I prezzi della costruzione di un albergo
   - HOUSE_RENT : I prezzi del pernottamento in casa
   - HOTEL_RENT : I prezzi del pernattamento in albergo

## Descrizione degli enum :
### GameType : 
Questo enum rappresenta il tipo di partita:
   - INVALID (-1) : partita non inizializzata.
   - PLAYER_VS_ENTITY (0) : partita human vs computer
   - ENTITY_VS_ENTITY (1) : partita computer vs computer
     
## Descrizione delle classi:
### Game : 
La classe Game è un singleton che gestisce la partita.

#### Variabili private :
   - gameType_ : un enum che definisce il tipo di partita (-1 = non inizializzata, 0 = human vs computer, 1 = computer vs computer)
   - output_ : un oggetto di class Output che gestisce il log.txt della partita
   - table_ : il tabellone
   - human_ : il giocatore umano
   - bots_ : un array di quattro giocatori bot

Il cuore della classe è il metodo `Get` che tiene dentro di se una variabile statica `instance` che rappresenta l'unica istanza della class visto che l'unico costruttore definito è quello privato.
Ogni metodo statico di Game chiamerà tramite `Get().` il metodo relativo di istanza privato nominato "nomeMetodo_Internal(...)".

Per inizializzare una partita si chiama il metodo `Init` che prende come parametro la stringa passata per argomento e esegue le seguenti istruzioni : 
1) Inizializza il generatore di numeri randomici.
2) Assegna a gameType il valore corretto.
3) Inizializza il file di output corretto : pve_game_log per le partite human vs computer e eve_game_log per le partite computer vs computer
4) Se è una partita "Human vs Computer" assegnera al tabellone tre puntatori dall'array dei bot e il puntatore del giocatore umano, in caso contrario assegna tutti e quattro i bot al tabellone.
5) Svolge la decisione per chi inizia il turno.

Dopo aver inizializzato la partita il metodo `Run` gestisce il game loop e una volta terminata la partita espone i vincitori.

La classe Game fornisce anche dei metodi necessari al log sia su console con il metodo `Log`, che printa la stringa passatagli, e `Command`, che esegue il comando passatogli come specificato sopra. 
In più sono presenti anche dei metodi di utility come `GetCoordinate` che restituisce una stringa con le coordinate della posizione passatagli per input e altri due metodi simili : `X` per sapere le ascisse e `Y` per sapere le ordinate.

### Output :
La class Output gestisce il file di log e viene usato per disegnare il tabellone e mostrare possedimenti e bilanci dei giocatori
#### Variabili private :
   - isInitialized_ : serve a sapere se il log di output è stato aperto
   - gameLog_ : il file di output
   - grid : una matrice di stringhe che serve come buffer per stampare il tabellone

Una volta creato un oggetto Output questo deve essere inizializzato, così da sapere che file di output aprire, se il log non è inizializzato verrà lanciato un errore e il programma terminera con il messaggio "Output not initialized!".

Per scrivere nel file di log la classe dispone del metodo `UpdateLog` che aggiorna il file con la riga passatagli come parametro.
Sono disponibili altri tre metodi di output che permettono di :
1) Stampare il tabellone con `PrintTable`.
2) Stampare i possedimenti dei giocatori con `PrintList`.
3) Stampare i bilanci dei giocatori con `PrintBalances`.




   
   
