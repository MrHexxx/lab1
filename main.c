#include <math.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

double f(double x);
double integral(double x);
double defIntegral(double a, double b);
double integrate(double a, double b, int steps);
int calcN(double a, double b, double accuracy);
double r01();

double max = 23;

double integrateMine(double a, double b, double accuracy)
{
  int steps = 32;
  double oldIntegral = integrate(a, b, steps);
  steps *= 2;
  double newIntegral = integrate(a, b, steps);
  while( fabs(newIntegral - oldIntegral) > accuracy )
  {
    steps = (int)(2 * steps);
    oldIntegral = newIntegral;
    newIntegral = integrate(a, b, steps);
  }
  double integral = integrate(a, b, steps);
  return integral;
}

double integrateMath(double a, double b, double accuracy)
{
  int steps = calcN(a, b, accuracy) * 2;
  double integral = integrate(a, b, steps);
  return integral;
}

int main()
{
  srand(3);

  double (*integralPtr)(double, double, double) = &integrateMath;

  // for(int i = 0; i < 1000000; i++)
  int i = 1;
  while(1)
  {
    double a = r01() * 10 - 5; //<-5,5>
    double bRange = 5 - a;
    double b = r01() * bRange + a;
    if(b == a)
    {
      a = -2;
      b = 2;
    }
    double accuracy = r01() / 100.0;

    double calculated = (*integralPtr)(a, b, accuracy);
    double value = defIntegral(a, b);
    double error = fabs( calculated - value );
    if(error <= accuracy)
    {
      if(i % 10000 == 0)
        printf("%d - Correct!\n", i);
    }
    else
    {
      printf("%d - Error - a=%f b=%f accuracy=%f error=%f value=%f calculated=%f\n", i, a, b, accuracy, error, value, calculated);
    }

    i++;
  }
  printf("FINISHED\n");
  return 0;
}

double f(double x)
{
  return -x*x*cos(x);
}

double integral(double x)
{
  return -(x*x - 2)*sin(x) - 2*x*cos(x);
}

double defIntegral(double a, double b)
{
  return integral(b) - integral(a);
}

double integrate(double a, double b, int steps)
{
  double dx = (b - a) / steps;
  double integral = 0;
  double left = a;
  double right = left + dx;
  for(int i = 0; i < steps; i++)
  {
    integral += dx * ( f(left) + f(right) ) / 2;
    left += dx;
    right += dx;
  }
  return integral;
}

int calcN(double a, double b, double accuracy)
{
  int n = sqrt( max * (pow(b-a, 3) / 12.0) * (1.0 / accuracy) ) + 1;
  //printf("n = %d\n", n);
  return n;
}

double r01()
{
  return (double)rand() / (double)RAND_MAX;
}
