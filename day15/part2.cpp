#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <cmath>

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


map<pair<int64_t,int64_t>,pair<int64_t,int64_t>> get_sensors(string fn)
{
  map<pair<int64_t,int64_t>,pair<int64_t,int64_t>> sensors;
  auto ip = read_ip(fn);
  
  for(auto line : ip)
  {
    pair<int64_t,int64_t> s,b;
    //sscanf(line.c_str(),"Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
    //  &(s.first),&(s.second),&(b.first),&(b.second));
    string dummy, sx, sy, bx, by;
    stringstream ss(line);
    ss >> dummy >> dummy >> sx >> sy >> dummy >> dummy >> dummy >> dummy >> bx >> by;
    sx=sx.substr(2);sx.pop_back();s.first =atoi(sx.c_str());
    sy=sy.substr(2);sy.pop_back();s.second=atoi(sy.c_str());    
    bx=bx.substr(2);bx.pop_back();b.first =atoi(bx.c_str());
    by=by.substr(2);              b.second=atoi(by.c_str());
  
    //sensors.insert(s,b);
    cout << s.first << "," << s.second << ":" << b.first << "," << b.second << endl;
    sensors[s]=b;
  }
  return sensors;
}

int64_t manhatten_dist(int64_t a1, int64_t a2, int64_t b1, int64_t b2)
{
  return abs(a1-b1) + abs(a2-b2);  
}

int64_t manhatten_dist(const pair<int64_t,int64_t> & s, const pair<int64_t,int64_t> & b)
{
  return manhatten_dist(s.first,s.second,b.first,b.second);  
}

bool ranges_touch(int64_t a1, int64_t a2, int64_t b1, int64_t b2)
{
  a2++;b2++;
  return (a1 <= b2 && a2 >= b1);
}

bool ranges_touch(pair<int64_t,int64_t> r1,pair<int64_t,int64_t> r2)
{
  return ranges_touch(r1.first,r1.second,r2.first,r2.second);
}

class RangeMap
{
public:
  int64_t n;
  set<pair<int64_t,int64_t>> data;
  RangeMap(int64_t sz) : n(sz) {}
  void insert(int64_t x0, int64_t x1)
  {
    bool overlap=false;
    pair<int64_t,int64_t> r0={x0,x1};

    for(auto r : data)
    {
      if(ranges_touch(r,r0))
      {
        r0.first=min(r.first,r0.first);
        r0.second=max(r.second,r0.second);
        data.erase(r);
      }
    }
    data.insert(r0);
  }

  bool operator[](int64_t i)
  {
    for(auto r:data)
      if(i>=r.first && i<=r.second)
        return true;
    return false;
  }

  void print(int x0, int x1)
  {
    for(int i=x0;i<=x1;i++)
      if((*this)[i]) cout << '#';
      else cout << '.';
    cout << endl;
  }

  int64_t size()
  {
    int64_t s=0;
    for(auto r:data)
      s+=r.second-r.first+1;
    return s;
  }

  void print(){print(0,n-1);}
};

class SensorMap
{
public:
  int64_t n;
  vector<RangeMap> ranges;
  
  SensorMap(int64_t sz):n(sz),ranges(sz,RangeMap(sz)){}
  void insert(int64_t y, int64_t x0, int64_t x1)
  {
    x0 = x0<0   ? 0   : x0;
    x1 = x1>n-1 ? n-1 : x1;
    if(y>=0 && y <= n)
      ranges[y].insert(x0,x1);
  }

  void print()
  {
    for(auto & r : ranges)
    {
      r.print();
    }
  }

  void print_remaining_ranges()
  {
    for(int64_t y=0; y<n; y++)
    {
      auto & r = ranges[y];
      bool is_remaining=false;
      if(r.data.size()>0)
      {
        int64_t x = r.data.begin()->first;
        if(x != 0)
        {
          cout << "0 -> " << x-1 << " ";
          is_remaining=true;
        }
        x = (--r.data.end())->second;
        if(x != n-1)
        {
          cout << x+1 << " -> " << n-1 << " ";
          is_remaining=true;
        }
        if(r.data.size()>1)
        {
          is_remaining=true;
          auto it = r.data.begin();
          auto it2 = it;
          ++it2;
          while(it2!=r.data.end())
          {
            x=it->second;
            int64_t x1 = it2->first;
            cout << x+1 << " -> " << x1-1 << " ";
            ++it;
            ++it2;
          }
        }
      }
      else
        cout << "0 -> " << n-1 << " ";
      if(is_remaining) cout << " y = " << y << endl;
    }
  }


};


void eliminate(SensorMap & m,int64_t xo, int64_t yo, int64_t d)
{
  //cout << xo << " , " << yo << "->" <<d << endl;
  for(int64_t y = yo-d;y<=yo+d;y++)
  {
    if(y>=0 && y<m.n)
    {
      int64_t abs_dy = abs(y-yo);
      int64_t abs_dx = abs(d-abs_dy);
      int64_t x1=xo-abs_dx;
      int64_t x2=xo+abs_dx;
      //cout << y << " : " << x1 << "->" << x2 << endl;
      if(x1<=x2)
      {
        m.insert(y,x1,x2);
        //m.print();
      }
    }
    
  }
  //m.print();
}


void part2(string fn, int64_t N)
{
  auto sensors = get_sensors(fn);

  SensorMap m(N);



  for(auto sb : sensors)
  {
    uint64_t d = manhatten_dist(sb.first,sb.second);
    
    cout << "Manhatten distance for sensor " << sb.first.first << "," << sb.first.second << " = " << d << endl;
    eliminate(m,sb.first.first,sb.first.second,d);
    //m.print();
  }

   //m.print();
   m.print_remaining_ranges();
  
}

int main()
{
  RangeMap m(20);
  m.print();
  m.insert(3,5);
  m.print();
  m.insert(7,8);
  m.print();
  m.insert(2,2);
  m.print();
  m.insert(4,12);
  m.print();

  //part1("input.txt",2000000);
  //part1("test.txt",10);
  
  part2("input.txt",4000001);
  part2("test.txt",21);

  return 0;
}
