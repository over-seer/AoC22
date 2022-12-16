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


map<pair<int,int>,pair<int,int>> get_sensors(string fn)
{
  map<pair<int,int>,pair<int,int>> sensors;
  auto ip = read_ip(fn);
  
  for(auto line : ip)
  {
    pair<int,int> s,b;
    sscanf(line.c_str(),"Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
      &(s.first),&(s.second),&(b.first),&(b.second));
    //sensors.insert(s,b);
    sensors[s]=b;
  }
  return sensors;
}

int manhatten_dist(const pair<int,int> & s, const pair<int,int> & b)
{
  //int diff;
  //diff = abs(s.first - b.first) + abs(s.second - b.second);
  return abs(s.first - b.first) + abs(s.second - b.second);  
}

set<int> no_beacons_for_y(map<pair<int,int>,pair<int,int>> & sensors, int y)
{
  set<int> pts;
  for(auto & sb : sensors)
  {
    auto & s = sb.first;
    auto & b = sb.second;
    int mdiff = manhatten_dist(s,b);
    cout << "Manhatten distance for sensor " << s.first << "," << s.second << " = " << mdiff << endl;
    int abs_dy = abs(y-s.second);
    int dx = mdiff-abs_dy;
    
    for(int x=s.first - dx; x<s.first + dx; x++)
    {
      //pair<int,int> pt = {x,y};
      pts.insert(x);
    }
  }
  return pts;
}


void part1(string fn, int y)
{
  auto sensors = get_sensors(fn);

  auto beaconless_pts = no_beacons_for_y(sensors,y);

  int answer = beaconless_pts.size();

  cout << fn << " Part 1 answer = " << answer << endl;

}

int main()
{
  part1("input.txt",2000000);
  part1("test.txt",10);

  return 0;
}
