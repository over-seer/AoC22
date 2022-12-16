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

void part1(string fn)
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
  
  int sum=0;
  for(size_t i=20;i<=220;i+=40)
    sum += xreg[i]*i;
  
  cout << fn << " part 1 sum = " << sum << endl;
  
}





int main()
{
  part1("input.txt");
  part1("test.txt");

  return 0;
}
