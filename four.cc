#include <iostream>
#include <string>
#include <vector>

using namespace std;

uint64_t count(uint64_t n)
{
  uint64_t m = n / 2;

  vector<char> is_prime(m, true);

  // Sieve
  for (uint64_t k = 1; 2 * k * (k + 1) < m; ++k)
    if (is_prime[k])
      for (uint64_t multiple = 2 * k * (k + 1); multiple < m; multiple += 2 * k + 1)
        is_prime[multiple] = false;

  // Count
  uint64_t primes = 1;

  for (uint64_t k = 1; k < m; ++k)
    if (is_prime[k])
      ++primes;

  return primes;
}

int main(int argc, char const **argv)
{
  uint64_t n = (argc == 2 ? stoull(argv[1]) : 1'000'000);
  uint64_t primes = count(n);
  cout << primes << '\n';
}