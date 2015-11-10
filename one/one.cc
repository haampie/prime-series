#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t defaultBound = 10000;

size_t getBound(int argc, char const **argv)
{
  return argc == 2 ? stoull(argv[1]) : defaultBound;
}

size_t countPrimesUnder(size_t upperbound)
{
  size_t primes = 0;

  vector<char> isPrime(upperbound, true);

  for (size_t number = 2; number != upperbound; ++number)
  {
    if (isPrime[number])
    {
      // Count
      ++primes;

      // Cross off multiples
      for (size_t multiple = 2 * number; multiple < upperbound; multiple += number)
        isPrime[multiple] = false;
    }
  }

  return primes;
}

int main(int argc, char const **argv)
{
  size_t primes = countPrimesUnder(getBound(argc, argv));

  cout << primes << '\n';
}