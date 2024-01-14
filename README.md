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

   
   
