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

void test_should_add_code(void) {
    TEST_ASSERT_EQUAL("up", remoteControl.hasCode(0x123));
}
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_led_builtin_pin_number);
    UNITY_END();

    return 0;
}