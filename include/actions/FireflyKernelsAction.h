#pragma once
#include "Action.h"

class FireflyKernelsAction : public Action
{
public:
  FireflyKernelsAction(InputParameters params);

  virtual void act() override;
};

template <>
InputParameters validParams<FireflyKernelsAction>();
