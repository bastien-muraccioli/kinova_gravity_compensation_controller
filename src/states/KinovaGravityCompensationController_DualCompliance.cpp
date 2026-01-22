#include "KinovaGravityCompensationController_DualCompliance.h"

#include "../KinovaGravityCompensationController.h"
#include <cstdlib>

void KinovaGravityCompensationController_DualCompliance::configure(const mc_rtc::Configuration & config) {}

void KinovaGravityCompensationController_DualCompliance::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
  compEETask = std::make_shared<mc_tasks::CompliantEndEffectorTask>(
      "end_effector_link", ctl.robots(), ctl.robot().robotIndex(), 1.0, 1000.0);

  compEETask->reset();
  compEETask->positionTask->stiffness(400.0);
  compEETask->orientationTask->stiffness(400.0);
  compEETask->makeCompliant(false);

  ctl.solver().addTask(compEETask);
  
  ctl.compPostureTask->reset();
  ctl.compPostureTask->stiffness(0.0);
  ctl.compPostureTask->damping(1.0);
  ctl.compPostureTask->makeCompliant(true);

  ctl.gui()->addElement(this, {"DualCompliance"},
                        mc_rtc::gui::NumberInput(
                            "External Torque Threshold",
                            [this]() { return tau_ext_threshold_; },
                            [this](double threshold) {
                              tau_ext_threshold_ = threshold;
                            }));
  ctl.gui()->addElement(
      {"DualCompliance"},
      mc_rtc::gui::Label("Current External Torque at the End Effector: ",
                         [this]() { return tau_ext_EE_; }));
}

bool KinovaGravityCompensationController_DualCompliance::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);

  auto extTorqueSensor = ctl.robot().device<mc_rbdyn::VirtualTorqueSensor>("ExtTorquesVirtSensor");
  tau_ext_EE_ = abs(extTorqueSensor.torques()[5]) + abs(extTorqueSensor.torques()[6]);

  if(tau_ext_EE_ > tau_ext_threshold_ && !compliant_){
    mc_rtc::log::info("Compliant mode activated");
    compliant_ = true;
    compEETask->positionTask->stiffness(0.0);
    compEETask->positionTask->damping(10.0);
    compEETask->orientationTask->stiffness(0.0);
    compEETask->orientationTask->damping(10.0);
    compEETask->makeCompliant(true);
  }
  else if(tau_ext_EE_ <= tau_ext_threshold_ && compliant_){
    mc_rtc::log::info("Compliant mode deactivated");
    compliant_ = false;
    compEETask->reset();
    compEETask->positionTask->stiffness(400.0);
    compEETask->orientationTask->stiffness(400.0);
    compEETask->makeCompliant(false);
  }

  // output("OK");
  return false;
}

void KinovaGravityCompensationController_DualCompliance::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KinovaGravityCompensationController &>(ctl_);
  ctl.gui()->removeElement({"DualCompliance"}, "External Torque Threshold");
  ctl.gui()->removeElement({"DualCompliance"}, "Current External Torque at the End Effector: ");
  ctl.solver().removeTask(compEETask);
}

EXPORT_SINGLE_STATE("KinovaGravityCompensationController_DualCompliance", KinovaGravityCompensationController_DualCompliance)
