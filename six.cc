#include <iostream>
#include <cstdint>
#include <vector>

// Wheel:  |  x  x  x  |  x
//         1  2  3  4  5  6
//         7  8  9 10 11 12
//        13 14 15 16 17 18
//        19 20 21 22 23 24

constexpr uint64_t primes = 2;
constexpr uint64_t width = 2 * 3;
constexpr uint64_t gap[]{2, 4};
constexpr uint64_t prime_to_gap[]{0, 0, 0, 0, 0, 1, 1};

inline uint64_t idx2prime(uint64_t idx)
{
  // 0 -> 5, 1 -> 7, 2 -> 11, 3 -> 13
  return 3 + (idx / primes) * width + gap[idx % primes];
}

inline uint64_t prime2idx(uint64_t idx)
{
  // 5 -> 0, 7 -> 1, 11 -> 2
  auto d = (idx - 3) / width;
  auto r = (idx - 3) % width;
  return d * primes + prime_to_gap[r + 1];
}

uint64_t count(uint64_t n)
{
  // TODO: what if n < 5?

  // Should be somewhat smaller...
  uint64_t size = n / 3;
  uint64_t count = 2;

  std::vector<uint8_t> is_prime(size, true);

  for (uint64_t i = 0; idx2prime(i) * idx2prime(i) < n; i++)
  {
    if (is_prime[i])
    {
      uint64_t p = idx2prime(i);

      std::cout << p << '\n';

      for (uint64_t q = p * p, j = prime_to_gap[p % width]; q < n; q += p * gap[j], j = (j + 1) % primes)
      {
        is_prime[prime2idx(q)] = false;
      }
    }
  }

  for (uint64_t i = 0; idx2prime(i) < n; i++)
    if (is_prime[i])
      ++count;

  return count;
}

int main()
{
  std::cout << count(10000);
}