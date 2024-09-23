// Author: Colin Jamison 0006627752
#include <math.h>
#include <time.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdfloat>
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

vector<int> sorted_vector(int size) {
  vector v(size, 0);

  for (int i = 0; i < size; i++) {
    v[i] = i;
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

/**
 * @brief Measures the time taken to sort a vector using the specified sorting
 * algorithm.
 *
 * @param type The sorting algorithm to use, specified by the SORT_TYPE enum.
 * @param v The vector of integers to be sorted.
 * @return long double The duration in microseconds taken to sort the vector.
 *
 * @throws const char* If an invalid SORT_TYPE is provided or if the output
 * vector is not sorted.
 */
long double run_test(SORT_TYPE type, vector<int> v) {
  using namespace std::chrono;
  vector<int> out;

  time_point<high_resolution_clock> start;

  switch (type) {
    case BUBBLE:
      start = high_resolution_clock::now();
      out = bubble_sort(v);
      break;
    case INSERTION:
      start = high_resolution_clock::now();
      out = insertion_sort(v);
      break;
    case SELECTION:
      start = high_resolution_clock::now();
      out = selection_sort(v);
      break;
    case QUICK_FIRST:
      start = high_resolution_clock::now();
      out = quick_sort_first(v);
      break;
    case QUICK_MIDDLE:
      start = high_resolution_clock::now();
      out = quick_sort_middle(v);
      break;
    default:
      throw "Invalid SORT_TYPE";
  }
  auto end = high_resolution_clock::now();
  duration<long double, std::micro> duration = end - start;

  if (!is_sorted(out)) {
    throw "Received unsorted array out.";
  }

  return duration.count();
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <sorting_algorithm>" << std::endl;
    return -1;
  }

  SORT_TYPE alg_selection;

  std::string arg = argv[1];
  std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
  if (arg == "insertion") {
    alg_selection = INSERTION;
  } else if (arg == "selection") {
    alg_selection = SELECTION;
  } else if (arg == "quick_first") {
    alg_selection = QUICK_FIRST;
  } else if (arg == "quick_middle") {
    alg_selection = QUICK_MIDDLE;
  } else if (arg == "bubble") {
    alg_selection = BUBBLE;
  } else {
    std::cerr << "Invalid sorting algorithm: " << arg << ". Expected one of: bubble, insertion, selection, quick_first, quick_middle." << std::endl;
    return 1;
  }

  srand(time(NULL));
  vector<int> v = random_vector(1000, 0, 20);
  auto time = run_test(alg_selection, v);
  std::cout << "Sorting took: " << time << " microseconds" << std::endl;
}
