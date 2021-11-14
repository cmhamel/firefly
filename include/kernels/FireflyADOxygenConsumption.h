#pragma once
#include "ADKernel.h"

class FireFlyADOxygenConsumption;

template <>
InputParameters validParams<FireFlyADOxygenConsumption>();

class FireflyADOxygenConsumption : public ADKernel
{
public:
  static InputParameters validParams();
  FireflyADOxygenConsumption(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  // const MaterialProperty<Real> _sigma;

private:
  unsigned int _C_R_var;
  const ADVariableValue & _C_R;
  const ADMaterialProperty<Real> & _k_O;
};
