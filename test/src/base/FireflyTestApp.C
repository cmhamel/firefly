//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "FireflyTestApp.h"
#include "FireflyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
FireflyTestApp::validParams()
{
  InputParameters params = FireflyApp::validParams();
  return params;
}

FireflyTestApp::FireflyTestApp(InputParameters parameters) : MooseApp(parameters)
{
  FireflyTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

FireflyTestApp::~FireflyTestApp() {}

void
FireflyTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  FireflyApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"FireflyTestApp"});
    Registry::registerActionsTo(af, {"FireflyTestApp"});
  }
}

void
FireflyTestApp::registerApps()
{
  registerApp(FireflyApp);
  registerApp(FireflyTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
FireflyTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  FireflyTestApp::registerAll(f, af, s);
}
extern "C" void
FireflyTestApp__registerApps()
{
  FireflyTestApp::registerApps();
}
