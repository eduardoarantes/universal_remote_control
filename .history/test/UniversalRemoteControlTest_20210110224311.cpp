#include <unity.h>
#include <IUniversalRemoteControl.h>

RemoteControl remoteControl;

void setUp(void) {
    remoteControl = RemoteControl();
    remoteControl.addCode(0x123, "up");
}

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