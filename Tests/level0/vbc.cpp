#include <ctype.h>
#include <unistd.h>
#include <stdio.h>

const char* input;
char currChar;
int err = 0;

void	next(){ currChar = *input ? *input++ : 0;	}
int expr();


void	err_fail()
{
	write(1, "Unexpected end of input\n", 24);
	err = 1;
}

void	err_token()
{
	write(1, "Unexpected token '", 18);
	write(1, &currChar, 1);
	write(1, "'\n", 2);
	err = 1;
}


int	factor()
{
	if(err) return 1;

	if (isdigit(currChar))
	{
		int v = currChar - '0';
		next();
		return v;
	}

	if(currChar == '(')
	{
		next();
		int v  = expr();
		
		if (currChar != ')') return err_token(), 1;

		next();
		return v;

	}


	if (currChar == 0)
		return err_fail(), 1;

	return err_token(), 1;
}

int term()
{
	int v = factor();
	
	while (!err && currChar == '*')
	{
		next();
		v *= factor();
	
	}
	return v;
}


int expr()
{
	int v = term();
	
	while (!err && currChar == '+')
	{
		next();
		v += term();
	
	}
	return v;
}

int main(int argc, char** argv)
{
	if (argc != 2) return 1;

	input = argv[1];

	next();
	int result = expr();
	
	if (err == 0 && currChar) return err_fail(), 1;

	if (err == 1)	return 1;

	printf("%d\n", result);


	return 0;
}










