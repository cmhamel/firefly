#include "FireflyDegreeOfCure.h"
registerMooseObject("FireflyApp", FireflyDegreeOfCure);

template<>
InputParameters
validParams<FireflyDegreeOfCure>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<Real>("initial_monomer_concentration",
    "initial_monomer_concentration");
  params.addRequiredCoupledVar("monomer_concentration",
    "monomer_concentration");
  return params;
}

FireflyDegreeOfCure::FireflyDegreeOfCure(const InputParameters & parameters)
  : AuxKernel(parameters),
    _initial_monomer_concentration(getParam<Real>("initial_monomer_concentration")),
    _monomer_concentration(coupledValue("monomer_concentration"))
{}

Real
FireflyDegreeOfCure::computeValue()
{
  return 1.0 - _monomer_concentration[_qp] / _initial_monomer_concentration;
}
