#include "FireflyRadiativeTransfer.h"
registerMooseObject("FireflyApp", FireflyRadiativeTransfer);
// defineLegacyParams(FireflyRadiativeTransfer);
template <>
InputParameters
validParams<FireflyRadiativeTransfer>()
{
  // InputParameters params = Kernel::validParams();
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Beer-Lambert law kernel");
  // params.addRequiredParam<MaterialPropertyName>("sigma", "light attentuation");
  params.addRequiredParam<RealVectorValue>("direction", "light direction");
  return params;
}

FireflyRadiativeTransfer::FireflyRadiativeTransfer(const InputParameters & params)
  : Kernel(params),
    _sigma(getMaterialProperty<Real>("sigma")),
    _direction(getParam<RealVectorValue>("direction"))
{}

Real
FireflyRadiativeTransfer::computeQpResidual()
{
  Real tau = _current_elem->hmin();
  Real residual = _direction * _grad_u[_qp] +
                  _sigma[_qp] * _u[_qp];
  return (_test[_i][_qp] + tau * _direction * _grad_test[_i][_qp]) * residual;
}

Real
FireflyRadiativeTransfer::computeQpJacobian()
{
  Real tau = _current_elem->hmin();
  Real tangent = _direction * _grad_phi[_j][_qp] +
                 _sigma[_qp] * _phi[_j][_qp];
  return (_test[_i][_qp] + tau * _direction * _grad_test[_i][_qp]) * tangent;
}
