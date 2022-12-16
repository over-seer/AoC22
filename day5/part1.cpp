#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <cstdio>

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

void parse(vector<deque<char>> & stacks, vector<pair<size_t,size_t> > & moves, string fn, size_t n)
{
  stacks.resize(n);
  auto ip=read_ip(fn);
  for(string s : ip	)
  {
    size_t inum,i1,i2;
    if(sscanf(s.c_str(),"move %u from %u to %u", &inum, &i1, &i2)==3)
    {
      i1--; i2--;
      for(size_t i=0;i<inum;i++)
        moves.push_back({i1,i2});
    }
    else if(s.length()==n*4-1)
      for(size_t i=0;i<n;i++)
      {
        char c = s[1+4*i];
        if(c != ' ')  stacks[i].push_front(c);
      }
  }

}

void move(vector<deque<char>> & stacks, pair<size_t,size_t> m)
{
  stacks[m.second].push_back(stacks[m.first].back());
  stacks[m.first].pop_back();
}

void calc(string fn, size_t n)
{
  vector<deque<char> > stacks;
  vector<pair<size_t,size_t> > moves;
  parse(stacks,moves,fn,n);

  //TEST PRINT
  for(auto m:moves)
    cout << m.first << " -> " << m.second << endl;
  for(auto s : stacks)
  {
    for(char c : s)
      cout << c << " ";
    cout << endl;
  }

  for(auto m : moves)
    move(stacks,m);

  cout << "result for " << fn << " : ";
  for(auto s: stacks)
    cout << s.back();
  cout << " " << endl;
}

int main()
{
  calc("input.txt",9);
  calc("test.txt",3);
  return 0;
}

