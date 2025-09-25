#include "application.hpp"
#include <iostream>
#include "log.hpp"

inline Application* s_Application = nullptr;

Application* Application::GetApplication() {
	return s_Application;
}

Application::Application() {
	s_Application = this;
}

bool Application::Run() {
	return true;
}
