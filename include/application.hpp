#ifndef APPLICATION_HPP
#define APPLICATION_HPP

class Application {
public:
	Application();
	~Application();

	enum class Platform {
		Windows,
		Linux,
		Android,
		Unknown
	};

	static Platform GetPlatform() {
	#if defined(WINDOWS)
		return Platform::Windows;
	#elif defined(LINUX)
		return Platform::Linux;
	#elif defined(ANDROID)
		return Platform::Android;
	#else
		return Platform::Unknown;
	#endif
	}

	static Application* GetApplication();

	bool Run();
};


#endif // APPLICATION_HPP