# uuid

Minimal UUID v4 generator for modern C++.

`uuid` provides RFC 4122 compliant version 4 (random) UUID generation.

Header-only. Cryptographically secure. Zero configuration.

Depends on:

-   `secure_random` (Vix Registry)

## Download

https://vixcpp.com/registry/pkg/gaspardkirira/uuid

## Why uuid?

Unlike ad-hoc random ID generators, this library:

-   Generates RFC 4122 compliant UUID v4
-   Uses cryptographically secure randomness
-   Produces canonical lowercase format
-   Is fully header-only
-   Has a minimal and explicit API

Perfect for:

-   Database identifiers
-   Distributed systems
-   Event IDs
-   Session identifiers
-   Message correlation IDs
-   Backend services
-   Microservices

## Installation

### Using Vix Registry

``` bash
vix add gaspardkirira/uuid
vix deps
```

### Manual

Clone the repository:

``` bash
git clone https://github.com/GaspardKirira/uuid.git
```

Add the `include/` directory to your project.

## Quick Examples

### Generate UUID String

``` cpp
#include <uuid/uuid.hpp>
#include <iostream>

int main()
{
  std::string id = uuid::v4();
  std::cout << id << "\n";
}
```

Example output:
```
    550e8400-e29b-41d4-a716-446655440000
```
-   36 characters
-   Lowercase hex
-   RFC 4122 compliant

### Generate Raw UUID Bytes

``` cpp
#include <uuid/uuid.hpp>
#include <iostream>

int main()
{
  auto bytes = uuid::v4_bytes();
  std::cout << "size: " << bytes.size() << "\n";
}
```

Returns exactly 16 bytes.

## API Overview

``` cpp
uuid::v4_bytes();
uuid::v4();
```

### uuid::v4_bytes()

Returns:

-   `std::array<std::uint8_t, 16>`

Sets:

-   Version field to 4
-   Variant field to RFC 4122

### uuid::v4()

Returns:

-   `std::string`

Canonical format:
```
    xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
```
Always lowercase.

## Technical Details

-   Uses `secure_random` for cryptographically secure randomness
-   Version field forced to 4
-   Variant field forced to RFC 4122 (`10xxxxxx`)
-   No dynamic allocation beyond final string construction
-   No global state
-   Fully deterministic formatting

## Tests

Run:

``` bash
vix build
vix tests
```

Tests verify:

-   Byte size correctness
-   Version bits
-   Variant bits
-   Canonical formatting
-   Lowercase hex output

## Design Philosophy

`uuid` focuses on:

-   Minimal surface area
-   Security by default
-   Strict RFC compliance
-   Zero runtime configuration
-   Clean integration with modern C++ systems

Built for serious backend infrastructure.

## License

MIT License
Copyright (c) Gaspard Kirira

