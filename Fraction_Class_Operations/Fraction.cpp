//
//  Fraction_Mathworks
//  Author: Ram Hariesh Coimbatore Annadorai
//

#include <iostream>
#include <limits>
using namespace std;


/*
 * Fraction class supports the following operations: addition, subtraction, multiplication, division, lesser than,
 * greater than, equality, Inequality and display(<<)
 * NOTE:  This works for the fractions of the same template type
 * Any Fraction should not have its denominator to be zero and adding/multiplying any two template type values should not
 * result in overflow error, else "overflow error" is thrown.
 */


template <class T>
class Fraction {
    
    // Numerator and Denominator of a fraction of template type is represented as T num, T den.
    T num;
    T den;
    
    // gcd function is there to find the Greatest Common Divisor any two given value of Template type.
    T gcd( T a, T b ) {
        if( b == 0 ) return a;
        return gcd (b, a % b);
    }
    
public:
    
    
    // Default Constructor
    Fraction() : num(0), den(0) { }
    
    
    
    // Parametirized constructor
    Fraction( T n, T d ) : num(n) , den(d) { }
    
    
    
    
    /* Overlaoded Operator '+'
     * Returns the sum of two fractions of the same template type.
     * Throws an error message on invalid denominator(denominator is zero) and overflow during addition.
     * Addition of any two given fractions of template type such as (a/b) and (c/d) happens as (((a*d)+(b*c))/(b*d))
     */
    Fraction<T> operator+(Fraction<T> rhs){
        try{
            // When the denominator of the (this)object or the rhs object is zero an error is thrown
            if(den==(T)0 || rhs.den==(T)0){
                throw "Denominator is zero";
            }
            
            /*  (this->num*rhs.den) and (rhs.num*this->den) is checked for, any of these two multiplication operation
             *  results in over flow. If an over flow is detected in either of these two then a overflow error is thrown.
             *  Which makes the numerator of the resultant fraction to overflow, which is wrong. And the whole addition
             *  operation is aborted.
             */
            
            if(!checkValid(abs(this->num),abs(rhs.den),'*')|| !checkValid(abs(rhs.num),abs(this->den),'*')){
                throw "Overflow error during addition operation";
            }
            
            T temp_first=(this->num)*(rhs.den);
            T temp_second=(rhs.num)*(this->den);
            
            /*  When above operation doesn't throw any error, then both multiplied values has to be added to form the
             *  numerator of the resultant fraction. But this addition operation should not overflow. It checked for the
             *  overflow and an error is thrown if there is an overflow.
             */
            
            if(!checkValid(temp_first,temp_second,'+')){
                throw "Overflow error during addition operation";
            }
            
            /*  Denominator of the resultant fraction is formed by multiplying the denominators of both the fractions, which
             *  should not result in any error. If so, an overflow error is thrown
             */
            
            if(!checkValid(abs(this->den), abs(rhs.den), '*')){
                throw "Overflow error during addition operation";
            }
            
        }
        catch(const char *err){
            cout<<"Error:\t"<<err<<endl;
            throw err;
        }
        catch(...){
            cout<<"Some Anonymous Ecrror"<<endl;
            throw;
        }
        
        /*  Having reached this step, which impllies that the potential numerator and denominator of the resultant fraction
         *  does not result in any error. so the numerator and denomninator of the resultant object is calculated and
         *  returned.
         */
        
        Fraction<T> result;
        result.num=(this->num)*(rhs.den)+(rhs.num)*(this->den);
        result.den=(this->den)*(rhs.den);
        result.simplify();
        return result;
    }
    
    
    
    
    /*  Overlaoded Operator '*'
     *  Returns the multiplications of two fractions of the same template type.
     *  Multiplication among fractions is performed by multiplying the numerators of both the fractions to form the
     *  numerator of the resultant fraction, multiplying both the denominators to form the denominator of the resultant
     *  fraction.
     *  Throws an error message on invalid denominator(denominator is zero) and overflow during multiplication.
     */
    Fraction<T> operator*(Fraction<T> rhs){
        try{
            // When the denominator of the (this)object or the rhs object is zero an error is thrown
            if(den==(T)0 || rhs.den==(T)0){
                throw "Denominator is zero";
            }
            /* multiplication of the numerators of both the fractions or the denominator of both the fractions should not
             * result in an overflow error. If so, overflow error is thrown.
             */
            if((!checkValid(abs(this->num),abs(rhs.num),'*'))||(!checkValid(abs(this->den), abs(rhs.den), '*')))
            {
                throw "Overflow error during mulitplication operation";
            }
        }
        catch(const char *err){
            cout<<"Error:\t"<<err<<endl;
            throw err;
        }
        catch(...){
            cout<<"Some Anonymous Error"<<endl;
            throw;
        }
        
        /* Having reached this step, it means that the resultant fractions objects' numerator and denominator does not
         * have overflow error, so the resultant object numerator and denominator is computed and the object is returned.
         */
        
        Fraction<T> result;
        result.num=(this->num)*(rhs.num);
        result.den=(this->den)*(rhs.den);
        result.simplify();
        if(result.den<(T)0){
            result.num=(-(result.num));
            result.den=abs(result.den);
        }
        return result;
    }
    
    
    
    
    /* Overloaded Operator '-'
     * Returns the subtraction of two fractions of the same template type.
     * Throws an error message on invalid denominator(denominator is zero) and overflow during subtraction.
     * Subtraction of any two given fractions of template type such as (a/b) and (c/d) happens as (((a*d)-(b*c))/(b*d))
     * The subtraction is similar to the addition operation except for the '-' sign in the numerator. The addition routine
     * can in turn be made use of by making the equation as(((a*d)+(-(b*c)))/(b*d))
     */
    Fraction<T> operator-(Fraction<T> rhs){
        try{
            //When the denominator of the (this)object or the rhs object is zero an error is thrown
            if(den==(T)0 || rhs.den==(T)0){
                throw "Denominator is zero";
            }
            return (*this+(-(rhs)));
        }
        catch(const char *err){
            cout<<"Error:\t"<<err<<endl;
            throw err;
        }
        catch(...){
            cout<<"One of the denominator is zero"<<endl;
            throw;
        }
        /* unary '-' operator routine is called to negate the rhs object such that addition of the (this) object and rhs
         * object can be performed. The resultant object/error from addition routine is returned.
         */
        
    }
    
    
    
    
    /* Overloaded unary operator '-'
     * Numerator of the (this) object is negated, so that it helps the subtraction routine to make use of the addition
     * routine.
     */
    Fraction<T> operator-(){
        Fraction result;
        result.num=(-(this->num));
        result.den=this->den;
        return result;
    }
    
    
    
    
    /* Overloaded operator '/'
     * Returns the division of two fractions of the same template type
     * Throws an error message on invalid denominator(denominator is zero) and overflow during division.
     * Division of any two given fractions of the same template type such as (a/b) and (c/d) is given as ((a*d)/(b*c))
     * This is the same as the multiplication routine except that the rhs fraction is being inverted to obtain the resultant
     * Fraction object.
     */
    Fraction<T> operator / (Fraction<T> rhs){
        try{
            // When the denominator of the (this)object or the rhs object is zero an error is thrown
            if(den==(T)0 || rhs.den==(T)0){
                throw "Denominator is zero";
            }
            Fraction result;
            result.num=rhs.den;
            result.den=rhs.num;
            return ((*this)*(result));
        }
        catch(const char *err){
            cout<<"Error:\t"<<err<<endl;
            throw err;
        }
        catch(...){
            cout<<"One of the denominator is zero"<<endl;
            throw;
        }
        /* The rhs object get inverted and a new object gets created out of that inversion. The (this) object is multiplied
         * with the inverted object to produce the resultant division Fraction object. For this purpose the multiplication
         * routine gets reused.
         */
        
    }
    
    
    
    
    /* For Example: A integer fraction (3/6) should be simplified as (1/2) by finding the Greatest Common Divisor(GCD) the
     * numerator and denominator and to divide both the numerator and denominator with that GCD value.That is the use of
     * this routine with the numerator and denominator in the template type.
     */
    void simplify( ) {
        T g = gcd ( abs(num),abs(den) );
        num = num / g;
        den = den / g;
    }
    
    
    
    
    /* Overloaded operator '=='
     * Throws an error message on invalid denominator(denominator is zero)
     * After simplying the (this) Fraction object and rhs object, both the Fraction objects has to be compared along the
     * terms of numerator with numerator and denominator with denominator to determine whether both the Fraction objects
     * are equal
     */
    bool operator == (Fraction<T> rhs) {
        try{
            //When the denominator of the (this)object or the rhs object is zero an error is thrown
            if(den==(T)0 || rhs.den==(T)0){
                throw "Denominator is zero";
            }
        }
        catch(const char *err){
            cout<<"Error:\t"<<err<<endl;
            throw err;
        }
        catch(...){
            cout<<"Some Anonymous Error"<<endl;
            throw;
        }
        
        /* Having reached this step,the (this) object's numerator is to be compared with rhs numerator and  rhs denominator
         * is compared with (this) object's denominator to determine whether both the objects are equal.
         */
        
        simplify();
        rhs.simplify();
        if( den == rhs.den ) return ( num == rhs.num );
        return false;
    }
    
    
    
    
    /* Overloaded operator '!='
     * Throws an error message on invalid denominator(denominator is zero)
     * To determine whether the Fraction Objects are Inequal, the Equality routine should return a false. So both the
     * Fraction both objects are sent to Equality routine to determine whether they are equal or not.
     */
    bool operator != (Fraction<T> rhs) {
        try{
            //When the denominator of the (this)object or the rhs object is zero an error is thrown
            if(den==(T)0 || rhs.den==(T)0){
                throw "Denominator is zero";
            }
            return !((*this)==rhs);
        }
        catch(const char *err){
            cout<<"Error:\t"<<err<<endl;
            throw err;
        }
        catch(...){
            cout<<"Some Anonymous Error"<<endl;
            throw;
        }
        
    }
    
    
    
    
    /* Overloaded operator '<'
     * Throws an error message on invalid denominator(denominator is zero)
     * To determine whether a Fraction Object is less than the other object, the Fraction of Template type is converted
     * to double data type by dividing the numerator with denominator for both the object.
     */
    bool operator < (Fraction<T> rhs){
        try{
            //When the denominator of the (this)object or the rhs object is zero an error is thrown
            if(den==(T)0 || rhs.den==(T)0){
                throw "Denominator is zero";
            }
        }
        catch(const char *err){
            cout<<"Error:\t"<<err<<endl;
            throw err;
        }
        catch(...){
            cout<<"Some Anonymous Error"<<endl;
            throw;
        }
        
        /* Having reached this step, the (this) object's numerator is divided by its denominator and the resultant value is 
         * converted to double data type. The same is done with rhs object and then the this objects' doubel value is 
         * compared with rhs object double value to determine whether the latter is less than former.
         */
        
        double this_object=(static_cast<double>(this->num)/this->den);
        double rhs_object=(static_cast<double>(rhs.num)/rhs.den);
        return (this_object<rhs_object);
    }
    
    
    
    
    /* Overloaded operator '>'
     * Throws an error message on invalid denominator(denominator is zero)
     * To determine whether a Fraction Object is greater than the other object, the Fraction of Template type is
     * converted to double data type by dividing the numerator with denominator for both the object.
     */
    bool operator > (Fraction<T> rhs){
        try{
            //When the denominator of the (this)object or the rhs object is zero an error is thrown
            if(den==(T)0 || rhs.den==(T)0){
                throw "Denominator is zero";
            }
        }
        catch(const char *err){
            cout<<"Error:\t"<<err<<endl;
            throw err;
        }
        catch(...){
            cout<<"Some Anonymous Error"<<endl;
            throw;
        }
        
        /* Having reached this step, the (this) object's numerator is divided by its denominator and the resultant value is
         * converted to double data type. The same is done with rhs object and then the this objects' double value is
         * compared with rhs object double value to determine whether the latter is greater than former.
         */
        
        double this_object=(static_cast<double>(this->num)/this->den);
        double rhs_object=(static_cast<double>(rhs.num)/rhs.den);
        return (this_object>rhs_object);
    }
    
    
    
    /* Displaying of Fraction object involves displaying the numerator of the object and its denominator. But this display
     * will not only take place in a class but also outside the Fraction class. So for this purpose the operator ('<<') is o
     * overloaded and the function is declared as Friend function.
     */
    template <class F>
    friend ostream & operator << ( ostream & out ,  const Fraction<F> & f  );
    
    
    
    
    /* While doing any of the basic operations such as addition, subtraction and multiplication there is a possibility of
     * overflow, where the operation between any two template type values might go beyond the template type's max value or
     * below the template type's min value. This should be checked and reported as overflow error.
     */
    bool checkValid(T a,T b,char c){
        
        switch(c){
                  // Overflow error is being check for addition operation
            case '+':
            {
                if ((b > 0) && (a > numeric_limits<T>::max() - b)) return false;
                if ((b < 0) && (a < numeric_limits<T>::min() - b)) return false;
                return true;
                
            }
                  // Overflow error is being check for multiplication operation
            case '*':{
                
                if (a > numeric_limits<T>::max() / b) return false;
                if ((a < numeric_limits<T>::min() / b)) return false;
                if ((a == -1) && (b == numeric_limits<T>::min())) return false;
                if ((b == -1) && (a == numeric_limits<T>::min())) return false;
                return true;
            }
                
        }
        return true;
    }
    
};




/* Overloaded operator '<<'
 * Function template. Friend function that is being defined outside the Fraction class. Display operator '<<' is being
 * overloaded to display the numerator and denominator part of the Fraction object when the object is provided to the
 * output stream
 */
template <class F>
ostream & operator << ( ostream & out ,  const Fraction<F> & f  ) {
    out<<"Fraction is : "<<f.num<<"/"<<f.den<<endl;
    return out;
}
