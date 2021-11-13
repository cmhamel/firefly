#pragma once
#include "Kernel.h"

class FireFlyPhotoDecomposition;

template <>
InputParameters validParams<FireFlyPhotoDecomposition>();

class FireflyPhotoDecomposition : public Kernel
{
public:
  static InputParameters validParams();
  FireflyPhotoDecomposition(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int) override;

  // const MaterialProperty<Real> _sigma;

private:
  unsigned int _I_var;
  const VariableValue & _I;
  const MaterialProperty<Real> & _beta;
};
