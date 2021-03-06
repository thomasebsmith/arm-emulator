#ifndef SRC_UTILS_BIT_UTILS_H
#define SRC_UTILS_BIT_UTILS_H

#include <cassert>
#include <tuple>
#include <type_traits>
#include <utility>

/*
 * Note: All systems are assumed to be either big-endian or
 * little-endian with 8-bit bytes.
 */
namespace Utils::BitUtils {
  /*
   * Determines whether the endianness of the current OS aligns with the ARM
   * ISA's endianness (little endian).
   */
  bool is_correct_endianness();

  /*
   * Flips the endianness of num, from big to little or little to big.
   * Note that the endianness of num does not matter, since flip_endianness
   * is its own inverse.
   */
  template <typename T>
  void flip_endianness(T &num) {
    static_assert(sizeof(T) > 0, "Cannot flip endianness of empty type");
    char *begin = reinterpret_cast<char *>(num);
    char *end = begin + sizeof(T) - 1;
    while (begin != end) {
      std::swap(*begin, *end);
      ++begin;
      --end;
    }
  }

  /*
   * Flips num's endianness if this system does not have the same endianness as
   * the ARM ISA.
   */
  template <typename T>
  T convert_endianness(T num) {
    if (!is_correct_endianness()) {
      flip_endianness(num);
    }
    return num;
  }

  /*
   * Returns a tuple of the sections of bits in data bounded by the provided
   * offsets.
   */
  template <typename T, typename U>
  constexpr auto extract_bits(T data, U offset) {
    return std::tuple<T>{data >> offset};
  }

  template <typename T, typename U, typename... Args>
  constexpr auto extract_bits(T data, U offset, U next_offset, Args... args) {
    // Needed since many bit operations are UB or disallowed on signed numbers.
    static_assert(
      std::is_unsigned_v<T>,
      "Cannot extract bits from signed numbers"
    );
    static_assert(
      std::is_unsigned_v<U>,
      "Cannot extract bits using signed offsets"
    );
    assert(next_offset > offset && "Successive offsets must increase");
    auto result = (
      (data >> offset) &
      ~(~static_cast<T>(0) << (next_offset - offset))
    );
    return std::tuple_cat(
      std::tuple<T>{result},
      extract_bits(data, next_offset, args...)
    );
  }
}

#endif
