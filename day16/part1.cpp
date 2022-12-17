// done on myphone dont judge not giving right answer yet

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <utility>

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

void nearest(const string & s1,
                map<string,vector<string>> & tunnels,
                map<string,int64_t> & dist,
                int64_t d)
{
	d++;
	for(string & s : tunnels[s1])
	{
		if(dist[s]>d)
		{
			dist[s]=d;
			nearest(s,tunnels,dist,d);
		}
	}
}

bool all_true(map<string,bool> & bools)
{
	for(auto & p : bools)
	  if(!p.second)return false;
	return true;
}

struct Sys
{
	int64_t nsteps=30;
	int64_t minloss;
	
	map<string,int64_t> rates;
	
	map<string,vector<string>> tunnels;
	vector<string> nodes;
	map<string,vector<string>> links;
	map<pair<string,string>,int64_t> dists;
	
	map<string,int64_t> weights;
	
	void print()
	{
		for(auto p:rates)
		{
			cout << p.first << p.second << " ";
			for(auto v 	: tunnels[p.first])
			  cout << v << " ";
			cout << endl;
		}
		cout << "nodes\n";
		for(string s:nodes)
		  cout << s << endl;
		for(auto p : dists)
		  cout << p.first.first << ">" << p.first.second << " " << p.second<<endl;
	}
	bool comp(string & s1, string & s2){return rates[s1]>rates[s2];}
	void sort_nodes(map<string,int64_t> & r){sort(nodes.begin(),nodes.end(),
		[&r](string & s1, string & s2){return r[s1]>r[s2];});}
	void sort_nodes(){sort_nodes(rates);}
	void get_dists()
	{
		map<string,int64_t> dist;
		for(auto & p : rates)dist[p.first]=rates.size()*2;
		dist["AA"]=0;
		nearest("AA",tunnels,dist,0);
		for(string s : nodes)
		  dists[{"AA",s}]=dist[s]+1;//plus one for opening valve
		for(string s : nodes)
		{
			for(auto & p : dist) p.second=rates.size()*2;
			dist[s]=0;
			nearest(s,tunnels,dist,0);
			for(string s2 : nodes)
			  if(s!=s2)
		      dists[{s,s2}]=dist[s2]+1;//plus one for opening valve
		}	
	}
	void calc_weights()
	{
		int64_t ratesum = 0;
		for(auto p:rates) ratesum+=p.second;
		for(auto & p:rates) weights[p.first]=ratesum-p.second;
		//for(auto & p:dists) p.second*=weights
	}
	
	void step(string v, int64_t loss, int64_t ratesum, map<string,bool> & is_open)
	{
		if(loss>minloss)return;
		is_open[v]=true;
		ratesum -= rates[v];
		if(all_true(is_open))
		{
			minloss = minloss < loss 	? minloss : loss;
			is_open[v]=false;
			return;
		}
		for(auto s : nodes)
		{
			if(!is_open[s])
			{
			  int64_t d=dists[{v,s}];
			  loss += d*ratesum;
			  step(s,loss,ratesum,is_open);  
		  }
		}
		is_open[v]=false;
	}
	
	void get_best()
	{
		//int64_t step=0;
		int64_t ratesum = 0;
		for(auto p:rates) ratesum+=p.second;
		int64_t flowsum=ratesum*nsteps;
		minloss=flowsum*200;
		map<string,bool> is_open;
		for(auto s : nodes)is_open[s]=false;
		int64_t loss = 0;
		for(auto s : nodes)
		{
			int64_t d=dists[{"AA",s}];
			loss = d*ratesum;
			step(s,loss,ratesum,is_open);
		}
		cout << "min loss " << minloss << endl;
		cout << "best flow " << flowsum-minloss << endl;
	}

};



                

Sys parse(string fn)
{
	Sys rtn;
  auto ip=read_ip(fn);
  for(string s : ip	)
  {
    cout << s << endl;
    string dummy, name, srate, name2;
    stringstream ss(s);
    ss >> dummy >> name >> dummy >> dummy >> srate >> dummy >> dummy >> dummy >> dummy;
    srate=srate.substr(5);
    srate.pop_back();
    int64_t rate = atoi(srate.c_str());
    rtn.rates[name]=rate;
    vector<string> t;
    while(ss >> name2)
    {
    	if(name2.size()==3) name2.pop_back();
    	t.push_back(name2);
   	}  
   	rtn.tunnels[name]=t	;  
  }
  
  for(auto p : rtn.rates)
    if(p.second > 0) rtn.nodes.push_back(p.first);
  rtn.sort_nodes(rtn.rates);
  rtn.get_dists();
  
  
  return rtn;
}



void calc(string fn)
{
	Sys sys =parse(fn);
	sys.print();
	
	sys.get_best();
	
	
}

int main()
{
  //calc("input.txt",9);
  calc("test.txt");
  return 0;
}
