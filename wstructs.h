#define ng 1000

struct windowarray
{
  char name[50];
  long id;
  int screenx;
  int screeny;
  int posx;
  int posy;
  int desktop;
};

struct expected
{
  int expectedsizex;
  int expectedsizey;
  int expectedx;
  int expectedy;
  int on;
  int correspondingWin;
  int corrWinDistance;
};

struct Transform
{
  int distance;
  int id;
  int eid;
};

extern struct expected ewindows[ng];
extern struct windowarray windows[ng];
extern struct Transform transform[ng];