// prime_tables.h
#ifndef GTEST_SAMPLES_PRIME_TABLES_H_
#define GTEST_SAMPLES_PRIME_TABLES_H_

#include <algorithm>

//typed test는 c++에서만 가능하므로 gTest의 sample 코드 그대로 썼다.
// The prime table interface.
// virtual 함수가 있으므로 이건 인터페이스 함수다.  즉 virtual 함수를 다른 클래스가 상속받아 구현하면 된다.
class PrimeTable {
 public:
  virtual ~PrimeTable() {}

  // Returns true iff n is a prime number.
  virtual bool IsPrime(int n) const = 0;

  // Returns the smallest prime number greater than p; or returns -1
  // if the next prime is beyond the capacity of the table.
  virtual int GetNextPrime(int p) const = 0;
};

// Implementation #1 calculates the primes on-the-fly.
// PrimeTable 인터페이스를 상속해서 구현한 OnTheFlyPrimeTable 클래스
class OnTheFlyPrimeTable : public PrimeTable {
 public:
  virtual bool IsPrime(int n) const {
    if (n <= 1) return false;

    for (int i = 2; i*i <= n; i++) {
      // n is divisible by an integer other than 1 and itself.
      if ((n % i) == 0) return false;
    }

    return true;
  }

  virtual int GetNextPrime(int p) const {
    for (int n = p + 1; n > 0; n++) {
      if (IsPrime(n)) return n;
    }

    return -1;
  }
};

// Implementation #2 pre-calculates the primes and stores the result
// in an array.
//PrimeTable 인터페이스를 상속 구현한 PreCalculatedPrimeTable 클래스
class PreCalculatedPrimeTable : public PrimeTable {
 public:
  // 'max' specifies the maximum number the prime table holds.
  explicit PreCalculatedPrimeTable(int max)
      : is_prime_size_(max + 1), is_prime_(new bool[max + 1]) {
    CalculatePrimesUpTo(max);
  }
  virtual ~PreCalculatedPrimeTable() { delete[] is_prime_; }

  virtual bool IsPrime(int n) const {
    return 0 <= n && n < is_prime_size_ && is_prime_[n];
  }

  virtual int GetNextPrime(int p) const {
    for (int n = p + 1; n < is_prime_size_; n++) {
      if (is_prime_[n]) return n;
    }

    return -1;
  }

 private:
  void CalculatePrimesUpTo(int max) {
    ::std::fill(is_prime_, is_prime_ + is_prime_size_, true);
    is_prime_[0] = is_prime_[1] = false;

    // Checks every candidate for prime number (we know that 2 is the only even
    // prime).
    for (int i = 2; i*i <= max; i += i%2+1) {
      if (!is_prime_[i]) continue;

      // Marks all multiples of i (except i itself) as non-prime.
      // We are starting here from i-th multiplier, because all smaller
      // complex numbers were already marked.
      for (int j = i*i; j <= max; j += i) {
        is_prime_[j] = false;
      }
    }
  }

  const int is_prime_size_;
  bool* const is_prime_;

  // Disables compiler warning "assignment operator could not be generated."
  void operator=(const PreCalculatedPrimeTable& rhs);
};

#endif  // GTEST_SAMPLES_PRIME_TABLES_H_
