#include "KinovaGravityCompensationController_Initial.h"

#include "../KinovaGravityCompensationController.h"

void KinovaGravityCompensationController_Initial::configure(const mc_rtc::Configuration & config) {}

void KinovaGravityCompensationController_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
}

bool KinovaGravityCompensationController_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
  output("OK");
  return true;
}

void KinovaGravityCompensationController_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
}

EXPORT_SINGLE_STATE("KinovaGravityCompensationController_Initial", KinovaGravityCompensationController_Initial)
