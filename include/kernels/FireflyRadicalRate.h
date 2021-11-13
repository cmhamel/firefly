#pragma once
#include "Kernel.h"

class FireFlyRadicalRate;

template <>
InputParameters validParams<FireFlyRadicalRate>();

class FireflyRadicalRate : public Kernel
{
public:
  static InputParameters validParams();
  FireflyRadicalRate(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int) override;

  // const MaterialProperty<Real> _sigma;

private:
  unsigned int _I_var;
  unsigned int _C_I_var;
  unsigned int _C_M_var;
  unsigned int _C_O_var;
  const VariableValue & _I;
  const VariableValue & _C_I;
  const VariableValue & _C_M;
  const VariableValue & _C_O;
  const MaterialProperty<Real> & _beta;
  const MaterialProperty<Real> & _m;
  const MaterialProperty<Real> & _k_term;
  const MaterialProperty<Real> & _dk_term_dC_M;
  const MaterialProperty<Real> & _k_O;
};
