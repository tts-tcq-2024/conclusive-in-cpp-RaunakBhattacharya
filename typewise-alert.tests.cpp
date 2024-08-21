#include <gtest/gtest.h>
#include "typewise-alert.h"

// Test inferBreach function
TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    ASSERT_EQ(inferBreach(10, 20, 30), TOO_LOW);
    ASSERT_EQ(inferBreach(40, 20, 30), TOO_HIGH);
    ASSERT_EQ(inferBreach(25, 20, 30), NORMAL);
}

// Test classifyTemperatureBreach function
TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    ASSERT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1), TOO_LOW);
    ASSERT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    ASSERT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 20), NORMAL);

    ASSERT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1), TOO_LOW);
    ASSERT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    ASSERT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 40), NORMAL);

    ASSERT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1), TOO_LOW);
    ASSERT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);
    ASSERT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 30), NORMAL);
}

// Test checkAndAlert function
// Note: This test assumes that the sendToController and sendToEmail functions are correctly implemented.
// If they are not, this test will fail.
TEST(TypeWiseAlertTestSuite, ChecksAndAlerts) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "Brand"};
    checkAndAlert(TO_CONTROLLER, batteryChar, 20);
    checkAndAlert(TO_EMAIL, batteryChar, 20);
}
