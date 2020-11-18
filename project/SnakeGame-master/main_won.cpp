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
  vector <pair<int, int>> body; //Snake의 몸 좌표 저장. 0(head) ~ -1(tail)
  int item_pos[2][3][3] = {0}; //grow item이 생성 될 좌표를 저장할 배열.(poison or grow)
  int item_n[2] = {0}; //grow 의 개수
  char item_shape[2] = {'5', '6'};
  int h, w;
  int gate[2][3];

  char map[1][32][63] = {
    {
    "99999999999999999999999999999999999999999999999999999999999999",
    "92111111111111111111111111111111111111111111111111111111111129",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000111111111100000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000111111111100000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000111111111100000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000111111111100000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "92111111111111111111111111111111111111111111111111111111111129",
    "99999999999999999999999999999999999999999999999999999999999999"}
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
  void SpawnItem(int stage_num, int t); // item 생성.
  void DelItem(int stage_num, int t, int h, int w); //  item 시간이 지났는지 체크 후 삭제.
  bool GetItem(int f, int s, int t); // item 먹음.


  //Check Function
  bool CrushBody(int stage_num); // Snake의 head가 Body에 닿았는지 체크.
  bool UnableItem(int stage_num, int p1, int p2); // 아이템이 생성 가능한 지 확인.

  //Gate Function
  int DefineGate(int stage_num, int d, int gatey, int gatex);//게이트위치 정해주기, 좌우 게이트인지 상하 게이트인지 가장자리게이트인지.
  void SpawnGate(int stage_num, int h, int w);
  void DelGate(int stage_num, int h, int w);
  int GetGate(int stage_num, int f, int s); // gate탔는지 안탔는지 체크
  int MoveGate(int stage_num, int d, int gate_idx);// 게이트에 따른 움직임.
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
void Snake::SpawnItem(int stage_num, int t){
  //t가 1이면 grow아이템 t가 0이면 poison 아이템
  srand((unsigned int)time(0)); // 시드값으로 현재의 시간 초 입력.
  item_n[t] = rand()%3; // 아이템 개수 1~3개 정하기.
  for(int i = 0; i <= item_n[t]; i++){
    do{
    item_pos[t][i][0] = (rand()%(h)) + 1;
    item_pos[t][i][1] = (rand()%(w)) + 1;
  }while(!(UnableItem(stage_num, item_pos[t][i][0], item_pos[t][i][1]))) ;// 만일 임의의 좌표에 아이템 생성 불가시.
    item_pos[t][i][2] = time(0);
  }
  // 생성할 아이템 개수만큼 만들어질 좌표 정해주고 생성 시간 저장.
  // 만약 만들어질 좌표에 이미 무언가 있다면 다시 좌표 지정.
  //생성된 좌표에 따라 아이템 생성.
  for(int i=0; i<=item_n[t]; i++){
    map[stage_num][item_pos[t][i][0]][item_pos[t][i][1]] = item_shape[t];
  }
}

void Snake::DelItem(int stage_num, int t, int h, int w){
  if(time(0) - item_pos[t][0][2] > 1){
    for(int i=0; i<=item_n[t]; i++){map[stage_num][item_pos[t][i][0]][item_pos[t][i][1]] = '0';}
  SpawnItem(stage_num, t);}
}
    // 만약 t 타입의 아이템이 생성된지 5초가 지났다면 지워버리고 true return
    // 아니라면 false return

bool Snake::GetItem(int f, int s, int t){ // item 먹음.
  for(int i=0; i<=item_n[t]; i++){
    if(f == item_pos[t][i][0] && s == item_pos[t][i][1])
      return true;}
  return false;
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

int Snake::DefineGate(int stage_num, int d, int gatey, int gatex){
  //parameter
  // d 는 게이트에 진입한 뱀의 진행방향.
  char up, right, left, down; //게이트 기준 상하좌우 체크 하기 위한 변수
  up = map[stage_num][gatey-1][gatex];
  down = map[stage_num][gatey+1][gatex];
  right = map[stage_num][gatey][gatex+1];
  left = map[stage_num][gatey][gatex-1];

  /*
  return 값 정의
  1 : up
  2 : down
  3 : right
  4 : left
  */
  //가장자리게이트인지
  if(up == '9'){return 2;} // 진행방향 아래
  if(down == '9'){return 1;}
  if(right == '9'){return 4;}
  if(left == '9'){return 3;}
  //진행방향 d와 무관하게 맵 안쪽으로 진행방향 나감.


  //진출 방향 상 - 하
  if(right != '0' && left != '0'){
    //기존 진행방향 오른쪽 혹은 아래쪽일 때
    if(d == 3 || d == 2) return 2;
    //기존 진행방향 왼쪽 혹은 위쪽일 때
    if(d == 4 || d == 1) return 1;
  }
  //진출 방향 좌 - 우
  if(up != '0' && down != '0'){
    //기존 진행방향 왼쪽 혹은 위쪽 혹은 아래쪽일 때
    if(d == 1 || d == 2 || d == 4) return 4;
    //기존 진행방향 오른쪽 일 때
    if(d == 3) return 3;
  }

  // 진출 방향이 우, 하 일

  if(up != '0' && left != '0'){
    if(d == 3 || d == 4 || d == 2) return 2;
    if(d == 1) return 3;
  }
  //진출 방향이 좌, 하 일때
  if(up != '0' && right != '0'){
    if(d == 1 || d == 2 || d == 3) return 2;
    if(d == 4) return 4;
  }
  // 진출 방향이 우, 상 일
  if(down != '0' && left != '0'){
    if(d == 1 || d == 4) return 1;
    if(d == 2 || d == 3) return 3;
  }
  // 진출 방향이 좌, 상 일때
  if(down != '0' && right != '0'){
    if(d == 1 || d == 3) return 1;
    if(d == 2 || d == 4) return 4;
  }
}
void Snake::DelGate(int stage_num, int h, int w){
  if(time(0) - gate[0][2] > 100){
    for(int i=0; i<2; i++){
      map[stage_num][gate[i][0]][gate[i][1]] = '1';
  }
  SpawnGate(stage_num, h, w);}
}
void Snake::SpawnGate(int stage_num, int h, int w){
  srand((unsigned int)time(0)); // 시드값으로 현재의 시간 초 입력.

  int h1, w1;
  int h2, w2;
  do{
    h1 = rand()%h;
    w1 = rand()%w;
  }while(map[stage_num][h1][w1] != '1');

  do{
    h2 = rand()%h;
    w2 = rand()%w;
  }while((map[stage_num][h2][w2] != '1') || ((h1 != h2) && (w1 != w2)));

  gate[0][0] = h1;
  gate[0][1] = w1;
  gate[0][2] = time(0);

  gate[1][0] = h2;
  gate[1][1] = w2;
  gate[1][2] = time(0);

  map[stage_num][h1][w1] = '7';
  map[stage_num][h2][w2] = '7';

}
int Snake::GetGate(int stage_num, int f, int s){
  //들어간 게이트가 gate[0] 인지 gate[1]인지 확인
  //[0] 게이트면 2 출력, [1] 게이트면 1 출력.
  if(map[stage_num][f][s] == '7'){
    if(f == gate[0][0] && s == gate[0][1]) return 2;
    else if(f == gate[1][0] && s == gate[1][1])return 1;
  }
    return 0;
}
 // gate탔는지 안탔는지 체크
int Snake::MoveGate(int stage_num, int d, int gate_idx){// 게이트에 따른 움직임.
  body[0].first = gate[gate_idx][0];
  body[0].second = gate[gate_idx][1];
  return DefineGate(stage_num, d, gate[gate_idx][0], gate[gate_idx][1]);
}
void Snake::UpdateSnake(){ //진행방향으로 Snake 꼬리부터 머리쪽으로 이동해줌.
  for(int i=body.size() - 1; i>1; i--){
      body[i].first = body[i-1].first;
      body[i].second = body[i-1].second;}
}
void Snake::Game(WINDOW* w1,int stage_num){
  int d = KEY_RIGHT; // Snake 진행방향
  int old_d = 3;// Snake 이전 진행방향
  int q = 0;
  SpawnItem(stage_num, 0);
  SpawnGate(stage_num, h, w);
  while(1){
    DelItem(stage_num, 0, h, w); // 아이템 삭제 조건 충족 시 삭제 후 재 생성
    DelGate(stage_num, h, w);
    d = wgetch(w1);
    flushinp();
    usleep(250000);

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

    int g;//gate 들어갔는지 체크, 들어갔으면 진출게이트 idx+1 return값 저장
    switch(old_d){
      case 1:
        g = GetGate(stage_num, body[0].first - 1, body[0].second);
        break;
      case 2:
        g = GetGate(stage_num, body[0].first + 1, body[0].second);
        break;
      case 3:
        g = GetGate(stage_num, body[0].first, body[0].second + 1);
        break;
      case 4:
        g = GetGate(stage_num, body[0].first, body[0].second - 1);
    }
    if(g){
      body[1].first = body[0].first;
      body[1].second = body[0].second;
      old_d = MoveGate(stage_num, old_d, g-1);}
    switch(old_d){
      case 1:

        if(GetItem(body[0].first - 1, body[0].second, 0)){//성장 아이템 먹었다면
          body.insert(body.begin(),(make_pair(body[0].first - 1, body[0].second)));
        }
        else{
          UpdateSnake();
          if(g == 0){
            body[1].first = body[0].first;
            body[1].second = body[0].second;}
          body[0].first -= 1;
        }
        break;
      case 2:
        if(GetItem(body[0].first + 1, body[0].second, 0)){//성장 아이템 먹었다면
          body.insert(body.begin(), (make_pair(body[0].first + 1, body[0].second)));
        }
        else{
          UpdateSnake();
          if(g == 0){
            body[1].first = body[0].first;
            body[1].second = body[0].second;}
          body[0].first += 1;
        }
        break;
      case 3:
        if(GetItem(body[0].first, body[0].second + 1, 0)){//성장 아이템 먹었다면
          body.insert(body.begin(),(make_pair(body[0].first, body[0].second + 1)));
        }
        else{
          UpdateSnake();
          if(g == 0){
            body[1].first = body[0].first;
            body[1].second = body[0].second;}
          body[0].second += 1;
        }
        break;
      case 4:
        if(GetItem(body[0].first, body[0].second - 1, 0)){//성장 아이템 먹었다면
          body.insert(body.begin(),(make_pair(body[0].first, body[0].second - 1)));
        }
        else{
          UpdateSnake();
          if(g == 0){
            body[1].first = body[0].first;
            body[1].second = body[0].second;}
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
                  mvwaddch(w1, i, j, '-');
                  break;
                case 50:
                  mvwaddch(w1, i, j, 'X');
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
                  mvwaddch(w1, i, j, 'A');
                  break;
                case 57:
                  mvwaddch(w1, i, j, ' ');
                }
    			 }
         }

    wrefresh(w1);
  }
}
Stage::Stage(){ // 생성자.
  sx = 5; sy = 5;
  s1_h = 32; s1_w = 62;
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
