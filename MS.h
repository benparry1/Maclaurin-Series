#include <string>
using namespace std;
class MS
{

public:
   
   MS();				// constructs a MS for a sine series with n=0 and cenetred at 0
   MS(string f, int n, double c=0);       // series for function f of order n, centered at c
   ~MS();


   double approx (double x);		// uses MS to approximate x
   double * plot(double l, double r, int p);	//outputs an array of coordinates in the range l to r and in increpments determined by th enumber of data points desired
   void file (char * s);
   //acessors

   int GetPoints() const;
   string GetType() const;
   int GetOrder() const;
   double GetCenter() const;
   

private:

   double fac (int n);                  // n factorial
   double l_range;
   double r_range;
   int order;
   int points;
   double * coeff;
   double center;
   string type; 
   double * coord;
   bool perm;
};
