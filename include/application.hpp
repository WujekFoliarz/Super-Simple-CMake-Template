#ifndef APPLICATION_HPP
#define APPLICATION_HPP

class Application {
public:
	enum class Platform {
		Windows,
		Linux,
		Android,
		Unknown
	};

	inline Platform getPlatform() {
	#if defined(__linux__)
		return Platform::Linux;
	#elif defined(__ANDROID__)
		return Platform::Android;
	#elif defined(_WIN32)
		return Platform::Windows;
	#else
		return Platform::Unknown;
	#endif
	}

	bool run();
};


#endif // APPLICATION_HPP
