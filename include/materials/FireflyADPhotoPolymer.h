#pragma once
#include "ADMaterial.h"

class FireflyADPhotoPolymer;

//template <>
//InputParameters validParams<FireflyADPhotoPolymer>();

class FireflyADPhotoPolymer : public ADMaterial
{
public:
  FireflyADPhotoPolymer(const InputParameters & parameters);
  static InputParameters validParams();  

protected:
  virtual void computeQpProperties() override;

private:
  // Read in properties
  //
  // Absorption coefficients
  //
  const ADReal _alpha_I;
  const ADReal _A_absorber;
  const ADReal _A_monomer;
  const ADReal _A_polymer;
  //
  // photodecomposition coefficients
  //
  const ADReal _beta_input;
  const ADReal _m_input;
  //
  // radical/polymerization rates
  //
  const ADReal _k_TD0; // translation diffusion at zero conversion
  const ADReal _C_RD;  // reaction diffusion constant
  const ADReal _k_SD;  // segmental diffusion
  const ADReal _c;     // DOC multiplier
  const ADReal _k_p0;  // polymerization rate at zero conversion
  const ADReal _k_pD0; // diffusion controlled propagation reaction rate
  const ADReal _C_M0;  // initial monomer concentration
  const ADReal _k_O_input; // oxygen inhibition rate

  // Calculated properties
  //
  ADMaterialProperty<Real> & _sigma;
  ADMaterialProperty<Real> & _beta;
  ADMaterialProperty<Real> & _m;
  ADMaterialProperty<Real> & _k_term;
  ADMaterialProperty<Real> & _k_p;
  ADMaterialProperty<Real> & _k_O;
  ADMaterialProperty<Real> & _p;

  // coupled variable here
  //
  const ADVariableValue & _C_M;
};
