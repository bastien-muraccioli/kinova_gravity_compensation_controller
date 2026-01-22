#pragma once

#include <mc_control/fsm/State.h>
#include <mc_tasks/CompliantEndEffectorTask.h>

struct KinovaGravityCompensationController_DualCompliance : mc_control::fsm::State
{

  void configure(const mc_rtc::Configuration & config) override;

  void start(mc_control::fsm::Controller & ctl) override;

  bool run(mc_control::fsm::Controller & ctl) override;

  void teardown(mc_control::fsm::Controller & ctl) override;

  std::shared_ptr<mc_tasks::CompliantEndEffectorTask> compEETask;

private:

  bool compliant_ = false;
  double tau_ext_threshold_ = 1.0;
  double tau_ext_EE_ = 0.0;
};
