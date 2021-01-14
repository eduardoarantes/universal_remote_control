#include <unity.h>

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_led_builtin_pin_number(void) {
    TEST_ASSERT_EQUAL(13, 13);
}
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_led_builtin_pin_number);
    UNITY_END();

    return 0;
}