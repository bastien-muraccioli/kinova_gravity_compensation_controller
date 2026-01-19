#pragma once

#include <mc_control/fsm/Controller.h>
#include <mc_tasks/CompliantPostureTask.h>

#include "api.h"

struct KinovaGravityCompensationController_DLLAPI KinovaGravityCompensationController : public mc_control::fsm::Controller
{
  KinovaGravityCompensationController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

  bool run() override;

  void reset(const mc_control::ControllerResetData & reset_data) override;

  std::shared_ptr<mc_tasks::CompliantPostureTask> compPostureTask;

private:
  mc_rtc::Configuration config_;
};
