/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2013 Icinga Development Team (http://www.icinga.org/)   *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "methods/pluginchecktask.h"
#include "icinga/pluginutility.h"
#include "icinga/checkcommand.h"
#include "icinga/macroprocessor.h"
#include "icinga/icingaapplication.h"
#include "base/dynamictype.h"
#include "base/logger_fwd.h"
#include "base/scriptfunction.h"
#include "base/utility.h"
#include "base/process.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>

using namespace icinga;

REGISTER_SCRIPTFUNCTION(PluginCheck,  &PluginCheckTask::ScriptFunc);

CheckResult::Ptr PluginCheckTask::ScriptFunc(const Service::Ptr& service)
{
	CheckCommand::Ptr commandObj = service->GetCheckCommand();
	Value raw_command = commandObj->GetCommandLine();

	std::vector<MacroResolver::Ptr> resolvers;
	resolvers.push_back(service);
	resolvers.push_back(service->GetHost());
	resolvers.push_back(commandObj);
	resolvers.push_back(IcingaApplication::GetInstance());

	Value command = MacroProcessor::ResolveMacros(raw_command, resolvers, service->GetLastCheckResult(), Utility::EscapeShellCmd, commandObj->GetEscapeMacros());

	Dictionary::Ptr envMacros = make_shared<Dictionary>();

	Array::Ptr export_macros = commandObj->GetExportMacros();

	if (export_macros) {
		BOOST_FOREACH(const String& macro, export_macros) {
			String value;

			if (!MacroProcessor::ResolveMacro(macro, resolvers, service->GetLastCheckResult(), &value)) {
				Log(LogWarning, "icinga", "export_macros for service '" + service->GetName() + "' refers to unknown macro '" + macro + "'");
				continue;
			}

			envMacros->Set(macro, value);
		}
	}

	Process::Ptr process = make_shared<Process>(Process::SplitCommand(command), envMacros);

	process->SetTimeout(commandObj->GetTimeout());

	ProcessResult pr = process->Run();

	String output = pr.Output;
	output.Trim();
	CheckResult::Ptr result = PluginUtility::ParseCheckOutput(output);
	result->SetCommand(command);
	result->SetState(PluginUtility::ExitStatusToState(pr.ExitStatus));
	result->SetExitStatus(pr.ExitStatus);
	result->SetExecutionStart(pr.ExecutionStart);
	result->SetExecutionEnd(pr.ExecutionEnd);

	return result;
}

