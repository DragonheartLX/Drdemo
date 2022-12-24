#include "Config.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <spdlog/spdlog.h>

using std::ifstream;
using std::filesystem::path;
using std::filesystem::current_path;

void loadRenderConfig(RenderConfig& conf) {
    path confPath = current_path() / "RayTracing.drconf";
    ifstream confFile(confPath, std::ios::in);

    if (!confFile.is_open())
    {
        confFile.close();
        spdlog::warn("Config load failed!");
        exit(0);
    };

    spdlog::info("Config loaded: {0}", confPath.string());

	std::string temp;

    while (getline(confFile, temp, '\n'))
	{
		if (temp.find("=") != std::string::npos)
		{
			std::string key, content;
			size_t count = temp.find("=", 0);

			key = temp.substr(0, count);
			content = temp.substr(count + 1, temp.size() - count + 1);

			if (key == "aspectRatio")           conf.aspectRatio            = atof(content.c_str());
			if (key == "renderWidth")           conf.renderWidth            = atoi(content.c_str());
            if (key == "renderHeight")          conf.renderHeight           = atoi(content.c_str());
            if (key == "outPath")               conf.outPath                = content;
            if (key == "samples_per_pixel")     conf.samples_per_pixel      = atoi(content.c_str());
            if (key == "max_depth")             conf.max_depth              = atoi(content.c_str());
		}
	}

    confFile.close();
};