#pragma once
#include "AuxKernel.h"

class FireflyDegreeOfCure;

template <>
InputParameters validParams<FireflyDegreeOfCure>();

class FireflyDegreeOfCure : public AuxKernel
{
public:
  FireflyDegreeOfCure(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _monomer_concentration;
  const Real _initial_monomer_concentration;
};
