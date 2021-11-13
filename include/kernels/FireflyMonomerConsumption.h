#pragma once
#include "Kernel.h"

class FireFlyMonomerConsumption;

template <>
InputParameters validParams<FireFlyMonomerConsumption>();

class FireflyMonomerConsumption : public Kernel
{
public:
  static InputParameters validParams();
  FireflyMonomerConsumption(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int) override;

  // const MaterialProperty<Real> _sigma;

private:
  unsigned int _C_R_var;
  const VariableValue & _C_R;
  const MaterialProperty<Real> & _k_p;
  const MaterialProperty<Real> & _dk_p_dC_M;
};
