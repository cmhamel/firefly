#include "FireflyPhotoDecomposition.h"
registerMooseObject("FireflyApp", FireflyPhotoDecomposition);
// defineLegacyParams(FireflyPhotoDecomposition);
template <>
InputParameters
validParams<FireflyPhotoDecomposition>()
{
  // InputParameters params = Kernel::validParams();
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Photodecomposition reaction rate kernel");
  params.addRequiredCoupledVar("light_intensity", "radiative transfer variable");
  return params;
}

FireflyPhotoDecomposition::FireflyPhotoDecomposition(const InputParameters & params)
  : Kernel(params),
    _I_var(coupled("light_intensity")),
    _I(coupledValue("light_intensity")),
    _beta(getMaterialProperty<Real>("beta"))
{}

Real
FireflyPhotoDecomposition::computeQpResidual()
{
  return _test[_i][_qp] * _beta[_qp] * _I[_qp] * _u[_qp];
}

Real
FireflyPhotoDecomposition::computeQpJacobian()
{
  return _test[_i][_qp] * _beta[_qp] * _I[_qp] * _phi[_j][_qp];
}

Real
FireflyPhotoDecomposition::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _I_var)
  {
    return _test[_i][_qp] * _beta[_qp] * _phi[_j][_qp] * _u[_qp];
  }
  else
    return 0.0;
}
