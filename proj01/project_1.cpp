// Author: Colin Jamison 0006627752
#include <math.h>
#include <time.h>

#include <chrono>
#include <iostream>
#include <vector>

enum SORT_TYPE { BUBBLE, INSERTION, SELECTION, QUICK };

bool is_sorted_helper(std::vector<int>& v, int start, int end) {
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

bool is_sorted(std::vector<int>& v) {
  return is_sorted_helper(v, 0, v.size() - 1);
}

std::vector<int> bubble_sort(std::vector<int>& unsorted);
std::vector<int> insertion_sort(std::vector<int>& unsorted);
std::vector<int> selection_sort(std::vector<int>& unsorted);
std::vector<int> quick_sort(std::vector<int>& unsorted);

std::vector<int> random_vector(int size, int low, int high) {
  using std::vector;
  vector v(size, 0);
  for (int i = 0; i < size; i++) {
    v[i] = rand() % (high - low + 1) + low;
  }

  return v;
}
void print_vector(std::vector<int>& v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  return;
}

std::chrono::duration<float> run_test(SORT_TYPE type, std::vector<int>& v) {
  using namespace std::chrono;
  std::vector<int> out;

  time_point<system_clock> now;

  switch (type) {
    case BUBBLE:
      now = system_clock::now();
      out = bubble_sort(v);
      break;
    case INSERTION:
      now = system_clock::now();
      out = insertion_sort(v);
      break;
    case SELECTION:
      now = system_clock::now();
      out = selection_sort(v);
      break;
    case QUICK:
      now = system_clock::now();
      out = quick_sort(v);
      break;
    default:
      throw "Invalid SORT_TYPE";
  }

  auto duration = now.time_since_epoch();

  if (!is_sorted(out)) {
    throw "Received unsorted array out.";
  }

  return duration;
}

int main(int argc, char** argv) {
  srand(time(NULL));
  std::vector<int> v = random_vector(10, 0, 20);
  print_vector(v);
}
