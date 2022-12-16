#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

size_t ipos(const string & s, size_t n)
{
  size_t i;
  for(i = n-1; i<s.size(); i++)
  {
    set<char> cset;
    for(size_t j=i+1-n; j<=i; j++)
      if(!cset.insert(s[j]).second) break;
    if(cset.size()==n)break;
  }
  return i+1;
}

int main()
{
  auto ip = read_ip("input.txt");

  cout << ipos("mjqjpqmgbljsphdztnvjfqwrcgsmlb",4) << endl;
  cout << ipos("bvwbjplbgvbhsrlpgdmjqwftvncz",4) << endl;
  cout << ipos("nppdvjthqldpwncqszvftbrmjlhg",4) << endl;
  cout << ipos("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",4) << endl;
  cout << ipos("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw",4) << endl; 
  cout << endl;
  cout << ipos("mjqjpqmgbljsphdztnvjfqwrcgsmlb",14) << endl;
  cout << ipos("bvwbjplbgvbhsrlpgdmjqwftvncz",14) << endl;
  cout << ipos("nppdvjthqldpwncqszvftbrmjlhg",14) << endl;
  cout << ipos("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",14) << endl;
  cout << ipos("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw",14) << endl; 
  cout << endl;
  cout << ipos(ip[0],4) << endl;
  cout << ipos(ip[0],14) << endl;

  return 0;
}
