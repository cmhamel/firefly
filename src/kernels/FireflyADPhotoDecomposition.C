#include "FireflyADPhotoDecomposition.h"
registerMooseObject("FireflyApp", FireflyADPhotoDecomposition);

template <>
InputParameters
validParams<FireflyADPhotoDecomposition>()
{
  InputParameters params = validParams<ADKernel>();
  params.addClassDescription("Photodecomposition reaction rate kernel");
  params.addRequiredCoupledVar("light_intensity", "radiative transfer variable");
  return params;
}

FireflyADPhotoDecomposition::FireflyADPhotoDecomposition(const InputParameters & params)
  : ADKernel(params),
    _I_var(coupled("light_intensity")),
    _I(adCoupledValue("light_intensity")),
    _beta(getADMaterialProperty<Real>("beta"))
{}

ADReal
FireflyADPhotoDecomposition::computeQpResidual()
{
  return _test[_i][_qp] * _beta[_qp] * _I[_qp] * _u[_qp];
}
