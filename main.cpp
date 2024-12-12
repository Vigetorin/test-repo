﻿#include <vector>
#include <functional>
#include <iostream>

#include "candle.h"

//массив всех тестов, который мы заполняем в функции initTests
static std::vector<std::function<bool()>> tests;

// тесты для body_contains

// проверка обычной свечи (с тенями и непустым телом)
bool bodyContainsDefaultTest()
{
    Candle candleGreen(0.0, 5.0, -1.0, 3.0);
    Candle candleRed(3.0, 5.0, -1.0, 0.0);
    for (const Candle& candle : { candleGreen, candleRed })
    {
        // значение внутри тела
        if (!candle.body_contains(1.2))
            return false;
        // значения по краям тела
        if (!candle.body_contains(0.0) || !candle.body_contains(3.0))
            return false;
        // значения внутри теней
        if (candle.body_contains(-0.5) || candle.body_contains(5.0))
            return false;
        // значения вне свечи
        if (candle.body_contains(-1.7) || candle.body_contains(7.6))
            return false;
    }
    return true;
}

// проверка свечи с пустым телом
bool bodyContainsZeroBodyTest()
{
    Candle candle(1.0, 5.0, -1.0, 1.0);
    // проверка единственного значения внутри тела
    if (!candle.body_contains(1.0))
        return false;
    // проверка значений вне тела
    if (candle.body_contains(0.2) || candle.body_contains(7.3))
        return false;
    // пустая свеча без теней
    Candle candleEmpty(1.0, 1.0, 1.0, 1.0);
    // значение внутри свечи
    if (!candleEmpty.body_contains(1.0))
        return false;
    // внешние значения
    if (candleEmpty.body_contains(0.8) || candleEmpty.body_contains(1.7))
        return false;
    return true;
}

// проверка свечи без теней
bool bodyContainsNoShadowsTest()
{
    Candle candleGreen(0.0, 3.0, 0.0, 3.0);
    Candle candleRed(3.0, 3.0, 0.0, 0.0);
    for (const Candle& candle : { candleGreen, candleRed })
    {
        // значение внутри свечи
        if (!candle.body_contains(1.2))
            return false;
        // значения по краям свечи
        if (!candle.body_contains(0.0) || !candle.body_contains(3.0))
            return false;
        // значения вне свечи
        if (candle.body_contains(-1.7) || candle.body_contains(7.6))
            return false;
    }
    return true;
}

// тесты для contains

// проверка обычной свечи
bool containsDefaultTest()
{
    Candle candleGreen(0.0, 5.0, -1.0, 3.0);
    Candle candleRed(3.0, 5.0, -1.0, 0.0);
    for (const Candle& candle : { candleGreen, candleRed })
    {
        // значение внутри тела
        if (!candle.contains(1.2))
            return false;
        // значения внутри теней
        if (!candle.contains(-0.5) || !candle.contains(3.9))
            return false;
        // значения по краям теней
        if (!candle.contains(-1.0) || !candle.contains(5.0))
            return false;
        // значения вне свечи
        if (candle.contains(-1.7) || candle.contains(7.6))
            return false;
    }
    return true;
}

// проверка свечи с пустым телом
bool containsZeroBodyTest()
{
    Candle candle(1.0, 5.0, -1.0, 1.0);
    // проверка единственного значения внутри тела
    if (!candle.contains(1.0))
        return false;
    // проверка значений вне тела, но внутри свечи
    if (!candle.contains(0.2) || !candle.contains(5.0))
        return false;
    // значения вне свечи
    if (candle.contains(-1.7) || candle.contains(7.6))
        return false;
    // пустая свеча без теней
    Candle candleEmpty(1.0, 1.0, 1.0, 1.0);
    // значение внутри свечи
    if (!candleEmpty.contains(1.0))
        return false;
    // внешние значения
    if (candleEmpty.contains(0.8) || candleEmpty.contains(1.7))
        return false;
    return true;
}

// проверка свечи без теней
bool containsNoShadowsTest()
{
    Candle candleGreen(0.0, 3.0, 0.0, 3.0);
    Candle candleRed(3.0, 3.0, 0.0, 0.0);
    for (const Candle& candle : { candleGreen, candleRed })
    {
        // значение внутри свечи
        if (!candle.contains(1.2))
            return false;
        // значения по краям свечи
        if (!candle.contains(0.0) || !candle.contains(3.0))
            return false;
        // значения вне свечи
        if (candle.contains(-1.7) || candle.contains(7.6))
            return false;
    }
    return true;
}

void initTests()
{
    tests.push_back(bodyContainsDefaultTest);
    tests.push_back(bodyContainsZeroBodyTest);
    tests.push_back(bodyContainsNoShadowsTest);
    tests.push_back(containsDefaultTest);
    tests.push_back(containsZeroBodyTest);
    tests.push_back(containsNoShadowsTest);
}

int launchTests()
{
    int total = 0;
    int passed = 0;

    for (const auto& test : tests)
    {
        std::cout << "test #" << (total + 1);
        if (test())
        {
            passed += 1;
            std::cout << " passed\n";
        }
        else
        {
            std::cout << " failed\n";
        }
        total += 1;
    }

    std::cout << "\ntests " << passed << "/" << total << " passed!" << std::endl;

    //0 = success
    return total - passed;
}

int main()
{
    initTests();
    return launchTests();
}
