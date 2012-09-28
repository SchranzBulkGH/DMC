#include <igloo/igloo.h>
using namespace igloo;

Context(DefaultAdditionCalculator) {
  Spec(ShouldOutput4WhenAdding2And2) {
    Assert::That(2+2, Equals(4));
  }
};

