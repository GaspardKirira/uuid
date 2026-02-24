/**
 * @file uuid.hpp
 * @brief Minimal UUID v4 generator for modern C++.
 *
 * Header-only library generating RFC 4122 compliant UUID version 4.
 *
 * Depends on:
 *   - secure_random (Vix Registry)
 *
 * Features:
 *   - uuid::v4_bytes()  -> 16 raw bytes
 *   - uuid::v4()        -> canonical lowercase string
 *
 * Format:
 *   xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
 *
 * Version: 4 (random)
 * Variant: RFC 4122
 *
 * Design goals:
 *   - Minimal API
 *   - Header-only
 *   - Cryptographically secure randomness
 *   - Deterministic formatting
 *
 * MIT License
 */

#pragma once

#include <array>
#include <cstdint>
#include <string>

#include <secure_random/secure_random.hpp>

namespace uuid
{
  namespace detail
  {
    /**
     * @brief Convert a 4-bit value to lowercase hex digit.
     */
    inline char hex_digit(std::uint8_t v) noexcept
    {
      return "0123456789abcdef"[v & 0x0F];
    }

    /**
     * @brief Convert 16 UUID bytes to canonical string form.
     *
     * @param bytes 16-byte UUID
     * @return 36-character canonical UUID string
     */
    inline std::string to_canonical_string(
        const std::array<std::uint8_t, 16> &bytes)
    {
      std::string out;
      out.resize(36);

      std::size_t oi = 0;

      for (std::size_t i = 0; i < 16; ++i)
      {
        if (oi == 8 || oi == 13 || oi == 18 || oi == 23)
          out[oi++] = '-';

        out[oi++] = hex_digit(static_cast<std::uint8_t>(bytes[i] >> 4));
        out[oi++] = hex_digit(bytes[i]);
      }

      return out;
    }
  }

  /**
   * @brief Generate a UUID v4 as raw bytes.
   *
   * Sets:
   *   - Version field to 4
   *   - Variant field to RFC 4122 (10xxxxxx)
   *
   * @return 16-byte UUID
   */
  inline std::array<std::uint8_t, 16> v4_bytes()
  {
    std::array<std::uint8_t, 16> bytes{};

    const auto rnd = secure_random::bytes(16);
    for (std::size_t i = 0; i < 16; ++i)
      bytes[i] = rnd[i];

    // Set version (4)
    bytes[6] = static_cast<std::uint8_t>((bytes[6] & 0x0F) | 0x40);

    // Set variant (RFC 4122)
    bytes[8] = static_cast<std::uint8_t>((bytes[8] & 0x3F) | 0x80);

    return bytes;
  }

  /**
   * @brief Generate a UUID v4 canonical string.
   *
   * Example:
   *   550e8400-e29b-41d4-a716-446655440000
   *
   * @return Lowercase UUID string (36 chars)
   */
  inline std::string v4()
  {
    const auto b = v4_bytes();
    return detail::to_canonical_string(b);
  }

} // namespace uuid
