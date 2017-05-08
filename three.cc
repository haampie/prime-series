#include <iostream>
#include <string>
#include <vector>

using namespace std;

uint64_t count(uint64_t n)
{
  uint64_t primes = 1;

  vector<char> is_prime(n, true);

  // Sieve
  for (uint64_t k = 3; k * k < n; k += 2)
    if (is_prime[k])
      for (uint64_t multiple = k * k; multiple < n; multiple += 2 * k)
        is_prime[multiple] = false;

  // Count
  for (uint64_t k = 3; k < n; k += 2)
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