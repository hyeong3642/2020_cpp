#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

vector<int> sibal;

vector <pair<int, int>> snake;
void game1();

void goup(){
  snake[0].first +=1;
  for(int i=snake.size() - 1; i>0; i--){
    snake[i].first = snake[i-1].first;
    snake[i].second = snake[i-1].second;}
}
void godown(){
  snake[0].first -=1;
  for(int i=snake.size() - 1; i>0; i--){
    snake[i].first = snake[i-1].first;
    snake[i].second = snake[i-1].second;}
}
void goleft(){
  snake[0].second -=1;
  for(int i=snake.size() - 1; i>0; i--){
    snake[i].first = snake[i-1].first;
    snake[i].second = snake[i-1].second;}
}
void goright(){
  snake[0].second +=1;
  for(int i=snake.size() - 1; i>0; i--){
    snake[i].first = snake[i-1].first;
    snake[i].second = snake[i-1].second;}
}

void draw_snake(WINDOW* wsnake){

  noecho();
  curs_set(0);
  keypad(wsnake, TRUE);
  int old_d = KEY_RIGHT;
  int d;
  for(int i=0; i<6; i++){
    snake.push_back(make_pair(20, 20-i));
  } // 처음 뱀 위치 및 길이 초기화 헤드는 20, 20에 길이는 3이다.

  for(int i=0; i<snake.size(); i++){
    mvwaddch(wsnake, snake[i].first, snake[i].second, '0');}
  wrefresh(wsnake);

  while(1){
    d = wgetch(wsnake);
    mvwaddch(wsnake, snake.back().first, snake.back().second, ' ');
    while(1){
    int sibal2 = getch();
    sibal.push_back(sibal2);
    if(sibal.size() ==1){
      if(sibal2 == KEY_UP){
        goup();
        mvprintw(20,20, "sibal");
        break;
      }
      else if(sibal2 == KEY_DOWN){
        godown();
        break;
      }
      else if(sibal2 == KEY_LEFT){
        goleft();
        break;
      }
      else if(sibal2 == KEY_RIGHT){
        goright();
        break;
      }
    }
    else{
      if(sibal2 == KEY_UP){
        if(sibal[sibal.size()-1]!=KEY_DOWN){
          goup();
          break;
        }
        else{
          endwin();
        }
      }
      else if(sibal2 == KEY_DOWN){
        if(sibal[sibal.size()-1]!=KEY_UP){
          godown();
          break;
        }
        else{
          endwin();
        }
      }
      else if(sibal2 == KEY_LEFT){
        if(sibal[sibal.size()-1]!=KEY_RIGHT){
          goleft();
          break;
        }
        else{
          endwin();
        }
      }
      else if(sibal2 == KEY_RIGHT){
        if(sibal[sibal.size()-1]!=KEY_LEFT){
          goright();
          break;
        }
        else{
          endwin();
        }
      }
    }

    sleep(1);
    }
    wrefresh(wsnake);
  }
}

void open(){
  int key;
  // 특수키 입력을 가능하게 하는 함수
  keypad(stdscr, TRUE);
  // 화면에 커서 설정
  curs_set(0);
  // 화면에 입력 값 안보이게
  noecho();

  initscr();

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_WHITE);

  bkgd(COLOR_PAIR(1));
  attron(COLOR_PAIR(1));
  mvprintw(3, 4, "If you want to play a game, plz prees enter key");
  attroff(COLOR_PAIR(1));

  border('|','|','-','-','0','0','0','0');

  refresh();

  key = getch();
  if(key == KEY_UP){
      mvprintw(4,5, "sibal");
  }

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
  wborder(g1, '@','@','@','@','-','-','-','-');
  wrefresh(g1);

  draw_snake(g1);

  getch();
  delwin(g1);

}
int main()
{
  open();
}
