//Mateusz Okulus listopad 2017
//Projekt PRI laboratoria nr 1
#include <math.h> //funkcja cos(x)
#include <stdio.h> //konsola
#include <float.h> //uzywanie DBL_DIG

double f(double x); //funkcja całkowana
double integrate(double a, double b, int steps); //liczenie całki metodą trapezów z steps podziałów
double calculateIntegral(double a, double b, double accuracy); //oblicznie całki dopóki wartość nie ustabilizuje się poniżej błędu

double f(double x)
{
  return -x*x*cos(x);
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

double calculateIntegral(double a, double b, double accuracy)
{
  int steps = 32;
  double oldIntegral = integrate(a, b, steps);
  steps *= 2;
  double newIntegral = integrate(a, b, steps);
  while( fabs(newIntegral - oldIntegral) > accuracy )
  {
    oldIntegral = newIntegral;
    steps *= 2;
    newIntegral = integrate(a, b, steps);
  }
  double integral = integrate(a, b, steps);
  return integral;
}

int main()
{
  double a = 0, b = 0, e = 0;

  while( scanf("%lf %lf %lf", &a, &b, &e) == 3)
  {
    if(a < -5 || b < a || b > 5 || e <= 0)
    {
      printf("\nNiepoprawne dane");
      return 1;
    }

    double calculated = calculateIntegral(a, b, e);
    printf("%.*lf\n", DBL_DIG-1, calculated);
  }
  return 0;
}
