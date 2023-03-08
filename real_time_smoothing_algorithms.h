#ifndef REAL_TIME_SMOOTHING_ALGORITHMS_H
#define REAL_TIME_SMOOTHING_ALGORITHMS_H

float compute_SMA(float input);
float compute_RMA(float input);
float compute_fixed_length_RMA(float input);
float compute_CMA(float input, char reset);
float compute_EMA(float input);
float compute_fixed_length_EMA(float input);
float compute_simple_average(float input);
float compute_FIR(float input);
float compute_IIR(float input);
float compute_true_RMS(float input);

#endif /* REAL_TIME_SMOOTHING_ALGORITHMS_H */