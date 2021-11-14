#include "FireflyADPhotoPolymer.h"
#include <math.h>
registerMooseObject("FireflyApp", FireflyADPhotoPolymer);

template <>
InputParameters
validParams<FireflyADPhotoPolymer>()
{
  InputParameters params = validParams<ADMaterial>();
  params.addRequiredParam<Real>("alpha_I", "photoinitiator absorption");
  params.addRequiredParam<Real>("A_absorber", "photoabsorber absorption");
  params.addRequiredParam<Real>("A_monomer", "monomer absorption");
  params.addRequiredParam<Real>("A_polymer", "polymer absorption");
  params.addRequiredParam<Real>("beta_input", "beta parameter");
  params.addRequiredParam<Real>("m_input", "m parameter usually 2.0");
  params.addRequiredParam<Real>("translational_diffusion_at_zero_conversion",
                                "translational diffusion at zero conversion");
  params.addRequiredParam<Real>("reaction_diffusion_constant",
                                "reaction diffusion constant");
  params.addRequiredParam<Real>("segmental_diffusion", "segmental diffusion");
  params.addRequiredParam<Real>("relative_viscosity_coefficient",
                                "relative viscosity coefficient");
  params.addRequiredParam<Real>("polymerization_rate_at_zero_conversion",
                                "polymerization rate at zero conversion");
  params.addRequiredParam<Real>("diffusion_controlled_propagation_reaction_rate",
                                "diffusion controlled propagation reaction rate");
  params.addRequiredParam<Real>("initial_monomer_concentration",
                                "initial monomer concenetration");
  params.addRequiredParam<Real>("oxygen_inhibition_rate",
                                "oxygen inhibition rate");
  params.addRequiredCoupledVar("monomer_concentration",
                               "monomer concentration variable");
  return params;
}

FireflyADPhotoPolymer::FireflyADPhotoPolymer(const InputParameters & parameters)
  : ADMaterial(parameters),
    _alpha_I(getParam<Real>("alpha_I")),
    _A_absorber(getParam<Real>("A_absorber")),
    _A_monomer(getParam<Real>("A_monomer")),
    _A_polymer(getParam<Real>("A_polymer")),
    _beta_input(getParam<Real>("beta_input")),
    _m_input(getParam<Real>("m_input")),
    _k_TD0(getParam<Real>("translational_diffusion_at_zero_conversion")),
    _C_RD(getParam<Real>("reaction_diffusion_constant")),
    _k_SD(getParam<Real>("segmental_diffusion")),
    _c(getParam<Real>("relative_viscosity_coefficient")),
    _k_p0(getParam<Real>("polymerization_rate_at_zero_conversion")),
    _k_pD0(getParam<Real>("diffusion_controlled_propagation_reaction_rate")),
    _C_M0(getParam<Real>("initial_monomer_concentration")),
    _k_O_input(getParam<Real>("oxygen_inhibition_rate")),
    _sigma(declareADProperty<Real>("sigma")),
    _beta(declareADProperty<Real>("beta")),
    _m(declareADProperty<Real>("m")),
    _k_term(declareADProperty<Real>("k_term")),
    _k_p(declareADProperty<Real>("k_p")),
    _k_O(declareADProperty<Real>("k_O")),
    _p(declareADProperty<Real>("p")),
    _C_M(adCoupledValue("monomer_concentration"))
{}

void
FireflyADPhotoPolymer::computeQpProperties()
{
  // everything depends on _p so update that first
  //
  _p[_qp] = 1.0 - _C_M[_qp] / _C_M0;

  // other stuff
  //
  _sigma[_qp] = _A_absorber;
  _beta[_qp] = _beta_input;
  _m[_qp] = _m_input;
  _k_p[_qp] = _k_p0 / (1.0 + (_k_p0 / _k_pD0) * exp(_c * _p[_qp]));
  _k_term[_qp] = (1.0 / ((1.0 / _k_SD) + (exp(_c * _p[_qp]) / _k_TD0))) +
                 _C_RD * _k_p[_qp] * (1.0 - _p[_qp]);


  _k_O[_qp] = _k_O_input;
}
