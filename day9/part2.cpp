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

void follow(int xh, int yh, int & xt, int & yt)
{
  int dx=xt-xh;
  int dy=yt-yh;
  int x = abs(dx);
  int y = abs(dy);
  int signx = dx<0? -1 : 1;
  int signy = dy<0? -1 : 1;
    
  if(x>1 && y>1)
  {
    xt=xh + signx;
    yt=yh + signy;
  }
  else if(x>1)
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

struct Rope
{
  vector<array<int,2>> knots;
  Rope(size_t n) : knots(n,{0,0}){}

  void move(char c)
  {
    switch(c)
    {
      case 'U':
        knots[0][1]++;break;
      case 'D':
        knots[0][1]--;break;
      case 'R':
        knots[0][0]++;break;
      case 'L':
        knots[0][0]--;break;
      default:
        cout<<"ERROR"<<endl;exit(1);
    }

    for(size_t i=1;i<knots.size();i++)
      follow(knots[i-1][0],knots[i-1][1],knots[i][0],knots[i][1]);    
  }
};

void print(set<array<int,2>> hist)
{
  int minx = 0;
  int maxx = 0;
  int miny = 0;
  int maxy = 0;

  for(auto k : hist)
  {
    if(k[0]>maxx) maxx=k[0];
    if(k[1]>maxy) maxy=k[1];
    if(k[0]<minx) minx=k[0];
    if(k[1]<miny) miny=k[1];

  }
  
  for(int j=miny-1;j<=maxy+1;j++)
  {
    for(int i=minx-1;i<=maxx+1;i++)
      if(hist.find({i,j}) != hist.end()) cout << "#" ;
      else cout << ".";
    cout << endl;
  }
  
}

void part2(string fn,size_t n)
{
  string moves = read_moves(fn);
  Rope rope(n);
  set<array<int,2>> hist;
  hist.insert({0,0});
  for(char c : moves)
  {
    rope.move(c);
    hist.insert(rope.knots.back());
  }

  if(fn!="input.txt")print(hist);
     
  cout << fn << " sum of unique tail positions with " << n << " knots = " << hist.size() << endl;
}



int main()
{
  part2("input.txt",2);
  part2("test.txt",2);

  
  part2("input.txt",10);
  part2("test.txt",10);
  part2("test2.txt",10);

  return 0;
}
