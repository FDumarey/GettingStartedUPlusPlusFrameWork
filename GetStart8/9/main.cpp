#include <Core/Core.h> // includes core library

using namespace Upp;

double Expression(CParser& parser); // defines prototype because needed before

double Terms(CParser& parser) // the terms level
{
	Cout() << "In terms function" << '\n';
	if(parser.Id("cos")) { // if cos found
		parser.PassChar('('); // skips ( character
		double x = Expression(parser); // gets expression value
		parser.PassChar(')'); // skips ) character
		return cos(x); // returns cosine value
	}
	if(parser.Id("sin")) { // if sin found
		parser.PassChar('('); // skips ( character
		double x = Expression(parser); // gets expression value
		parser.PassChar(')'); // skips ) character
		return sin(x); // returns sinus value
	}
	if(parser.Char('(')) { // if parenthesis found
		double x = Expression(parser); // gets expression value
		parser.PassChar(')'); // skips ) character
		return x; // returns expression value
	}
	double x = parser.ReadDouble(); // reads terms value = double floating point
	Cout() << "    return terms value=" << x << '\n';
	return x; // returns terms value
}

double Multiply(CParser& parser) // the multiply level
{
	Cout() << "In multiplier function." << '\n';
	double x = Terms(parser); // goes to terms level and assign value
	Cout() << "   init multiply value=" << x << '\n';
	for(;;) // does a endless loop
		if(parser.Char('*')) // if multiplication
			x = x * Terms(parser); // multiplies terms recursion
		else
		if(parser.Char('/')) { // if division
			double y = Terms(parser); // divides terms recursion
			if(0 == y) // if divider is zero
				parser.ThrowError("Division by zero not allowed"); // throws error
			x = x / y; // divides
		}
		else {
			Cout() << "    return multiply value=" << x << '\n';
			return x; // returns multiply value
		}
}

double Expression(CParser& parser) // the expression level
{
	Cout() << "In expression function." << '\n';
	double x = Multiply(parser); // goes to multiply level and assign value
	Cout() << "   init expression value=" << x << '\n';
	for(;;) // does a endless loop
		if(parser.Char('+')) // if addition
			x = x + Multiply(parser); // adds multiply recursion
		else
		if(parser.Char('-')) // if subtraction
			x = x - Multiply(parser); // negates multiply recursion
		else {
			Cout() << "    return expression value=" << x << '\n';
			return x; // returns expression value
		}
}

CONSOLE_APP_MAIN // console entry point
{
		Cout() << "Enter a numerical expression: x= ";
		String linein = ReadStdIn(); // reads from standard in
		CParser parser(linein); // defines a cparser object
		try
		{
		Cout() << Expression(parser) << '\n'; // calls the expression level
		}
		catch(CParser::Error e) { // if a parsing error occurs
			Cout() << "Parsing error: " << e << '\n'; // prints error
		}
}