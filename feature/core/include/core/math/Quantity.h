// "RQuantity.h" header file
#include <ratio>

// The "RQuantity" class is the prototype template container class, that just holds a double value. The
// class SHOULD NOT BE INSTANTIATED directly by itself, rather use the quantity types defined below.
template<typename MassDim, typename LengthDim, typename TimeDim, typename TempDim>
class RQuantity
{
private:
    float value;

public:
    constexpr RQuantity() : value(0.0) {}
	constexpr RQuantity(float val) : value(val) {}
    explicit constexpr RQuantity(double val) : value(static_cast<float>(val)) {}
    explicit constexpr RQuantity(long double val) : value(static_cast<float>(val)) {}

    // The intrinsic operations for a quantity with a unit is addition and subtraction
    constexpr RQuantity const& operator+=(const RQuantity& rhs)
    {
        value += rhs.value;
        return *this;
    }
    constexpr RQuantity const& operator-=(const RQuantity& rhs)
    {
        value -= rhs.value;
        return *this;
    }

    // Returns the value of the quantity in multiples of the specified unit
    constexpr float Convert(const RQuantity& rhs) const
    {
        return value / rhs.value;
    }

    // returns the raw value of the quantity (should not be used)
    constexpr float getValue() const
    {
        return value;
    }
};


// Predefined (physical unit) quantity types:
// ------------------------------------------
#define QUANTITY_TYPE(_Mdim, _Ldim, _Tdim, _TempDim, name) \
    typedef RQuantity<std::ratio<_Mdim>, std::ratio<_Ldim>, std::ratio<_Tdim>, std::ratio<_TempDim>> name;

// Replacement of "float" type
QUANTITY_TYPE(0, 0, 0, 0, Number);

// Physical quantity types
QUANTITY_TYPE(1, 0, 0, 0, QMass);
QUANTITY_TYPE(0, 1, 0, 0, QLength);
QUANTITY_TYPE(0, 2, 0, 0, QArea);
QUANTITY_TYPE(0, 3, 0, 0, QVolume);
QUANTITY_TYPE(0, 0, 1, 0, QTime);
QUANTITY_TYPE(0, 1, -1, 0, QSpeed);
QUANTITY_TYPE(0, 1, -2, 0, QAcceleration);
QUANTITY_TYPE(0, 1, -3, 0, QJerk);
QUANTITY_TYPE(0, 0, -1, 0, QFrequency);
QUANTITY_TYPE(1, 1, -2, 0, QForce);
QUANTITY_TYPE(1, -1, -2, 0, QPressure);
QUANTITY_TYPE(0, 0, 0, 1, QTemperature);
QUANTITY_TYPE(1, 2, -2, -1, QGasConstant);

QUANTITY_TYPE(1, -3, 0, 0, QDensity);
QUANTITY_TYPE(0, 3, -1, 0, QVolumetricFlow);



// Standard arithmetic operators:
// ------------------------------
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> 
    operator+(const RQuantity<M, L, T, A>& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return RQuantity<M, L, T, A>(lhs.getValue() + rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> 
    operator-(const RQuantity<M, L, T, A>& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return RQuantity<M, L, T, A>(lhs.getValue() - rhs.getValue());
}
template <typename M1, typename L1, typename T1, typename A1, 
          typename M2, typename L2, typename T2, typename A2>
constexpr RQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>, 
                    std::ratio_add<T1, T2>, std::ratio_add<A1, A2>> 
    operator*(const RQuantity<M1, L1, T1, A1>& lhs, const RQuantity<M2, L2, T2, A2>& rhs)
{
    return RQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>, 
                     std::ratio_add<T1, T2>, std::ratio_add<A1, A2>>
                    (lhs.getValue()*rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> 
    operator*(const double& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return RQuantity<M, L, T, A>(lhs*rhs.getValue());
}
template <typename M1, typename L1, typename T1, typename A1, 
          typename M2, typename L2, typename T2, typename A2>
constexpr RQuantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>,
                    std::ratio_subtract<T1, T2>, std::ratio_subtract<A1, A2>> 
    operator/(const RQuantity<M1, L1, T1, A1>& lhs, const RQuantity<M2, L2, T2, A2>& rhs)
{
    return RQuantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>, 
                     std::ratio_subtract<T1, T2>, std::ratio_subtract<A1, A2>>
                    (lhs.getValue() / rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<std::ratio_subtract<std::ratio<0>, M>, std::ratio_subtract<std::ratio<0>, L>,
                    std::ratio_subtract<std::ratio<0>, T>, std::ratio_subtract<std::ratio<0>, A>> 
    operator/(double x, const RQuantity<M, L, T, A>& rhs)
{
    return RQuantity<std::ratio_subtract<std::ratio<0>, M>, std::ratio_subtract<std::ratio<0>, L>, 
                     std::ratio_subtract<std::ratio<0>, T>, std::ratio_subtract<std::ratio<0>, A>>
                    (x / rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> 
    operator/(const RQuantity<M, L, T, A>& rhs, double x)
{
    return RQuantity<M, L, T, A>(rhs.getValue() / x);
}


// Comparison operators for quantities:
// ------------------------------------
template <typename M, typename L, typename T, typename A>
constexpr bool operator==(const RQuantity<M, L, T, A>& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return (lhs.getValue() == rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr bool operator!=(const RQuantity<M, L, T, A>& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return (lhs.getValue() != rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr bool operator<=(const RQuantity<M, L, T, A>& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return (lhs.getValue() <= rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr bool operator>=(const RQuantity<M, L, T, A>& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return (lhs.getValue() >= rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr bool operator< (const RQuantity<M, L, T, A>& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return (lhs.getValue()<rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr bool operator> (const RQuantity<M, L, T, A>& lhs, const RQuantity<M, L, T, A>& rhs)
{
    return (lhs.getValue()>rhs.getValue());
}


// Predefined units:
// -----------------

// Predefined mass units:
constexpr QMass kg(1.0);                            // SI base unit
constexpr QMass gramme = 0.001 * kg;
constexpr QMass ounce = 0.028349523125 * kg;
constexpr QMass pound = 16 * ounce;

// Predefined length-derived units
constexpr QLength metre(1.0);                   // SI base unit
constexpr QLength decimetre = metre / 10;
constexpr QLength centimetre = metre / 100;
constexpr QLength millimetre = metre / 1000;
constexpr QLength kilometre = 1000 * metre;
constexpr QLength inch = 2.54 * centimetre;
constexpr QLength foot = 12 * inch;
constexpr QLength mile = 5280 * foot;

constexpr QArea kilometre2 = kilometre*kilometre;
constexpr QArea metre2 = metre*metre;
constexpr QArea decimetre2 = decimetre*decimetre;
constexpr QArea centimetre2 = centimetre*centimetre;
constexpr QArea millimetre2 = millimetre * millimetre;
constexpr QArea inch2 = inch*inch;
constexpr QArea foot2 = foot*foot;

constexpr QVolume kilometre3 = kilometre2*kilometre;
constexpr QVolume metre3 = metre2*metre;
constexpr QVolume decimetre3 = decimetre2*decimetre;
constexpr QVolume litre = decimetre3;
constexpr QVolume centimetre3 = centimetre2*centimetre;
constexpr QVolume inch3 = inch2*inch;

// Predefined time-derived units:
constexpr QTime second(1.0);                        // SI base unit
constexpr QTime minute = 60 * second;
constexpr QTime hour = 60 * minute;

constexpr QFrequency Hz(1.0);
constexpr QFrequency rpm = Hz / 60;

// Predefined mixed units:
constexpr QAcceleration G = 9.80665 *  metre / (second*second);

constexpr QForce newton(1.0);
constexpr QForce poundforce = pound*G;

constexpr QPressure Pascal(1.0);
constexpr QPressure kpa = 1000 * Pascal;
constexpr QPressure bar = 100000 * Pascal;
constexpr QPressure atm = 101.325 * kpa;
constexpr QPressure psi = pound*G / inch2;

// Ideal gas constant
// kg m^2 s^-2 K^-1
constexpr QGasConstant GAS_CONSTANT(8.3144598f);

// Physical unit literals:
// -----------------------

// literals for length units
constexpr QLength operator"" _mm(long double x) { return static_cast<double>(x)*millimetre; }
constexpr QLength operator"" _cm(long double x) { return static_cast<double>(x)*centimetre; }
constexpr QLength operator"" _m(long double x) { return static_cast<double>(x)*metre; }
constexpr QLength operator"" _km(long double x) { return static_cast<double>(x)*kilometre; }
constexpr QLength operator"" _mi(long double x) { return static_cast<double>(x)*mile; }
constexpr QLength operator"" _ft(long double x) { return static_cast<double>(x)*foot; }
constexpr QLength operator"" _in(long double x) { return static_cast<double>(x)*inch; }
constexpr QLength operator"" _mm(unsigned long long int x) { return static_cast<double>(x)*millimetre; }
constexpr QLength operator"" _cm(unsigned long long int  x) { return static_cast<double>(x)*centimetre; }
constexpr QLength operator"" _m(unsigned long long int  x) { return static_cast<double>(x)*metre; }
constexpr QLength operator"" _km(unsigned long long int  x) { return static_cast<double>(x)*kilometre; }
constexpr QLength operator"" _mi(unsigned long long int  x) { return static_cast<double>(x)*mile; }
constexpr QLength operator"" _ft(unsigned long long int  x) { return static_cast<double>(x)*foot; }
constexpr QLength operator"" _in(unsigned long long int  x) { return static_cast<double>(x)*inch; }

// literals for speed units
constexpr QSpeed operator"" _mps(long double x) { return QSpeed(x); };
constexpr QSpeed operator"" _miph(long double x) { return static_cast<double>(x)*mile / hour; };
constexpr QSpeed operator"" _kmph(long double x) { return static_cast<double>(x)*kilometre / hour; };
constexpr QSpeed operator"" _mps(unsigned long long int x) 
                                { return QSpeed(static_cast<long double>(x)); };
constexpr QSpeed operator"" _miph(unsigned long long int x) 
                                 { return static_cast<double>(x)*mile / hour; };
constexpr QSpeed operator"" _kmph(unsigned long long int x) 
                                 { return static_cast<double>(x)*kilometre / hour; };

// literal for frequency unit
constexpr QFrequency operator"" _Hz(long double x) { return QFrequency(x); };
constexpr QFrequency operator"" _Hz(unsigned long long int x) 
                                   { return QFrequency(static_cast<long double>(x)); };
constexpr QFrequency operator"" _Rpm(long double x) { return static_cast<double>(x)*rpm; };
constexpr QFrequency operator"" _Rpm(unsigned long long int x)
                                   { return static_cast<double>(x)*rpm; };

// literals for time units
constexpr QTime operator"" _s(long double x) { return QTime(x); };
constexpr QTime operator"" _min(long double x) { return static_cast<double>(x)*minute; };
constexpr QTime operator"" _h(long double x) { return static_cast<double>(x)*hour; };
constexpr QTime operator"" _s(unsigned long long int x) { return QTime(static_cast<double>(x)); };
constexpr QTime operator"" _min(unsigned long long int x) { return static_cast<double>(x)*minute; };
constexpr QTime operator"" _h(unsigned long long int x) { return static_cast<double>(x)*hour; };

// literals for mass units
constexpr QMass operator"" _kg(long double x) { return QMass(x); };
constexpr QMass operator"" _g(long double x) { return static_cast<double>(x)*gramme; };
constexpr QMass operator"" _lb(long double x) { return static_cast<double>(x)*pound; };
constexpr QMass operator"" _kg(unsigned long long int x) { return QMass(static_cast<double>(x)); };
constexpr QMass operator"" _g(unsigned long long int x) { return static_cast<double>(x)*gramme; };
constexpr QMass operator"" _lb(unsigned long long int x) { return static_cast<double>(x)*pound; };

// literals for acceleration units
constexpr QAcceleration operator"" _mps2(long double x) { return QAcceleration(x); };
constexpr QAcceleration operator"" _mps2(unsigned long long int x) 
                                        { return QAcceleration(static_cast<double>(x)); };
constexpr QAcceleration operator"" _G(long double x) { return static_cast<double>(x)*G; };
constexpr QAcceleration operator"" _G(unsigned long long int x) { return static_cast<double>(x)*G; }

// literals for force units
constexpr QForce operator"" _N(long double x) { return QForce(x); };
constexpr QForce operator"" _N(unsigned long long int x) { return QForce(static_cast<double>(x)); };
constexpr QForce operator"" _lbf(long double x) { return static_cast<double>(x)*poundforce; };
constexpr QForce operator"" _lbf(unsigned long long int x) { return static_cast<double>(x)*poundforce; };

// literals for pressure units
constexpr QPressure operator"" _Pa(long double x) { return QPressure(x); };
constexpr QPressure operator"" _Pa(unsigned long long int x) 
                                  { return QPressure(static_cast<double>(x)); };
constexpr QPressure operator"" _bar(long double x) { return static_cast<double>(x)*bar; };
constexpr QPressure operator"" _bar(unsigned long long int x) { return static_cast<double>(x)*bar; };
constexpr QPressure operator"" _kpa(long double x) { return static_cast<double>(x)*kpa; };
constexpr QPressure operator"" _kpa(unsigned long long int x) { return static_cast<double>(x)*kpa; };
constexpr QPressure operator"" _psi(long double x) { return static_cast<double>(x)*psi; };
constexpr QPressure operator"" _psi(unsigned long long int x) { return static_cast<double>(x)*psi; };
constexpr QPressure operator"" _atm(long double x) { return static_cast<double>(x)*atm; };
constexpr QPressure operator"" _atm(unsigned long long int x) { return static_cast<double>(x)*atm; };

// literals for temperature unit
constexpr QTemperature operator"" _k(long double x) { return QTemperature(x); };
constexpr QTemperature operator"" _k(unsigned long long int x) { return QTemperature(static_cast<double>(x)); };

// Conversion macro, which utilizes the string literals
#define ConvertTo(_x, _y) (_x).Convert(1.0_##_y)