#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const size_t defaultBound = 10000;

size_t getBound(int argc, char const **argv)
{
  return argc == 2 ? stoull(argv[1]) : defaultBound;
}

size_t countPrimesUnder(size_t upperbound)
{
  size_t primes = 0;
  size_t sieverBound = static_cast<size_t>(sqrt(upperbound));

  vector<char> isPrime(upperbound, true);

  // Sieve
  for (size_t number = 2; number <= sieverBound; ++number)
    if (isPrime[number])
      for (size_t multiple = number * number; multiple < upperbound; multiple += number)
        isPrime[multiple] = false;

  // Count
  for (size_t number = 2; number != upperbound; ++number)
    if (isPrime[number])
      ++primes;

  return primes;
}

int main(int argc, char const **argv)
{
  size_t primes = countPrimesUnder(getBound(argc, argv));

  cout << primes << '\n';
}