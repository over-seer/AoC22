#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

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

struct RangePair
{
  int a1;
  int a2;
  int b1;
  int b2;
  RangePair(string s)
  {
    if(sscanf(s.c_str(),"%d-%d,%d-%d",&a1,&a2,&b1,&b2)!=4)
    {
      cout << "ERROR - cannot parse input string" << endl;
      exit(1);
    }
  }
  bool complete_overlap(){return (a1 >= b1 && a2 <= b2) || (b1 >= a1 && b2 <= a2);}
  bool overlap(){return (a1 <= b2 && a2 >= b1);}
};

void count_instances_of_overlap(string fn)
{
  auto ip = read_ip(fn);
  size_t sum = 0;
  for(const string & s : ip)
  {
    RangePair as(s);
    if(as.overlap())
    {
      sum++;
      cout << "overlap: " << s << endl;
    }
  }
  cout << sum << " overlaps in " << fn << endl;
}

int main()
{
  cout << "ADVENT OF CODE 2022 DAY 4 PART 2" << endl;
  
  count_instances_of_overlap("input.txt");
  count_instances_of_overlap("test.txt");
  return 0;
}