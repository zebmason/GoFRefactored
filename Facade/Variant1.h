#pragma once

#include <iostream>

namespace FacadePattern::Variant1
{
	class Token {};

	class Scanner {
	public:
		Scanner(std::istream&) : _inputStream(std::cin) {}
		virtual ~Scanner() {}

		virtual Token& Scan() { return *(new Token()); }
	private:
		std::istream& _inputStream;
	};

	class INode {};
	class BytecodeStream {};

	class CodeGenerator {
	public:
		virtual void Visit(INode*) {}
		// ... 
	protected:
		CodeGenerator(BytecodeStream&) : _output(BytecodeStream()) {}
	protected:
		BytecodeStream& _output;
	};

	class ProgramNode {
	public:
		// program node manipulation 
		virtual void GetSourcePosition(int& line, int& index) {}
		// ... 

		// child manipulation 
		virtual void Add(ProgramNode*) {}
		virtual void Remove(ProgramNode*) {}
		// ... 

		virtual void Traverse(CodeGenerator&) {}
	protected:
		ProgramNode() {}
	};

	class ProgramNodeBuilder {
	public:
		ProgramNodeBuilder() {}

		virtual ProgramNode* NewVariable(
			const char* variableName
		) const {
			return nullptr;
		}

		virtual ProgramNode* NewAssignment(
			ProgramNode* variable, ProgramNode* expression
		) const {
			return nullptr;
		}

		virtual ProgramNode* NewReturnStatement(
			ProgramNode* value
		) const {
			return nullptr;
		}

		virtual ProgramNode* NewCondition(
			ProgramNode* condition,
			ProgramNode* truePart, ProgramNode* falsePart
		) const {
			return nullptr;
		}
		// ... 

		ProgramNode* GetRootNode() { return _node; }
	private:
		ProgramNode* _node;
	};

	class Parser {
	public:
		Parser() {}
		virtual ~Parser() {}

		virtual void Parse(Scanner&, ProgramNodeBuilder&) {}
	};

	class StatementNode : public INode {};

	class ExpressionNode : public INode
	{
		void Traverse(CodeGenerator& cg) {
			cg.Visit(this);

			//			ListIterator i(_children);

			//			for (i.First(); !i.IsDone(); i.Next()) {
			//				i.CurrentItem()->Traverse(cg);
			//			}
		}
	};

	class Compiler {
	public:
		Compiler() {}

		virtual void Compile(std::istream&, BytecodeStream&);
	};

	void Compiler::Compile(
		std::istream& input, BytecodeStream& output
	) {
		Scanner scanner(input);
		ProgramNodeBuilder builder;
		Parser parser;

		parser.Parse(scanner, builder);

		//		RISCCodeGenerator generator(output);
		ProgramNode* parseTree = builder.GetRootNode();
		//		parseTree->Traverse(generator);
	}
}
