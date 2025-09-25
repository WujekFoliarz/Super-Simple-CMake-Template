#include "application.hpp"

#if defined(WINDOWS)
#include <Windows.h>
#endif

#if defined(ANDROID)
#include <jni.h>
#endif
#include <iostream>

// Windows-specific code (Standard Executable)
#ifdef WINDOWS

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
#if !defined(PRODUCTION_BUILD)
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);
#endif

	Application application;
	application.Run();
}

#elif defined(LINUX) || defined(APPLE)

int main(int argc, char* argv[]) {
	Application application;
	application.Run();
}

// Windows-specific code (DLL)
#elif defined(WINDOWS) && defined(COMPILE_TO_DLL)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			// DLL loaded into process
			break;
		case DLL_THREAD_ATTACH:
			// New thread started
			break;
		case DLL_THREAD_DETACH:
			// Thread exiting
			break;
		case DLL_PROCESS_DETACH:
			// DLL unloading
			break;
	}
	return TRUE;
}

// Android-specific code
#elif defined(ANDROID)

extern "C"
JNIEXPORT void JNICALL Java_com_example_appname_MainActivity_callNativeMain(JNIEnv* env, jobject obj) {
	Application application;
	application.Run();
}

#endif