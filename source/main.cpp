#include "application.hpp"

#if defined(_WIN32)
#include <Windows.h>
#endif

#if defined(__ANDROID__)
#include <jni.h>
#endif

// Windows-specific code (Standard Executable)
#if (defined(_WIN32) && !defined(COMPILE_TO_DLL)) || defined(__linux__)

int main(int argc, char* argv[]) {
	Application application;
	application.run();
}

// Windows-specific code (DLL)
#elif defined(_WIN32) && defined(COMPILE_TO_DLL)

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
#elif defined(__ANDROID__)

extern "C"
JNIEXPORT void JNICALL Java_com_example_appname_MainActivity_callNativeMain(JNIEnv* env, jobject obj) {
	Application application;
	application.run();
}

#endif