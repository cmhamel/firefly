#include "FireflyADRadiativeTransfer.h"
registerMooseObject("FireflyApp", FireflyADRadiativeTransfer);
// defineLegacyParams(FireflyRadiativeTransfer);
template <>
InputParameters
validParams<FireflyADRadiativeTransfer>()
{
  InputParameters params = validParams<ADKernel>();
  params.addClassDescription("Beer-Lambert law kernel");
  params.addRequiredParam<RealVectorValue>("direction", "light direction");
  return params;
}

FireflyADRadiativeTransfer::FireflyADRadiativeTransfer(const InputParameters & params)
  : ADKernel(params),
    _direction(getParam<RealVectorValue>("direction")),
    _sigma(getADMaterialProperty<Real>("sigma"))

{}

ADReal
FireflyADRadiativeTransfer::computeQpResidual()
{
  ADReal tau = _current_elem->hmin();
  ADReal residual = _direction * _grad_u[_qp] +
                  _sigma[_qp] * _u[_qp];
  return (_test[_i][_qp] + tau * _direction * _grad_test[_i][_qp]) * residual;
}
