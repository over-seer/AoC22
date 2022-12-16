#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

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

vector<size_t> read(string filename)
{
  vector<size_t> cals(1,0);
  vector<string> ip = read_ip(filename);
  for(string & s : ip)
    s.length() > 0 ? cals.back() += atoi(s.c_str()) : cals.push_back(0);
  return cals;
}

void get_max(string s)
{
  auto cals = read(s);
  size_t mx = *max_element(cals.begin(),cals.end());
  cout << "Max in " << s << " = " << mx << endl;
}

void get_max_n(string s,size_t n)
{
  auto cals = read(s);
  //sort(cals.begin(),cals.end());
  //size_t mx = accumulate(cals.end() - n,cals.end(),0);
  size_t mx = 0;
  for(size_t i=0;i<n;i++)
  {
    auto it = max_element(cals.begin(),cals.end());
    mx += *it;
    *it = 0;
  }
  cout << s << " Sum of max " << n << " in " << s << " = " << mx << endl;
}

int main()
{
  cout << "ADVENT OF CODE DAY 1" << endl;
  get_max_n("input.txt",1);  
  get_max_n("test.txt",1);
  get_max_n("input.txt",3);  
  get_max_n("test.txt",3);
  return 0;
}
