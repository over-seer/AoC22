#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <array>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <limits>

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

class BMap
{
public:
  set<pair<int,int>> points;
  int xmin=std::numeric_limits<int>::max();
  int xmax=std::numeric_limits<int>::min();
  int ymax=std::numeric_limits<int>::min();
  void insert(int i, int j)
  {
    points.insert({j,i});
    xmin=min(xmin,i);
    xmax=max(xmax,i);
    ymax=max(ymax,j);
  }
  bool operator()(int i, int j){return points.find({j,i}) != points.end();}
  auto begin(){return points.begin();}
  auto end(){return points.end();}
  void print()
  {
    for(int j=0;j<=ymax;j++)
    {
      for(int i=xmin;i<=xmax;i++)
      {
        if((*this)(i,j)) cout << "#";
        else cout << ".";
      }
      cout << "\n";
    }
  }
};

BMap get_rocks(string fn)
{
  auto ip = read_ip(fn);
  BMap rocks;
  for(auto s : ip)
  {
    stringstream ss(s);
    string word;
    int x0=-1;
    int y0=-1;
    while(ss >> word)
    {
      if(word != "->")
      {
        int x1,y1;
        sscanf(word.c_str(),"%d,%d",&x1,&y1);
        if(x0!=-1 && y0!=-1)
        {
          //cout << x0 << "," << y0 << "--->"<<x1<<","<<y1<<endl;
          for(int x=min(x0,x1);x<=max(x0,x1);x++)
            for(int y=min(y0,y1);y<=max(y0,y1);y++)
              rocks.insert(x,y);
        }
        x0=x1;
        y0=y1;
      }
    }
  }
  return rocks;
}

bool drop(BMap & cave, const int floor, const int i0, const int j0)
{
  bool landed = false;
  bool blocked = false;

  int i=i0;
  int j=j0;

  while(!landed)
  {
    if(j + 1 == floor)
    {
      landed=true;
      cave.insert(i,j);
      //cout << i << "," << j << " landed on cave floor!\n";
    }
    else if(!cave(i,j+1)) j++;
    else if(!cave(i-1,j+1))
    {
      i--;
      j++;
      //cout << i << "," << j << " > ";
    }
    else if(!cave(i+1,j+1))
    {
      i++;
      j++;
      //cout << i << "," << j << " > ";
    }
    else
    {
      landed = true;
      cave.insert(i,j);
      if(i==i0 && j==j0) blocked = true;
      //cout << i << "," << j << " landed!\n";
    }
  }

  return blocked;
}

void play(string fn)
{
  auto rocks=get_rocks(fn);

  rocks.print();
  for(auto p : rocks) cout << p.first << "," << p.second << " ";
  cout <<endl;

  size_t sum=1;

  int floor = rocks.ymax+2;

  while(!drop(rocks,floor,500,0))
    sum++;

  cout << fn << " part 2 = " << sum << endl;
}

int main()
{
  play("input.txt");
  play("test.txt");

  return 0;
}
