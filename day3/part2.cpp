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

int badge(const string & s1, const string & s2, const string & s3)
{
  for(char c : s1)
  {
    set<char> cset;
    if(cset.insert(c).second)
      if(s2.find_first_of(c,0) != s2.npos)
        if(s3.find_first_of(c,0) != s3.npos)
          return priority(c);
  } 
  cout << "ERROR no badge found!  " << s1 << " " << s2 << " " << s3 << endl;
  exit(1);
  return 0;
}

void badge_sum(string fn)
{
  auto ip = read_ip(fn);
  int sum = 0;
  for(size_t i = 0; i < ip.size(); i += 3)
  {
    int score = badge(ip[i],ip[i+1],ip[i+2]);
    cout << score << endl;
    sum += score;
  }
  cout << "Badge sum for " << fn << " = " << sum << endl;
}

int main()
{
  cout << "ADVENT OF CODE DAY 3 PART 2" << endl;

  badge_sum("input.txt");
  badge_sum("test.txt");
  return 0;
}
