#include <vector>
#include <iostream>
#include <map>

using namespace std;

map<int, vector<int>> g;

int main(){
  g.insert({1, vector<int>{2,3,4}});
  g.insert(1, 10);
  g[1].push_back(10);
  cout << g[1][0] << endl;
  for (int elem: g[1]) cout << elem << " ";
  cout << endl;
  g.insert({1, vector<int>{10}});
  for (int elem: g[1]) cout << elem << " ";
  cout << endl;
  return 0;
}
