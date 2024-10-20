#include <vector>
#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

using vecindario = vector<pair<int, int>>;
using grafo = map<int, vecindario>;

template<int index> struct TupleLess
 {
    template<typename Tuple>
    bool operator() (const Tuple& left, const Tuple& right) const
    {
        return std::get<index>(left) < std::get<index>(right);
    }
};

grafo g = {
          {0, vecindario{make_pair(5, 10), make_pair(1, 28)}},
          {1, vecindario{make_pair(2, 16)}},
          {2, vecindario{make_pair(3, 12)}},
          {3, vecindario{make_pair(6, 18)}},
          {4, vecindario{make_pair(3, 22), make_pair(6, 24)}},
          {5, vecindario{make_pair(4, 25)}},
          {6, vecindario{make_pair(1, 14)}}
          };
          
int main(){
  /*
  for (int i = 0; i <= 6; i++) {
    cout << "nodo " << i << endl;
    for (pair<int, int> vecino : g[i]) cout << "(" << vecino.first << ", " << vecino.second << "), ";
    cout << endl;
  }
  */
  vector<tuple<int, int, int>> aristas;
  for (pair<int, vecindario> elem : g) {
    cout << "nodo " << elem.first << endl;
    for (pair<int, int> vecino : elem.second) {
      cout << "(" << vecino.first << ", " << vecino.second << "), ";
      aristas.push_back(make_tuple(elem.first, vecino.first, vecino.second));
    };
    cout << endl;
  }
  for (tuple<int, int, int> elem : aristas) {
    cout << "(" << get<0>(elem) << ", " << get<1>(elem) << ", " << get<2>(elem) << "), ";
  }
  cout << endl;
  sort(aristas.begin(), aristas.end(), TupleLess<2>());
  for (tuple<int, int, int> elem : aristas) {
    cout << "(" << get<0>(elem) << ", " << get<1>(elem) << ", " << get<2>(elem) << "), ";
  }
  cout << endl;
  return 0;
}
