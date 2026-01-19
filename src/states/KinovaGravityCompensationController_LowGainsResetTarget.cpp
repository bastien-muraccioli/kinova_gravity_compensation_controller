#include "KinovaGravityCompensationController_LowGainsResetTarget.h"

#include "../KinovaGravityCompensationController.h"

void KinovaGravityCompensationController_LowGainsResetTarget::configure(const mc_rtc::Configuration & config) {}

void KinovaGravityCompensationController_LowGainsResetTarget::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
  ctl.compPostureTask->reset();
  ctl.compPostureTask->stiffness(100.0);
  ctl.compPostureTask->makeCompliant(false);

  ctl.gui()->addElement(this, {"LowGainsResetTarget"},
                        mc_rtc::gui::NumberInput(
                            "External Torque Norm Threshold",
                            [this]() { return tau_ext_norm_threshold_; },
                            [this](double threshold) {
                              tau_ext_norm_threshold_ = threshold;
                            }));
  ctl.gui()->addElement(
      {"LowGainsResetTarget"},
      mc_rtc::gui::Label("Current External Torque Norm: ",
                         [this]() { return tau_ext_norm_; }));
}

bool KinovaGravityCompensationController_LowGainsResetTarget::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);

  auto extTorqueSensor = ctl.robot().device<mc_rbdyn::VirtualTorqueSensor>("ExtTorquesVirtSensor");
  tau_ext_norm_ = extTorqueSensor.torques().norm();

  if(tau_ext_norm_ > tau_ext_norm_threshold_ && !compliant_){
    mc_rtc::log::info("Compliant mode activated");
    compliant_ = true;
    ctl.compPostureTask->stiffness(0.0);
    ctl.compPostureTask->damping(5.0);
    ctl.compPostureTask->makeCompliant(true);
  }
  else if(tau_ext_norm_ <= tau_ext_norm_threshold_ && compliant_){
    mc_rtc::log::info("Compliant mode deactivated");
    compliant_ = false;
    ctl.compPostureTask->reset();
    ctl.compPostureTask->stiffness(100.0);
    ctl.compPostureTask->makeCompliant(false);
  }

  // output("OK");
  return false;
}

void KinovaGravityCompensationController_LowGainsResetTarget::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
  ctl.gui()->removeElement({"LowGainsResetTarget"}, "External Torque Norm Threshold");
  ctl.gui()->removeElement({"LowGainsResetTarget"}, "Current External Torque Norm: ");
}

EXPORT_SINGLE_STATE("KinovaGravityCompensationController_LowGainsResetTarget", KinovaGravityCompensationController_LowGainsResetTarget)
