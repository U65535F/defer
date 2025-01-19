# defer
Tiny C++ implementation of golang `defer` keyword.
A lightweight, header-only implementation that runs specific actions when the scope exits similar to the `defer` keyword in go, with optional execution based on success or failure inside that scope. This library emulates the functionality of std::scope_exit and its variants for the projects that utilize C++ versions before the C++23 projects. 

## Features
* Automatically run cleanup code on exiting a scope.
* **Conditional Execution**:
* * **Always* Mode: Executes **regardless** of scope outcome.
* * **Failure** Mode: Executes only if the scope exits due to an **exception**.
* * **Success** Mode: Executes only if the scope exits **without exceptions**.
* Macros for Simplicity: Use `DEFER`, `DEFER_ON_FAILURE`, and `DEFER_ON_SUCCESS` for concise syntax.

## Usage
Include the header file in your project:
```cpp
#include "defer.h"
```
**Example**
```cpp
#include "defer.h"
#include <iostream>
#include <stdexcept>

int main() {
    std::cout << "Start\n";

    DEFER { std::cout << "Always Mode: Exiting scope.\n"; };

    try {
        DEFER_ON_FAILURE { std::cout << "Failure Mode: Exception occurred.\n"; };
        throw std::runtime_error("An error occurred");
    } catch (...) {
        std::cout << "Caught an exception.\n";
    }

    DEFER_ON_SUCCESS { std::cout << "Success Mode: Scope exited normally.\n"; };

    return 0;
}
```
**Output**
```cpp
Start
Caught an exception.
Failure Mode: Exception occurred.
Always Mode: Exiting scope.
```

## Minimum Requirements
* **C++ Version**: C++11 or above.
* **Dependencies**: Standard library components (`<functional>`, `<exception>`).

## Alternatives
* **std::scope_exit (C++23)**: A standard utility that provides similar functionality but is unavailable in earlier C++ versions.
```cpp
#include <scope>
std::scope_exit scopeExit = [] { std::cout << "Cleanup on scope exit\n"; };
```
**std::scope_failure (C++23)**: Executes a cleanup action only when the scope exits due to an exception.
**std::scope_success (C++23**): Executes a cleanup action only when the scope exits without an exception. <br>
It is highly recommended that you use the alternatives provided by `C++23`. It is generally recommended because it avoids the task of using this external implementation.
* **GSL (gsl::final_action)**: Provided by the Guideline Support Library, offering `final_action` for cleanup.

## Non-Working Functionality
* **Exception Safety in Lambdas**: The implementation assumes the user-provided lambda functions are exception-safe.
* **No RAII Replacement**: While this implementation provides cleanup, it does not serve as a replacement for RAII patterns in C++.
* **Limited to Lambda Syntax**: The macros only support in-scope lambdas and cannot directly take reusable functions.
---
## Why Use This Library?
* **Pre-C++23 Compatibility**: Enables scoped cleanup in projects targeting older standards.
* **Simple and Lightweight**: Minimal overhead compared to full-featured libraries like GSL.
* **Flexible Modes**: Tailor cleanup actions to specific scope outcomes.

## License
This library is provided as-is under an CC0 license. See CC0 for more information. <br>
TL;dr: See the `LICENSE` file, GitHub provides you a TL;dr. <br>

## Acknowledgments
Inspired by the `defer` keyword in Go and `std::scope_exit` family introduced in C++23 and similar concepts in other programming languages.
