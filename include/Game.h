// Autore: Andrea Mutti

#ifndef GAME_H
#define GAME_H

#include <fstream>	// libreria fstream per gestire output su file di log
#include "DefenceGrid.h"
#include "AttackGrid.h"

// Classe per la gestione di una partita di Battaglia navale
// Presenta funzioni virtuali pure, non istanziabile
// Descrive il comportamento base di una partita
class Game{
	public:	
		// Distruttore virtual con chiusura file di log, per evitare perdita di dati
		virtual ~Game(){log_.close();}		
		
		// Metodi getter
		// Ritorna il player iniziale
		int starter(void){return starter_;} 	
		// Utile per il controllo di una nave abbattuta	, true = abbattuta una nave				
		bool ship_went_down(void) const { return ship_went_down_;}	
		// Ritorna il turno attuale del gioco
		int turn(void) const { return turn_;}						
	
	protected:
		// Costruttore protected, non istanziabile ma utilizzabile da classi derivate
		Game(std::string log_file);
		// Costruttore di copia disabilitato
		Game(const Game&) = delete;			
		// Assegnamento di copia disabilitato	
		Game& operator=(const Game&) = delete;	

		// Funzione virtual per il giocatore che inizia
		virtual void select_starter(void);
		// Funzione positioning virtuale pura (ogni classe derivata gestisce il poszionamento navi)
		virtual void positioning(void) = 0;		
		// Funzione virtual per il posizionamento della navi
		virtual void make_move(int s);	

		// Funzioni membro per l'aggiunta della nave nella rispettiva griglia di difesa
		void add_ship(int player, Coord& p, Coord& c, int type);	
		
		// Selezione randomica di una nave tra quelle disponibili per il player
		int select_ship(int player);	
		// Fuoco della corazzata in un punto		
		void fire(int pl, int pos, Coord& c);
		// Spostamento di una nave HelpShip o ExplorationSubmarine
		void move_ship(int pl, int pos, Coord& c);
		// Cura delle navi in un'area 3x3
		void heal(int pl, int pos, Coord& c);	// passaggio di oggetti Coord avvengono per riferimento
		// Radar del sottomarino in un'area 5x5
		void search(int pl, int pos, Coord& c);
		
		// Scrittura su file di log del player iniziale
		void write_log(int player);		
		// Scrittura su file di log delle coordinate delle navi o delle mosse				
		void write_log(std::pair<Coord, Coord>& x);		

		// Controlla la fine della partita
		bool end(bool over);
		// Turno successivo e controlla il limite di turni
		void increment_turn(void);

		// Stampa delle griglie di difesa
		void print_defence(int pl);
		// Stampa della griglie di attacco
		void print_attack(int pl);

		// Variabili d'esemplare protected - accessibili alle classi derivate
		AttackGrid att_grid1_;		// griglia di attacco player 1
		AttackGrid att_grid2_;		// griglia di attacco player 2
		DefenceGrid def_grid1_;		// griglia di difesa player 1
		DefenceGrid def_grid2_;		// griglia di difesa player 2
		bool ship_went_down_;		// variabile di utilità, per una nave abbattuta
		int starter_;				// giocatore iniziale

	private:
		// Funzione membro private, utilizzata solo da funzioni membro di Game
		void titanic(int pl, int pos);		
		// Funzione di stampa delle info del gioco iniziali
		void print_info(void);
		// Variabili d'esemplare private
		int turn_;						// turno corrente
		std::ofstream log_;				// oggetto ofstream per output su file di log
		const int MAX_TURNS = 2000;		// massimo numero di turni per evitare stalli
};

// Namespace di utilità per la gestione di stringa
namespace util{		
	// Conversione di una stringa in maiuscolo, sfruttando il metodo std::toupper(char)
	// Modifica direttamente le stringa in questione, passaggio per riferimento
	void to_upper(std::string& x);		
}

#endif // GAME_H
