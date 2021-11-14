#pragma once
#include "ADKernel.h"

class FireflyADPhotoDecomposition;

template <>
InputParameters validParams<FireflyADPhotoDecomposition>();

class FireflyADPhotoDecomposition : public ADKernel
{
public:
  static InputParameters validParams();
  FireflyADPhotoDecomposition(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:
  unsigned int _I_var;
  const ADVariableValue & _I;
  const ADMaterialProperty<Real> & _beta;
};
