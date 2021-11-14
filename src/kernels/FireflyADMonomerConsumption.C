#include "FireflyADMonomerConsumption.h"
registerMooseObject("FireflyApp", FireflyADMonomerConsumption);

template <>
InputParameters
validParams<FireflyADMonomerConsumption>()
{
  InputParameters params = validParams<ADKernel>();
  params.addClassDescription("MonomerConsumption reaction rate kernel");
  params.addRequiredCoupledVar("radical_concentration",
                               "radical concentration variable");
  return params;
}

FireflyADMonomerConsumption::FireflyADMonomerConsumption(const InputParameters & params)
  : ADKernel(params),
    _C_R_var(coupled("radical_concentration")),
    _C_R(adCoupledValue("radical_concentration")),
    _k_p(getADMaterialProperty<Real>("k_p"))
{}

ADReal
FireflyADMonomerConsumption::computeQpResidual()
{
  return _test[_i][_qp] * _k_p[_qp] * _C_R[_qp] * _u[_qp];
}
