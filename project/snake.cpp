#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

vector <pair<int, int>> snake;
void game1();

void draw_snake(WINDOW* wsnake){

  noecho();
  curs_set(0);
  keypad(wsnake, TRUE);
  nodelay(wsnake, TRUE);
  cbreak();
  int d;

  for(int i=0; i<6; i++){
    snake.push_back(make_pair(20, 20-i));
  } // 처음 뱀 위치 및 길이 초기화 헤드는 20, 20에 길이는 3이다.

  for(int i=0; i<snake.size(); i++){
    mvwaddch(wsnake, snake[i].first, snake[i].second, '0');}
  wrefresh(wsnake);
  d = KEY_RIGHT;
  int old_d = 0;
  switch(d)
  {

  case KEY_UP:
    old_d = 1;
    break;
  case KEY_DOWN :
    old_d = 2;
    break;
  case KEY_RIGHT :
    old_d = 3;
    break;
  case KEY_LEFT :
    old_d = 4;
  }
  while(1){
    d = wgetch(wsnake);
    mvwaddch(wsnake, snake.back().first, snake.back().second, ' ');

    for(int i=snake.size() - 1; i>0; i--){
      snake[i].first = snake[i-1].first;
      snake[i].second = snake[i-1].second;}

    switch(d)
    {

    case KEY_UP:
      old_d = 1;
      break;
    case KEY_DOWN :
      old_d = 2;
      break;
    case KEY_RIGHT :
      old_d = 3;
      break;
    case KEY_LEFT :
      old_d = 4;
    }
    switch(old_d){
      case 1:
      if(d == KEY_UP){
        for(int i=0; i<snake.size(); i++){
          mvwaddch(wsnake, snake[i].first, snake[i].second, '0');}
        wrefresh(wsnake);
        continue;
      }
        snake[0].first -= 1;
        break;
      case 2:
      if(d == KEY_DOWN){
        for(int i=0; i<snake.size(); i++){
          mvwaddch(wsnake, snake[i].first, snake[i].second, '0');}
        wrefresh(wsnake);
        continue;
      }
        snake[0].first += 1;
        break;
      case 3:
      if(d == KEY_RIGHT){
        for(int i=0; i<snake.size(); i++){
          mvwaddch(wsnake, snake[i].first, snake[i].second, '0');}
        wrefresh(wsnake);
        continue;
      }
        snake[0].second += 1;
        break;
      case 4:
      if(d == KEY_LEFT){
        for(int i=0; i<snake.size(); i++){
          mvwaddch(wsnake, snake[i].first, snake[i].second, '0');}
        wrefresh(wsnake);
        continue;
      }
        snake[0].second -= 1;
    }


    for(int i=0; i<snake.size(); i++){
      mvwaddch(wsnake, snake[i].first, snake[i].second, '0');}
    wrefresh(wsnake);
    usleep(500000);
  }
}

void open(){
  int key;

  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();

  initscr();
  nodelay(stdscr, TRUE);

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_WHITE);

  bkgd(COLOR_PAIR(1));
  attron(COLOR_PAIR(1));
  mvprintw(3, 4, "If you want to play a game, plz prees enter key");
  attroff(COLOR_PAIR(1));

  border('|','|','-','-','0','0','0','0');

  refresh();

  key = getch();
  if(key != KEY_ENTER){
    game1();
  }
  getch();
  endwin();
}

void game1(){

  WINDOW *g1 = newwin(40, 100, 5, 5);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  wbkgd(g1, COLOR_PAIR(2));
  wborder(g1, '@','@','@','@','@','@','@','@');
  wrefresh(g1);

  draw_snake(g1);

  getch();
  delwin(g1);

}
int main()
{
  open();
}
