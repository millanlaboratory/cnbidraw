#include "Engine.hpp"

int main(int argc, char** argv) {


	cnbi::draw::Engine engine;


	printf("Starting the engine with default values\n");
	engine.Open();

	CcTime::Sleep(2000.0f);

	printf("Stopping the engine\n");

	return 0;
}
