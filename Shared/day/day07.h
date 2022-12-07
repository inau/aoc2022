#pragma once
#include <string>
#include "dayShared.h"
#include "../io/dataInstance.h"

namespace AoC22 { namespace Days {

	class Day07 : public Day
	{
	protected:
		// Inherited via Day
		virtual std::shared_ptr<DayResult> _runFirst(std::ifstream& data) override;
		virtual std::shared_ptr<DayResult> _runSecond(std::ifstream& data) override;

		virtual const unsigned int GetDay() const override;
	public:
		Day07(IO::InputDataReader& reader) : Day(reader) {};
	};

	class Hierarchy
	{
	public:
		class Node 
		{
		protected:
			Node* m_Parent;
			std::string m_name;
		public:
			Node(Node* ancestor = nullptr, std::string name = "")
				: m_Parent(ancestor)
				, m_name(name) {}

			Node* GoToParent();
			virtual unsigned long GetSize() = 0;
		};

		class File : public Node
		{
		protected:
			const unsigned long m_Size;
		public:
			File(Node* ancestor, std::string name, unsigned long sz)
				: Node(ancestor, name)
				, m_Size(sz) {}

			// Inherited via Node
			virtual unsigned long GetSize() override;
		};

		class Directory : public Node
		{
		protected:
			std::vector<std::shared_ptr<Node>> m_Children;
			
		public:
			Directory(Node* ancestor, std::string name)
				: Node(ancestor, name) {}

			Directory* AddDirectory(std::string name);
			File* AddFile(std::string name, unsigned long sz);

			Directory* GetDirectory(std::string name);
			std::vector<Directory*> GetDirectories();
			// Inherited via Node
			virtual unsigned long GetSize() override;
		};
	protected:
		std::shared_ptr<Node> m_root;

	public:
		Node* GetRoot();
	};


}}
