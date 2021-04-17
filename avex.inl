inline void erase(std::string& path, bool rename, int passes) {
	LOG_F(INFO, "Removing: %s", CSTR(path));
	if (rename) {
		rename_path(path);
	}

	if (!fs::is_directory(path) && passes != 0) {
		overwrite_content(path, passes);
	}

	unlink_path(path);
}

// https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-std::string-in-c
inline auto generate_random_str(const int len) {
	std::string tmp_str;
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	static auto once = false;

	if (once) {
		srand(static_cast<unsigned int>(time(nullptr)));
		once = true;
	}

	tmp_str.reserve(len);

	for (auto i = 0; i < len; ++i) {
		tmp_str += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return tmp_str;
}

inline auto compare_dir_last(const fs::path& first, const fs::path& second)
{
	return !fs::is_directory(first) && fs::is_directory(second);
}
