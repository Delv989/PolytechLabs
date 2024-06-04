#include "GameInstance.h"

int main() {
	GameInstance game({ Global::WindowWidth / 2.f, Global::WindowHeight - 40.f });
	game.Start();
	return 0;
}