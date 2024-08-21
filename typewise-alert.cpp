#include "typewise-alert.h"
#include <stdio.h>
#include <map>

const std::map<CoolingType, std::pair<int, int>> coolingLimits = {
    {PASSIVE_COOLING, {0, 35}},
    {HI_ACTIVE_COOLING, {0, 45}},
    {MED_ACTIVE_COOLING, {0, 40}}
};

const std::map<BreachType, std::string> emailMessages = {
    {TOO_LOW, "Hi, the temperature is too low\n"},
    {TOO_HIGH, "Hi, the temperature is too high\n"},
    {NORMAL, ""}
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  auto limits = coolingLimits.at(coolingType);
  return inferBreach(temperatureInC, limits.first, limits.second);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  if(alertTarget == TO_CONTROLLER) {
    sendToController(breachType);
  } else if(alertTarget == TO_EMAIL) {
    sendToEmail(breachType);
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  printf("To: %s\n", recepient);
  printf("%s", emailMessages.at(breachType).c_str());
}
