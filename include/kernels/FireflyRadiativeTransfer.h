#pragma once
#include "Kernel.h"

class FireFlyRadiativeTransfer;

template <>
InputParameters validParams<FireFlyRadiativeTransfer>();

class FireflyRadiativeTransfer : public Kernel
{
public:
  static InputParameters validParams();
  FireflyRadiativeTransfer(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  // const MaterialProperty<Real> _sigma;

private:
  const MaterialProperty<Real> & _sigma;
  RealVectorValue _direction;
};
