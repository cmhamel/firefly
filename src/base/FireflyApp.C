#include "FireflyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"
#include "ActionFactory.h"

InputParameters
FireflyApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  // Do not use legacy material output, i.e., output properties on INITIAL as well as TIMESTEP_END
  params.set<bool>("use_legacy_material_output") = false;

  return params;
}

FireflyApp::FireflyApp(InputParameters parameters) : MooseApp(parameters)
{
  FireflyApp::registerAll(_factory, _action_factory, _syntax);
}

FireflyApp::~FireflyApp() {}

void
FireflyApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"FireflyApp"});
  Registry::registerActionsTo(af, {"FireflyApp"});

  /* register custom execute flags, action syntax, etc. here */

  registerSyntax("FireflyKerenelsAction", "FireflyKernels");
  registerSyntax("FireflyADKernelsAction", "FireflyADKernels");
  registerSyntax("FireflyICAction", "FireflyICs");

}

void
FireflyApp::registerApps()
{
  registerApp(FireflyApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
FireflyApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  FireflyApp::registerAll(f, af, s);
}
extern "C" void
FireflyApp__registerApps()
{
  FireflyApp::registerApps();
}
