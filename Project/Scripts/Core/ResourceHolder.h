#pragma once
#include <unordered_map>
#include <memory>
#include "Loadable.h"

class ResourceHolder
{
private:
	static std::unordered_map<std::string, std::unique_ptr<Loadable>>& GetLoadedResources()
	{
		static std::unordered_map<std::string, std::unique_ptr<Loadable>> resources;

		return resources;
	}
public:
	template <class T>
	static T* Get(std::string filePath)
	{
		auto& loadedResources = GetLoadedResources();
		auto foundIdx = loadedResources.find(filePath);

		if (foundIdx != loadedResources.end())
		{
			return static_cast<T*>(foundIdx->second.get());
		}

		auto newLoadable = std::make_unique<T>(filePath);
		if (!newLoadable->Load())
		{
			return nullptr;
		}

		auto result = newLoadable.get();
		loadedResources[filePath] = std::move(newLoadable);
		return result;
	}
};
