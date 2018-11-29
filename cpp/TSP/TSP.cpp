#ifdef _WIN32
	#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <vector>
#include <chrono>
#include <filesystem>
#include <iostream>

struct [[nodiscard]] Location {
	float Latitude{ 0.0f };
	float Longitude{ 0.0f };
};

[[nodiscard]] std::vector<Location> LoadCSV(const std::filesystem::path& csvPath) {
	if (!std::filesystem::exists(csvPath)) {
		throw std::runtime_error("CSV file not found.");
	}

	std::vector<Location> locations;
	if (std::FILE* fp{ std::fopen(csvPath.generic_string().c_str(), "r") }) {
		
		int id{ 0 };
		float lat{ 0.0f }, lon{ 0.0f };
		while (fscanf_s(fp, "%d %f %f", &id, &lat, &lon) == 3) {
			locations.emplace_back(Location{ lat, lon });
		}

		std::fclose(fp);
	}

	return locations;
}

int main() {
	const auto& now{ std::chrono::high_resolution_clock::now() };
	const auto& vals{ LoadCSV("C:/Users/Nabil/Documents/GitHub/cs3201-final-project/data/TSP_Canada_4663.txt") };
	const auto& end{ std::chrono::high_resolution_clock::now() };
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count() << "ms" << '\n';
	std::cout << vals.size() << '\n';
	return 0;
}