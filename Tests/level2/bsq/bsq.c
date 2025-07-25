#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int rows, cols;
    char empty, obs, fill;
    char **grid;
} Map;

int min3(int a, int b, int c) { return a < b ? (a < c ? a : c) : (b < c ? b : c); }

void free_map(Map *m)
{
    if (!m) return;
    for (int i=0;i<m->rows;i++) free(m->grid[i]);
    free(m->grid);
    free(m);
}

Map* read_map(const char *argv)
{
    FILE *f = argv ? fopen(argv, "r") : stdin;
    if (f == 0) return NULL;
    Map *m = calloc(1, sizeof(Map));
    if (fscanf(f, "%d %c %c %c\n", &m->rows, &m->empty, &m->obs, &m->fill) != 4) goto err;
    m->grid = malloc(m->rows * sizeof(char*));
    for (int i = 0; i < m->rows; i++)
	{
        size_t len = 0;
        if (getline(&m->grid[i], &len, f) < 0) goto err;
		
		int collen = 0;
    	while (m->grid[i][collen] && m->grid[i][collen] != '\n')
			collen++;
		
		m->grid[i][collen] = '\0';
        
		if (!i) m->cols = collen;
        else if (collen != m->cols) goto err;
    }
    if (f != stdin) fclose(f);
    return m;
err:
    if (f != stdin) fclose(f);
    free_map(m);
    return NULL;
}

int validate(const Map *m)
{
    if (!m || m->rows<1 || m->cols<1) return 0;

    if (m->empty==m->obs||m->empty==m->fill||m->obs==m->fill) return 0;
    
	for (int i=0;i<m->rows;i++)
        for (int j=0;j<m->cols;j++)
            if (m->grid[i][j]!=m->empty && m->grid[i][j]!=m->obs)
                return 0; 
    return 1;
}

void solve(Map *m)
{
    int R=m->rows, C=m->cols;
    int **dp = calloc(R, sizeof(*dp));
    
	for (int i=0;i<R;i++) dp[i] = calloc(C, sizeof(*dp[i]));
	
	int best=0, bi=0, bj=0;
    
	for (int i=0;i<R;i++)
	{	for (int j=0;j<C;j++)
		{
    	    if (m->grid[i][j]==m->obs) dp[i][j]=0;
    	    else dp[i][j] = (i&&j ? min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) : 0) + 1;
    	    
			if (dp[i][j]>best) best=dp[i][j], bi=i, bj=j;
    	}
	}
	
	for (int i=bi-best+1;i<=bi;i++)
    {
		for (int j=bj-best+1;j<=bj;j++)
			m->grid[i][j]=m->fill;
	}
	for (int i=0;i<R;i++)
		free(dp[i]);
	
	free(dp);
	

}



void process(const char *argv)
{
	Map *m = read_map(argv);
	if (!m || !validate(m))
	{
		fprintf(stderr, "map error\n");
		free_map(m);
		return;
	}
	solve(m);
	for (int i = 0; i < m->rows; i++)
		fprintf(stdout, "%s\n", m->grid[i]);
	free_map(m);
}

int main(int ac, char **av)
{
	if (ac<2) process(NULL);
	else for (int i=1;i<ac;i++) process(av[i]);
	return 0;
}
