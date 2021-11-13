#pragma once
#include "Kernel.h"

class FireFlyOxygenConsumption;

template <>
InputParameters validParams<FireFlyOxygenConsumption>();

class FireflyOxygenConsumption : public Kernel
{
public:
  static InputParameters validParams();
  FireflyOxygenConsumption(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int) override;

  // const MaterialProperty<Real> _sigma;

private:
  unsigned int _C_R_var;
  const VariableValue & _C_R;
  const MaterialProperty<Real> & _k_O;
};
