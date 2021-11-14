#pragma once
#include "ADKernel.h"

class FireFlyADMonomerConsumption;

template <>
InputParameters validParams<FireFlyADMonomerConsumption>();

class FireflyADMonomerConsumption : public ADKernel
{
public:
  static InputParameters validParams();
  FireflyADMonomerConsumption(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:
  unsigned int _C_R_var;
  const ADVariableValue & _C_R;
  const ADMaterialProperty<Real> & _k_p;
};
