#include "KinovaGravityCompensationController_GravityCompensationDamped.h"

#include "../KinovaGravityCompensationController.h"

void KinovaGravityCompensationController_GravityCompensationDamped::configure(const mc_rtc::Configuration & config) {}

void KinovaGravityCompensationController_GravityCompensationDamped::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
  ctl.compPostureTask->reset();
  ctl.compPostureTask->stiffness(0.0);
  ctl.compPostureTask->damping(5.0);
  ctl.compPostureTask->makeCompliant(true);
}

bool KinovaGravityCompensationController_GravityCompensationDamped::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
  // output("OK");
  return false;
}

void KinovaGravityCompensationController_GravityCompensationDamped::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
}

EXPORT_SINGLE_STATE("KinovaGravityCompensationController_GravityCompensationDamped", KinovaGravityCompensationController_GravityCompensationDamped)
