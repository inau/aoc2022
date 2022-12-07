#include "day07.h"
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <algorithm>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day07::GetDay() const
{
	return 7u;
}

enum class Cmd { Unknown, ChangeDir, ListDir };
bool is_command(const std::string& line, Cmd& cmd, std::string& argument)
{
	bool command = !line.empty() && line[0] == '$';
	std::stringstream strm(line);
	if (command)
	{
		while (strm >> argument)
		{
			if (argument == "$") continue;
			else if (argument == "cd") { cmd = Cmd::ChangeDir; }
			else if (argument == "ls") { cmd = Cmd::ListDir; }
			else {}
		}
	}
	
	return command;
}

struct FileInfo
{
	bool isDirectory;
	std::string name;
	unsigned long size;
};


bool parse_fileinfo(const std::string& line, bool& directory, std::string& name, unsigned long& size)
{
	std::stringstream strm(line);
	if (strm >> name)
	{
		directory = (name == "dir");
		size = directory ? 0 : std::stoi(name);
	}
	if (strm >> name)
	{
		return true;
	}
}

bool parse_fileinfo(const std::string& line, FileInfo& fi)
{
	return parse_fileinfo(line, fi.isDirectory, fi.name, fi.size);
}

std::shared_ptr<DayResult> AoC22::Days::Day07::_runFirst(std::ifstream& data)
{
	unsigned lineCount = 0;

	Hierarchy h;
	
	Hierarchy::Directory* root = dynamic_cast<Hierarchy::Directory*>(h.GetRoot());
	Hierarchy::Directory* node = nullptr;
	Cmd cmd;
	FileInfo file;
	std::string arg;
	auto func = [&](const std::string& line)
	{
		if (is_command(line, cmd, arg))
		{
			switch (cmd)
			{
			case Cmd::ChangeDir:
			{
				if (arg == "/") node = root;
				else node = node ? node->GetDirectory(arg) : nullptr;
			} break;
			}
		}
		else // process directory
		{
			if (node)
			{
				parse_fileinfo(line, file);
				if (file.isDirectory)
				{
					node->AddDirectory(file.name);
				}
				else node->AddFile(file.name, file.size);
			}
		}
	};

	IterateData(data, func);

	unsigned long sum = 0u;
	unsigned long threshold = 100000;

	/// Process file graph
	auto dirs = root->GetDirectories();
	for (auto& dir : dirs)
	{
		auto sz = dir->GetSize();
		if (sz > threshold)
		{
			auto subdirs = dir->GetDirectories();
			for (auto sdir : subdirs)
			{
				dirs.push_back(sdir);
			}
		}
		else sum += sz;
	}

	return std::make_shared<DayIntegerResult>(sum);
}



std::shared_ptr<DayResult> AoC22::Days::Day07::_runSecond(std::ifstream& data)
{
	unsigned cc = 14;

	std::vector<int> _index;
	auto func = [&cc, &_index](const std::string& line)
	{

	};

	IterateData(data, func);

	/// Process command queue

	return std::make_shared<DayIntegerResult>(_index[0]);
}

// ------------ DATA
Hierarchy::Directory* Hierarchy::Directory::AddDirectory(std::string name)
{
	m_Children.push_back(std::make_shared<Hierarchy::Directory>(this, name));
	return dynamic_cast<Hierarchy::Directory*>(m_Children.back().get());
}

Hierarchy::File* Hierarchy::Directory::AddFile(std::string name, unsigned long sz)
{
	m_Children.push_back(std::make_shared<Hierarchy::File>(this, name, sz));
	return dynamic_cast<Hierarchy::File*>(m_Children.back().get());
}

Hierarchy::Directory* Hierarchy::Directory::GetDirectory(std::string name)
{
	if (name == "..")
	{
		return dynamic_cast<Hierarchy::Directory*>(m_Parent);
	}

	Hierarchy::Directory* child = nullptr;
	for (auto& c : m_Children)
	{
		Hierarchy::Directory* dir = dynamic_cast<Hierarchy::Directory*>(c.get());
		if (dir && dir->m_name == name)
		{
			child = dir;
			break;
		}
	}
	return child;
}

std::vector<Hierarchy::Directory*> Hierarchy::Directory::GetDirectories()
{
	std::vector<Directory*> directories;
	for (auto& c : m_Children)
	{
		Hierarchy::Directory* dir = dynamic_cast<Hierarchy::Directory*>(c.get());
		if (dir)
		{
			directories.push_back(dir);
		}
	}

	return directories;
}

unsigned long Hierarchy::Directory::GetSize()
{
	unsigned long sz = 0u;
	for (auto& node : m_Children)
	{
		sz += node->GetSize();
	}
	return sz;
}

Hierarchy::Node* Days::Hierarchy::Node::GoToParent()
{
	return m_Parent;
}

Hierarchy::Node* Hierarchy::GetRoot()
{
	if (!m_root) m_root = std::make_shared<Hierarchy::Directory>(nullptr, "/");
	return m_root.get();
}

}
unsigned long Days::Hierarchy::File::GetSize()
{
	return m_Size;
}
}