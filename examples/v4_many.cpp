#include <uuid/uuid.hpp>

#include <iostream>

int main()
{
  for (int i = 0; i < 5; ++i)
    std::cout << uuid::v4() << "\n";

  return 0;
}
