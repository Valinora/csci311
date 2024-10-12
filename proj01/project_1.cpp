// Author: Colin Jamison 0006627752
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <numeric>
#include <stdexcept>
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
template <typename T>
void print_vector(const vector<T>& v) {
  for (unsigned int i = 0; i < v.size(); i++) {
    std::cout << v[i];
    if (i < v.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
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
long double run_test(SORT_TYPE type, vector<int> v, bool print = false) {
  using namespace std::chrono;
  vector<int> out;

  time_point<high_resolution_clock> start;
  std::string tag;

  switch (type) {
    case BUBBLE:
      tag = "bubble";
      start = high_resolution_clock::now();
      out = bubble_sort(v);
      break;
    case INSERTION:
      tag = "insertion";
      start = high_resolution_clock::now();
      out = insertion_sort(v);
      break;
    case SELECTION:
      tag = "selection";
      start = high_resolution_clock::now();
      out = selection_sort(v);
      break;
    case QUICK_FIRST:
      tag = "quick";
      start = high_resolution_clock::now();
      out = quick_sort_first(v);
      break;
    case QUICK_MIDDLE:
      tag = "quick";
      start = high_resolution_clock::now();
      out = quick_sort_middle(v);
      break;
    default:
      throw "Invalid SORT_TYPE";
  }
  auto end = high_resolution_clock::now();
  duration<long double, std::micro> duration = end - start;

  if (print) {
    std::cout << tag << "," << v.size() << "," << duration.count() << std::endl;
  }

  if (!is_sorted(out)) {
    throw "Received unsorted array out.";
  }

  return duration.count();
}

enum SORT_CASE {
  SORTED,
  REV_SORTED,
  RANDOM,
};

/**
 * @brief Runs a series of sorting tests and records the timings.
 *
 * @param type The type of sorting algorithm to use (SORT_TYPE).
 * @param sort_case The initial configuration of the vector (SORT_CASE).
 * @param num_runs The number of sorting runs to execute.
 * @param run_size The size of the vector for each sorting run.
 * @return A vector of long doubles containing the timing results for each run.
 *
 * @throws const char* If an invalid SORT_CASE is provided.
 */
vector<long double> run_battery(SORT_TYPE type, SORT_CASE sort_case, int num_runs, int run_size, bool print = false) {
  vector<long double> timings;

  for (int i = 0; i < num_runs; i++) {
    vector<int> v;

    switch (sort_case) {
      case SORTED:
        v = sorted_vector(run_size);
        break;
      case REV_SORTED:
        v = sorted_vector(run_size);
        std::reverse(v.begin(), v.end());
        break;
      case RANDOM:
        v = random_vector(run_size, 0, 100);
        break;
      default:
        throw "Invalid SORT_CASE provided";
    }

    timings.push_back(run_test(type, v, print));
  }

  return timings;
}

class TimingSummary {
 public:
  long double min;
  long double max;
  long double average;
  long double stddev;

  TimingSummary(vector<long double> timings) {
    if (timings.empty()) {
      throw std::invalid_argument("Timings vector is empty.");
    }

    min = *std::min_element(timings.begin(), timings.end());
    max = *std::max_element(timings.begin(), timings.end());
    average = std::accumulate(timings.begin(), timings.end(), 0.0L) / timings.size();
    stddev = 0.0L;
    for (unsigned long i = 0; i < timings.size(); i++) {
      stddev += std::pow(timings[i] - average, 2);
    }
    stddev = std::sqrt(stddev / (timings.size() - 1));
  }
  friend std::ostream& operator<<(std::ostream& os, const TimingSummary& ts) {
    os << "Min/Avg/Max/Stddev: " << ts.min << " / " << ts.average << " / " << ts.max << " / " << ts.stddev;
    return os;
  }
};

void run_default() {
  auto separator = "***************************************";

  std::cout << separator << std::endl;
  std::cout << "Bubble Sort on 10 vectors of length 100" << std::endl;
  auto timings = run_battery(BUBBLE, RANDOM, 10, 100);
  TimingSummary summary(timings);
  std::cout << summary << " microseconds" << std::endl;
  std::cout << separator << std::endl;

  std::cout << separator << std::endl;
  std::cout << "Insertion Sort on 10 vectors of length 100" << std::endl;
  timings = run_battery(INSERTION, RANDOM, 10, 100);
  summary = TimingSummary(timings);
  std::cout << summary << " microseconds" << std::endl;
  std::cout << separator << std::endl;

  std::cout << separator << std::endl;
  std::cout << "Selection Sort on 10 vectors of length 100" << std::endl;
  timings = run_battery(SELECTION, RANDOM, 10, 100);
  summary = TimingSummary(timings);
  std::cout << summary << " microseconds" << std::endl;
  std::cout << separator << std::endl;

  std::cout << separator << std::endl;
  std::cout << "Quick Sort on 10 vectors of length 100" << std::endl;
  timings = run_battery(QUICK_FIRST, RANDOM, 10, 100);
  summary = TimingSummary(timings);
  std::cout << summary << " microseconds" << std::endl;
  std::cout << separator << std::endl;
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  if (argc == 1) {
    run_default();
    return 0;
  }

  if (argc > 2) {
    std::cerr << "Usage: " << argv[0] << " [SORT_CASE]" << std::endl;
    return -1;
  }

  int run_sizes[] = {10, 100, 1000, 5000, 10000};

  std::string sort_case = argv[1];
  std::transform(sort_case.begin(), sort_case.end(), sort_case.begin(), ::tolower);

  if (sort_case == "best") {
    for (int i = 0; i < 5; i++) {
      run_battery(BUBBLE, SORTED, 50, run_sizes[i], true);
      run_battery(INSERTION, SORTED, 50, run_sizes[i], true);
      run_battery(SELECTION, SORTED, 50, run_sizes[i], true);
      run_battery(QUICK_MIDDLE, SORTED, 50, run_sizes[i], true);
    }
  } else if (sort_case == "worst") {
    for (int i = 0; i < 5; i++) {
      run_battery(BUBBLE, REV_SORTED, 50, run_sizes[i], true);
      run_battery(INSERTION, REV_SORTED, 50, run_sizes[i], true);
      run_battery(SELECTION, REV_SORTED, 50, run_sizes[i], true);
      run_battery(QUICK_FIRST, SORTED, 50, run_sizes[i], true);
    }
  } else if (sort_case == "average") {
    for (int i = 0; i < 5; i++) {
      run_battery(BUBBLE, RANDOM, 50, run_sizes[i], true);
      run_battery(INSERTION, RANDOM, 50, run_sizes[i], true);
      run_battery(SELECTION, RANDOM, 50, run_sizes[i], true);
      run_battery(QUICK_FIRST, RANDOM, 50, run_sizes[i], true);
    }
  } else {
    std::cerr << "Invalid SORT_CASE provided." << std::endl;
    return -1;
  }
}
