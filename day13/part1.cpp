#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
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

vector<array<string,2>> parse_ip(string fn)
{
  vector<array<string,2>> pairs;
  auto ip = read_ip(fn);
  for(size_t i=0;i<ip.size();i+=3)
  {
    pairs.push_back({ip[i],ip[i+1]});
  }
  return pairs;
}

string get_item(string & buffer)
{
  string item;
  int bra_level=0;
  for(size_t i=0;i<buffer.size();i++)
  {
    char c = buffer[i];
    if(c=='[') bra_level++;
    else if(c==']') bra_level--;
    else if(bra_level == 0 && c==',')
    {
      item = buffer.substr(0,i);
      buffer = buffer.substr(i+1);
      return item;
    }
  }
  item = buffer;
  buffer = "";
  return item;
}

vector<string> get_items(string str)
{
  vector<string> items;
  str=str.substr(1,str.size()-2);
  while(str!="")
    items.push_back(get_item(str));
  return items;
}

bool is_list(string str){return str.front()=='[' && str.back()==']';}

void listify(string & s)
{
  s.insert(0,"]");
  s.push_back(']');
}

int compare_item(string str1, string str2);
int compare_list(string str1, string str2);

int compare_item(string str1, string str2)
{
  if(!is_list(str1) && !is_list(str2))
  {
    int left = atoi(str1.c_str());
    int right = atoi(str2.c_str());
    if(left<right)      return -1;
    else if(left>right) return 1;
    else                return 0;
  }
  else if(!is_list(str1) && is_list(str2))
  {
    listify(str1);
    return compare_list(str1,str2);
  }
  else if(is_list(str1) && !is_list(str2))
  {
    listify(str2);
    return compare_list(str1,str2);
  }
  else
    return compare_list(str1,str2);
}

int compare_list(string list1, string list2)
{
  int rtn=0;
  auto items1 = get_items(list1);
  auto items2 = get_items(list2);

  size_t minlen = min(items1.size(),items2.size());

  for(size_t i=0;i<minlen;i++)
  {
    rtn = compare_item(items1[i],items2[i]);
    if(rtn != 0) return rtn;
  }

  if(items1.size()<items2.size()) return -1;
  else if(items1.size()>items2.size()) return 1;
  else return 0;

}

void play(string fn)
{
  auto pairs = parse_ip(fn);

  for(auto p : pairs) cout << p[0] << " " << p[1] << endl;

  int sum=0;
  int i=0;
  for(auto p : pairs)
  {
    i++;
    if(compare_list(p[0],p[1])==-1) sum+=i;
  }

  cout << fn << " Answer to part 1 = " << sum << endl;

}

int main()
{
  //cout << get_item(string("[[4,4],6,[5,[1,2,4]]],3,4")) << endl;
  //cout << get_item(string("4")) << endl;

  play("input.txt");
  play("test.txt");

  return 0;
}
