#include "KinovaGravityCompensationController.h"

KinovaGravityCompensationController::KinovaGravityCompensationController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::fsm::Controller(rm, dt, config, Backend::TVM)
{
  // Initialize the constraints
  selfCollisionConstraint->setCollisionsDampers(solver(), {1.8, 40.0});
  dynamicsConstraint = mc_rtc::unique_ptr<mc_solver::DynamicsConstraint>(
      new mc_solver::DynamicsConstraint(
          robots(), 0, {0.1, 0.01, 0.0, 1.8, 70.0}, 0.9, true));
  solver().addConstraintSet(dynamicsConstraint);

  // Remove the default posture task created by the FSM
  solver().removeTask(getPostureTask(robot().name()));
  
  // Create the compliant posture task
  compPostureTask = std::make_shared<mc_tasks::CompliantPostureTask>(
      solver(), robot().robotIndex(), 1, 1);
  compPostureTask->reset();
  compPostureTask->stiffness(100.0);
  solver().addTask(compPostureTask);

  datastore().make<std::string>("ControlMode", "Torque");
  datastore().make<std::string>("TorqueMode", "Custom");
  datastore().make_call("getPostureTask", [this]() -> mc_tasks::PostureTaskPtr { return postureTask; });

  mc_rtc::log::success("KinovaGravityCompensationController init done ");
}

bool KinovaGravityCompensationController::run()
{
  return mc_control::fsm::Controller::run(
        mc_solver::FeedbackType::ClosedLoopIntegrateReal);
}

void KinovaGravityCompensationController::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::fsm::Controller::reset(reset_data);
}
