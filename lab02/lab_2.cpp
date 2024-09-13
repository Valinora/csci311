// Lab 2 Skeleton
// Author: Colin Jamison

#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

/*************************************************************
 * Your solutions go below here and do not change the headers*
 * ***********************************************************/

int triangleNum(int n) {
  if (n == 1) {
    return 1;
  }
  return n + triangleNum(n - 1);
}

int rFib(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  }

  return rFib(n - 1) + rFib(n - 2);
}

int rSumHelper(const vector<int> &v, int i) {
  if (i == 0) {
    return v[i];
  } else {
    return v[i] + rSumHelper(v, i - 1);
  }
}

int rSum(const vector<int> &v) {
  if (v.size() == 0) {
    return 0;
  }
  return rSumHelper(v, v.size() - 1);
}

inline int max(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}
int rMaxHelper(const vector<int> &v, int start) {
  if (start == 0) {
    return v[start];
  } else {
    return max(v[start], rMaxHelper(v, start - 1));
  }
}

int rMax(const vector<int> &v) {
  if (v.size() == 0) {
    return INT_MIN;
  }
  return rMaxHelper(v, v.size() - 1);
}

bool isSorted(const vector<int> &v, int start, int end) {
  // A single element is always sorted
  if (start == end) {
    return true;
  } else if (v.size() < 2 ) {
    return true;
  }

  if (v[start] <= v[start + 1]) {
    return isSorted(v, start + 1, end);
  } else {
    return false;
  }

}

bool isPalindromeHelper(string s, int start, int end) {
  if (start >= end) {
    return true;
  }
  // Check the start and finish
  if (s[start] != s[end]) {
    return false;
  }

  // Meet in the middle
  return isPalindromeHelper(s, start + 1, end - 1);
}

bool isPalindrome(string s) {
  return isPalindromeHelper(s, 0, s.length() - 1);
}

int rBinarySearch(const vector<int> &v, int low, int high, int target) {
  if (low > high) {
    return -1;
  }
  int mid = low + (high - low) / 2;
  if (v[mid] == target) {
    return mid;
  }

  if (v[mid] > target) {
    // Search bottom half
    return rBinarySearch(v, low, mid - 1, target);
  } else {
    // Search top half
    return rBinarySearch(v, mid + 1, high, target);
  }


}

// Hmmm....
// Easy Cases:
// Length of array is 0 or 1, and the single value does not match target
// All positive values combined sum to less than target
// Target is 0; empty subset is valid
// Observations:
// If we were only dealing with positive integers, we could easily exclude all values larger than our target.
// For every element, it is either in the subset or it isn't.
bool rSubsetSum(const vector<int> &v, int start, int target) {
  if (target == 0) {
    return true;
  }
  // No more elements to consider
  if (start >= v.size()) {
    return false;
  }

  // Check if a sum can be made based on inclusion || exclusion of current element
  return rSubsetSum(v, start + 1, target - v[start]) || rSubsetSum(v, start + 1, target);
}

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);

int main() {
  int question = -1;
  cout << "Question: ";
  cin >> question;

  int n = 0, start = 0, end = 0;
  vector<int> v;
  string s = "";
  switch (question) {
  case 1: // triangleNum
    cout << "Triangle Number n: ";
    cin >> n;
    cout << triangleNum(n) << endl;
    break;
  case 2: // rFib
    cout << "Nth Fibonacci Number: ";
    cin >> n;
    cout << rFib(n) << endl;
    break;
  case 3: // rSum
    cout << "Recursive Sum Vector Size: ";
    cin >> n;
    cout << "Values: ";
    readIntVector(v, n);
    cout << rSum(v) << endl;
    break;
  case 4: // rMax
    cout << "Recursive Max Vector Size: ";
    cin >> n;
    cout << "Values: ";
    readIntVector(v, n);
    cout << rMax(v) << endl;
    break;
  case 5: // isSorted
    cout << "isSorted Vector Size: ";
    cin >> n;
    cout << "Start and End: ";
    cin >> start >> end;
    cout << "Values: ";
    readIntVector(v, n);
    cout << isSorted(v, start, end) << endl;
    break;
  case 6: // isPalindrome
    cout << "String: ";
    cin >> s;
    cout << isPalindrome(s) << endl;
    break;
  case 7: // rBinarySearch
    cout << "Binary Search Vector Size: ";
    cin >> n;
    cout << "Target: ";
    cin >> end;
    cout << "Values: ";
    readIntVector(v, n);
    cout << rBinarySearch(v, 0, v.size() - 1, end) << endl;
    break;
  case 8: // rSubsetSum
    cout << "Subset Sum Vector Size: ";
    cin >> n;
    cout << "Target: ";
    cin >> end;
    cout << "Values: ";
    readIntVector(v, n);
    cout << rSubsetSum(v, 0, end) << endl;
    break;
  }

  return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int> &v, int n) {
  int m = 0;
  for (int i = 0; i < n; i++) {
    cin >> m;
    v.push_back(m);
  }
}
