# defer - C++ Implementation of Golang's defer Keyword
Tiny C++ implementation of golang `defer` keyword. <br>
A lightweight, header-only implementation that runs specific actions when the scope exits similar to the `defer` keyword in go, with optional execution based on success or failure inside that scope. This library emulates the functionality of `std::scope_exit` and its variants.

---
## **Features**
* Automatically run cleanup code on exiting a scope.
* **Conditional Execution**:
  * **Always** Mode: Executes **regardless** of scope outcome.
  * **Failure** Mode: Executes only if the scope exits due to an **exception**.
  * **Success** Mode: Executes only if the scope exits **without exceptions**.

---
## **Usage**
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
You can also use lower-case macros i.e. `defer`, `defer_on_success`, and `defer_on_failure` too.

---
## **Minimum Requirements**
* **C++ Version**: C++11 or above.
* **Dependencies**: Standard library components (`<functional>`, `<exception>`).

---
## **Alternatives**
* **GSL (gsl::final_action)**: Provided by the Guideline Support Library, offering `final_action` for cleanup.
* **Do while loops**: Do while loops for cleanup too. Check this silly code snippet <br>
```c
char* buffer;
unsigned char* buffer2;
do {
  buffer = malloc(128);
  buffer2 = calloc(256, sizeof unsigned char);
  Error e = foo();
  if (e.HasError) {
   break;
  }
  e = bar();
  if (e.HasError) {
   break;
  }
  printf("foo & bar were successful. yay!\n");
} while (false);
if (buffer) free(buffer);
if (buffer2) free(buffer2);
buffer = NULL; buffer2 = NULL; // we don't like dangling pointers, do we? #NoUAFBugs
```
Do while loops execute the code once no matter what the `while` takes (that's the reason it's below the loop code). <br>
`while(false)` will make sure that the code doesn't get executed again. 
* **std::scope_exit (experimental TS)**: A experimental utility (still not a part of C++ standard, I hope it gets standardized soon) that provides similar functionality.
```cpp
#include <scope>
std::scope_exit scopeExit = [] { std::cout << "Cleanup on scope exit\n"; };
```
**std::scope_failure (experimental TS)**: Executes a cleanup action only when the scope exits due to an exception. <br>
**std::scope_success (experimental TS)**: Executes a cleanup action only when the scope exits without an exception. <br>

---
## **Non-Working Functionality**
* **Exception Safety in Lambdas**: The implementation assumes the user-provided lambda functions are exception-safe.
* **No RAII Replacement**: While this implementation provides cleanup, it does not serve as a replacement for RAII (SBRM) patterns in C++.
* **Limited to Lambda Syntax**: The macros only support in-scope lambdas and cannot directly take reusable functions.

---
## **Why Use This Implementation?**
* **Simple and Lightweight**: Minimal overhead compared to full-featured libraries like GSL.
* **Flexible Modes**: Tailor cleanup actions to specific scope outcomes.

---
## **Contributing**
We welcome all the contributions to improve this tiny implementation! <br>
You can help by submitting issues, enhancements, or pull requests.

### How to Contribute:
1. **Fork the Repository**: Fork this repository to your GitHub account.
2. **Create a Branch**: Create a new branch for your changes.
3. **Make Changes**: Implement your changes, add tests, and ensure everything is working.
4. **Open a Pull Request (PR)**: Submit a pull request describing your changes.
Before contributing, please ensure the following:
* Your code adheres to the existing style.
* You have added tests for any new functionality.
* All tests are passing.
---

## Issues
Have any issues or bugs to report? Please use the GitHub issues to report any problems or request new features. <br>
1. Visit the Issues section.
2. Provide a description of the problem or feature request.
I'll try my best to help you.

---
## License
This library is provided as-is under an **CC0** license. <br>
See the `LICENSE` file. <br>

---
## Acknowledgments
Inspired by the `defer` keyword in Go and `std::scope_exit` family introduced as an experimental feature (still not standardized) and similar concepts in other programming languages.
