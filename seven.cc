#include <iostream>
#include <cstdint>
#include <vector>

// Wheel:  |  x  x  x  x  x  |  x  x  x  |  x  |  x  x  x  |  x  |  x  x  x  |  x  x  x  x  x  |  x
//         1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
//        31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60

constexpr uint64_t primes = 8;
constexpr uint64_t width = 2 * 3 * 5;
constexpr uint64_t gap[]{4, 2, 4, 2, 4, 6, 2, 6};
constexpr uint64_t wheel_primes[]{7, 11, 13, 17, 19, 23, 29, 31};
constexpr uint64_t prime_to_gap[]{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7};

inline uint64_t idx2prime(uint64_t idx)
{
  // 0 -> 7, 1 -> 11, 2 -> 13, 3 -> 17
  return (idx / primes) * width + wheel_primes[idx % primes];
}

inline uint64_t prime2idx(uint64_t prime)
{
  // 7 -> 0, 11 -> 1, 13 -> 2
  auto d = prime / width;
  auto r = prime % width;
  return d * primes + prime_to_gap[r];
}

uint64_t count(uint64_t n)
{
  // TODO: n < 6?

  // Should be somewhat smaller...
  uint64_t size = n * 8 / 30;
  uint64_t count = 3;

  std::vector<uint8_t> is_prime(size, true);

  for (uint64_t i = 0; idx2prime(i) * idx2prime(i) < n; i++)
  {
    if (is_prime[i])
    {
      uint64_t p = idx2prime(i);

      // Given the prime number p, we cross off the multiples;
      // however, we must only cross off multiples without factors of 2, 3, 5.
      // E.g. 7 * 7, 7 * 11, 7 * 13, 7 * 17, 7 * 19, 7 * 23, 7 * 29, 7 * 31, 7 * 37, ...
      // E.g. 41 * 41, 41 * 43, 41 * 47, ...

      for (uint64_t q = p * p, j = prime_to_gap[p % width]; q < n; q += p * gap[j], j = (j + 1) % primes)
      {
        is_prime[prime2idx(q)] = false;
      }
    }
  }

  for (uint64_t i = 0; idx2prime(i) < n; i++)
    if (is_prime[i])
    {
      std::cout << idx2prime(i) << '\n';
      ++count;
    }

  return count;
}

int main()
{
  std::cout << prime2idx(19 * 19) << '\n';
    // std::cout << count(1000) << '\n';
}