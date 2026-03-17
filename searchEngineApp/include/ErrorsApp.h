#pragma once
#include <stdexcept>
#include <string>

class AppError : public std::runtime_error
{
public: 
    explicit AppError (const std::string& msg) : std::runtime_error(msg) {}
};

class FatallError : public AppError
{
public:
    explicit FatallError (const std::string& msg) : AppError(msg) {}
};

class WarningError : public AppError
{
public:
    explicit WarningError (const std::string& msg) : AppError(msg) {}
};