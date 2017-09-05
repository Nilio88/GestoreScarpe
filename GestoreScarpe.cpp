//============================================================================
// Name        : GestoreMagazzinoScarpe.cpp
// Author      : Davide Monopoli
/* Programma adatto a gestire un magazzino di scarpe: localizzazione scarpe,visualizzazione scarpe presenti in magazzino,
 * operazioni di  ordinamento delle scarpe secondo il proprio codice identificativo, di odifica del prezzo di base delle scarpe
 * e capacità di aggiungere o rimuovere un paio di scarpe a seconda della richiesta del cliente
 * Il magazzino non può contenere più di 5 marche di scarpe diverse e per ognuna marca non può contenere più di 10 paia
 * Codice identificativo basato su inziale marca di scarpa dello specifico scaffale e un elemento numerico compreso tra 0 e 9
*/

// Copyright   : polib
// Description : Gestore di un magazzino di scarpe 
//============================================================================


#include <iostream>   // inserimento file di intestazione che permette l'introduzione delle funzioni di input ed output
#include <iomanip>    // inserimento file di intestazione che permette l'introduzione di endl(manipolatore di stream) ed setprecision
#include <cstring>    // inserimento file di intestazione che permette l'introduzione di strcpy ed strcmp utili per copia e confronto di stringhe
#include <cstdlib>    // inserimento file di intestazione che permette la generazione di numeri casuali mediante la funzione rand

using std::cin;       // using serve per importare cin,cout,endl,setprecison nel programma senza ripetere volta per volta std 
using std::cout;       
using std::endl;
using std::setprecision;

/* struct utilizzata per rappresentare un paio di scarpe
* struct � un costrutto utilizzare per fornire un nuovo tipo di dato oltre int,float,double e char
* nella struct quando inserisco un nuovo tipo di dato , rispetto ai dati int, float,double e char esso pu� assumere un valore qualsiasi potenzialmente 
*/

struct PaioDiScarpe {
	char codiceIdentificativo[3]; // vettore che contiene il codice identificativo a 2 valori pi� il carattere nullo :/0
	char nome[9]; // vettore di caratteri che contiene il nome di una delle 5 marche diverse
	float prezzo;
	int taglia;
	int sconto;
};

const int paioDiScarpeSize = 10;
// dichiarazione dei vettori di tipo PaioDiScarpe (nuovo tipo di dato della struct) 
PaioDiScarpe scaffaleNike[paioDiScarpeSize];
PaioDiScarpe scaffaleConverse[paioDiScarpeSize];
PaioDiScarpe scaffaleAdidas[paioDiScarpeSize];
PaioDiScarpe scaffaleVans[paioDiScarpeSize];
PaioDiScarpe scaffaleDiadora[paioDiScarpeSize];

void stampaMagazzino();
void applicaSconto(int sconto, char scaffale);
int ricercaBinaria(char *chiave, PaioDiScarpe *scaffale);
void sostituzionePaioDiScarpe(char codiceIdentificativo[3]);
void informazionePaioDiScarpe(char codiceIdentificativo[3]);
void richiestaComando();
//void eliminazionePaioDiScarpe();

int main()
{
	// procedura per inizializzare gli array PaioDiScarpe
	int i;	
	for(i=0; i < paioDiScarpeSize; i++) {
	
		//Inizializzazione dello scaffale delle scarpe di marca Nike
		scaffaleNike[i].codiceIdentificativo[0] = 'N'; // inizializzando il campo della struct, codiceIdentificativo, avente come iniziale 'N' e seguito da un numero da 0 a 9.
		scaffaleNike[i].codiceIdentificativo[1] = '0' + i;
		scaffaleNike[i].codiceIdentificativo[2] = '\0';
		
		//cout <<"scaffaleNike.codiceIdentificativo = " << scaffaleNike[i].codiceIdentificativo<<'\n';	//Scopo di debug
		
		//Inizializzazione dei nomi delle paia di scarpe Nike
		strcpy(scaffaleNike[i].nome, "Nike");	//Inizializzando il campo della struct, nome, con il nome della marca di scarpe.
		
		//Inizializzazione delle taglie delle scarpe Nike
		int tagliaCasuale = rand() % 8 + 37;	//Genera un numero casuale di taglia di scarpe compreso tra 37 e 44.
		scaffaleNike[i].taglia = tagliaCasuale;
		
		//Inizializzazione dei prezzi delle scarpe Nike
		int prezzoCasuale = rand() % 51 + 50;	//Genera un nmero casuale per il prezzo delle paia di scarpe compresto tra 50 e 100 euro.
		scaffaleNike[i].prezzo = prezzoCasuale;
		
		//Inizializzazione dello sconto applicato alle paia di scarpe
		scaffaleNike[i].sconto = 0;
		
		//Inizializzazione dello scaffale delle scarpe di marca Converse
		scaffaleConverse[i].codiceIdentificativo[0] = 'C'; // inizializzando il campo della struct, codiceIdentificativo, avente come iniziale 'N' e seguito da un numero da 0 a 9.
		scaffaleConverse[i].codiceIdentificativo[1] = '0' + i;
		scaffaleConverse[i].codiceIdentificativo[2] = '\0';
		
		//cout <<"scaffaleNike.codiceIdentificativo = " << scaffaleConverse[i].codiceIdentificativo<<'\n';	//Scopo di debug
		
		//Inizializzazione dei nomi delle paia di scarpe Nike
		strcpy(scaffaleConverse[i].nome, "Converse");	//Inizializzando il campo della struct, nome, con il nome della marca di scarpe.
		
		//Inizializzazione delle taglie delle scarpe Nike
		tagliaCasuale = rand() % 8 + 37;	//Genera un numero casuale di taglia di scarpe compreso tra 37 e 44.
		scaffaleConverse[i].taglia = tagliaCasuale;
		
		//Inizializzazione dei prezzi delle scarpe Nike
		prezzoCasuale = rand() % 51 + 50;	//Genera un nmero casuale per il prezzo delle paia di scarpe compresto tra 50 e 100 euro.
		scaffaleConverse[i].prezzo = prezzoCasuale;
		
		//Inizializzazione dello sconto applicato alle paia di scarpe
		scaffaleConverse[i].sconto = 0;
		
		//Inizializzazione dello scaffale delle scarpe di marca Adidas
		scaffaleAdidas[i].codiceIdentificativo[0] = 'A'; // inizializzando il campo della struct, codiceIdentificativo, avente come iniziale 'N' e seguito da un numero da 0 a 9.
		scaffaleAdidas[i].codiceIdentificativo[1] = '0' + i;
		scaffaleAdidas[i].codiceIdentificativo[2] = '\0';
		
		//cout <<"scaffaleNike.codiceIdentificativo = " << scaffaleNike[i].codiceIdentificativo<<'\n';	//Scopo di debug
		
		//Inizializzazione dei nomi delle paia di scarpe Nike
		strcpy(scaffaleAdidas[i].nome, "Adidas");	//Inizializzando il campo della struct, nome, con il nome della marca di scarpe.
		
		//Inizializzazione delle taglie delle scarpe Nike
		tagliaCasuale = rand() % 8 + 37;	//Genera un numero casuale di taglia di scarpe compreso tra 37 e 44.
		scaffaleAdidas[i].taglia = tagliaCasuale;
		
		//Inizializzazione dei prezzi delle scarpe Nike
		prezzoCasuale = rand() % 51 + 50;	//Genera un nmero casuale per il prezzo delle paia di scarpe compresto tra 50 e 100 euro.
		scaffaleAdidas[i].prezzo = prezzoCasuale;
		
		//Inizializzazione dello sconto applicato alle paia di scarpe
		scaffaleAdidas[i].sconto = 0;
		
		//Inizializzazione dello scaffale delle scarpe di marca Vans
		scaffaleVans[i].codiceIdentificativo[0] = 'V'; // inizializzando il campo della struct, codiceIdentificativo, avente come iniziale 'N' e seguito da un numero da 0 a 9.
		scaffaleVans[i].codiceIdentificativo[1] = '0' + i;
		scaffaleVans[i].codiceIdentificativo[2] = '\0';
		
		//cout <<"scaffaleNike.codiceIdentificativo = " << scaffaleNike[i].codiceIdentificativo<<'\n';	//Scopo di debug
		
		//Inizializzazione dei nomi delle paia di scarpe Nike
		strcpy(scaffaleVans[i].nome, "Vans");	//Inizializzando il campo della struct, nome, con il nome della marca di scarpe.
	
		//Inizializzazione delle taglie delle scarpe Nike
		tagliaCasuale = rand() % 8 + 37;	//Genera un numero casuale di taglia di scarpe compreso tra 37 e 44.
		scaffaleVans[i].taglia = tagliaCasuale;
		
		//Inizializzazione dei prezzi delle scarpe Nike
		prezzoCasuale = rand() % 51 + 50;	//Genera un nmero casuale per il prezzo delle paia di scarpe compresto tra 50 e 100 euro.
		scaffaleVans[i].prezzo = prezzoCasuale;
		
		//Inizializzazione dello sconto applicato alle paia di scarpe
		scaffaleVans[i].sconto = 0;
		
		//Inizializzazione dello scaffale delle scarpe di marca Diadora
		scaffaleDiadora[i].codiceIdentificativo[0] = 'D'; // inizializzando il campo della struct, codiceIdentificativo, avente come iniziale 'N' e seguito da un numero da 0 a 9.
		scaffaleDiadora[i].codiceIdentificativo[1] = '0' + i;
		scaffaleDiadora[i].codiceIdentificativo[2] = '\0';
		
		//cout <<"scaffaleNike.codiceIdentificativo = " << scaffaleNike[i].codiceIdentificativo<<'\n';	//Scopo di debug
		
		//Inizializzazione dei nomi delle paia di scarpe Nike
		strcpy(scaffaleDiadora[i].nome, "Diadora");	//Inizializzando il campo della struct, nome, con il nome della marca di scarpe.
		
		//Inizializzazione delle taglie delle scarpe Nike
		tagliaCasuale = rand() % 8 + 37;	//Genera un numero casuale di taglia di scarpe compreso tra 37 e 44.
		scaffaleDiadora[i].taglia = tagliaCasuale;
		
		//Inizializzazione dei prezzi delle scarpe Nike
		prezzoCasuale = rand() % 51 + 50;	//Genera un nmero casuale per il prezzo delle paia di scarpe compresto tra 50 e 100 euro.
		scaffaleDiadora[i].prezzo = prezzoCasuale;
		
		//Inizializzazione dello sconto applicato alle paia di scarpe
		scaffaleDiadora[i].sconto = 0;
	}
	richiestaComando();
	
	return 0; 
}

//Procedura per stampare il contenuto degli array che rappresentano gli scaffali.
void stampaMagazzino() {
	
	cout << "-----Scaffale delle Nike-----" << '\n';
	
	int i;
	for(i = 0; i < paioDiScarpeSize; i++) {
		cout << "ID: " << scaffaleNike[i].codiceIdentificativo << "| Nome: " << scaffaleNike[i].nome << "| Taglia: " << scaffaleNike[i].taglia << "| Prezzo: " << scaffaleNike[i].prezzo << "| Sconto: " << scaffaleNike[i].sconto << '\n';
		
	}
}

/** Procedura per applicare lo sconto alle paia di scarpe di un
  * particolare scaffale dato in input.
*/
void applicaSconto(int sconto, char scaffale) {
	switch (scaffale) {
		case 'N':
			//Applica lo sconto alle paia dello scaffale delle Nike
			int i;
			for (i = 0; i < paioDiScarpeSize; i++) {
				scaffaleNike[i].sconto = sconto;
			}
			cout<<"Sconto eseguito con successo"<<endl;
			break;
			
		case 'A':
			//Applica lo sconto alle paia dello scaffale delle Adidas
			for (i = 0; i <paioDiScarpeSize ; i++) {
				scaffaleAdidas[i].sconto = sconto;
			}
			cout<<"Sconto eseguito con successo"<<endl;
			break;
			
		case 'C':
			//Applica lo sconto alle paia dello scaffale delle Converse
			for (i = 0; i <paioDiScarpeSize ; i++) {
				scaffaleConverse[i].sconto = sconto;
			}
			cout<<"Sconto eseguito con successo"<<endl;
			break;
			
		case 'V':
			//Applica lo sconto alle paia dello scaffale delle Vans
			for (i = 0; i <paioDiScarpeSize ; i++) {
				scaffaleVans[i].sconto = sconto;
			}
			cout<<"Sconto eseguito con successo"<<endl;
			break;
			
		case 'D':
			//Applica lo sconto alle paia dello scaffale delle Diadora
			for (i = 0; i < paioDiScarpeSize; i++) {
				scaffaleDiadora[i].sconto = sconto;
			}
			cout<<"Sconto eseguito con successo"<<endl;
			break;
			
		default:
			//L'utente ha inserito un valore non valido
			cout << "Scaffale non valido." << '\n';
			break;
	}
}

/** Ricerca il paio di scarpe nello scaffale dato in input tramite
  * la ricerca binaria.
*/
int ricercaBinaria(char *chiave, PaioDiScarpe *scaffale) {
	int high = paioDiScarpeSize - 1;
	int low = 0;
	int middle;
	
	while (low <= high) {
		middle = (low + high) / 2;
		
		if (strcmp(chiave, scaffale[middle].codiceIdentificativo) == 0)
			return middle;
		
		else if (strcmp(chiave, scaffale[middle].codiceIdentificativo) < 0)
			high = middle - 1;
		
		else
			low = middle + 1;
	}
	
	return -1;	//la ricerca non ha trovato il paio di scarpe con quel identificativo
}

/* Funzione adatta all'implementazione della ricerca del paio di scarpe ,riconosciuto mediante codice identificativo.
* Si presuppone che nel caso in cui un paio di scarpe ,ricercato mediante il suo codice identificativo, venga venduto
* esso sia immediatamente sostituito con uno stesso paio : cio� con stesso codice identificativo.
* Si inizia nella progettazione di una funzione che dato un codice identificativo richiesto dal cliente, permetta di ricercare e vendere quel paio richiesto 
* e ne permetta la sostituzione immediata nello scaffale dato.
*/
void sostituzionePaioDiScarpe(char codiceIdentificativo[3]){
	int memorizzazione;
	memorizzazione=ricercaBinaria(codiceIdentificativo,scaffaleNike);
	if (memorizzazione==-1)
		memorizzazione=ricercaBinaria(codiceIdentificativo,scaffaleAdidas);
	else {
		cout<<"Inserisci la nuova taglia"<<endl;
		cin>>scaffaleNike[memorizzazione].taglia;
		cout<<"Inserisci il nuovo prezzo"<<endl;
		cin>>scaffaleNike[memorizzazione].prezzo;
		cout<<"Paio sostituito con successo"<<endl;
		return;                                        // il return serve a porre fine alla ricerca una volta identificato il paio di scarpa con il codice selezionato
	}	
	if (memorizzazione==-1)	
		memorizzazione=ricercaBinaria(codiceIdentificativo,scaffaleConverse);
	else {
		cout<<"Inserisci la nuova taglia"<<endl;
		cin>>scaffaleAdidas[memorizzazione].taglia;
		cout<<"Inserisci il nuovo prezzo"<<endl;
		cin>>scaffaleAdidas[memorizzazione].prezzo;
		cout<<"Paio sostituito con successo"<<endl;
		return;
	}
	if (memorizzazione==-1)
		memorizzazione=ricercaBinaria(codiceIdentificativo,scaffaleVans);
	else {
		cout<<"Inserisci la nuova taglia"<<endl;
		cin>>scaffaleConverse[memorizzazione].taglia;
		cout<<"Inserisci il nuovo prezzo"<<endl;
		cin>>scaffaleConverse[memorizzazione].prezzo;
		cout<<"Paio sostituito con successo"<<endl;
		return;
	}
	if (memorizzazione==-1)
		memorizzazione=ricercaBinaria(codiceIdentificativo,scaffaleDiadora);
	else {
		cout<<"Inserisci la nuova taglia"<<endl;
		cin>>scaffaleVans[memorizzazione].taglia;
		cout<<"Inserisci il nuovo prezzo"<<endl;
		cin>>scaffaleVans[memorizzazione].prezzo;
		cout<<"Paio sostituito con successo"<<endl;
		return;
	}
	if (memorizzazione==-1) {
		cout<<"Il paio di scarpe non esiste in magazzino"<<endl;
	
	}
	else{
		cout<<"Inserisci la nuova taglia"<<endl;
		cin>>scaffaleDiadora[memorizzazione].taglia;
		cout<<"Inserisci il nuovo prezzo"<<endl;
		cin>>scaffaleDiadora[memorizzazione].prezzo;
		cout<<"Paio sostituito con successo"<<endl;
	}				
		
}
/* Funzione che dato il codice identificativo mi fornisca indicazioni di taglia,prezzo,sconto,nome del paio di scarpe.
* Funzione tale da dare in output sullo schermo tali informazioni .
*/
void informazionePaioDiScarpe(char codiceIdentificativo[3]){
	int memorizzazione;
	memorizzazione = ricercaBinaria(codiceIdentificativo, scaffaleNike);
        if (memorizzazione == -1){
                memorizzazione = ricercaBinaria(codiceIdentificativo, scaffaleAdidas);
	}
        else {
                cout<<"Nome: "<<scaffaleNike[memorizzazione].nome<<" |Prezzo: "<<scaffaleNike[memorizzazione].prezzo<<" |Sconto: "<<scaffaleNike[memorizzazione].sconto<<"%"<<" |Taglia: "<<scaffaleNike[memorizzazione].taglia<<endl;
		return;
	}
        if (memorizzazione == -1){
                memorizzazione = ricercaBinaria(codiceIdentificativo, scaffaleConverse);
	}
	else {
		cout<<"Nome: "<<scaffaleAdidas[memorizzazione].nome<<" |Prezzo: "<<scaffaleAdidas[memorizzazione].prezzo<<" |Sconto: "<<scaffaleAdidas[memorizzazione].sconto<<"%"<<" |Taglia: "<<scaffaleAdidas[memorizzazione].taglia<<endl;
		return;
	}
	 if (memorizzazione == -1) {
                memorizzazione = ricercaBinaria(codiceIdentificativo, scaffaleVans);
	}
	else {
		cout<<" |Nome: "<<scaffaleConverse[memorizzazione].nome<<" |Prezzo: "<<scaffaleConverse[memorizzazione].prezzo<<" |Sconto: "<<scaffaleConverse[memorizzazione].sconto<<"%"<<" |Taglia: "<<scaffaleConverse[memorizzazione].taglia<<endl;
		return;
	}
	 if (memorizzazione == -1) {
                memorizzazione = ricercaBinaria(codiceIdentificativo, scaffaleDiadora);
	}
	else {
		cout<<" |Nome: "<<scaffaleVans[memorizzazione].nome<<" |Prezzo: "<<scaffaleVans[memorizzazione].prezzo<<" |Sconto: "<<scaffaleVans[memorizzazione].sconto<<"%"<<" |Taglia: "<<scaffaleVans[memorizzazione].taglia<<endl;
		return;
	}
	if (memorizzazione == -1) {
                cout<<"Il paio di scarpa non esiste"<<endl;
	}
	else {
		cout<<" |Nome: "<<scaffaleDiadora[memorizzazione].nome<<" |Prezzo: "<<scaffaleDiadora[memorizzazione].prezzo<<" |Sconto: "<<scaffaleDiadora[memorizzazione].sconto<<"%"<<" |Taglia: "<<scaffaleDiadora[memorizzazione].taglia<<endl;
	}
	
}
/* void eliminazionePaioDiScarpe(){
char codiceIdentificativo[3];
* cout<<"inserisci il codice del paio di scarpe da eliminare"<<endl;
* cin>>codiceIdentificativo;
*/



//Funzione che si interfaccia con l'utente,richiede i comandi da eseguire all'utente.
void richiestaComando(){
	int comando=0;                                                              /* in alternativa al ciclo while � possibile utilizzare la struttura do-while
																				* con la quale effettuo il cin>>comando e lo switch completo ed infine avr�
																				* il controllo col while
																				*/
	while(comando!=4){
		
		cout<<"Quale operazione vuoi eseguire?"<<endl;
		cout<< "1. Rimozione e sostituzione paio di scarpa"<<endl;	
		cout<<"2. Ricerca paio di scarpa per codice e lettura delle sue informazioni "<<endl;
		cout<<"3. Applicare lo sconto"<<endl;
		cout<<"4. Esci"<<endl;
		cout<<"Cmd> ";
		
		cin >> comando;
		
		switch(comando) {
			case 1 :
				char cambio[3];
				cout<<"Inserisci il codice identificativo del paio di scarpe da sostituire"<<endl;
				cin>>cambio;
				sostituzionePaioDiScarpe(cambio);
				break;
			case 2 :
				cout<<"Inserisci il codice identificativo per la ricerca paio di scarpe"<<endl;
				cin>>cambio;
				informazionePaioDiScarpe(cambio);
				break;
			
			case 3:
				int scontoInserito;
				char inizialeScaffale;
				cout<<"Inserire il tipo di sconto da applicare"<<endl;		
				cin>>scontoInserito;
				cout<<"Inserisci lo scaffale(N per Nike,A per Adidas,C per Converse,V per Vans,D per Diadora)";
				cin>>inizialeScaffale;
				applicaSconto(scontoInserito,inizialeScaffale);
				break;
			case 4:
				break;
		 	default:
		 		cout<<"Operazione inesistente"<<endl;
			
		}
	}

}





