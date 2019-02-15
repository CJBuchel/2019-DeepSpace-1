#pragma once

#include "Elevator.h"
#include "HarvesterIntake.h"

#include "strategy/Strategy.h"

class Lift : public curtinfrc::Elevator {
 public:
  Lift(curtinfrc::ElevatorConfig elevatorConfig, curtinfrc::control::PIDGains gain) : curtinfrc::Elevator(elevatorConfig, gain) {};

 private:
  // Collision stuffs?
};

class LiftManualStrategy : public curtinfrc::Strategy {
 public:
  LiftManualStrategy(Lift &lift, curtinfrc::JoystickGroup &joyGroup) : Strategy("Lift Manual"), _lift(lift), _joyGroup(joyGroup) {
    Requires(&lift);
    SetCanBeInterrupted(true);
    SetCanBeReused(true);
  };

  void OnUpdate(double dt) override;

 private:
  Lift &_lift;
  curtinfrc::JoystickGroup &_joyGroup;
};

class LiftGotoStrategy : public curtinfrc::Strategy {
 public: 
  LiftGotoStrategy(Lift &lift, double setpoint) : Strategy("Lift Goto"), _lift(lift), _setpoint(setpoint) {
    Requires(&lift);
    SetCanBeInterrupted(true);
    SetCanBeReused(false);
  };

  void OnStart() override;
  void OnUpdate(double dt) override;

 private:
  Lift &_lift;
  double _setpoint;
};

class LiftZeroStrategy : public curtinfrc::Strategy {
 public: 
  LiftZeroStrategy(Lift &lift, curtinfrc::Joystick &joy) : Strategy("Lift Zero"), _lift(lift), _joy(joy) {
    Requires(&lift);
    SetCanBeInterrupted(true);
    SetCanBeReused(false);
  };

  void OnStart() override;
  void OnUpdate(double dt) override;

 private:
  Lift &_lift;
  curtinfrc::Joystick &_joy;
};

