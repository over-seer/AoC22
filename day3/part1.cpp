#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

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

int priority(char c)
{
  int p;
  if(c >= 'a' && c <= 'z') p = (int)c - (int)'a' + 1;
  else if (c >= 'A' && c <= 'Z') p = (int)c - (int)'A' + 27;
  else {cout << "ERROR BAD PRIORITY" << endl; exit(1);}
  return p;
}

int duplicate_score(const string & str)
{
  size_t n = str.length()/2;
  string s1 = str.substr(0,n);
  string s2 = str.substr(n,n);
  for(char c : s1)
  {
    set<char> cset;
    if(cset.insert(c).second)
      if(s2.find_first_of(c,0) != s2.npos)
        return priority(c);
  }
  cout << "ERROR no duplicate!  " << str << endl;
  exit(1);
  return 0;
}

void priority_sum(string fn)
{
  int sum = 0;
  auto ip = read_ip(fn);
  for(const string & s : ip)
  {
    int score = duplicate_score(s);
    cout << score << endl;
    sum += score;
  }
  cout << "Priority sum for " << fn << " = " << sum << endl;
}

int main()
{
  cout << "ADVENT OF CODE DAY 3 PART 1" << endl;

  priority_sum("input.txt");
  priority_sum("test.txt");
  return 0;
}
