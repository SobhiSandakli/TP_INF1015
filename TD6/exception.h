#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
using namespace std;


class ExceptionEntreeValeur: public std::logic_error
{
public:
    using logic_error::logic_error;
};

class ExceptionDescriptionVide : public ExceptionEntreeValeur
{
public:
    using ExceptionEntreeValeur::ExceptionEntreeValeur;
};

class ExceptionPrixNul: public ExceptionEntreeValeur
{
public:
    using ExceptionEntreeValeur::ExceptionEntreeValeur;
};


#endif // EXCEPTION_H
