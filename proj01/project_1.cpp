// Author: Colin Jamison 0006627752
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <numeric>
#include <stdexcept>
#include <stdfloat>
#include <time.h>
#include <vector>

using std::vector;

enum SORT_TYPE { BUBBLE, INSERTION, SELECTION, QUICK_FIRST, QUICK_MIDDLE };

const int RUN_SIZES[] = {10, 100, 1000, 5000, 10000};

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

enum SORT_CASE {
  SORTED,
  REV_SORTED,
  RANDOM,
  SORTED_QUICK_MIDDLE,
};

vector<long double> run_battery(SORT_TYPE type, SORT_CASE sort_case, int num_runs, int run_size) {
  vector<long double> timings;

  for (int i = 0; i < num_runs; i++) {
    vector<int> v;

    switch (sort_case) {
      case SORTED:
      case SORTED_QUICK_MIDDLE:
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

    timings.push_back(run_test(type, v));
  }

  return timings;
}

class Args {
 public:
  SORT_CASE sort_case;
  SORT_TYPE sort_type;

  void parse_args(int argc, char* argv[]) {
    if (argc < 3) {
      std::cerr << "Usage: " << argv[0] << " <algorithm> <case>" << std::endl;
      exit(1);
    }

    // Parse sorting algorithm
    std::string alg_arg = argv[1];
    std::transform(alg_arg.begin(), alg_arg.end(), alg_arg.begin(), ::tolower);
    if (alg_arg == "insertion") {
      this->sort_type = INSERTION;
    } else if (alg_arg == "selection") {
      this->sort_type = SELECTION;
    } else if (alg_arg == "quick_first") {
      this->sort_type = QUICK_FIRST;
    } else if (alg_arg == "quick_middle") {
      this->sort_type = QUICK_MIDDLE;
    } else if (alg_arg == "bubble") {
      this->sort_type = BUBBLE;
    } else {
      std::cerr << "Invalid sorting algorithm: " << alg_arg << ". Expected one of: bubble, insertion, selection, quick_first, quick_middle." << std::endl;
      exit(1);
    }

    // Parse sorting case
    std::string case_arg = argv[2];
    std::transform(case_arg.begin(), case_arg.end(), case_arg.begin(), ::tolower);
    if (case_arg == "sorted") {
      this->sort_case = SORTED;
    } else if (case_arg == "rev_sorted") {
      this->sort_case = REV_SORTED;
    } else if (case_arg == "random") {
      this->sort_case = RANDOM;
    } else {
      std::cerr << "Invalid sorting case: " << case_arg << ". Expected one of: sorted, rev_sorted, random." << std::endl;
      exit(1);
    }
  }
};

class TimingSummary {
 public:
  long double min;
  long double max;
  long double average;

  TimingSummary(vector<long double> timings) {
    if (timings.empty()) {
      throw std::invalid_argument("Timings vector is empty.");
    }

    min = *std::min_element(timings.begin(), timings.end());
    max = *std::max_element(timings.begin(), timings.end());
    average = std::accumulate(timings.begin(), timings.end(), 0.0L) / timings.size();
  }
};

int main(int argc, char* argv[]) {
  Args args;
  args.parse_args(argc, argv);

  srand(time(NULL));
  auto timings = run_battery(args.sort_type, args.sort_case, 100, 1000);
  print_vector(timings);

  TimingSummary summary(timings);
  std::cout << "Min: " << summary.min << std::endl;
  std::cout << "Max: " << summary.max << std::endl;
  std::cout << "Average: " << summary.average << std::endl;
}
