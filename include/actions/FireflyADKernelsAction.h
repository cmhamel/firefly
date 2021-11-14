#pragma once
#include "Action.h"

class FireflyADKernelsAction : public Action
{
public:
  FireflyADKernelsAction(InputParameters params);

  virtual void act() override;
};

template <>
InputParameters validParams<FireflyADKernelsAction>();
