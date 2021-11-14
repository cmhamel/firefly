#include "FireflyADRadicalRate.h"
registerMooseObject("FireflyApp", FireflyADRadicalRate);

template <>
InputParameters
validParams<FireflyADRadicalRate>()
{
  InputParameters params = validParams<ADKernel>();
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

FireflyADRadicalRate::FireflyADRadicalRate(const InputParameters & params)
  : ADKernel(params),
    _I_var(coupled("light_intensity")),
    _C_I_var(coupled("photoinitiator_concentration")),
    _C_M_var(coupled("monomer_concentration")),
    _C_O_var(coupled("oxygen_concentration")),
    _I(adCoupledValue("light_intensity")),
    _C_I(adCoupledValue("photoinitiator_concentration")),
    _C_M(adCoupledValue("monomer_concentration")),
    _C_O(adCoupledValue("oxygen_concentration")),
    _beta(getADMaterialProperty<Real>("beta")),
    _m(getADMaterialProperty<Real>("m")),
    _k_term(getADMaterialProperty<Real>("k_term")),
    _k_O(getADMaterialProperty<Real>("k_O"))
{}

ADReal
FireflyADRadicalRate::computeQpResidual()
{
  return -_test[_i][_qp] * _beta[_qp] * _m[_qp] * _I[_qp] * _C_I[_qp] +
         2.0 * _test[_i][_qp] * _k_term[_qp] * _u[_qp] * _u[_qp] +
         _test[_i][_qp] * _k_O[_qp] * _C_O[_qp] * _u[_qp];
}
