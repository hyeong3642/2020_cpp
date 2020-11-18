#include <iostream>
#include "Board.h"

Board::Board(int b, int g, int p, int d){
  //mission clear
  //score = s;
  //mission = m;
  body_mission = b;
  grow_mission = g;
  poison_mission = p;
  gate_mission = d;

}

void Board::ScoreBoard(int body, int max_body, int grow, int poison, int gate){
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  wmove(score, 0, 0);
	wattron(score, COLOR_PAIR(3));
  wborder(score, '|','|','-','-','*','*','*','*');
	wbkgd(score, COLOR_PAIR(3));
  mvwprintw(score, 2, 3, " SCORE BOARD");
  mvwprintw(score, 3, 3, " B : %d / %d ",body, max_body);
  mvwprintw(score, 4, 3, " + : %d", grow );
  mvwprintw(score, 5, 3, " - : %d", poison );
  mvwprintw(score, 6, 3, " G : %d ", gate);
	wrefresh(score);
}

bool Board::MissionBoard(int max_body, int grow, int poison, int gate){
  bool clear = true;;
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  wmove(mission, 0, 0);
  wattron(mission, COLOR_PAIR(3));
  wborder(mission, '|','|','-','-','*','*','*','*');
  wbkgd(mission, COLOR_PAIR(3));
  mvwprintw(mission, 2, 3, " MISSION");

  if(max_body >= body_mission)
    mvwprintw(mission, 3, 3, " B : %d  (Clear!)", body_mission );
  else{
    mvwprintw(mission, 3, 3, " B : %d ( X )", body_mission );
    clear = false;}

  if(grow >= grow_mission)
    mvwprintw(mission, 4, 3, " + : %d  (Clear!)", grow_mission );
  else{
    mvwprintw(mission, 4, 3, " + : %d ( X )", grow_mission );
    clear = false;}

  if(poison >= poison_mission)
    mvwprintw(mission, 5, 3, " - : %d  (Clear!)", poison_mission );
  else{
    mvwprintw(mission, 5, 3, " - : %d ( X )", poison_mission );
    clear = false;}

  if(gate >= gate_mission)
    mvwprintw(mission, 6, 3, " G : %d  (Clear!)", gate_mission );
  else{
    mvwprintw(mission, 6, 3, " G : %d ( X )", gate_mission );
    clear = false;}

  wrefresh(mission);
  return clear;
}

void Board::gameover(){
  delwin(score);
  delwin(mission);
}
