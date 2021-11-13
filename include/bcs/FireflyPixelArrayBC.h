#pragma once
#include "NodalBC.h"
// #include "IntegratedBC.h"

class FireflyPixelArrayBC;

template <>
InputParameters validParams<FireflyPixelArrayBC>();

// class FireflyPixelArrayBC : public IntegratedBC
class FireflyPixelArrayBC : public NodalBC
{
public:
  static InputParameters validParams();
  FireflyPixelArrayBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  // virtual Real computeQpJacobian() override;

private:
  // Real _penalty;
  Real _pixel_intensity;
  Real _pixel_diameter;
  Real _pixel_center;
};
