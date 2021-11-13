#include "FireflyPixelArrayBC.h"
registerMooseObject("FireflyApp", FireflyPixelArrayBC);
defineLegacyParams(FireflyPixelArrayBC);

InputParameters
FireflyPixelArrayBC::validParams()
{
  // InputParameters params = IntegratedBC::validParams();
  InputParameters params = NodalBC::validParams();
  // params.set<Real>("penalty") = 1e6;
  params.set<Real>("pixel_intensity") = 0.0;
  params.set<Real>("pixel_diameter") = 1.0;
  params.set<Real>("pixel_center") = 0.0;
  params.addClassDescription("Pixel array light boundary condition");
  return params;
}

FireflyPixelArrayBC::FireflyPixelArrayBC(const InputParameters & parameters)
  : NodalBC(parameters),
  // : IntegratedBC(parameters),
    // _penalty(getParam<Real>("penalty")),
    _pixel_intensity(getParam<Real>("pixel_intensity")),
    _pixel_diameter(getParam<Real>("pixel_diameter")),
    _pixel_center(getParam<Real>("pixel_center"))
{}

Real
FireflyPixelArrayBC::computeQpResidual()
{
  // Real inside_exp_x;
  // Real inside_exp_y;
  // Real value;
  // value = _pixel_intensity *
  //         exp(-(_q_point[_qp] - _pixel_center) * (_q_point[_qp] - _pixel_center)
  //              / _pixel_diameter * _pixel_diameter);
  // return _u[_qp] - value;

  // inside_exp_x = ((*_q_point[0])[_qp] - inside_exp_x) * ((*_q_point[0])[_qp] - inside_exp_x) /
  //                (2.0 * _pixel_diameter_x * _pixel_diameter_x);
  // inside_exp_y = (_q_point[_qp][1] - inside_exp_y) * (_q_point[_qp][1] - inside_exp_y) /
  //                (2.0 * _pixel_diameter_y * _pixel_diameter_y);
  // value = _pixel_intensity * (exp(-inside_exp_x) + exp(-(inside_exp_y)));
  //
  // return _penalty * _test[_i][_qp] * (_u[_qp] - value);

  // std::cout << *_current_node << std::endl;
  // std::cout << *_current_node->processor_id() << std::endl;
  // std::cout << _current_node->processor_id() << std::endl;
  // std::cout << *_current_node->_coords << std::endl;
  // std::cout << _current_node-> << std::endl;
  return 0.0;

}

// Real
// FireflyPixelArrayBC::computeQpJacobian()
// {
//   return _penalty * _test[_i][_qp] * _phi[_j][_qp];
// }
