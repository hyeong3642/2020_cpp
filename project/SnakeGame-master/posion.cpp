#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

class Stage{ //main 화면 부터 stage까지 생성.
public:
  int sx, sy; //stage window 생성 위치
  int s1_h, s1_w; //stage1의 가로 세로 길이
  //Window Function
  Stage();
  void InitHome();// 처음 시작화면(윈도우 생성)
  void Stage_1(); // First Stage
};

class Snake{
public:

  int set_x, set_y; // Snake 생성 좌표 지정.
  int min_len = 3;
  int max_len = 12; // Snake 최소 최대 길이 지정.
  vector <pair<int, int> > body; //Snake의 몸 좌표 저장. 0(head) ~ -1(tail)
  int item_pos[3][4] = {0}; //grow item이 생성 될 좌표를 저장할 배열.(poison or grow)
  int item_n = 0; //grow 의 개수
  int itemType = 0;
  char item_shape[2] = {'5', '6'};
  int h, w;

  char map[1][30][61] = {
    {"211111111111111111111111111111111111111111111111111111111112",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000001111111111000000000000000000000000111111111100000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000011111111110000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000001111111111000000000000000000000000111111111100000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000011111111110000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000001111111111000000000000000000000000111111111100000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000011111111110000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000001111111111000000000000000000000000111111111100000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000011111111110000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000001111111111000000000000000000000000111111111100000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "100000000000000000000000000000000000000000000000000000000001",
    "211111111111111111111111111111111111111111111111111111111112"}
  };
  // 추후 추가 할 변수 목록
  // poison item의 좌표와 개수;
  // Score 변수
  // wall에 생성될 portal 관련 변수
  // 기타 등등


  //Snake Function
  Snake(int y, int x, int h, int w); //생성자.
  void ShowSnake(int stage_num); // 뱀 화면에 출력.

  //Item Function 인자에 따라 Grow인지 Poison인지 구분.
  void SpawnItem(int stage_num); // item 생성.
  void DelItem(int stage_num, int h, int w); //  item 시간이 지났는지 체크 후 삭제.
  bool GetItem(int f, int s); // item 먹음.
  bool diffItem(int f, int s);
  //Check Function
  bool CrushBody(int stage_num); // Snake의 head가 Body에 닿았는지 체크.
  bool UnableItem(int stage_num, int p1, int p2); // 아이템이 생성 가능한 지 확인.

  void UpdateSnake();// 꼬리부터 머리까지 움직이는 방향으로 좌표 최신
  void Game(WINDOW* w1, int stage_num);// 게임 시작!
};

Snake::Snake(int y, int x, int height, int width):set_y(y), set_x(x), h(height), w(width){//생성자
  for(int i=0; i<3; i++){
      body.push_back(make_pair(set_y, set_x-i));} // 뱀 위치, 크기 초기화
}
void Snake::ShowSnake(int stage_num){
  map[stage_num][body[0].first][body[0].second] = '3';
  for(int i = 1; i < body.size(); i++){
    map[stage_num][body[i].first][body[i].second] = '4';}
}
//아이템 생성 , t(타입)이 grow인지 poison인지 구분
void Snake::SpawnItem(int stage_num){
  //t가 1이면 grow아이템 t가 0이면 poison 아이템
  srand((unsigned int)time(0)); // 시드값으로 현재의 시간 초 입력.
  item_n = rand()%3; // 아이템 개수 1~3개 정하기.
  for(int i = 0; i <= item_n; i++){
    do{
    itemType = rand()%2;
    item_pos[i][0] = (rand()%(h)) + 1;
    item_pos[i][1] = (rand()%(w)) + 1;
    item_pos[i][3] = itemType;
  }while(!(UnableItem(stage_num, item_pos[i][0], item_pos[i][1]))) ;// 만일 임의의 좌표에 아이템 생성 불가시.
    item_pos[i][2] = time(0);
  }
  // 생성할 아이템 개수만큼 만들어질 좌표 정해주고 생성 시간 저장.
  // 만약 만들어질 좌표에 이미 무언가 있다면 다시 좌표 지정.
  //생성된 좌표에 따라 아이템 생성.
  for(int i=0; i<=item_n; i++){
    map[stage_num][item_pos[i][0]][item_pos[i][1]] = item_shape[item_pos[i][3]];
  }
}

void Snake::DelItem(int stage_num, int h, int w){
  if(time(0) - item_pos[0][2] > 12){
    for(int i=0; i<=item_n; i++){map[stage_num][item_pos[i][0]][item_pos[i][1]] = '0';}
  SpawnItem(stage_num);}
}
    // 만약 t 타입의 아이템이 생성된지 5초가 지났다면 지워버리고 true return
    // 아니라면 false return

bool Snake::GetItem(int f, int s){ // item 먹음.
  for(int i=0; i<=item_n; i++){
    if(f == item_pos[i][0] && s == item_pos[i][1]){
        return true;
    }
  }
  return false;
}

bool Snake::diffItem(int f, int s){
  if(map[0][f][s] == item_shape[0]){
    return true;
  }else if(map[0][f][s] == item_shape[1]){
    return false;
  }
}
//Check Function
bool Snake::CrushBody(int stage_num){ // Snake의 head가 Body에 닿았는지 체크.
  if(body.size() < 3){return true;}
  if(map[stage_num][body[0].first][body[0].second] == '1'){
    return true;
  }
  for(int i=1; i<body.size(); i++){
    if(body[0].first == body[i].first && body[0].second == body[i].second)
      return true; }
  return false;
}

bool Snake::UnableItem(int stage_num, int p1, int p2){ // 아이템이 생성 가능한 지 확인.
  if(map[stage_num][p1][p2] != '0'){
    return false;}
  return true;
}
void Snake::UpdateSnake(){ //진행방향으로 Snake 꼬리부터 머리쪽으로 이동해줌.
  for(int i=body.size() - 1; i>0; i--){
      body[i].first = body[i-1].first;
      body[i].second = body[i-1].second;}
}
void Snake::Game(WINDOW* w1,int stage_num){
  int d = KEY_RIGHT; // Snake 진행방향
  int old_d = 3;// Snake 이전 진행방향
  int q = 0;
  SpawnItem(stage_num);
  while(1){
    DelItem(stage_num, h, w); // 아이템 삭제 조건 충족 시 삭제 후 재 생성

    d = wgetch(w1);
    flushinp();
    usleep(200000);

    //꼬리 자르기
    map[stage_num][body.back().first][body.back().second] = '0';

    //키 입력 -> 좀 더 단순화 가능 할 듯, 고안해보기.
    //추측이지만 특수키입력에도 정수가 있는듯, KEY_ENTER가 10이듯, 그걸 사용하면 스위치 하나 없앨 수 있지 않을까?
    // 이 부분 단순화 후 함수로 다시 정리하기.
    switch(d)
    {
    case KEY_UP:
      if(old_d == 2){q = 1;}
      old_d = 1;
      break;
    case KEY_DOWN :
      if(old_d == 1){q = 1;}
      old_d = 2;
      break;
    case KEY_RIGHT :
      if(old_d == 4){q = 1;}
      old_d = 3;
      break;
    case KEY_LEFT :
      if(old_d == 3){q = 1;}
      old_d = 4;
    }


    switch(old_d){
      case 1:
        if(GetItem(body[0].first - 1, body[0].second)){
          if(diffItem(body[0].first -1, body[0].second)){
            body.insert(body.begin(),(make_pair(body[0].first - 1, body[0].second)));
          }else{
            UpdateSnake();
            body[0].first -= 1;
            map[stage_num][body.back().first][body.back().second] = '0';
            body.pop_back();
          }
        }else{
          UpdateSnake();
          body[0].first -= 1;
        }
        break;
      case 2:
      if(GetItem(body[0].first + 1, body[0].second)){
        if(diffItem(body[0].first +1, body[0].second)){
          body.insert(body.begin(),(make_pair(body[0].first + 1, body[0].second)));
        }else{
            UpdateSnake();
            body[0].first += 1;
            map[stage_num][body.back().first][body.back().second] = '0';
            body.pop_back();
        }
      }else{
          UpdateSnake();
          body[0].first += 1;
        }
        break;
      case 3:
      if(GetItem(body[0].first, body[0].second + 1)){
        if(diffItem(body[0].first , body[0].second + 1)){
          body.insert(body.begin(),(make_pair(body[0].first, body[0].second + 1)));
        }else{
          UpdateSnake();
          body[0].second += 1;
          map[stage_num][body.back().first][body.back().second] = '0';
          body.pop_back();
        }
      }else{
          UpdateSnake();
          body[0].second += 1;
        }
        break;
      case 4:
      if(GetItem(body[0].first, body[0].second - 1)){
        if(diffItem(body[0].first , body[0].second) - 1){
          body.insert(body.begin(),(make_pair(body[0].first, body[0].second -1)));
        }else{
          UpdateSnake();
          body[0].second -= 1;
          map[stage_num][body.back().first][body.back().second] = '0';
          body.pop_back();
        }
      }else{
          UpdateSnake();
          body[0].second -= 1;
        }
      }
      q = CrushBody(stage_num);
      if(q == 1){break;}
      ShowSnake(stage_num);
        for(int i = 0; i < h; i++){
    		    for(int j = 0; j < w; j++){
              switch(map[0][i][j]){
                case 48:
                  mvwaddch(w1, i, j, ' ');
                  break;
                case 49:
                  mvwaddch(w1, i, j, 'W');
                  break;
                case 50:
                  mvwaddch(w1, i, j, 'I');
                  break;
                case 51:
                  mvwaddch(w1, i, j, 'H');
                  break;
                case 52:
                  mvwaddch(w1, i, j, 'B');
                  break;
                case 53:
                  mvwaddch(w1, i, j, 'G');
                  break;
                case 54:
                  mvwaddch(w1, i, j, 'P');
                  break;
                case 55:
                  mvwaddch(w1, i, j, 'R');
                }
    			 }
         }

    wrefresh(w1);
  }
}
Stage::Stage(){ // 생성자.
  sx = 5; sy = 5;
  s1_h = 30; s1_w = 60;
}
void Stage::InitHome(){
  int key;

  initscr(); // 처음 Main 화면 생성.

  keypad(stdscr, TRUE); // 특수키 입력 가능.
  curs_set(0); // cursor 안 보이게.
  noecho(); // 입력 값 출력 안 되게 하기.

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_WHITE); // 배경이 white, 글씨가 green

  bkgd(COLOR_PAIR(1)); // pair 1의 색으로 배경 색칠

  mvprintw(3, 4, "Test Game -> prees enter key");

  border('|','|','-','-','0','0','0','0');
  refresh();

  key = getch();
  switch(key){ // ENTER입력 시 sTAGE1 실행
    case 10:
      Stage_1();
  }
  mvprintw(3, 4, "EndGame , press anykey -> shutdown");
  refresh();
  getch();
  endwin();
}

void Stage::Stage_1(){

  WINDOW *s1 = newwin(s1_h, s1_w, sy, sx); //stage1 화면 생성.
  init_pair(2, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(2));
  wbkgd(s1, COLOR_PAIR(2));

  keypad(s1, TRUE);
  nodelay(s1, TRUE); // 입력을 안 받아도 넘어가게 해 주는 함수.

  Snake s(10, 10, s1_h, s1_w); //20, 20위치에 뱀 생성.
  s.Game(s1, 0);
  getch();
  delwin(s1);
}

int main(){
  Stage start;
  start.InitHome();
}
