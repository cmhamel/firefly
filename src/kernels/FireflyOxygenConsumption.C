#include "FireflyOxygenConsumption.h"
registerMooseObject("FireflyApp", FireflyOxygenConsumption);
// defineLegacyParams(FireflyOxygenConsumption);
template <>
InputParameters
validParams<FireflyOxygenConsumption>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("OxygenConsumption reaction rate kernel");
  params.addRequiredCoupledVar("radical_concentration",
                               "radical concentration variable");
  return params;
}

FireflyOxygenConsumption::FireflyOxygenConsumption(const InputParameters & params)
  : Kernel(params),
    _C_R_var(coupled("radical_concentration")),
    _C_R(coupledValue("radical_concentration")),
    _k_O(getMaterialProperty<Real>("k_O"))
{}

Real
FireflyOxygenConsumption::computeQpResidual()
{
  return _test[_i][_qp] * _k_O[_qp] * _C_R[_qp] * _u[_qp];
}

Real
FireflyOxygenConsumption::computeQpJacobian()
{
  return _test[_i][_qp] * _k_O[_qp] * _C_R[_qp] * _phi[_j][_qp];
  // TODO: need to fill out the nonlinear terms due to _k_p!!!
}

Real
FireflyOxygenConsumption::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _C_R_var)
  {
    return _test[_i][_qp] * _k_O[_qp] * _phi[_j][_qp] * _u[_qp];
    // no nonlinear terms here
  }
  else
    return 0.0;
}
