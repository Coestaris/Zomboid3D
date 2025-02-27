/*
//
// Created by maxim on 2/6/20.
//

#ifndef DEEPCARS_EVALUATOR_H
#define DEEPCARS_EVALUATOR_H

#include "../../lib/coredefs.h"
#include "genome.h"

#define EV_MUTATE_MIN_WEIGHT -2
#define EV_MUTATE_MAX_WEIGHT 2

typedef float (*evaluate_func_t)(genome_t* genome);

typedef struct _evaluator
{
   size_t population_size;
   list_t* genomes;
   list_t* new_genomes;

   evaluate_func_t evaluate_func;

   species_t** species;
   size_t species_count;

} evaluator_t;

evaluator_t* ev_create(size_t population_size, genome_t* orig, evaluate_func_t evaluate_func);

void ev_mutate(evaluator_t* evaluator);
void ev_evaluate(evaluator_t* evaluator);

void ev_free(evaluator_t* evaluator);
genome_t* ev_fittest_genome(evaluator_t* evaluator);

#endif //DEEPCARS_EVALUATOR_H
*/
