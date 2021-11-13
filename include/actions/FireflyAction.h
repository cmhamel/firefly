#pragma once
#include "Action.h"

class FireflyAction : public Action
{
public:
  FireflyAction(InputParameters params);

  virtual void act() override;
};

template <>
InputParameters validParams<FireflyAction>();
