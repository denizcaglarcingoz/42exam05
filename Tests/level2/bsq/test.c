#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int rows, cols;
	char empty, obs, fill;
	char **map;

} Map;


int min3(int a, int b, int c) {return a < b ? ( a < c ?  a : c) : ( b < c ? b : c);} 

void	free_map(Map* m)
{
	if (!m) return;
	
	for(int i=0; i < m->rows; i++) free(m->map[i]);

	free(m->map);
	free(m);

}


Map* read_map(char *argv)
{

	FILE* f = argv ? fopen(argv, "r") : stdin;
	if (f==0) return NULL;
	
	Map* m = calloc(1, sizeof(Map));

	if (fscanf(f, "%d %c %c %c\n", &m->rows, &m->empty, &m->obs, &m->fill) != 4) goto err;

	m->map = calloc(m->rows, sizeof(char*));
	
	for (int i =0; i < m->rows; i++)
	{
	
		size_t len = 0;
		if (getline(&m->map[i], &len, f) < 0 ) goto err;

		int collen =0;

		while ( m->map[i][collen] && m->map[i][collen] != '\n')
			collen++;

		m->map[i][collen] = '\0';

		if (i == 0) m->cols = collen;
		else if(m->cols != collen) return NULL;

	}
	

	if (f != stdin) fclose(f);
	
	return m;


err: 
	fclose(f);
	free_map(m);
	return NULL;

}





void	solve (Map* m)
{
	int** dp = calloc(m->rows, sizeof(int*));
	
	for (int i = 0; i < m->rows; i++) dp[i] = calloc(m->cols, sizeof(int));

	int best =0, bi=0, bj=0;

	for (int i = 0; i < m->rows; i++)
	{	for (int j = 0; j<m->cols; j++)
		{

			if (m->map[i][j] == m->obs) dp[i][j] = 0;
			else dp[i][j] = (i&&j ? min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) : 0) +1;

			if (dp[i][j] > best) { best = dp[i][j]; bi = i; bj =j;}  
		}
	}

	
	for (int  i = bi - best +1; i <= bi; i++)
		for (int  j = bj - best +1; j <= bj; j++)
			m->map[i][j] = m->fill;

	for(int i=0; i < m->rows; i++) free(dp[i]);
	
	free(dp);
}


int validate(Map* m)
{
	if (!m || m->rows < 1 || m->cols < 1) return 0;
	
	if (m->empty == m->obs || m->empty == m->fill || m->fill == m->obs) return 0;

	for (int i=0; i < m->rows; i++)
		for (int j=0; j < m->cols; j++)
			if (m->map[i][j] != m->empty && m->map[i][j] != m->obs) return 0;
	

	return 1;
}





void	process(char *argv)
{
	Map* m = read_map(argv);
	
	if (!m || validate(m) == 0)
	{
		fprintf(stdout, "map error\n");
		free_map(m);
		return;
	}


	solve(m);

	for (int i=0; i < m->rows; i++) fprintf(stdout, "%s\n", m->map[i]);

	free_map(m);
}






int main (int argc, char** argv)
{
	if (argc < 2)	process(NULL);
	else for(int i=1; i < argc; i++) process(argv[i]);	

	return 0;

}