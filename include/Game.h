#ifndef Game_h
#define Game_h

class Game{
	public:
		virtual ~Game();
		virtual void make_move(int s) = 0;
		int starter(void){return starter_}
		
	protected:
		Game(void);
		void add_ship(int s, std::string p, std::string c, char type);
		virtual void positioning(void) = 0;
		virtual void select_starter(void);
		
	private:
		AttackGrid att_grid1_;
		DefenceGrid def_grid1_;
		AttackGrid att_grid2_;
		DefenceGrid def_grid2_;
		int turn_;
		int starter_;
};



#endif
