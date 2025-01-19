#include "defer.hpp"
#include <iostream>
#include <cassert>

void separator(const std::string& title) {
    std::cout << "\n============ " << title << " ============\n\n";
}

void TestAlways() {
    separator("Test Always Mode");

    try {
        DEFER { std::cout << "Always mode - normal scope exit.\n"; };
        std::cout << "Inside scope (normal).\n";
    }
    catch (...) {
        std::cout << "Exception caught (should not occur).\n";
    }

    try {
        DEFER { std::cout << "Always mode - exception scope exit.\n"; };
        std::cout << "Inside scope (exception).\n";
        throw std::runtime_error("Exception in scope.");
    }
    catch (...) {
        std::cout << "Exception caught.\n";
    }
}

void TestFailure() {
    separator("Test OnFailure Mode");

    try {
        DEFER_ON_FAILURE { std::cout << "OnFailure mode - normal scope exit (should not trigger).\n"; };
        std::cout << "Inside scope (normal).\n";
    }
    catch (...) {
        std::cout << "Exception caught (should not occur).\n";
    }

    try {
        DEFER_ON_FAILURE { std::cout << "OnFailure mode - exception scope exit.\n"; };
        std::cout << "Inside scope (exception).\n";
        throw std::runtime_error("Exception in scope.");
    }
    catch (...) {
        std::cout << "Exception caught.\n";
    }
}

void TestSuccess() {
    separator("Test OnSuccess Mode");

    try {
        DEFER_ON_SUCCESS { std::cout << "OnSuccess mode - normal scope exit.\n"; };
        std::cout << "Inside scope (normal).\n";
    }
    catch (...) {
        std::cout << "Exception caught (should not occur).\n";
    }

    try {
        DEFER_ON_SUCCESS { std::cout << "OnSuccess mode - exception scope exit (should not trigger).\n"; };
        std::cout << "Inside scope (exception).\n";
        throw std::runtime_error("Exception in scope.");
    }
    catch (...) {
        std::cout << "Exception caught.\n";
    }
}


int main() {
    std::cout << "Starting Tests:\n";

    TestAlways();
    TestFailure();
    TestSuccess();

    separator("All Tests Completed");
}
