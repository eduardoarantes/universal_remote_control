
#include <AUnit.h>
using namespace aunit;

test(example) {
  assertXxx(...)
  ...
}


void setup() {

  TestRunner::exclude("*");
  TestRunner::include("looping*");
  TestRunner::include("CustomTestAgain", "example*");
}

void loop() {
  TestRunner::run();
}