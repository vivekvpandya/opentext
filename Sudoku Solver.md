Sudoku Solver
=============

- In this problem we need to find out valid values for each n * n cells
  so that all constraints of sudoku is satisfied.
- Here we use recursive approach at each step for given cell we have n choice
  of value. Algorithm checks if given value does not lead to a conflict then
  it continues to find values for next cell. At any point a conflict is found then
  algorithm stop exploring that path and tries different value.
- If there is a solution for given initial state we eventually find that.
- Time complexity is O(N^3) as for each N * N cell there is N choice possible.

How to Run
==========
clang++ sudoku_solver.cpp
./a.out

To add more tests update tests vector with new entries in main() function.