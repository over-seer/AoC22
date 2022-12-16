#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> read_ip(string s)
{
  vector<string> ip;
  ifstream ipfile(s);
  string line;
  while(getline(ipfile,line))
    ip.push_back(line);
  return ip;
}

struct Game
{
  int a; int b;
  int result1(){return ((4 + b - a) % 3) * 3 + b;}
  int result2(){return (a + b) % 3 + 1 + (b - 1) * 3;}
};

map<char,int> amap {{'A',1},{'B',2},{'C',3}};
map<char,int> bmap {{'X',1},{'Y',2},{'Z',3}};

vector<Game> read(string filename)
{
  vector<Game> games;
  vector<string> ip = read_ip(filename);
  for(string & s : ip)
    games.push_back({amap.at(s[0]),bmap.at(s[2])});
  return games;
}

void play(string s)
{
  auto games = read(s);
  int total1 = 0;
  int total2 = 0;
  for(auto game : games)
  {
    total1 += game.result1();
    total2 += game.result2();
  }
  cout << s << " Total score based on strategy 1 " << s << " = " << total1 << endl;
  cout << s << " Total score based on strategy 2 " << s << " = " << total2 << endl;
}

int main()
{
  cout << "ADVENT OF CODE DAY 2" << endl;
  play("input.txt");  
  play("test.txt");
  return 0;
}
