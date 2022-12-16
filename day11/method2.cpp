#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
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

// N/c = a remainder b
struct Multiple
{
  uint64_t a=0;
  uint64_t b=0;
  uint64_t c=1;

  Multiple(){};
  Multiple(uint64_t i,uint64_t j,uint64_t k):a(i),b(j),c(k){}
  Multiple(uint64_t v,uint64_t d):a(v/d),b(v%d),c(d){}
  //Multiple(uint64_t v):a(v/c),b(v%c){}

  
  void operator+=(Multiple m)
  {
    if(c!=m.c){cout << "ERROR += mismatch denominator" << c << " " << m.c << endl;exit(1);}
    a += m.a;
    b += m.b;
    a += b/c;
    b =  b%c;
  }

  void operator*=(Multiple m)
  {
    if(c!=m.c){cout << "ERROR *= mismatch denominator" << c << " " << m.c << endl;exit(1);}
    a = a*m.a*c + a*m.b + b*m.a;
    b = b*m.b;
    a += b/c;
    b =  b%c;
  }

};

deque<uint64_t> get_items(string s)
{
  deque<uint64_t> items;
  stringstream ss(s.substr(18));
  string str1, str2;
  while(ss >> str1)
  {
    if(str1.find(",")!=string::npos) str1.pop_back();
     uint64_t n = atoi(str1.c_str());
     items.push_back(n);
  }
  return items;
}

void get_operation(string s, char & op, string & n)
{
  op = s[23];
  n = s.substr(25);
}

void get_test(string s, uint64_t & n)
{
  stringstream ss(s);
  string s1, s2, s3;
  ss >> s1 >> s2 >> s3 >> n;
}

void get_monkey(string s, uint64_t & n)
{
  stringstream ss(s);
  string s1, s2, s3, s4, s5;
  ss >> s1 >> s2 >> s3 >> s4 >> s5 >> n;
}

class Monkey
{
public:
  deque<Multiple> items;
  char op = '+';
  string operand;
  uint64_t test = 1;
  uint64_t monkey_true = 0;
  uint64_t monkey_false = 0;
  size_t inspected = 0;
  void parse(vector<string> & ip)
  {
    //for(string s : ip) cout << s << endl;
    items.clear();
    auto items_ip = get_items(ip[1]);
    get_operation(ip[2],op,operand);
    get_test(ip[3],test);
    get_monkey(ip[4],monkey_true);
    get_monkey(ip[5],monkey_false);
    for(uint64_t v : items_ip)items.push_back({v,test});
  }
};


void parse_ip(string fn, vector<Monkey> & monkeys)
{
  auto ip = read_ip(fn);
  Monkey m;
  for(size_t i=0; i<ip.size(); i+=7)
  {
    vector<string> section(6);
    copy(ip.begin()+i,ip.begin()+i+6,section.begin());
    m.parse(section);
    monkeys.push_back(m);
  }

  for(Monkey & m : monkeys)
  {
    for(Multiple i : m.items) cout << i.a*i.c+i.b << ", ";
    cout << " " << m.op << " " << m.operand << " " << m.test << " " << m.monkey_true << " " << m.monkey_false << endl;
  }

}

void round(vector<Monkey> & monkeys)
{
  for(Monkey & m : monkeys)
  {
    m.inspected+=m.items.size();
    for(Multiple worry : m.items)
    {
      Multiple operand({0,0,m.test});
      if(m.operand=="old") operand = worry;
      else
      {
        uint64_t v = atoi(m.operand.c_str());
        operand = {v,m.test};
      }
      if(m.op=='+') worry += operand;
      else worry *= operand;

      uint64_t recipient = worry.b == 0 ? m.monkey_true : m.monkey_false;

      monkeys[recipient].items.push_back(worry);
    }
    m.items.clear();
  }
}

void play(string fn, size_t nrounds)
{
  vector<Monkey> monkeys;
  parse_ip(fn,monkeys);
  for(size_t iturn=0; iturn<nrounds; iturn++)
    round(monkeys);

  vector<size_t> inspected(monkeys.size(),0);
  for(size_t i = 0;i<monkeys.size();i++)
    inspected[i]=monkeys[i].inspected;

  sort(inspected.begin(),inspected.end());

  for(Monkey & m : monkeys) cout << m.inspected << endl;

  size_t monkey_business = *(inspected.end()-1) * *(inspected.end()-2);

  cout << fn << " after " << nrounds << " rounds, monkey business = " << monkey_business << endl;

    
}

int main()
{
  cout << ((123%27)*(145%27))%27 << " " << (123*145)%27 << endl;
  play("input.txt",10000);
  play("test.txt",10000);

  return 0;
}
