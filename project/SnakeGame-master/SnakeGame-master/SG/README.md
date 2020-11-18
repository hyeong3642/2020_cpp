Snake Game 
=

## 구성요소



<li><h3>Class Snake</h3></li>
		<ol> 전반적인 게임의 중추.<br>
		Snake의 움직임, 아이템, 게이트 생성, 화면 출력까지 사실상 모든 것을 담당하고 있음.<br>
		생성자로는 뱀이 초기 생성될 좌표를 받는다.</ol>

<li><h3>Class Board</h3></li>
	<ol> Mission / Score 판을 생성 / 출력
	미션이 클리어 여부를 Boolean type으로 return
	생성자로는 미션 클리어 조건을 받는다.
	ex) 몸 길이 / 아이템 섭취 갯수 / 게이트 갯수
	</ol>

<li><h3>Class Stage</h3></li>
	<ol>초기 시작화면을 구성하고, 게임 진행을 담당한다고 보면 된다.  게임의 시작부터 종료, 스테이지 클리어여부에 따른 게임 종료 및 재시작여부에 따라 게임 진행.

<hr>

## 1단계
> NCurses Library 함수들을 사용하여 2차원 배열로 된 Snake Map을 Game 화면으로 표시하는 프로그램을 완성한다. 그림의 세부사항은 각자 정한다


Snake Class에서 public variable에 char map[4][32][63] 이 있다.

map [ Stage 갯수] [세로 길이 ] [가로 길이] 

출력은 map 변수에 저장되어 있는 값을 토대로 출력.
ShowWin 함수를 사용한다. 

여기서 우리는 0을 빈공간 1 wall 2 immune wall..했다고 말하기 

인자로 들어온 Window에 맵 배열을 읽어서 그에 맞는 문자열 출력해서 맵을 보여주는 것.

```C++
	void Snake::ShowWin(WINDOW* w1, int stage_num){
  for(int i = 0; i < h; i++){
      for(int j = 0; j < w; j++){
        switch(map[stage_num][i][j]){
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
            mvwaddch(w1, i, j, '?');
            break;
          case 57:
            mvwaddch(w1, i, j, ' ');
          }
     }
   }
}
```
<hr>

## 2단계
>1단계의 맵 위에 Snake를 표시하고, 화살표를 입력받아 Snake가 움직이도록
프로그램을 완성한다.
● Snake는 규칙 #1을 준수해야 한다
>> ●  Snake 는 진행방향의 반대방향으
●  Snake 는 자신의 Body를 통과할 수 없다.
● Snake 는 벽(Wall) 을 통과할 수 없다.
● Head 방향 이동은 일정시간(틱)에 의해 이
동한다.


1단계와 유사

1. 맵 위에 Snake 표시?
```C++
Snake::Snake(int y, int x):set_y(y), set_x(x){//생성자
  for(int i=0; i<3; i++){
      body.push_back(make_pair(set_y, set_x-i));} // 뱀 위치, 크기 초기화
}
void Snake::ShowSnake(int stage_num){
  map[stage_num][body[0].first][body[0].second] = '3';
  for(int i = 1; i < body.size(); i++){
    map[stage_num][body[i].first][body[i].second] = '4';}
}
```
생성자로 뱀 만들고 뱀 변수 앞에서부터 읽어서 뱀 있는 맵 좌표에 뱀 있다고 표시.

만들 때 벡터 이용


2. Move Snake

   Snake 움직이는 부분까지는 같이 짜고 했으니까 설명 그냥 패스하겠습니다.
   원래 대강 다 정리해 보려 했는데, 굳이 그럴 필요도 없을 거 같아서. 제 독단으로 짰던 부분에 대해서만 좀 설명 들어갈게요.



## 3단계
>● 2단계 프로그램에서, Map위에 Growth Item와 Poison Item을 출현하도록 수정한다.
● 게임 규칙#2를 준수해야 한다.
● Growth Item과 Poison Item을 Map 배열에 표현할 때 값을 정한다.
>>  규칙 2는 그냥, 랜덤으로 생성하고, 나타났다 사라져야 하며 growth는 진행방향 증가 poison은 꼬리사라짐.
몸 길이 3미만 DIE


### 변수
```C++
int item_pos[3][4] = {0}; 
//item이 생성 될 좌표를 저장할 배열.
//item_pos[아이템 갯수][생성 y좌표, x좌표, 생성시간, 아이템 종류(grow인지 poison인지)]

int item_n = 0; 
// Item 갯수

int itemType = 0;
// Item 종류, Grown / Poison

char item_shape[2] = {'5', '6'};
//Map에 저장, '5' == grow '6' == 'poison'
  ```

### 함수

- SpawnItem
```C++
//인자로 몇 번째 스테이지인지 받아서 그 맵에다가 스폰 된 아이템 저장.
void Snake::SpawnItem(int stage_num){
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
  //생성된 좌표에 따라 아이템 Map 배열에 저장
  for(int i=0; i<=item_n; i++){
    map[stage_num][item_pos[i][0]][item_pos[i][1]] = item_shape[item_pos[i][3]];
  }
}
```
item_n에서 한 번에 나타날 아이템의 개수를 random하게 저장하고
itemType을 이용해서 Growth, Poison인지를 각각 정해줌 
아이템생성가능한 좌표에 지정될 때까지 while문 돌림
for문을 이용해 map에 itemType에 따른 item_shape 입력

- UnableItem
	해당 위치에 아이템 만들 수 있나 확인함.

```C++
bool Snake::UnableItem(int stage_num, int p1, int p2){ // 아이템이 생성 가능한 지 확인.
  if(map[stage_num][p1][p2] != '0'){
    return false;}
  return true;
}
```

설명생략
- DelItem
	시간 지나면 아이템 삭제
```C++
void Snake::DelItem(int stage_num){
  if(time(0) - item_pos[0][2] > 6){
    for(int i=0; i<=item_n; i++){map[stage_num][item_pos[i][0]][item_pos[i][1]] = '0';}
  SpawnItem(stage_num);}
}
    // 만약 아이템이 생성된지 6초가 지났다면 지워버리고 새로운 아이템 생성
```
시간을 비교해서 6초가 지나면 map의 item좌표를 '0'으로 바꿔주고 다시 SpawnItem호출

- GetItem
	아이템 얻었는 지 확인
	(뱀 머리랑 아이템 위치 겹치나 정도.)
```C++
bool Snake::GetItem(int f, int s){ // item 먹음.
  for(int i=0; i<=item_n; i++){
    if(f == item_pos[i][0] && s == item_pos[i][1])
      return true;}
  return false;
}
//vector[0].first == int f
//vector[0].second == int s
```
for문을 이용해 어떤 아이템이 뱀의 머리와 겹치면 return true

- diffItem
	먹은 아이템이 Growth인지 Poison인지 구분
```C++
bool Snake::diffItem(int f, int s, int *gcnt, int *pcnt, int stage_num){
  if(map[stage_num][f][s] == item_shape[0]){
    *gcnt += 1;
    //Board에 표시될 growth Count 증가
    return true;
  }else if(map[stage_num][f][s] == item_shape[1]){
    *pcnt += 1;
    //Board에 표시될 Poison Count 증가
    return false;
  }
}
//전반적인 Logic은 GetItem과 유사.
```
map좌표의 모양과 item_shape비교해서 Growth item이면 Growth counter인 gcnt 1증가, return true
Poison item이면 Poison counter인 pcnt 1증가, return false

- 아이템 섭취 후 Snake변화 
```C++
switch(old_d){
      case 1:
      if(GetItem(body[0].first - 1, body[0].second)){
      // 진행방향에 따른 다음 머리 위치에 아이템이 있다면.
        if(diffItem(body[0].first -1, body[0].second, &Gcount, &Pcount, stage_num)){
        // 먹게 될 아이템이 Grow라면 
          body.insert(body.begin(),(make_pair(body[0].first - 1, body[0].second)));
          // 기존 뱀의 앞부분에 한 칸 추가하고 끝. Grow 해버렸다.
        }else{
        // Poison먹었다면 
          UpdateSnake();
          // 이동방향으로 Tail부터 Head까지 한 칸씩 당겨준다. 그럼 꼬리 하나가 잘렸을 것.
          body[0].first -= 1;
          // Head는 이동방향으로 움직여줌.
          map[stage_num][body.back().first][body.back().second] = '0';
          // vector 내 좌표로는 뱀이 움직였지만 맵 배열에 저장한 값은 안 바뀌어 꼬리가 있으니까
          // 꼬리였던 부분 0 만들어줘서 진짜 안보이게 삭-제
          body.pop_back();
          // 뱀 맨 뒤부분 Pop, Poison먹어서 한 칸 줄은것.
          // 헷갈릴듯 하여 다시 설명 **
          //pop_back 이전까지는 원래 뱀이 움직이는 로직. 뱀이 다 움직일거 움직이고 꼬리 하나 잘랐다고 생각.
        }
 ```

-머리가 진행한 곳에 GetItem을 이용해 아이템이 있는지 확인 true일 경우

	-diffItem을 이용 아이템 판별, true일 경우(Growth item)
	insert를 이용해 '머리 앞부분'에 추가
	
	-diffItem을 이용 아이템 판별, false일 경우(Poison item)
	poison을 먹은 경우 꼬리가 잘리기 때문에 UpdateSnake와 머리를 진행방향으로 진행 후, pop_back
	

 

Game 함수 중 일부 발췌.
주석을 달아 설명

몸 길이 3 미만 사망은 아마 2단계에서 다뤘을것.

## 4단계
>● 3단계 프로그램에서, Map의 Wall의 임의의 위치에 한 쌍의 Gate가 출현할 수 있도록 변경하고, 각 Gate에 Snake가 통과할 수 있도록 수정한다.
● 게임 규칙 #3, #4, #5를 준수해야한다.
● Wall(Immune Wall 포함)과 Gate를 Map 배열에 표현할 때 값을 결정한다.


규칙 ㄹㅇ 개많다. 

규칙 요약
게이트
2개 / 겹치기 ㄴ / wall에서만 / 한번에 한쌍 / 
gate진입중인경우 안사라짐 
규칙 4... 후술
규칙 5 게이트 wall에서만, 벽꿍사
gate출현 방ㅂㅓㅂ 결정

- 변수
```C++
int h, w; 
//현재 맵 크기
int gate[2][3];
// gate[첫번째, 두번째 게이트][y좌표, x좌표, 생성시간]
  ```
- SpawnGate
	조건에 충족하게 게이트 생성, 아이템 만드는 것과 유사함.
```C++
void Snake::SpawnGate(int stage_num, int h, int w){
  srand((unsigned int)time(0)); // 시드값으로 현재의 시간 초 입력.

  int h1, w1; // 게이트 생성할 좌표.
  int h2, w2;
  do{
    h1 = rand()%h;
    w1 = rand()%w;
  }while(map[stage_num][h1][w1] != '1');//생성할 곳으로 잡은 좌표가 벽이 아니라면 다시
  //이 부분이 렉의 가장큰 요인이 아닐까...

  do{
    h2 = rand()%h;
    w2 = rand()%w;
  }while((map[stage_num][h2][w2] != '1') || ((h1 == h2) && (w1 == w2))); 
  //이상동문

  gate[0][0] = h1;
  gate[0][1] = w1;
  gate[0][2] = time(0);
 //변수 설명 참조

  gate[1][0] = h2;
  gate[1][1] = w2;
  gate[1][2] = time(0);
  if(body.size() > 4){
    map[stage_num][h1][w1] = '7';
    map[stage_num][h2][w2] = '7';
  }
  // 몸 길이 4 이상일때만 게이트 생성되는 조건.
}
```

- 규칙 4
	뭐 어떻게 설명하기 힘들다. ppt규칙읽으면서 코드 정독하는 것을 추천...
```C++
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

  if(down == '0' && right == '0'){
    if(d == 3 || d == 4 || d == 2) return 2;
    if(d == 1) return 3;
  }
  //진출 방향이 좌, 하 일때
  if(down == '0' && left != '0'){
    if(d == 1 || d == 2 || d == 3) return 2;
    if(d == 4) return 4;
  }
  // 진출 방향이 우, 상 일
  if(up == '0' && right == '0'){
    if(d == 1 || d == 4) return 1;
    if(d == 2 || d == 3) return 3;
  }
  // 진출 방향이 좌, 상 일때
  if(up == '0' && left == '0'){
    if(d == 1 || d == 3) return 1;
    if(d == 2 || d == 4) return 4;
  }
}

```
한마디로 게이트 탔으면 진행방향 + 나오는 게이트의 진출방향에 따른 향후 이동 방향 결정하는 함수

- DelGate
	gate 삭제, delItem과 유사함.
```C++
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

  if(down == '0' && right == '0'){
    if(d == 3 || d == 4 || d == 2) return 2;
    if(d == 1) return 3;
  }
  //진출 방향이 좌, 하 일때
  if(down == '0' && left != '0'){
    if(d == 1 || d == 2 || d == 3) return 2;
    if(d == 4) return 4;
  }
  // 진출 방향이 우, 상 일
  if(up == '0' && right == '0'){
    if(d == 1 || d == 4) return 1;
    if(d == 2 || d == 3) return 3;
  }
  // 진출 방향이 좌, 상 일때
  if(up == '0' && left == '0'){
    if(d == 1 || d == 3) return 1;
    if(d == 2 || d == 4) return 4;
  }
}
void Snake::DelGate(int stage_num, int h, int w){
  if(time(0) - gate[0][2] > 10){
    for(int i=0; i<2; i++){
      map[stage_num][gate[i][0]][gate[i][1]] = '1';
  }
  if(body.size() > 4) SpawnGate(stage_num, h, w);}
}
```
 - gate Move.
 ```C++
 int Snake::GetGate(int stage_num, int f, int s){
  //들어간 게이트가 gate[0] 인지 gate[1]인지 확인
  //[0] 게이트면 2 출력, [1] 게이트면 1 출력.
  if(map[stage_num][f][s] == '7'){
    if(f == gate[0][0] && s == gate[0][1]) return 2;
    else if(f == gate[1][0] && s == gate[1][1])return 1;
  }
    return 0;
} // 이 함수를 통해 서로 다른 게이트로 각각 진입 진출이  가능함.

 // gate탔는지 안탔는지 체크
int Snake::MoveGate(int stage_num, int d, int gate_idx){// 게이트에 따른 움직임.
  body[0].first = gate[gate_idx][0];
  body[0].second = gate[gate_idx][1];
  return DefineGate(stage_num, d, gate[gate_idx][0], gate[gate_idx][1]);
} //게이트를 탔다면 향후 진행방향 결정해서 리턴
```

- gate 타 있느동안 안 사라지게 하는 법
```C++
  case 4:
        g = GetGate(stage_num, body[0].first, body[0].second - 1);
      }
// 대강 진행 방향으로 가면 게이트를 만난다(GetGate 충족한 경우)

    if(g!=0){ // 다음틱에서 게이트탈 예정.
    
      pass = body.size(); 
	//통과하면서, pass지역변수에 body.size() 넣어준다.
      Gatecount++;//gate 개수 늘려주고~
      UpdateSnake(); //snake몸 땡기고
      old_d = MoveGate(stage_num, old_d, g-1);}
//그리고 좀 지나서 마지막에 움직이러 다 움진인 후에

 
 if(--pass < 0) DelGate(stage_num, h, w);
 // 매 틱마다 pass에서 1씩 빼주고, pass가 0미만일때부터 게이트를 삭제하고, 생성함.
```


## 6단계

```C++
void Stage::Start(int step){
  int now = step;
  int next = now + 1;
  WINDOW *s1 = newwin(s1_h, s1_w, sy, sx); //stage1 화면 생성.
  
  Board b(Goal[step][0], Goal[step][1], Goal[step][2], Goal[step][3]);
  //Stage시작하는 함수인데, Snake 생성하기 직전에 Board를 만들어준다.
  //Goal이라는 변수에 각 스테이지별(Step) 클리어 조건 담겨있다.

  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(2));
  wbkgd(s1, COLOR_PAIR(2));

  keypad(s1, TRUE);
  nodelay(s1, TRUE); // 입력을 안 받아도 넘어가게 해 주는 함수.

  Snake s(10, 10, s1_h, s1_w); //20, 20위치에 뱀 생성.
  

```

```C++
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
```

이 부분은 크게 설명할 게 없는게
그냥 Snake.game하는 도중에
```C++
b.ScoreBoard(body.size(), MaxBody,  Gcount, Pcount, Gatecount);
if(b.MissionBoard(body.size(),  Gcount, Pcount, Gatecount)){
b.gameover();
delwin(w1);
return true;
      ```
     
  한번 틱이 돌면서 아이템을 먹은거나 bodysize의 변화를 반영해서 Score 띄워주고
  bool타입 return하는 Mission은 Board 생성자로 들어온 클리어 조건에 충족했으면 게임 종료하고
  조건 충족되는 틱이 지나면 clear했다고 표시하고, 주석이 별 필요없이 직관적이라 쉽게 이해 가능하실듯...
````


기본적으로 1~6단계 까지 사용되는 함수 정리해드렸읍니다. 이거 토대로 보고서 작성하시면 될 듯하구요, 아마 주요 함수 외에 함수가 있긴한데 약간 곁다리로 들어가는 부분도 한 번 살펴보시고 보고서 화이팅해 주시면 감사하겠습니다..
