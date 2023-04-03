#include <iostream>
#include <cstdlib>
using namespace std;

class NComplex
{
public:
    NComplex();
    NComplex(double re, double im);
    friend NComplex operator +(double d, NComplex num2);
    friend NComplex operator -(double d, NComplex num2);
    friend NComplex operator *(double d, NComplex num2);
    friend NComplex operator /(double d, NComplex num2);
    friend NComplex operator +(NComplex num1, double d);
    friend NComplex operator -(NComplex num1, double d);
    friend NComplex operator *(NComplex num1, double d);
    friend NComplex operator /(NComplex num1, double d);
    friend NComplex operator +(NComplex num1, NComplex num2);
    friend NComplex operator -(NComplex num1, NComplex num2);
    friend NComplex operator *(NComplex num1, NComplex num2);
    friend NComplex operator /(NComplex num1, NComplex num2);
    friend ostream& operator <<(ostream& os, NComplex num1);

private:
    double RePart;
    double ImPart;
};

int main()
{
    NComplex n1(5.1, 2.2), n2(2.0, 2.0), n3;
    double d1 = 3.0;

    cout << "n1+n2: " << n1+n2 << endl;
    cout << "n1*n2: " << n1*n2 << endl;
    cout << "n1-d1: " << n1-d1 << endl;
    cout << "d1*n2: " << d1*n2 << endl;
    cout << "n1/n3: " << n1/n3 << endl;
}

NComplex::NComplex()
{
    RePart = 0;
    ImPart = 0;
}

NComplex::NComplex(double re, double im)
{
    RePart = re;
    ImPart = im;
}

NComplex operator +(double d, NComplex num2)
{
   return NComplex(num2.RePart + d, num2.ImPart);
}

NComplex operator -(double d, NComplex num2)
{
   return NComplex(d - num2.RePart, num2.ImPart);
}

NComplex operator *(double d, NComplex num2)
{
   return NComplex(num2.RePart * d, num2.ImPart * d);
}

NComplex operator /(double d, NComplex num2)
{
    if (num2.RePart == 0)
    {
        cout << "Error: divide by zero" << endl;
        exit(0);
    }
    return NComplex(d / num2.RePart, d / num2.ImPart);
}

NComplex operator +(NComplex num1, double d)
{
   return NComplex(num1.RePart + d, num1.ImPart);
}

NComplex operator -(NComplex num1, double d)
{
   return NComplex(num1.RePart - d, num1.ImPart);
}

NComplex operator *(NComplex num1, double d)
{
   return NComplex(num1.RePart * d, num1.ImPart * d);
}

NComplex operator /(NComplex num1, double d)
{
    if (d == 0)
    {
        cout << "Error: divide by zero" << endl;
        exit(0);
    }
    return NComplex(num1.RePart / d, num1.ImPart / d);
}

NComplex operator +(NComplex num1, NComplex num2)
{
    double aRe = num1.RePart + num2.RePart;
    double aIm = num1.ImPart + num2.ImPart;
    return NComplex(aRe, aIm);
}

NComplex operator -(NComplex num1, NComplex num2)
{
    double aRe = num1.RePart - num2.RePart;
    double aIm = num1.ImPart - num2.ImPart;
    return NComplex(aRe, aIm);
}

NComplex operator *(NComplex num1, NComplex num2)
{
    double calcRe = num1.RePart * num2.RePart;
    double ipow = num1.ImPart * num2.ImPart;
    double aIm = (num1.RePart * num2.ImPart) + (num1.ImPart * num2.RePart);
    return NComplex(calcRe - ipow, aIm);
}

NComplex operator /(NComplex num1, NComplex num2)
{
    double aNumerRe = (num1.RePart * num2.RePart) + (num1.ImPart * num2.ImPart);
    double aNumerIm = (num1.RePart * -num2.ImPart) + (num1.ImPart * num2.RePart);
    double aDenom = (num2.RePart * num2.RePart) + (num2.ImPart * num2.ImPart);
    if (num2.RePart == 0)
    {
        cout << "Error: divide by zero" << endl;
        exit(0);
    }
    return NComplex(aNumerRe / aDenom, aNumerIm / aDenom);
}

ostream& operator <<(ostream& os, NComplex num1)
{
    os << fixed;
    os.precision(1);
    os << num1.RePart << " + " << num1.ImPart << "i";
    return os;
}