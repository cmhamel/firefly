#include "FireflyMonomerConsumption.h"
registerMooseObject("FireflyApp", FireflyMonomerConsumption);
// defineLegacyParams(FireflyMonomerConsumption);
template <>
InputParameters
validParams<FireflyMonomerConsumption>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("MonomerConsumption reaction rate kernel");
  params.addRequiredCoupledVar("radical_concentration",
                               "radical concentration variable");
  return params;
}

FireflyMonomerConsumption::FireflyMonomerConsumption(const InputParameters & params)
  : Kernel(params),
    _C_R_var(coupled("radical_concentration")),
    _C_R(coupledValue("radical_concentration")),
    _k_p(getMaterialProperty<Real>("k_p")),
    _dk_p_dC_M(getMaterialProperty<Real>("dk_p_dC_M"))
{}

Real
FireflyMonomerConsumption::computeQpResidual()
{
  return _test[_i][_qp] * _k_p[_qp] * _C_R[_qp] * _u[_qp];
}

Real
FireflyMonomerConsumption::computeQpJacobian()
{
  return _test[_i][_qp] * _k_p[_qp] * _C_R[_qp] * _phi[_j][_qp] +
         _test[_i][_qp] * _dk_p_dC_M[_qp] * _C_R[_qp] * _u[_qp];
  // TODO: need to fill out the nonlinear terms due to _k_p!!!
}

Real
FireflyMonomerConsumption::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _C_R_var)
  {
    return _test[_i][_qp] * _k_p[_qp] * _phi[_j][_qp] * _u[_qp];
    // no nonlinear terms here
  }
  else
    return 0.0;
}
