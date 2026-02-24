#include <uuid/uuid.hpp>

#include <cstdlib>
#include <iostream>

static void expect_true(bool v, const char *msg)
{
  if (!v)
  {
    std::cerr << "FAIL: " << msg << "\n";
    std::exit(1);
  }
}

static bool is_hex_lower(char c)
{
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

int main()
{
  const auto bytes = uuid::v4_bytes();
  expect_true(bytes.size() == 16, "v4_bytes size");

  // Version check
  expect_true((bytes[6] >> 4) == 0x4, "version 4");

  // Variant check (10xxxxxx)
  expect_true((bytes[8] & 0xC0) == 0x80, "variant RFC4122");

  const std::string id = uuid::v4();

  expect_true(id.size() == 36, "string size");
  expect_true(id[8] == '-' && id[13] == '-' &&
                  id[18] == '-' && id[23] == '-',
              "dash positions");

  for (std::size_t i = 0; i < id.size(); ++i)
  {
    if (i == 8 || i == 13 || i == 18 || i == 23)
      continue;

    expect_true(is_hex_lower(id[i]), "lowercase hex");
  }

  expect_true(id[14] == '4', "version char is 4");

  const char v = id[19];
  expect_true(v == '8' || v == '9' || v == 'a' || v == 'b',
              "variant char valid");

  std::cout << "ok\n";
  return 0;
}
