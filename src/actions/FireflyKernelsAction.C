#include "FireflyKernelsAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("FireflyApp", FireflyKernelsAction, "add_kernel");

template <>
InputParameters
validParams<FireflyKernelsAction>()
{
  InputParameters params = validParams<Action>();
  params.addRequiredParam<std::vector<NonlinearVariableName>>("variables",
    "variable names to use for the photochemistry variables");
  params.addRequiredParam<RealVectorValue>("light_direction", "light direction");
  return params;
}

FireflyKernelsAction::FireflyKernelsAction(InputParameters params)
  : Action(params)
{}

void
FireflyKernelsAction::act()
{
  std::vector<NonlinearVariableName> variables =
    getParam<std::vector<NonlinearVariableName>>("variables");

  RealVectorValue light_direction = getParam<RealVectorValue>("light_direction");
  // MaterialProperty<Real> photoinitiator_diffusivity =
  //   getMaterialProperty<Real>("photoinitiator_diffusivity");

  std::vector<VariableName> light_variable_name;
  std::vector<VariableName> photoinitiator_variable_name;
  std::vector<VariableName> radical_variable_name;
  std::vector<VariableName> monomer_variable_name;
  std::vector<VariableName> oxygen_variable_name;

  mooseAssert(variables.size() == 5, "expected 5 variables for photopolymerization");

  // radiative transfer kernels
  //
  {
    InputParameters params = _factory.getValidParams("FireflyRadiativeTransfer");
    params.set<NonlinearVariableName>("variable") = variables[0];
    params.set<RealVectorValue>("direction") = light_direction;
    _problem->addKernel("FireflyRadiativeTransfer", "radiative_transfer", params);
  }

  // photoinitiator kernels
  //
  {
    InputParameters params = _factory.getValidParams("TimeDerivative");
    params.set<NonlinearVariableName>("variable") = variables[1];
    _problem->addKernel("TimeDerivative", "photodecomposition_time_derivative", params);
  }

  {
    InputParameters params = _factory.getValidParams("FireflyPhotoDecomposition");
    params.set<NonlinearVariableName>("variable") = variables[1];
    light_variable_name.push_back(variables[0]);
    params.set<std::vector<VariableName>>("light_intensity") = light_variable_name;
    _problem->addKernel("FireflyPhotoDecomposition", "photodecomposition_rate", params);
  }

  // radical termination and production
  //
  {
    InputParameters params = _factory.getValidParams("TimeDerivative");
    params.set<NonlinearVariableName>("variable") = variables[2];
    _problem->addKernel("TimeDerivative", "radical_termination_time_derivative", params);
  }

  {
    InputParameters params = _factory.getValidParams("FireflyRadicalRate");
    params.set<NonlinearVariableName>("variable") = variables[2];
    light_variable_name.push_back(variables[0]);
    photoinitiator_variable_name.push_back(variables[1]);
    // radical_variable_name.push_back(variables[2]);
    monomer_variable_name.push_back(variables[3]);
    oxygen_variable_name.push_back(variables[4]);
    params.set<std::vector<VariableName>>("light_intensity") = light_variable_name;
    params.set<std::vector<VariableName>>("photoinitiator_concentration") = photoinitiator_variable_name;
    // params.set<std::vector<VariableName>>("radical_concentration") = radical_variable_name;
    params.set<std::vector<VariableName>>("monomer_concentration") = monomer_variable_name;
    params.set<std::vector<VariableName>>("oxygen_concentration") = oxygen_variable_name;
    _problem->addKernel("FireflyRadicalRate", "radical_termination_rate", params);
  }

  // monomer consumption
  //
  {
    InputParameters params = _factory.getValidParams("TimeDerivative");
    params.set<NonlinearVariableName>("variable") = variables[3];
    _problem->addKernel("TimeDerivative", "monomer_consumption_time_derivative", params);
  }

  {
    InputParameters params = _factory.getValidParams("FireflyMonomerConsumption");
    params.set<NonlinearVariableName>("variable") = variables[3];
    radical_variable_name.push_back(variables[2]);
    params.set<std::vector<VariableName>>("radical_concentration") = radical_variable_name;
    _problem->addKernel("FireflyMonomerConsumption", "monomer_consumption_rate", params);
  }

  // oxygen consumption
  //
  {
    InputParameters params = _factory.getValidParams("TimeDerivative");
    params.set<NonlinearVariableName>("variable") = variables[4];
    _problem->addKernel("TimeDerivative", "oxygen_consumption_time_derivative", params);
  }

  {
    InputParameters params = _factory.getValidParams("FireflyOxygenConsumption");
    params.set<NonlinearVariableName>("variable") = variables[4];
    radical_variable_name.push_back(variables[2]);
    params.set<std::vector<VariableName>>("radical_concentration") = radical_variable_name;
    _problem->addKernel("FireflyOxygenConsumption", "oxygen_consumption_rate", params);
  }
}
