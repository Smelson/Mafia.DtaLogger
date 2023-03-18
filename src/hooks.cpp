#include "hooks.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace hooks
{
	DWORD dta_open_return;
	char* file_name;

	std::vector<std::string> animations_names;
	std::vector<std::string> textures_names;
	std::vector<std::string> models_names;
	std::vector<std::string> missions;
	std::vector<std::string> tables;
	std::vector<std::string> sounds_names;
	std::vector<std::string> records_names;
	std::vector<std::string> diff_names;
	std::vector<std::string> others;

	void dumper()
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_F1))
			{
				std::ofstream file;
				file.open("DtaLogger.txt");

				file << "ANIMATIONS\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < animations_names.size(); i++)
					file << animations_names[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file << "TEXTURES\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < textures_names.size(); i++)
					file << textures_names[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file << "MODELS\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < models_names.size(); i++)
					file << models_names[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file << "MISSIONS\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < missions.size(); i++)
					file << missions[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file << "TABLES\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < tables.size(); i++)
					file << tables[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file << "SOUNDS\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < sounds_names.size(); i++)
					file << sounds_names[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file << "RECORDS\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < records_names.size(); i++)
					file << records_names[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file << "DIFFS\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < diff_names.size(); i++)
					file << diff_names[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file << "OTHER\n";
				file << "---------------------------------------------------------------------------------------------------\n\n";

				for (int i = 0; i < others.size(); i++)
					file << others[i] << "\n";

				file << "\n---------------------------------------------------------------------------------------------------\n\n";

				file.close();
			}

			if (GetAsyncKeyState(VK_F2))
			{
				animations_names.clear();
				textures_names.clear();
				models_names.clear();
				missions.clear();
				tables.clear();
				sounds_names.clear();
				records_names.clear();
				diff_names.clear();
				others.clear();
			}

			Sleep(1000);
		}
	}

	HMODULE wait_for_rwdata()
	{
		while (GetModuleHandleA("rw_data.dll") == NULL)
		{
			Sleep(10);
		}

		HMODULE rw_data = GetModuleHandleA("rw_data.dll");
		
		dta_open_return = (DWORD)rw_data + 0x18A0 + 0x161 + 0x5;

		return rw_data;
	}

	void print_dta_file(char* file_name_print)
	{
		std::cout << "[INFO] -> File \"" << file_name_print << "\" was opened!\n";
	}

	void sort_names(char* sorting_name)
	{
		std::string temp = sorting_name;

		if ((temp.find("Anims") != std::string::npos) || (temp.find("anims") != std::string::npos)) {
			if (std::find(animations_names.begin(), animations_names.end(), sorting_name) == animations_names.end())
				animations_names.push_back(temp);
		}

		else if ((temp.find("Maps") != std::string::npos) || (temp.find("maps") != std::string::npos)) {
			if (std::find(textures_names.begin(), textures_names.end(), sorting_name) == textures_names.end())
				textures_names.push_back(temp);
		}

		else if ((temp.find("Models") != std::string::npos) || (temp.find("models") != std::string::npos)) {
			if (std::find(models_names.begin(), models_names.end(), sorting_name) == models_names.end())
				models_names.push_back(temp);
		}

		else if ((temp.find("Missions") != std::string::npos) || (temp.find("missions") != std::string::npos)) {
			if (std::find(missions.begin(), missions.end(), sorting_name) == missions.end())
				missions.push_back(temp);
		}

		else if ((temp.find("Tables") != std::string::npos) || (temp.find("tables") != std::string::npos)) {
			if (std::find(tables.begin(), tables.end(), sorting_name) == tables.end())
				tables.push_back(temp);
		}

		else if ((temp.find("Sounds") != std::string::npos) || (temp.find("sounds") != std::string::npos)) {
			if (std::find(sounds_names.begin(), sounds_names.end(), sorting_name) == sounds_names.end())
				sounds_names.push_back(temp);
		}

		else if ((temp.find("Records") != std::string::npos) || (temp.find("records") != std::string::npos)) {
			if (std::find(records_names.begin(), records_names.end(), sorting_name) == records_names.end())
				records_names.push_back(temp);
		}

		else if ((temp.find("Diff") != std::string::npos) || (temp.find("diff") != std::string::npos)) {
			if (std::find(diff_names.begin(), diff_names.end(), sorting_name) == diff_names.end())
				diff_names.push_back(temp);
		}

		else
			others.push_back(temp);

		print_dta_file(sorting_name);
	}


	__declspec(naked) void dta_open()
	{
		_asm
		{
			mov ecx, [esp+0x68]
			push ecx
			mov file_name, ecx
		}

		_asm pushad
		sort_names(file_name);
		_asm popad

		_asm 
		{
			jmp dta_open_return
		}
	}
}