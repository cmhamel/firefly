#pragma once
#include "ADKernel.h"

class FireflyADRadiativeTransfer;

template <>
InputParameters validParams<FireflyADRadiativeTransfer>();

class FireflyADRadiativeTransfer : public ADKernel
{
public:
  static InputParameters validParams();
  FireflyADRadiativeTransfer(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:
  const ADMaterialProperty<Real> & _sigma;
  ADRealVectorValue _direction;
};
