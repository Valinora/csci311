// CSCI 311
// Lab 1 Skeleton
// Author: Carter Tillquist

#include <chrono>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

/*************************************************************
 * Your solutions go below here and do not change the headers*
 * ***********************************************************/

// Colin Jamison
// 006627752

int collatzLength(int n) {
  int count = 0;
  int prev = 0;
  int curr = n;
  while (curr != 1) {
    count++;
    prev = curr;
    if (curr % 2 == 0) {
      curr = curr / 2;
    } else {
      curr = (3 * curr) + 1;
    }
  }
  return count;
}

void printStats(const vector<int> &v) {
  if (v.size() == 0) {
    std::cout << "Empty vector" << std::endl;
    return;
  }

  // Without changing headers to include climits I cannot use INT_MAX
  // int min = INT_MAX;
  // Signed INT_MAX
  int min = 0b01111111111111111111111111111111;

  int max = -1;
  float sum = 0;
  for (auto elem : v) {
    sum += elem;
    if (elem > max) {
      max = elem;
    }
    if (elem < min) {
      min = elem;
    }
  }
  std::cout << min << " " << sum / v.size() << " " << max << std::endl;
}

int sumMultiples(const vector<int> &v, int n) {
  int sum = 0;
  for (auto elem : v) {
    for (int i = 1; i <= n; i++) {
      if (elem * i >= n) {
        break;
      }
      sum += elem * i;
    }
  }

  if (v.size() > 1) {

    for (int i = 0; i < v.size(); i++) {
      for (int j = i + 1; j < v.size(); j++) {
        sum -= v[i] * v[j];
      }
    }
  }

  return sum;
}

void greaterThanK(vector<int> &v, int k) {
  auto iter = v.begin();
  while (iter != v.end()) {
    if ((*iter) <= k) {
      v.erase(iter);
    } else {
      iter++;
    }
  }
}

bool isSubarray(const vector<string> &a, const vector<string> &b) {
  return false;
}

bool isPrimeA(int n) { return false; }

int sumPrimesA(int n) { return 0; }

bool isPrimeB(int n) { return false; }

int sumPrimesB(int n) { return 0; }

int sieveOfEratosthenes(int n) { return 0; }

/*************************************************************
 * Your solutions ends here and do not change anything below *
 * ***********************************************************/

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);
void timePrimes();

int main() {
  int question = -1;
  cout << "Question: ";
  cin >> question;

  int n = 0, k = 0, m = 0;
  vector<int> v;
  string s = "";
  vector<string> a;
  vector<string> b;

  switch (question) {
  case 1: // collatzLength
    cout << "Collatz Sequence n: ";
    cin >> n;
    cout << collatzLength(n) << endl;
    break;
  case 2: // printStats
    cout << "Print Stats Number of Values: ";
    cin >> n;
    cout << "Values: ";
    readIntVector(v, n);
    cout << "Stats: " << endl;
    printStats(v);
    break;
  case 3: // sumMultiples
    cout << "Sum Multiples Number of Values: ";
    cin >> n;
    cout << "Values: ";
    readIntVector(v, n);
    cout << "Max Value: ";
    cin >> k;
    cout << "Sum: ";
    cout << sumMultiples(v, k) << endl;
    break;
  case 4: // greaterThanK
    cout << "Greater than K Number of Values: ";
    cin >> n;
    cout << "Values: ";
    readIntVector(v, n);
    cout << "k: ";
    cin >> k;
    cout << "Result: ";
    greaterThanK(v, k);
    for (int j = 0; j < v.size(); j++) {
      cout << v[j] << " ";
    }
    break;
  case 5: // isSubarray
    cout << "Is Subarray Array Sizes: ";
    cin >> n >> m;
    cout << "Values for First Vector: ";
    for (int i = 0; i < n; i++) {
      cin >> s;
      a.push_back(s);
    }
    cout << "Values for Second Vector: ";
    for (int i = 0; i < m; i++) {
      cin >> s;
      b.push_back(s);
    }
    cout << "Result: ";
    cout << isSubarray(a, b) << endl;
    break;
  case 6: // naive prime sum
    cout << "Primes Max Value: ";
    cin >> n;
    cout << "Sum: " << sumPrimesA(n) << endl;
    break;
  case 7: // prime sum 2
    cout << "Primes Max Value: ";
    cin >> n;
    cout << "Sum: " << sumPrimesB(n) << endl;
    break;
  case 8: // sieve of eratosthenes
    cout << "Primes Max Value: ";
    cin >> n;
    cout << "Sum: " << sieveOfEratosthenes(n) << endl;
    break;
  case 9: // time primes
    cout << "Time Primes" << endl;
    timePrimes();
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

/***************************************************************************************************
 * Testing run times of different approaches to finding the sum of prime numbers
 * under a threshold *
 * *************************************************************************************************/
void timePrimes() {
  int sum = -1;
  chrono::high_resolution_clock::time_point start;
  chrono::high_resolution_clock::time_point end;
  double elapsed = -1;
  vector<int> x = {10, 100, 1000, 10000, 100000, 500000};
  for (int i = 0; i < x.size(); i++) {
    cout << "Value: " << x[i] << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesA(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed =
        chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "A ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesB(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed =
        chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "B ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sieveOfEratosthenes(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed =
        chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "C ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;
    cout << endl << endl;
  }

  cout << "Sieve of Eratosthenes on primes below 1 million" << endl;
  start = chrono::high_resolution_clock::now();
  long sum2 = sieveOfEratosthenes(1000000);
  end = chrono::high_resolution_clock::now();
  elapsed =
      chrono::duration_cast<chrono::duration<double>>(end - start).count();
  cout << "Sum: " << sum2 << ", Time elapsed: " << elapsed << endl;
  cout << endl << endl;
}
