#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <set>

using namespace std;

vector<string> read_ip(string s)
{
  vector<string> lines;
  string line;
  ifstream ip(s);
  while(getline(ip,line))
    lines.push_back(line);
  return lines;
}

string read_moves(string fn)
{
  string moves;
  auto ip = read_ip(fn);
  for(string s : ip)
  {
    char c;
    size_t n;
    stringstream ss(s);
    ss >> c >> n;
    for(size_t i=0;i<n;i++)
      moves.push_back(c);
  }
  return moves;
}

struct Rope
{
  int xh=0;
  int yh=0;
  int xt=0;
  int yt=0;

  void move(char c)
  {
    switch(c)
    {
      case 'U':
        yh++;break;
      case 'D':
        yh--;break;
      case 'R':
        xh++;break;
      case 'L':
        xh--;break;
      default:
        cout<<"ERROR"<<endl;exit(1);
    }
    int dx=xt-xh;
    int dy=yt-yh;
    int x = abs(dx);
    int y = abs(dy);
    int signx = dx<0? -1 : 1;
    int signy = dy<0? -1 : 1;
    
    if(x>1)
    {
      yt=yh;
      xt=xh + signx;
    }
    else if(y>1)
    {
      xt=xh;
      yt=yh + signy;
    }
  }
};

void part1(string fn)
{
  string moves = read_moves(fn);
  Rope rope;
  set<array<int,2>> hist;
  hist.insert({0,0});
  for(char c : moves)
  {
    rope.move(c);
    hist.insert({rope.xt,rope.yt});
  }
  cout << fn << " Part 1 = " << hist.size() << endl;
}

int main()
{
  part1("input.txt");
  part1("test.txt");

  return 0;
}
