/*
 * Nome: Michele
 * Cognome: Viotto
 * Classe: 3A ITT
 * Data: 16/01/2018
 * Titolo: Tris
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

//variabili globali
char tris[3][3];
bool turno=true; //true: giocatore A; false: giocatore B
bool error=false; // true quando c'è un errore
int codice_errore; // contiene il codice dell'errore che si verifica
bool win=false; // segnala se c'è una vittoria
bool winner; //true: giocatore A; false: giocatore B

//funzioni
//stampa dei messaggi all'avvio del programma
void inizio(){
    cout << "BENVENUTO AL GIOCO TRIS" << endl << endl << endl << endl;
    cout << "Giocatore A: X" << endl;
    cout << "Giocatore B: O" << endl;
    cout << endl;
    cout << "Press enter to continue...";
    getchar();
    system("clear");
}

//resetta il Tris
void resetTris(){
    for(int i=0; i<3; i++){
        for(int k=0;k<3; k++){
            tris[i][k] = 'M';
        }
    }
}

//stampa il tris
void stampaTris(){
    for(int i=0; i<3; i++){
        cout << " ";
        for(int k=0;k<3; k++){
            if(tris[i][k] == 'M'){ // sostituisce le M con uno spazio (SOLO PER LA STAMPA)
                cout << " " << " | ";
            } else {
                cout << tris[i][k] << " | ";
            }
        }
        cout << endl;
    }
}

//stampa l'errore
void printErrorCode(int codice_errore){
    switch(codice_errore){
        case 0:
            cout << "ERRORE: Casella piena" << endl;
            break;
        case 1:
            cout << "ERRORE: Riga non esistente" << endl;
            break;
        case 2:
            cout << "ERRORE: Colonna non esistente" << endl;
            break;
    }
    cout << "Press enter to continue...";
    getchar();
    cout << endl;
}

//aquisisce la colonna da tastiera
int getColonna(){
    int c;
    do{
        cout << "Inserisci colonna: ";
        cin >> c;
    } while (c < 1 && c > 3);
    c--;
    return c;
}

//aquisisce la riga da tastiera
int getRiga(){
    int r;
    do{
        cout << "Inserisci riga: ";
        cin >> r;
    } while (r < 1 && r > 3);
    r--;
    return r;
}

//controlla se la riga e la colonna inserite sono valide
bool controllaInserimento(int riga, int colonna){
    bool ok;
    if(riga >= 0 && riga <= 2){
        if(colonna >= 0 && colonna <= 2){
            if(tris[riga][colonna] == 'M'){
                ok = true;
            } else {
                ok = false;
                error=true;
                codice_errore=0;
            }
        } else {
            ok = false;
            error=true;
            codice_errore=2;
        }
    } else {
        ok = false;
        error=true;
        codice_errore=1;
    }
    return ok;
}

// controlla chi vince
bool vittoria(){
    // GIOCATORE A(X)
    int x=0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tris[j][i] == 'X'){
                x++;
            }
        }
        if (x<3)
            x=0;
    }

    if (x==3){ // vittoria A con una colonna
        win = true;
        winner = true;
        return win;
    } else {
        x=0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tris[i][j] == 'X'){
                    x++;
                }
            }
            if (x<3)
                x=0;
        }
        if (x==3) { //vittoria A con una riga
            win = true;
            winner = true;
            return win;
        }
    }

    if (x==0){
        for (int i = 0; i < 3; i++) {
            if (tris[i][i] == 'X'){
                x++;
            }
        }
        if (x==3) { // vittoria A con la diagonale principale
            win = true;
            winner = true;
            return win;
        }
        else
            x=0;
    }

    if (x==0){
        for (int i = 0; i < 3; i++) {
            for (int j = 2; j >= 0; j--) {
                if (i+j==2) {
                    if (tris[i][j] == 'X') {
                        x++;
                    }
                }
            }
        }
        if (x==3) { // vittoria A con la diagonale secondaria
            win = true;
            winner = true;
            return win;
        }
    }
    // GIOCATORE B(O)
    int o=0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tris[j][i] == 'O'){
                o++;
            }
        }
        if (o<3)
            o=0;
    }

    if (o==3){ // vittoria B con una colonna
        win = true;
        winner = false;
        return win;
    } else {
        o=0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tris[i][j] == 'O'){
                    o++;
                }
            }
            if (o<3)
                o=0;
        }
        if (o==3) { //vittoria B con una riga
            win = true;
            winner = false;
            return win;
        }
    }

    if (o==0){
        for (int i = 0; i < 3; i++) {
            if (tris[i][i] == 'O'){
                o++;
            }
        }
        if (o==3) { // vittoria B con la diagonale principale
            win = true;
            winner = false;
            return win;
        }
        else
            o=0;
    }

    if (o==0){
        for (int i = 0; i < 3; i++) {
            for (int j = 2; j >= 0; j--) {
                if (i+j==2) {
                    if (tris[i][j] == 'O') {
                        o++;
                    }
                }
            }
        }
        if (o==3) { // vittoria B con la diagonale secondaria
            win = true;
            winner = false;
            return win;
        }
    }
}

//gestisce le varie parti del gioco unendole insieme creando il gioco
void gioco(){
    int riga, colonna;
    bool controllo_inserimento;
    for(int turni=0; turni<9; turni++){
        if(turno){
            stampaTris();
            cout << "Turno: " << turni+1 << endl;
            cout << "Turno giocatore A(X)" << endl;
            riga = getRiga();
            colonna = getColonna();
            controllo_inserimento = controllaInserimento(riga, colonna);
            if(controllo_inserimento){
                tris[riga][colonna] = 'X';
                turno=false;
            } else {
                printErrorCode(codice_errore);
                turni--;
                turno=true;
            }
        } else {
            stampaTris();
            cout << "Turno: " << turni+1 << endl;
            cout << "Turno giocatore B(O)" << endl;
            riga = getRiga();
            colonna = getColonna();
            controllo_inserimento = controllaInserimento(riga, colonna);
            if(controllo_inserimento){
                tris[riga][colonna] = 'O';
                turno=true;
            } else {
                printErrorCode(codice_errore);
                turni--;
                turno=false;
            }
        }

        if(!error){
            system("clear");
        }
        error=false;
        vittoria();
        if (win){ // finisce il gioco
            turni=9;
        }
    }
}

//main function
int main(){

    inizio();
    resetTris();
    gioco();

    if(!win){
        cout << "Nessun vincitore..." << endl << endl;
    } else {
        if (winner){
            cout << "Vincitore: giocatore A(X)" << endl << endl;
        } else {
            cout << "Vincitore: giocatore B(O)" << endl << endl;
        }
    }

    cout << "Press enter to continue...";
    getchar();
    return 0;
}

/*
ERROR CODE
0: Casella già occupata
1: Riga non esistente
2: Colonna non esistente
*/
