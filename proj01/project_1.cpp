// Author: Colin Jamison 0006627752
#include <chrono>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

bool is_sorted_helper(std::vector<int> &v, int start, int end) {
  if (start == end) {
    return true;
  } else if (v.size() < 2) {
    return true;
  }

  if (v[start] <= v[start + 1]) {
    return is_sorted_helper(v, start + 1, end);
  } else {
    return false;
  }
}

bool is_sorted(std::vector<int> &v) {
  return is_sorted_helper(v, 0, v.size() - 1);
}

std::vector<int> bubble_sort(std::vector<int> &unsorted);
std::vector<int> insertion_sort(std::vector<int> &unsorted);
std::vector<int> selection_sort(std::vector<int> &unsorted);
std::vector<int> quick_sort(std::vector<int> &unsorted);

std::vector<int> random_vector(int size, int low, int high) {
  using std::vector;
  vector v(size, 0);
  for (int i = 0; i < size; i++) {
    v[i] = rand() % (high - low + 1) + low;
  }

  return v;
}
void print_vector(std::vector<int> &v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  return;
}

int main(int argc, char **argv) {
  srand(time(NULL));
  std::vector<int> v = random_vector(10, 0, 20);
  print_vector(v);
}
