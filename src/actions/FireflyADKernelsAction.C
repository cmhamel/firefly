#include "FireflyADKernelsAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("FireflyApp", FireflyADKernelsAction, "add_kernel");

template <>
InputParameters
validParams<FireflyADKernelsAction>()
{
  InputParameters params = validParams<Action>();
  params.addRequiredParam<std::vector<NonlinearVariableName>>("variables",
    "variable names to use for the photochemistry variables");
  params.addRequiredParam<RealVectorValue>("light_direction", "light direction");
  params.addRequiredParam<MaterialPropertyName>("photoinitiator_diffusivity",
    "photoinitiator_diffusivity");
  params.addRequiredParam<MaterialPropertyName>("radical_diffusivity",
    "radical_diffusivity");
  params.addRequiredParam<MaterialPropertyName>("monomer_diffusivity",
    "monomer_diffusivity");
  params.addRequiredParam<MaterialPropertyName>("oxygen_diffusivity",
    "oxygen_diffusivity");
  return params;
}

FireflyADKernelsAction::FireflyADKernelsAction(InputParameters params)
  : Action(params)
{}

void
FireflyADKernelsAction::act()
{
  std::vector<NonlinearVariableName> variables =
    getParam<std::vector<NonlinearVariableName>>("variables");

  RealVectorValue light_direction = getParam<RealVectorValue>("light_direction");

  std::vector<VariableName> light_variable_name;
  std::vector<VariableName> photoinitiator_variable_name;
  std::vector<VariableName> radical_variable_name;
  std::vector<VariableName> monomer_variable_name;
  std::vector<VariableName> oxygen_variable_name;

  mooseAssert(variables.size() == 5, "expected 5 variables for photopolymerization");

  // radiative transfer kernels
  //
  {
    InputParameters params = _factory.getValidParams("FireflyADRadiativeTransfer");
    params.set<NonlinearVariableName>("variable") = variables[0];
    params.set<RealVectorValue>("direction") = light_direction;
    _problem->addKernel("FireflyADRadiativeTransfer", "radiative_transfer", params);
  }

  // photoinitiator kernels
  //
  {
    InputParameters params = _factory.getValidParams("ADTimeDerivative");
    params.set<NonlinearVariableName>("variable") = variables[1];
    _problem->addKernel("ADTimeDerivative", "photodecomposition_time_derivative", params);
  }

  {
    InputParameters params = _factory.getValidParams("FireflyADPhotoDecomposition");
    params.set<NonlinearVariableName>("variable") = variables[1];
    light_variable_name.push_back(variables[0]);
    params.set<std::vector<VariableName>>("light_intensity") = light_variable_name;
    _problem->addKernel("FireflyADPhotoDecomposition", "photodecomposition_rate", params);
  }

  {
    InputParameters params = _factory.getValidParams("ADMatDiffusion");
    params.set<NonlinearVariableName>("variable") = variables[1];
    params.set<MaterialPropertyName>("diffusivity") =
    getParam<MaterialPropertyName>("photoinitiator_diffusivity");
    _problem->addKernel("ADMatDiffusion", "photoinitiator_diffusion", params);
  }

  // radical termination and production
  //
  {
    InputParameters params = _factory.getValidParams("ADTimeDerivative");
    params.set<NonlinearVariableName>("variable") = variables[2];
    _problem->addKernel("ADTimeDerivative", "radical_termination_time_derivative", params);
  }

  {
    InputParameters params = _factory.getValidParams("FireflyADRadicalRate");
    params.set<NonlinearVariableName>("variable") = variables[2];
    light_variable_name.push_back(variables[0]);
    photoinitiator_variable_name.push_back(variables[1]);
    monomer_variable_name.push_back(variables[3]);
    oxygen_variable_name.push_back(variables[4]);
    params.set<std::vector<VariableName>>("light_intensity") = light_variable_name;
    params.set<std::vector<VariableName>>("photoinitiator_concentration") = photoinitiator_variable_name;
    params.set<std::vector<VariableName>>("monomer_concentration") = monomer_variable_name;
    params.set<std::vector<VariableName>>("oxygen_concentration") = oxygen_variable_name;
    _problem->addKernel("FireflyADRadicalRate", "radical_termination_rate", params);
  }

  {
    InputParameters params = _factory.getValidParams("ADMatDiffusion");
    params.set<NonlinearVariableName>("variable") = variables[1];
    params.set<MaterialPropertyName>("diffusivity") =
      getParam<MaterialPropertyName>("radical_diffusivity");
    _problem->addKernel("ADMatDiffusion", "radical_diffusion", params);
  }
  //
  // monomer consumption
  //
  {
    InputParameters params = _factory.getValidParams("ADTimeDerivative");
    params.set<NonlinearVariableName>("variable") = variables[3];
    _problem->addKernel("ADTimeDerivative", "monomer_consumption_time_derivative", params);
  }

  {
    InputParameters params = _factory.getValidParams("FireflyADMonomerConsumption");
    params.set<NonlinearVariableName>("variable") = variables[3];
    radical_variable_name.push_back(variables[2]);
    params.set<std::vector<VariableName>>("radical_concentration") = radical_variable_name;
    _problem->addKernel("FireflyADMonomerConsumption", "monomer_consumption_rate", params);
  }

  {
    InputParameters params = _factory.getValidParams("ADMatDiffusion");
    params.set<NonlinearVariableName>("variable") = variables[1];
    params.set<MaterialPropertyName>("diffusivity") =
      getParam<MaterialPropertyName>("monomer_diffusivity");
    _problem->addKernel("ADMatDiffusion", "monomer_diffusion", params);
  }
  //
  // oxygen consumption
  //
  {
    InputParameters params = _factory.getValidParams("TimeDerivative");
    params.set<NonlinearVariableName>("variable") = variables[4];
    _problem->addKernel("TimeDerivative", "oxygen_consumption_time_derivative", params);
  }

  {
    InputParameters params = _factory.getValidParams("FireflyADOxygenConsumption");
    params.set<NonlinearVariableName>("variable") = variables[4];
    radical_variable_name.push_back(variables[2]);
    params.set<std::vector<VariableName>>("radical_concentration") = radical_variable_name;
    _problem->addKernel("FireflyADOxygenConsumption", "oxygen_consumption_rate", params);
  }

  {
    InputParameters params = _factory.getValidParams("ADMatDiffusion");
    params.set<NonlinearVariableName>("variable") = variables[1];
    params.set<MaterialPropertyName>("diffusivity") =
      getParam<MaterialPropertyName>("oxygen_diffusivity");
    _problem->addKernel("ADMatDiffusion", "oxygen_diffusion", params);
  }
}
