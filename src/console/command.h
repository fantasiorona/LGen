#pragma once

#include "console/input.h"
#include "console/console.h"
#include "console/commandList.h"

#include <vector>
#include <string>
#include <memory>

namespace LGen {
	class Command {
	public:
		class Exit;
		class Help;
		class System;
		class Render;
		class Environment;

		Command(const std::vector<std::string> triggers, const char args = -1);
		Command(const std::vector<std::string> triggers, const std::string help, const char args = -1);
		Command(const std::vector<std::string> triggers, const std::vector<std::shared_ptr<Command>> commands, const char args = -1);
		virtual ~Command() = default;
		bool apply(const Input &input, Console &console);
		const std::string &getTrigger() const;
		std::vector<std::string> getAliases() const;

	protected:
		virtual void application(
			const std::vector<std::string> arguments,
			Console &console);

	private:
		static const std::string MSG_HELP_LIST;
		static const std::string MSG_NEED_MORE_ARGUMENTS;
		static const std::string MSG_THIS_COMMAND_TAKES;
		static const std::string MSG_ARGUMENT;
		static const std::string MSG_ARGUMENTS;
		static const std::string MSG_INVALID_INPUT;

		const char args;
		const bool hasHelp;
		const std::vector<std::string> triggers;
		const std::string help;
		std::unique_ptr<CommandList> commandList;

		void showHelp(const Console &console) const;
	};
}