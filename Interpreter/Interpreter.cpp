// Interpreter.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

int main()
{
	{
		InterpreterPattern::GoF::BooleanExp* expression;
		InterpreterPattern::GoF::Context context;
		auto x = new InterpreterPattern::GoF::VariableExp("X");
		auto y = new InterpreterPattern::GoF::VariableExp("Y");
		expression = new InterpreterPattern::GoF::OrExp(
			new InterpreterPattern::GoF::AndExp(new InterpreterPattern::GoF::Constant(true), x),
			new InterpreterPattern::GoF::AndExp(y, new InterpreterPattern::GoF::NotExp(x))
		);
		context.Assign(x, false);
		context.Assign(y, true);
		bool result = expression->Evaluate(context);

		auto z = new InterpreterPattern::GoF::VariableExp("Z");
		InterpreterPattern::GoF::NotExp not_z(z);
		InterpreterPattern::GoF::BooleanExp* replacement = expression->Replace("Y", not_z);
		context.Assign(z, true);
		result = replacement->Evaluate(context);
	}

	{
		InterpreterPattern::Variant1::BooleanExp* expression;
		InterpreterPattern::Variant1::Context context;
		auto x = new InterpreterPattern::Variant1::VariableExp("X");
		auto y = new InterpreterPattern::Variant1::VariableExp("Y");
		expression = new InterpreterPattern::Variant1::OrExp(
			new InterpreterPattern::Variant1::AndExp(new InterpreterPattern::Variant1::Constant(true), x),
			new InterpreterPattern::Variant1::AndExp(y, new InterpreterPattern::Variant1::NotExp(x))
		);
		context.Assign(x, false);
		context.Assign(y, true);
		bool result = expression->Evaluate(context);

		auto z = new InterpreterPattern::Variant1::VariableExp("Z");
		InterpreterPattern::Variant1::NotExp not_z(z);
		InterpreterPattern::Variant1::BooleanExp* replacement = expression->Replace("Y", not_z);
		context.Assign(z, true);
		result = replacement->Evaluate(context);
	}
    return 0;
}

