#pragma once
#include "ADKernel.h"

class FireFlyADRadicalRate;

template <>
InputParameters validParams<FireFlyADRadicalRate>();

class FireflyADRadicalRate : public ADKernel
{
public:
  static InputParameters validParams();
  FireflyADRadicalRate(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:
  unsigned int _I_var;
  unsigned int _C_I_var;
  unsigned int _C_M_var;
  unsigned int _C_O_var;
  const ADVariableValue & _I;
  const ADVariableValue & _C_I;
  const ADVariableValue & _C_M;
  const ADVariableValue & _C_O;
  const ADMaterialProperty<Real> & _beta;
  const ADMaterialProperty<Real> & _m;
  const ADMaterialProperty<Real> & _k_term;
  const ADMaterialProperty<Real> & _k_O;
};
