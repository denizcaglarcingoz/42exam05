#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

//curChar for current charrachter
const char *input;
char currChar;
int err = 0;

void next() { currChar = *input ? *input++ : 0; }
int expr(void);

void fail_end()
{
	write(2, "Unexpected end of input\n", 24);
	err = 1;
}

void fail_token()
{
	write(2, "Unexpected token '", 18);
	write(2, &currChar, 1);
	write(2, "'\n", 2);
	err = 1;
}

int factor(void)
{
    if (err) return 1;
    
	if (isdigit(currChar))
	{
        int v = currChar - '0';
        next();
        return v;
    }

	if (currChar == '(')
	{
        next();
        int v = expr();
        if (currChar != ')') fail_end();
        next();
        return v;
    }

	if (currChar == 0)
		return fail_end(), 1;

	return fail_token(), 1;
}

int term(void) {
    int v = factor();
    while (!err && currChar == '*')
	{
        next();
        v *= factor();
    }
    return v;
}

int expr(void)
{
    int v = term();
    while (!err && currChar == '+')
	{
		next();
		v += term();
    }
	return v;
}

int main(int ac, char **av)
{
	if (ac != 2) return 1;
	input = av[1];
	next();
	int result = expr();
	if (!err && currChar) return fail_token(), 1;

	if (err) return 1;
	printf("%d\n", result);
	return 0;
}