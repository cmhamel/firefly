#include "FireflyADOxygenConsumption.h"
registerMooseObject("FireflyApp", FireflyADOxygenConsumption);

template <>
InputParameters
validParams<FireflyADOxygenConsumption>()
{
  InputParameters params = validParams<ADKernel>();
  params.addClassDescription("OxygenConsumption reaction rate kernel");
  params.addRequiredCoupledVar("radical_concentration",
                               "radical concentration variable");
  return params;
}

FireflyADOxygenConsumption::FireflyADOxygenConsumption(const InputParameters & params)
  : ADKernel(params),
    _C_R_var(coupled("radical_concentration")),
    _C_R(adCoupledValue("radical_concentration")),
    _k_O(getADMaterialProperty<Real>("k_O"))
{}

ADReal
FireflyADOxygenConsumption::computeQpResidual()
{
  return _test[_i][_qp] * _k_O[_qp] * _C_R[_qp] * _u[_qp];
}
