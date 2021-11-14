#pragma once
#include "Action.h"

class FireflyICAction : public Action
{
public:
  FireflyICAction(InputParameters params);

  virtual void act() override;
};

template <>
InputParameters validParams<FireflyICAction>();
