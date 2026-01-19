#include "KinovaGravityCompensationController_Initial.h"

#include "../KinovaGravityCompensationController.h"

void KinovaGravityCompensationController_Initial::configure(const mc_rtc::Configuration & config) {}

void KinovaGravityCompensationController_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
    // Enable feedback from external forces estimator
  if (!ctl.datastore().call<bool>("EF_Estimator::isActive")) {
    ctl.datastore().call("EF_Estimator::toggleActive");
  }
  // Setting residual gain of external forces estimator
  ctl.datastore().call<void, double>("EF_Estimator::setGain", 30.0);

  ctl.compPostureTask->reset();
  ctl.compPostureTask->stiffness(100.0);
  ctl.compPostureTask->makeCompliant(false);
}

bool KinovaGravityCompensationController_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
  // output("OK");
  return false;
}

void KinovaGravityCompensationController_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
}

EXPORT_SINGLE_STATE("KinovaGravityCompensationController_Initial", KinovaGravityCompensationController_Initial)
