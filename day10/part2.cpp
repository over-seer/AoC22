#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

void print_row(vector<int>::iterator & begin)
{
  for(int i=0; i<40; i++)
  {
    int x1 = begin[i];
    char c = '.';
    for(int x = x1; x<x1+3; x++)
      if(x==i)
      {
        c = '#';
        break;
      }
    cout << c;   
  }
  cout << endl;
}


void day10(string fn)
{
  auto ip = read_ip(fn);
  vector<int> xreg(1,0);
  int x=1;
  for(string s : ip)
  {
    if(s=="noop")
    {
      xreg.push_back(x);
    }
    else
    {
      int dx=0;
      string cmd;
      stringstream ss(s);
      ss >> cmd >> dx;
      xreg.push_back(x);
      xreg.push_back(x);
      x+=dx;
    } 
  }
  xreg.push_back(x);
  
  //Part 1 sum
  int sum=0;
  for(size_t i=20;i<=220;i+=40)
    sum += xreg[i]*i;
  cout << fn << " part 1 sum = " << sum << endl;

  //Part 2 pretty picture
  for(size_t i=0;i<40*6;i+=40) print_row(xreg.begin()+i);
  cout << endl;
  
}


int main()
{
  day10("input.txt");
  day10("test.txt");
  return 0;
}
