#include "FireflyRadicalRate.h"
registerMooseObject("FireflyApp", FireflyRadicalRate);
// defineLegacyParams(FireflyRadicalRate);
template <>
InputParameters
validParams<FireflyRadicalRate>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("RadicalRate reaction rate kernel");
  params.addRequiredCoupledVar("light_intensity",
                               "radiative transfer variable");
  params.addRequiredCoupledVar("photoinitiator_concentration",
                               "photoinitiator concentration variable");
  params.addRequiredCoupledVar("monomer_concentration",
                               "monomer concentration variable");
  params.addRequiredCoupledVar("oxygen_concentration",
                               "oxygen concentration variable");
  return params;
}

FireflyRadicalRate::FireflyRadicalRate(const InputParameters & params)
  : Kernel(params),
    _I_var(coupled("light_intensity")),
    _C_I_var(coupled("photoinitiator_concentration")),
    _C_M_var(coupled("monomer_concentration")),
    _C_O_var(coupled("oxygen_concentration")),
    _I(coupledValue("light_intensity")),
    _C_I(coupledValue("photoinitiator_concentration")),
    _C_M(coupledValue("monomer_concentration")),
    _C_O(coupledValue("oxygen_concentration")),
    _beta(getMaterialProperty<Real>("beta")),
    _m(getMaterialProperty<Real>("m")),
    _k_term(getMaterialProperty<Real>("k_term")),
    _dk_term_dC_M(getMaterialProperty<Real>("dk_term_dC_M")),
    _k_O(getMaterialProperty<Real>("k_O"))
{}

Real
FireflyRadicalRate::computeQpResidual()
{
  return -_test[_i][_qp] * _beta[_qp] * _m[_qp] * _I[_qp] * _C_I[_qp] +
         2.0 * _test[_i][_qp] * _k_term[_qp] * _u[_qp] * _u[_qp] +
         _test[_i][_qp] * _k_O[_qp] * _C_O[_qp] * _u[_qp];
}

Real
FireflyRadicalRate::computeQpJacobian()
{
  return 4.0 * _test[_i][_qp] * _k_term[_qp] * _u[_qp] * _phi[_j][_qp] +
         _test[_i][_qp] * _k_O[_qp] * _C_O[_qp] * _phi[_j][_qp];
}

Real
FireflyRadicalRate::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _I_var)
  {
    return _test[_i][_qp] * _beta[_qp] * _m[_qp] * _phi[_j][_qp] * _C_I[_qp];
  }
  else if (jvar == _C_I_var)
  {
    return -_test[_i][_qp] * _beta[_qp] * _m[_qp] * _I[_qp] * _phi[_j][_qp];
  }
  else if (jvar == _C_M_var)
  {
    return 2.0 * _test[_i][_qp] * _dk_term_dC_M[_qp] * _u[_qp] * _u[_qp];
  }
  else if (jvar == _C_O_var)
  {
    return _test[_i][_qp] * _k_O[_qp] * _phi[_j][_qp] * _u[_qp];
  }
  else
    return 0.0;
}
