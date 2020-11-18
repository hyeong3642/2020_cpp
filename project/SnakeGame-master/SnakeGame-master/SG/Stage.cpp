#include <iostream>
#include "Stage.h"

Stage::Stage(){ // 생성자.
  sx = 10; sy = 5;
  s1_h = 32; s1_w = 62;
}
void Stage::InitHome(){
  initscr(); // 처음 Main 화면 생성.

  keypad(stdscr, TRUE); // 특수키 입력 가능.
  curs_set(0); // cursor 안 보이게.
  noecho(); // 입력 값 출력 안 되게 하기.

  start_color();
  Home();
  refresh();
  endwin();
}

void Stage::Start(int step){
  mvprintw(2, 4, "Stage %d", step+1);
  refresh();
  int now = step;
  int next = now + 1;
  WINDOW *s1 = newwin(s1_h, s1_w, sy, sx); //stage1 화면 생성.
  Board b(Goal[step][0], Goal[step][1], Goal[step][2], Goal[step][3]);

  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(2));
  wbkgd(s1, COLOR_PAIR(2));

  keypad(s1, TRUE);
  nodelay(s1, TRUE); // 입력을 안 받아도 넘어가게 해 주는 함수.

  Snake s(10, 10, s1_h, s1_w); //20, 20위치에 뱀 생성.
  WINDOW *msg = newwin(15, 40, 15, 30);
  int k;
  if(s.Game(s1, b, now)){//stage clear
    if(now == 3){//mission all clear
      stage_msg(msg, 2);
      while(!((k=wgetch(msg)) == 'q')){
        flushinp();
        switch(k){
          case '1':
            delwin(msg);
            delwin(s1);
            clear();
            Start(0);}
    }
    delwin(msg);
    delwin(s1);
    clear();
    Home();
  }else{
      stage_msg(msg, 1);
      while(!((k=wgetch(msg)) == 'q')){
        flushinp();
        switch(k){
          case '1':
            delwin(msg);
            delwin(s1);
            clear();
            Start(next);}
    }
    delwin(msg);
    delwin(s1);
    clear();
    Home();}
  }else{ //stage fail
    stage_msg(msg, 3);
    while(!((k=wgetch(msg)) == 'q')){
      flushinp();
      switch(k){
        case '1':
          delwin(msg);
          delwin(s1);
          clear();
          Start(0);}
    }
    delwin(msg);
    delwin(s1);
    clear();
    Home();
  }
}

void Stage::stage_msg(WINDOW* clear, int condition){
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  wmove(clear, 0, 0);
  wattron(clear, COLOR_PAIR(3));
  wborder(clear, '|','|','-','-','*','*','*','*');
  wbkgd(clear, COLOR_PAIR(3));
  if(condition == 1){
    mvwprintw(clear, 3, 4, " MISSION CLEAR!");
    mvwprintw(clear, 4, 4, " NEXT STAGE : 1");
    mvwprintw(clear, 5, 4, " RETURN TO MAIN : 'Q'");
  }
  else if(condition == 2){
    mvwprintw(clear, 3, 4, " ALL Clear Mission!");
    mvwprintw(clear, 4, 4, " RESTART GAME : 1");
    mvwprintw(clear, 5, 4, " RETURN TO MAIN : 'Q'");}
  else if (condition == 3){
    mvwprintw(clear, 3, 4, " MISSION FAIL!");
    mvwprintw(clear, 4, 4, " RESTART GAME : 1");
    mvwprintw(clear, 5, 4, " RETURN TO MAIN : 'Q'");}
  wrefresh(clear);
}


void Stage::Home(){
  WINDOW *h = newwin(52, 140, 0, 0); //create main

  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  attron(COLOR_PAIR(4));
  wbkgd(h, COLOR_PAIR(4));

  keypad(h, TRUE);
  nodelay(h, TRUE); // 입력을 안 받아도 넘어가게 해 주는 함수.


  char art[33][139] =
  {
  "SSSSSSSSSSSSSSS      NNNNNNNN        NNNNNNNN                    AAA                    KKKKKKKKK    KKKKKKK     EEEEEEEEEEEEEEEEEEEEEE   ",
  "SS:::::::::::::::S     N:::::::N       N::::::N                   A:::A                   K:::::::K    K:::::K     E::::::::::::::::::::E ",
  "S:::::SSSSSS::::::S     N::::::::N      N::::::N                  A:::::A                  K:::::::K    K:::::K     E::::::::::::::::::::E",
  "S:::::S     SSSSSSS     N:::::::::N     N::::::N                 A:::::::A                 K:::::::K   K::::::K     EE::::::EEEEEEEEE::::E",
  "S:::::S                 N::::::::::N    N::::::N                A:::::::::A                KK::::::K  K:::::KKK       E:::::E       EEEEEE",
  "S:::::S                 N:::::::::::N   N::::::N               A:::::A:::::A                 K:::::K K:::::K          E:::::E             ",
  " S::::SSSS              N:::::::N::::N  N::::::N              A:::::A A:::::A                K::::::K:::::K           E::::::EEEEEEEEEE   ",
  "  SS::::::SSSSS         N::::::N N::::N N::::::N             A:::::A   A:::::A               K:::::::::::K            E:::::::::::::::E   ",
  "    SSS::::::::SS       N::::::N  N::::N:::::::N            A:::::A     A:::::A              K:::::::::::K            E:::::::::::::::E   ",
  "       SSSSSS::::S      N::::::N   N:::::::::::N           A:::::AAAAAAAAA:::::A             K::::::K:::::K           E::::::EEEEEEEEEE   ",
  "            S:::::S     N::::::N    N::::::::::N          A:::::::::::::::::::::A            K:::::K K:::::K          E:::::E             ",
  "            S:::::S     N::::::N     N:::::::::N         A:::::AAAAAAAAAAAAA:::::A         KK::::::K  K:::::KKK       E:::::E       EEEEEE",
  "SSSSSSS     S:::::S     N::::::N      N::::::::N        A:::::A             A:::::A        K:::::::K   K::::::K     EE::::::EEEEEEEE:::::E",
  "S::::::SSSSSS:::::S     N::::::N       N:::::::N       A:::::A               A:::::A       K:::::::K    K:::::K     E::::::::::::::::::::E",
  "S:::::::::::::::SS      N::::::N        N::::::N      A:::::A                 A:::::A      K:::::::K    K:::::K     E::::::::::::::::::::E",
  "SSSSSSSSSSSSSSS        NNNNNNNN         NNNNNNN     AAAAAAA                   AAAAAAA     KKKKKKKKK    KKKKKKK     EEEEEEEEEEEEEEEEEEEEEE ",
  "                                                                                                                                          ",
  "                                                                                                                                          ",
  "                                                                                                                                          ",
  "                                                                                                                                          ",
  "                                                     Press 'Enter' to Start the Game!!                                                    ",
  "                                                                                                                                          ",
  "                                                                                                                                          ",
  "                                                         Prees 'Q' to End the Game!!                                                      ",
  "                                                                                                                                          ",
  "                                                          1. Start : Stage - 1                                                            ",
  "                                                          2. Start : Stage - 2                                                            ",
  "                                                          3. Start : Stage - 3                                                            ",
  "                                                          4. Start : Stage - 4                                                            ",
  "                                                                                                                                          ",
  "                                                                                                                                          ",
  "                                                                                                                                          "};
  for(int i=0; i<32; i++){
    for(int j=0;j<139; j++){
      mvwaddch(h, i+3, j+3, art[i][j]);
    }
  }

  refresh();
  int key;
  flushinp();
  while(!((key=wgetch(h)) == 'q')){
    flushinp();
  refresh();
  switch(key){ // ENTER입력 시 sTAGE1 실행
    case 10:
      delwin(h);
      clear();
      Start(0);
      break;
    case '1':
      delwin(h);
      clear();
      Start(0);
      break;
    case '2':
      delwin(h);
      clear();
      Start(1);
      break;
    case '3':
      delwin(h);
      clear();
      Start(2);
      break;
    case '4':
      delwin(h);
      clear();
      Start(3);
      break;}

  }
  endwin();
  exit(0);
}
