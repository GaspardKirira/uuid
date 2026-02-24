#include <uuid/uuid.hpp>

#include <iostream>

int main()
{
  const auto b = uuid::v4_bytes();

  std::cout << "uuid v4 bytes: " << b.size() << "\n";
  std::cout << "version nibble: " << ((b[6] >> 4) & 0x0F) << "\n";
  std::cout << "variant bits  : " << ((b[8] & 0xC0) >> 6) << "\n";
  return 0;
}
