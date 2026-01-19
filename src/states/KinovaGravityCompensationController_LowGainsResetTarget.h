#pragma once

#include <mc_control/fsm/State.h>

struct KinovaGravityCompensationController_LowGainsResetTarget : mc_control::fsm::State
{

  void configure(const mc_rtc::Configuration & config) override;

  void start(mc_control::fsm::Controller & ctl) override;

  bool run(mc_control::fsm::Controller & ctl) override;

  void teardown(mc_control::fsm::Controller & ctl) override;

private:

  bool compliant_ = false;
  double tau_ext_norm_threshold_ = 3.0;
  double tau_ext_norm_ = 0.0;
};
