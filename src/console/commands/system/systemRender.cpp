#include "console/commands/system/systemRender.h"
#include "environment/environment.h"
#include "environment/terrain/terrainFlat.h"
#include "lrender.h"

#include <sstream>

using namespace LGen;

const std::string Command::System::Render::KEYWORD = "render";
const std::string Command::System::Render::FILE_HELP = "text/helpSystemRender.txt";

Command::System::Render::Render() :
	Command({ KEYWORD }, FILE_HELP, 0) {

}
#include <iostream>
void Command::System::Render::application(
	const std::vector<std::string> &arguments,
	Console &console) {
	if(!workspace.system) {
		console << MSG_NO_SYSTEM << std::endl;

		return;
	}
	
	LGen::Environment environment;

	environment.setTerrain(std::make_shared<TerrainFlat>(20.0f, 20.0f));
	environment.setMaxIterations(workspace.systemIterations);
	environment.addAgent(Agent(*workspace.system, 3, 3));
	environment.addAgent(Agent(*workspace.system, 6, 3));
	environment.addAgent(Agent(*workspace.system, 6, 6));
	environment.addAgent(Agent(*workspace.system, 3, 6));

	auto task = std::make_shared<LRender::Renderer::Task::SceneReport>(environment.makeScene(workspace.randomizer));
	
	console.getMonitor()->makeVisible();
	console.getMonitor()->enqueue(task);

	const auto report = task->getReport();

	std::cout << "Size: " << report->getAgents()[0].getLimits().getMaximum() - report->getAgents()[0].getLimits().getMinimum() << std::endl;
	std::cout << "Area: " << report->getAgents()[0].getArea().getArea() << std::endl;
}
