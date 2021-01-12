// Rough implementation of a C Math library, for educational purposes 

#define PI 3.14159265358979323846264338327950
#define E 2.7182818284590452353602874713527

// Returns |x| (absolute value of x)
double abs(double x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

// Returns a raised to the power of b
double pow(double a, double b) {
    if (b == 0)
        return 1;
    else if (b < 0) {
        return 1 / pow(a, -1 * b);
    }
    else if ((int)b % 2 == 0) {
        double h = pow(a, (int)(b / 2));
        return h * h;
    }
    else {
        return a * pow(a, b-1);
    }
}

// square root finder using Newton's method.
// let a be the number we are looking for and x be the root of a
// sqrt(a) = x
// a = x^2
// we are looking for a function with roots at x and -x, so we can say:
// 0 = x^2 - a
// f(x) = x^2 - a (if this part is confusing, imagine 'a' as 25 or 16)
// f'(x) = 2x
// By Newton's method, we can say:
// x_n+1 = x_n - f(x)/f'(x)
// when plugging the functions in, we get:
// x_n+1 = x_n - (x_n^2 - a)/(2x_n)
//       = x_n - (x_n - a/x_n)/2
//       = 2(x_n)/2 - (x_n - a/x_n)/2
//       = (x_n + a/x_n) / 2
// now we can solve for x_300, by which point this should converge well
// also, let x_1 = a 
double newtons_method_sqrt(double a) {
    double x_n = a;
    for (int i = 0; i < 300; i++) {
        x_n = (x_n + a / x_n) / 2.0;
    }
    return x_n;
}

// calculate natural log of x using taylor series
// https://en.wikipedia.org/wiki/Logarithm#Power_series - Implemented from 'More efficient series'
// Converges very slowly, have to rewrite this function :P
double ln(double x) {
    double sum = 0;
    for (int k = 0; k < 100; k++) {
        sum += (1.0 / (2 * k + 1)) * pow((x -  1) / (x + 1), 2 * k + 1);
    }
    return 2 * sum;
}

// returns logb n
// Remember: logb a = ln(a)/ln(b)
double log(double base, double n) {
    return ln(n) / ln(base);
}

// Truncates 'number' to 'places' decimal places
double truncate(double number, int places) {
    return ((int) (number * pow(10, places))) / pow(10, places); 
}

// Rounds floating number 'num' to 'places' places.
double round(double num, int places) {
    return truncate(num + (1.0 / (2 * pow(10,places))), places);
}

double floor(double x) {
    return (int) x;
}

double ceil(double x) {
    return (int) x + 1;
}

// Recursive factorial function, returns x!.
double factorial(double x) {
    if (x <= 1) {
        return 1;
    }
    return x * factorial(x - 1);
} 

// Converts radians to degrees
double radiansToDegrees(double radians) {
    return radians * 180 / PI;
}

// Converts degrees to radians
double degreesToRadians(double degrees) {
    return degrees / 180 * PI;
}


// Implementation of sin(x) using Taylor's Series of sin(x) 
// https://bit.ly/34FtnjF - MIT OCW Notes
// sin(x) = x - (x^3)/(3!) + (x^5/5!) - (x^7/7!) + ...
double sin(double radians) {
    double sum = 0;
    for (int n = 1; n < 100; n+=2) {
        sum += (1 / factorial(n)) * pow(radians, n); 
    }
    return sum;
}

// d/dx sin(x) = cos(x)
// Taking the derivative of the sin(x) series above gives us:
// cos(x) = 1 - (3x^2)/(3!) + (5x^4)/(5!) - (7x^6)/(7!)
// which simplifies to:
// cos(x) = 1 - (x^2)/(2!) + (x^4)/(4!) - (x^6)/(6!)
// So, instead of looping through odd numbers, we will use evens (notice n=1 vs n=0).
double cos(double radians) {
    double sum = 0;
    for (int n = 0; n < 100; n+=2) { 
        sum += (1 / factorial(n)) * pow(radians, n);
    }
    return sum;
}

// I'm too lazy to code the series for tan(x), so this will do for now, even if it's slower :P
double tan(double radians) {
    return sin(radians) / cos(radians);
}

double arcsin(double radians) {
    if (abs(radians) > 1) {
        return 1.0 / 0.0;
    }
    double sum = 0;
    for (int n = 0; n < 50; n++) {
        sum += (factorial(2 * n)) / (pow(4,n) * pow(factorial(n), 2) * (2 * n + 1)) * pow(radians, 2 * n + 1);
    }
    return sum;
}

// differentiation of a function at a point
double d_dx(double (*f) (double), double x) {
    double h = 0.000000001;
    return (f(x + h) - f(x)) / h;
}

int main() {
    printf("%f", round(10.3251,2));
    return 0;
}
