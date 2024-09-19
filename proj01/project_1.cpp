// Author: Colin Jamison 0006627752
#include <math.h>
#include <time.h>

#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

using std::vector;

enum SORT_TYPE { BUBBLE, INSERTION, SELECTION, QUICK_FIRST, QUICK_MIDDLE };

bool is_sorted_helper(vector<int>& v, int start, int end) {
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

bool is_sorted(vector<int> v) { return is_sorted_helper(v, 0, v.size() - 1); }

/*
 * Sorting algorithms
 */
vector<int> bubble_sort(vector<int> unsorted) {
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (uint64_t i = 1; i < unsorted.size(); i++) {
      if (unsorted[i - 1] > unsorted[i]) {
        std::swap(unsorted[i - 1], unsorted[i]);
        sorted = false;
      }
    }
  }
  return unsorted;
};
vector<int> insertion_sort(vector<int> unsorted) {
  uint64_t i = 1;
  while (i < unsorted.size()) {
    int j = i;
    while (j > 0 && (unsorted[j] < unsorted[j - 1])) {
      std::swap(unsorted[j - 1], unsorted[j]);
      j--;
    }
    i++;
  }
  return unsorted;
}
vector<int> selection_sort(vector<int> unsorted) {
  for (uint64_t i = 0; i < unsorted.size() - 1; i++) {
    int min = i;
    for (uint64_t j = i + 1; j < unsorted.size(); j++) {
      if (unsorted[j] < unsorted[min]) {
        min = j;
      }
    }
    std::swap(unsorted[i], unsorted[min]);
  }
  return unsorted;
}

vector<int> quick_sort_first(vector<int> unsorted) {
  if (unsorted.size() <= 1) {
    return unsorted;
  }
  auto pivot = unsorted[0];
  vector<int> less;
  vector<int> more;

  for (uint64_t i = 1; i < unsorted.size(); i++) {
    if (unsorted[i] <= pivot) {
      less.push_back(unsorted[i]);
    } else {
      more.push_back(unsorted[i]);
    }
  }

  less = quick_sort_first(less);
  more = quick_sort_first(more);

  vector<int> sorted;
  sorted.insert(sorted.end(), less.begin(), less.end());
  sorted.push_back(pivot);
  sorted.insert(sorted.end(), more.begin(), more.end());

  return sorted;
}

vector<int> quick_sort_middle(vector<int> unsorted) {
  if (unsorted.size() <= 1) {
    return unsorted;
  }
  auto pivot = unsorted[unsorted.size() / 2];
  vector<int> less;
  vector<int> more;

  for (uint64_t i = 1; i < unsorted.size(); i++) {
    if (unsorted[i] <= pivot) {
      less.push_back(unsorted[i]);
    } else {
      more.push_back(unsorted[i]);
    }
  }

  less = quick_sort_middle(less);
  more = quick_sort_middle(more);

  vector<int> sorted;
  sorted.insert(sorted.end(), less.begin(), less.end());
  sorted.push_back(pivot);
  sorted.insert(sorted.end(), more.begin(), more.end());

  return sorted;
}

vector<int> random_vector(int size, int low, int high) {
  vector v(size, 0);
  for (int i = 0; i < size; i++) {
    v[i] = rand() % (high - low + 1) + low;
  }

  return v;
}
void print_vector(vector<int>& v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  return;
}

std::chrono::duration<float> run_test(SORT_TYPE type, vector<int>& v) {
  using namespace std::chrono;
  vector<int> out;

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
    case QUICK_FIRST:
      now = system_clock::now();
      out = quick_sort_first(v);
      break;
    case QUICK_MIDDLE:
      now = system_clock::now();
      out = quick_sort_middle(v);
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
  vector<int> v = random_vector(10, 0, 20);
  auto sorted = quick_sort_first(v);
  print_vector(sorted);
}
