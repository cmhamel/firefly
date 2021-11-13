#pragma once
#include "Material.h"

class FireflyPhotoPolymer;

template <>
InputParameters validParams<FireflyPhotoPolymer>();

class FireflyPhotoPolymer : public Material
{
public:
  FireflyPhotoPolymer(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

private:
  // Read in properties
  //
  // Absorption coefficients
  //
  const Real _alpha_I;
  const Real _A_absorber;
  const Real _A_monomer;
  const Real _A_polymer;
  //
  // photodecomposition coefficients
  //
  const Real _beta_input;
  const Real _m_input;
  //
  // radical/polymerization rates
  //
  const Real _k_TD0; // translation diffusion at zero conversion
  const Real _C_RD;  // reaction diffusion constant
  const Real _k_SD;  // segmental diffusion
  const Real _c;     // DOC multiplier
  const Real _k_p0;  // polymerization rate at zero conversion
  const Real _k_pD0; // diffusion controlled propagation reaction rate
  const Real _C_M0;  // initial monomer concentration
  const Real _k_O_input; // oxygen inhibition rate

  // Calculated properties
  //
  MaterialProperty<Real> & _sigma;
  MaterialProperty<Real> & _beta;
  MaterialProperty<Real> & _m;
  MaterialProperty<Real> & _k_term;
  MaterialProperty<Real> & _dk_term_dC_M;
  MaterialProperty<Real> & _k_p;
  MaterialProperty<Real> & _dk_p_dC_M;
  MaterialProperty<Real> & _k_O;
  MaterialProperty<Real> & _p;

  // coupled variable here
  //
  const VariableValue & _C_M;
};
