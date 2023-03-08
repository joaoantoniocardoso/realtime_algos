#include "real_time_smoothing_algorithms.h"

float compute_SMA(float input)
{
    const unsigned int length = 10;
    static float buffer[10] = {0};
    static unsigned int n = 0;
    static float sum = 0;

    sum += (input -buffer[n]);
    buffer[n] = input;
    if(++n >= length) n = 0;

    return sum/length;
}

float compute_RMA(float input)
{
    const unsigned int length = 10;
    static unsigned int n = 0;
    static float sum = 0;

    if(n < length) n++;
    sum = ((n -1)*sum +input)/n

    return sum;
}

float compute_fixed_length_RMA(float input)
{
    const unsigned int length = 10;
    static float sum = 0;

    sum = ((length -1)*sum +input)/length

    return sum;
}

float compute_CMA(float input, char reset)
{
    static unsigned int n = 0;
    static float sum = 0;

    if(reset) n = sum = 0;

    sum += (input -sum)/++n;

    return sum;
}

float compute_EMA(float input)
{
    const unsigned int length = 10;
    static unsigned int n = 0;
    static float sum = 0;

    if(n < length) n++;
    sum += (input -sum)/n;

    return sum;
}

float compute_fixed_length_EMA(float input)
{
    const unsigned int length = 10;
    static float sum = 0;

    sum += (input -sum)/length;

    return sum;
}

float compute_simple_average(float input)
{
    const unsigned int length = 10;
    static unsigned int n = 0;
    static float sum = 0;
    static float avg = 0;

    sum += input;
    if(++n >= length){
        avg = sum/length;
        sum = n = 0;
    }

    return avg;
}

float compute_FIR(float input)
{
    const unsigned int numtaps = 25;
    static float input_buffer[25] = {0};
    static unsigned int n = 0;

    // Hanning lowpass FIR for w = 600Hz/24000Hz w/ 25 taps
    const float b[25] = {
        0.0,        0.00087568, 0.00383456, 0.00919984, 0.01701295, 0.02700228,
        0.03859222, 0.05095322, 0.06308749, 0.07394001, 0.08252077, 0.08802234,
        0.08991729, 0.08802234, 0.08252077, 0.07394001, 0.06308749, 0.05095322,
        0.03859222, 0.02700228, 0.01701295, 0.00919984, 0.00383456, 0.00087568,
        0.0
    };

    unsigned int k=0, i;
    float output = 0;

    input_buffer[n] = input;

    for(i=n; i; k++, i--)
        output += b[k] * input_buffer[i];

    for(i=numtaps-1; i > n; k++, i--)
        output += b[k] * input_buffer[i];

    if(n++ >= numtaps) n = 0;

    return output;
}

float compute_IIR(float input)
{
    const unsigned int numtaps = 5;
    static float input_buffer[5] = {0};
    static float output_buffer[5] = {0};
    static unsigned int n = 0;

    // Butterworth lowpass IIR for w = 600Hz/24000Hz w/ 5 taps
    const float b[5] = {
        3.12389769e-5, 1.24955908e-4, 1.87433862e-4, 1.24955908e-4, 3.12389769e-5
    };
    const float a[5] = {
        1.0, -3.58973389, 4.85127588, -2.92405266, 0.66301048
    };

    unsigned int k=0, i;
    float output = 0;

    input_buffer[n] = input;

    for(i=n; i; ++k, --i)
        output += b[k] * input_buffer[i]
                 -a[k] * output_buffer[i];

    for(i=(numtaps-1); i > n; ++k, i--)
        output += b[k] * input_buffer[i]
                 -a[k] * output_buffer[i];

    output_buffer[n] = output;
    if(n++ >= numtaps) n = 0;

    return output;
}

float compute_true_RMS(float input)
{
    static unsigned int n = 0;
    const unsigned int length = 100
    static float buffer[100] = {0};
    static float sum = 0;

    sum -= buffer[n];
    buffer[n] = powf(input, 2);
    sum += buffer[n];

    if(++n >= length) n = 0;

    return sqrtf(sum/length);
}