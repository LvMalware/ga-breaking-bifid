#include "ga.h"

void
ga_clean (ga * const g)
{
    size_t i;
    for (i = 0; i < g->pop_size; i ++)
        del_cromossome(g->population[i]);
    free(g->population);
    free(g);
}

ga *
new_ga (char * const alphabet, char * (*decrypt)(char * const key))
{
    ga *g = calloc(1, sizeof(*g));
    g->decrypt = decrypt;
    g->alphabet = alphabet;
    return g;
}

int
cmpr (const void * a, const void * b)
{
    cromossome **x = (cromossome **) a;
    cromossome **y = (cromossome **) b;
    if (x[0]->fitness > y[0]->fitness)
        return -1;
    return (x[0]->fitness < y[0]->fitness) ? 1 : 0;
}

void
init_population (ga * const g, size_t pop_size, size_t key_len)
{
    size_t i;
    char *alphabet = strdup(g->alphabet);
    g->population = calloc(pop_size, sizeof(cromossome *));
    g->pop_size = pop_size;
    for (i = 0; i < pop_size; i++)
    {
        g->population[i] = new_cromossome(key_len, alphabet);
        cromossome_fitness(g->population[i], g->decrypt);
    }
    qsort(g->population, pop_size, sizeof(cromossome *), cmpr);
    free(alphabet);
}

double 
frand(double max)
{
    return (double)rand()/(double)(RAND_MAX/max);
}

size_t
weighted_rand(cromossome ** const pop, const size_t size, const double sum)
{
    size_t i;
    double rnd = frand(1);
    for (i = 0; i < size; i ++)
        if ((rnd -= (pop[i]->fitness / sum)) <= 0)
            break;
    return i;
}

ssize_t
find_worst(cromossome ** const pop, const size_t size, double fit)
{
    size_t i = 0, j = size - 1;
    while (i != j)
    {
        size_t m = (i + j) / 2;
        if (pop[m]->fitness < fit)
        {
            if ((m == 0) || (pop[m - 1]->fitness > fit))
                return m;
            j = m - 1;
            continue;
        }
        
        if (m == size - 1)
            return -1;
        
        i = m + 1;

        if (pop[i]->fitness < fit)
            return i;
    }
    return (pop[i]->fitness < fit) ? i : -1;
}

void
next_generation (ga * const g, size_t rounds, double cross, double mut)
{
    cromossome **pop = g->population;
    double sum = 0;
    size_t i;

    for (i = 0; i < g->pop_size; i ++)
        sum += pop[i]->fitness;

    for (i = 0; i < rounds; i ++)
    {

       if (frand(1) < cross)
       {
           size_t a = weighted_rand(pop, g->pop_size, sum);
           size_t b = weighted_rand(pop, g->pop_size, sum);
           while (b == a)
               b = weighted_rand(pop, g->pop_size, sum);

           cromossome *c = cromossome_crossover(pop[a], pop[b]);
           if (frand(1) < mut)
               mutate_cromossome(c);
           double fit = cromossome_fitness(c, g->decrypt);
           ssize_t index = find_worst(pop, g->pop_size, fit);
           if (index < 0)
           {
               del_cromossome(c);
               continue;
           }
           sum -= pop[g->pop_size - 1]->fitness;
           sum += c->fitness;
           del_cromossome(pop[g->pop_size - 1]);
           memmove(&pop[index + 1], &pop[index], (g->pop_size - index) * sizeof(cromossome *));
           pop[index] = c;
       }
    }
}

void
ga_evolve (ga * const g, size_t max, size_t stop,
        size_t rounds, double cross, double mut)
{
    size_t i;
    cromossome *best = g->population[0];
    printf("Best fitness: %s (%f)\n", best->key, best->fitness);
    size_t count = 0;
    double fit = 0; //best->fitness;
    for (i = 0; i < max; i ++)
    {
        next_generation(g, rounds, cross, mut);
        best = g->population[0];
        if (best->fitness > fit)
        {
            fit = best->fitness;
            count = 0;
            printf("Generation %lu\n", i);
            printf("Best fitness: %s (%lf)\n", best->key, best->fitness);
            char *plain = g->decrypt(best->key);
	    printf("%s\n\n", plain);
	    free(plain);
        }
        else
            count ++;
        if (count >= stop)
	{
            printf("Early stop at generation %lu. Algorithm is stuck.\n", i);
            break;
	}
    }
}
