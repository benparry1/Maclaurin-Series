#include "MS.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

MS::MS()    //constructs a 0th order MS with the default function being sine centered at 0 
{
   center=0;
   order=0;
   coeff= new double[1];
   coeff[0]=0;
   perm=1;
   coord = new double[1];
}

MS::MS(string f, int n, double c)      // creates an nth order MS for function f, centered at c
{
   type=f;
   center=c;
   order=n;
   coord=new double [1];

   coeff= new double[order+1];
   double a;
   if(type=="sine" || type=="sin") 			// series coefficiants f^n(c)/n!
   {
      for (int i = 0; i <= order; i++) {
      if ((i + 4) % 4 == 0)
          a = sin(center);
      else if ((i + 4) % 4 == 1)
          a = cos(center);
      else if ((i + 4) % 4 == 2)
          a = -sin(center);
      else if ((i + 4) % 4 == 3)
          a = -cos(center);
      coeff[i] = a/fac(i);
      }
      perm=1;
   }
   else if(type=="euler" || type=="e")    // x^n/n!
   {
      for(int i=0; i<=order; i++){
         a=exp(center);
         coeff[i]=a/fac(i);
      }
      perm=1; 
   }
   else if(type=="cosine" || type == "cos"){    // (-1)^n * x^2n / (2n)!
      for (int i = 0; i <= order; i++) {
         if ((i + 4) % 4 == 0)
            a = cos(center);
         else if ((i + 4) % 4 == 1)
            a = -sin(center);
         else if ((i + 4) % 4 == 2)
            a = -cos(center);
         else if ((i + 4) % 4 == 3)
            a = sin(center);
         coeff[i] = a/fac(i);
       }
      perm=1;
   }
   else if(type=="rs" || type=="reciprical squared")     // 1/1+x^2
   {
      // (-1)^n * x^2n  -->  cos(x) w/o factorial

      for (int i = 0; i <= order; i++) {
         if ((i + 4) % 4 == 0)
            a = cos(center);
         else if ((i + 4) % 4 == 1)
            a = -sin(center);
         else if ((i + 4) % 4 == 2)
            a = -cos(center);
         else if ((i + 4) % 4 == 3)
            a = sin(center);
         coeff[i] = a;
       }
      perm=1;
   }
   else if(type=="rd" || type=="reciprical difference")
   {
      //sigma x^n  -->  e^x w/o the factorial

      for(int i=0; i<=order; i++)
         coeff[i]=exp(center);

      perm=1; 
   }
   else if(type=="ln" || type=="natural log")      // ln(1+x)
   {
      //(-1)^n+1 * x^n/n  -->  e^x without constant 1 term and without factorial of n

      for(int i=0; i<=order; i++){
         a=exp(center);
         coeff[i]=a/i+1;
      }
      perm=1; 
   }
   else
   {
      cout<<"invalid function name"<<'\n';
      delete [] coeff;
      coeff= new double[1];
      order=0;
      coeff[0]=0;
   }
}

double MS::fac (int n)                  // n factorial
{
   double sum=1;
   for(int i=1; i<=n; i++)
      {  sum=sum*i;   }
   return sum;
}

double MS::approx (double x)            // uses MS to approximate x
{
   //if(perm){
      double sum=0;
      for(int i=0; i<=order; i++)
         sum=sum+(coeff[i]* pow(x-center,i));

      return sum;
   //}
}

double * MS::plot(double l, double r, int p)      //outputs an array of coordinates in the range l to r and in increpments of step
{
   l_range=l;
   r_range=r;
   delete [] coord;
   coord = new double [p+1];
   points=p;
   double itt=(r-l)/p;
   int step=0;
   while(step<=p)
   {
      coord[step]=approx(l+(step*itt));
      step++;
   }

   return coord;
   //delete [] coord;
}

void MS::file (char *  s) 
{

   ofstream out;
   out.open(s);
   double itt=(r_range-l_range)/points;
   for(int i=0; i<=points; i++)
      out<<"("<<l_range+(i*itt)<<","<<coord[i]<<")"<<'\n';
   out.close();
}

int MS::GetPoints() const
{
   return points;
}

string MS::GetType() const
{
   return type;
}

int MS::GetOrder() const
{
   return order;
}

double MS::GetCenter() const
{
   return center;
}

MS::~MS()
{
   delete [] coeff;
   delete [] coord;
}
