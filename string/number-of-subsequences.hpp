#pragma once

#include <unordered_map>

template <typename Container, typename mint>
mint number_of_subsequences(const Container& S) {
  using Key = typename Container::value_type;
  std::unordered_map<Key, mint> last;
  mint total = 1;
  for (const auto& value : S) {
    mint& last_total = last[value];
    mint previous = last_total;
    last_total = total;
    total += total - previous;
  }
  return total - 1;
}

/**
 * @docs docs/string/number-of-subsequences.md
 */
