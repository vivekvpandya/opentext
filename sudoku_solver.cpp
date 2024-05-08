#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int empty_cell = 0; // 0 means cell is empty

bool is_valid_choice(int i, int j, int val, vector<vector<int>> &state) {
  for (int k = 0; k < state.size(); k++) {
    // check row conflicts
    if (val == state[k][j])
      return false;
    // check column conflicts
    if (val == state[i][k])
      return false;
  }

  // check region conflicts
  int r_size = sqrt(state.size());
  // locate region in 2D matrix of regions
  int r_i = i / r_size;
  int r_j = j / r_size;
  for (int a = 0; a < r_size; ++a) {
    for (int b = 0; b < r_size; ++b) {
      if (val == state[r_i * r_size + a][r_j * r_size + b]) {
        return false;
      }
    }
  }
  return true;
}

bool solve_recursive(int i, int j, vector<vector<int>> &state) {
  if (i == state.size()) {
    i = 0; // start a next row.
    if (++j == state[i].size()) {
      return true; // all n * n cells are filled so its a success case.
    }
  }
  // skip all ready filled entries
  if (state[i][j] != empty_cell) {
    return solve_recursive(i + 1, j, state);
  }

  for (int val = 1; val <= state.size(); ++val) {
    if (is_valid_choice(i, j, val, state)) {
      state[i][j] = val;
      if (solve_recursive(i + 1, j, state))
        return true;
    }
  }
  state[i][j] = empty_cell;
  return false;
}
bool solve(vector<vector<int>> &initial_state) {
  return solve_recursive(0, 0, initial_state);
}
void print(vector<vector<int>> &state) {
  for (auto r : state) {
    for (auto c : r) {
      cout << c << " ";
    }
    cout << endl;
  }
}
int main() {
  vector<vector<vector<int>>> tests;
  tests.push_back({
      {0, 1, 3, 8, 0, 0, 4, 0, 5},
      {0, 2, 4, 6, 0, 5, 0, 0, 0},
      {0, 8, 7, 0, 0, 0, 9, 3, 0},
      {4, 9, 0, 3, 0, 6, 0, 0, 0},
      {0, 0, 1, 0, 0, 0, 5, 0, 0},
      {0, 0, 0, 7, 0, 1, 0, 9, 3},
      {0, 6, 9, 0, 0, 0, 7, 4, 0},
      {0, 0, 0, 2, 0, 7, 6, 8, 0},
      {1, 0, 2, 0, 0, 8, 3, 5, 0},
  });
  tests.push_back({
      {0, 0, 2, 0, 0, 0, 0, 4, 1},
      {0, 0, 0, 0, 8, 2, 0, 7, 0},
      {0, 0, 0, 0, 4, 0, 0, 0, 9},
      {2, 0, 0, 0, 7, 9, 3, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 8, 0},
      {0, 0, 6, 8, 1, 0, 0, 0, 4},
      {1, 0, 0, 0, 9, 0, 0, 0, 0},
      {0, 6, 0, 4, 3, 0, 0, 0, 0},
      {8, 5, 0, 0, 0, 0, 4, 0, 0},
  });
  for (auto test : tests) {
    cout << "------ Input ------" << endl;
    print(test);
    if (solve(test)) {
      cout << "---- Solution ----" << endl;
      print(test);
    } else {
      cout << "Can't solve with this initial state" << endl;
    }
    cout << endl;
  }
  return 0;
}