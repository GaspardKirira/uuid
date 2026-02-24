#include <uuid/uuid.hpp>

#include <iostream>

int main()
{
  const std::string id = uuid::v4();

  std::cout << "uuid v4: " << id << "\n";
  std::cout << "length : " << id.size() << "\n";
  return 0;
}
