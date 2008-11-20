#ifndef LDA_INFERENCE_H
#define LDA_INFERENCE_H

#include <math.h>
#include <float.h>
#include <assert.h>
#include "lda.h"
#include "utils.h"

#define NEWTON_THRESH 1e-5
#define MAX_ALPHA_ITER 1000


int LAG = 5;

float EM_CONVERGED;
int EM_MAX_ITER;
int ESTIMATE_ALPHA;
double INITIAL_ALPHA;
int NTOPICS;
float VAR_CONVERGED;
int VAR_MAX_ITER;

#ifdef USE_RUBY
corpus *last_corpus;
lda_model *last_model;
double **last_gamma;

enum BOOL { FALSE, TRUE } corpus_loaded, model_loaded, VERBOSE;
#endif

double lda_inference(document*, lda_model*, double*, double**);
double compute_likelihood(document*, lda_model*, double**, double*);


double doc_e_step(document* doc,
                  double* gamma,
                  double** phi,
                  lda_model* model,
                  lda_suffstats* ss);

void save_gamma(char* filename,
                double** gamma,
                int num_docs,
                int num_topics);

void run_em(char* start,
            char* directory,
            corpus* corpus);

#ifdef USE_RUBY
void run_quiet_em(char* start, corpus* corpus);
#endif

void read_settings(char* filename);

void infer(char* model_root,
           char* save,
           corpus* corpus);
           
           

double alhood(double a, double ss, int D, int K);
double d_alhood(double a, double ss, int D, int K);
double d2_alhood(double a, int D, int K);
double opt_alpha(double ss, int D, int K);
void maximize_alpha(double** gamma, lda_model* model, int num_docs);


#endif