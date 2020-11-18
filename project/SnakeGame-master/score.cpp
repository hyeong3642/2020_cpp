void Stage::ScoreBoard(){
  initscr();
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	WINDOW *score = newwin(15, 40, 2, 120);
  wmove(score, 0, 0);
	attron(COLOR_PAIR(3));
  wborder(score, '|','|','-','-','*','*','*','*');
	wbkgd(score, COLOR_PAIR(3));
  mvprintw(3, 121, " B : (Current Length) / (Max Length)" );
  mvprintw(6, 121, " + : (Growth Items)" );
  mvprintw(9, 121, " - : (Poison Items)" );
  mvprintw(12, 121, " G : (gate) ");
	attroff(COLOR_PAIR(3));
	wrefresh(score);
  getch();
	delwin(score);
	endwin();
	}
void Stage::Mission(){
  initscr();
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  WINDOW *mission = newwin(15, 40, 19, 120);
  wmove(mission, 0, 0);
  attron(COLOR_PAIR(3));
  wborder(mission, '|','|','-','-','*','*','*','*');
  wbkgd(mission, COLOR_PAIR(3));
  mvprintw(20, 121, " B : " );
  mvprintw(23, 121, " + : " );
  mvprintw(26, 121, " - : " );
  mvprintw(29, 121, " G : ");
  attroff(COLOR_PAIR(3));
  wrefresh(mission);
  getch();
  delwin(mission);
  endwin();
  }
