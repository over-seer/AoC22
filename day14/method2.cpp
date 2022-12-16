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

class Cave
{
public:
  deque<deque<bool>> points;
  int xmin=std::numeric_limits<int>::max();
  int xmax=std::numeric_limits<int>::min();
  int ymin=std::numeric_limits<int>::max();
  int ymax=std::numeric_limits<int>::min();
  void insert(int i, int j,bool b)
  {

    if(points.size()==0)
      points.push_back({true});
    else
    {
      if(j>ymax)
        for(int y=ymax; y<j; y++)
          points.push_back(deque<bool>(xmax-xmin+1,false));
      else if(j<ymin)
        for(int y=j; y<ymin; y++)
          points.push_front(deque<bool>(xmax-xmin+1,false));
      if(i>xmax)
        for(auto & d : points)
          for(int x=xmax; x<i; x++)
            d.push_back(false);
      else if(i<xmax)
        for(auto & d : points)
          for(int x=i; x<xmin; x++)
            d.push_front(false);
    }
    
    xmin=min(xmin,i);
    xmax=max(xmax,i);
    ymin=min(ymin,j);
    ymax=max(ymax,j);
    points[j-ymin][i-xmin]=b;
  }
  bool operator()(int i, int j)
  {
    if(i<xmin || i > xmax || j < ymin || j > ymax) return false;
    else return points[j-ymin][i-xmin];
  }

  void print()
  {
    cout << "  ";
    for(int i=xmin;i<=xmax;i++)
      cout << i%10;
    cout << endl;
    for(int j=ymin;j<=ymax;j++)
    {
      cout << j%10 << " ";
      for(int i=xmin;i<=xmax;i++)
      {
        if(points[j-ymin][i-xmin]) cout << "#";
        //if((*this)(i,j)) cout << "#";
        else cout << ".";
      }
      cout << "\n";
    }
  }
};

Cave get_rocks(string fn)
{
  auto ip = read_ip(fn);
  Cave rocks;
  for(auto s : ip)
  {
    stringstream ss(s);
    string word;
    int x0=-1;
    int y0=-1;
    while(ss >> word)
    {
      array<int,2> ab;
      if(word != "->")
      {
        int x1,y1;
        sscanf(word.c_str(),"%d,%d",&x1,&y1);
        if(x0!=-1 && y0!=-1)
        {
          //cout << x0 << "," << y0 << "--->"<<x1<<","<<y1<<endl;
          for(int x=min(x0,x1);x<=max(x0,x1);x++)
            for(int y=min(y0,y1);y<=max(y0,y1);y++)
              rocks.insert(x,y,true);
        }
        x0=x1;
        y0=y1;
      }
    }
  }
  return rocks;
}

bool drop(Cave & cave, const int floor, const int i0, const int j0)
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
      cave.insert(i,j,true);
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
      cave.insert(i,j,true);
      if(i==i0 && j==j0) blocked = true;
      //cout << i << "," << j << " landed!\n";
    }
  }

  return blocked;
}

void play(string fn)
{
  auto rocks=get_rocks(fn);
  rocks.insert(500,0,false);

  rocks.print();

  size_t sum=1;

  int floor = rocks.ymax+2;

  while(!drop(rocks,floor,500,0))
    sum++;

  rocks.print();

  cout << fn << " part 2 = " << sum << endl;
}

int main()
{
  play("input.txt");
  play("test.txt");

  //Cave c;
  ///c.insert(3,5);
  //c.insert(7,9);

  //cout << string(c(3,5)? "true" : "false") << endl;
  //cout << string(c(3,7)? "true" : "false") << endl;
  //cout << string(c(4,8)? "true" : "false") << endl;
  //cout << string(c(7,9)? "true" : "false") << endl;
  //c.print();

  return 0;
}
