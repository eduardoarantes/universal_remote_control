
#include <AUnit.h>
using namespace aunit;

test(example) {
  assertEqual(1,1);
}


void setup() {

  TestRunner::exclude("*");
  TestRunner::include("looping*");
  TestRunner::include("CustomTestAgain", "example*");
}

void loop() {
  TestRunner::run();
}