#include <iostream>
#include <string>
#include <vector>

using namespace std;

uint64_t count(uint64_t n)
{
  uint64_t primes = 0;

  vector<char> is_prime(n, true);

  for (uint64_t k = 2; k < n; ++k)
  {
    if (is_prime[k])
    {
      // Count
      ++primes;

      // Cross off multiples
      for (uint64_t multiple = 2 * k; multiple < n; multiple += k)
        is_prime[multiple] = false;
    }
  }

  return primes;
}

int main(int argc, char const **argv)
{
  uint64_t n = (argc == 2 ? stoull(argv[1]) : 1'000'000);
  uint64_t primes = count(n);
  cout << primes << '\n';
}