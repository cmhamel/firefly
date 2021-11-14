#include "FireflyICAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("FireflyApp", FireflyICAction, "add_ic");

template <>
InputParameters
validParams<FireflyICAction>()
{
  InputParameters params = validParams<Action>();
  params.addRequiredParam<std::vector<NonlinearVariableName>>("variables",
    "variable names to use for the photochemistry variables");
  params.addRequiredParam<Real>("photoinitiator_concentration", "photoinitiator_concentration");
  params.addRequiredParam<Real>("monomer_concentration", "photoinitiator_concentration");
  params.addRequiredParam<Real>("oxygen_concentration", "oxygen_concentration");
  return params;
}

FireflyICAction::FireflyICAction(InputParameters params)
  : Action(params)
{}

void
FireflyICAction::act()
{
  std::vector<NonlinearVariableName> variables =
    getParam<std::vector<NonlinearVariableName>>("variables");

  std::vector<VariableName> light_intensity_variable_name;
  std::vector<VariableName> photoinitiator_variable_name;
  std::vector<VariableName> radical_variable_name;
  std::vector<VariableName> monomer_variable_name;
  std::vector<VariableName> oxygen_variable_name;

  Real light_intensity_ic = 0.0;
  Real photoinitiator_ic = getParam<Real>("photoinitiator_concentration");
  Real radical_ic = 0.0;
  Real monomer_ic = getParam<Real>("monomer_concentration");
  Real oxygen_ic = getParam<Real>("oxygen_concentration");

  mooseAssert(variables.size() == 5, "expected 5 variables for photopolymerization");

  // light intensity ic kernels
  //
  {
    InputParameters params = _factory.getValidParams("ConstantIC");
    params.set<VariableName>("variable") = variables[0];
    params.set<Real>("value") = light_intensity_ic;
    _problem->addInitialCondition("ConstantIC", "light_intensity_ic", params);
  }

  // photoinitiator ic kernels
  //
  {
    InputParameters params = _factory.getValidParams("ConstantIC");
    params.set<VariableName>("variable") = variables[1];
    params.set<Real>("value") = photoinitiator_ic;
    _problem->addInitialCondition("ConstantIC", "photo_initiator_ic", params);
  }

  // radical ic kernels
  //
  {
    InputParameters params = _factory.getValidParams("ConstantIC");
    params.set<VariableName>("variable") = variables[2];
    params.set<Real>("value") = radical_ic;
    _problem->addInitialCondition("ConstantIC", "radical_ic", params);
  }

  // monomer ic kernels
  //
  {
    InputParameters params = _factory.getValidParams("ConstantIC");
    params.set<VariableName>("variable") = variables[3];
    params.set<Real>("value") = monomer_ic;
    _problem->addInitialCondition("ConstantIC", "monomer_ic", params);
  }

  // oxygen ic kernels
  //
  {
    InputParameters params = _factory.getValidParams("ConstantIC");
    params.set<VariableName>("variable") = variables[4];
    params.set<Real>("value") = oxygen_ic;
    _problem->addInitialCondition("ConstantIC", "oxygen_ic", params);
  }
}
