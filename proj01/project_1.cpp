// Author: Colin Jamison 0006627752
#include <chrono>
#include <math.h>
#include <time.h>
#include <vector>

int main(int argc, char **argv) { return 0; }

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