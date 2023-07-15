#ifndef __TEST_CAR_H
#define __TEST_CAR_H

#include <gtest/gtest.h>

#include "car.hpp"

using namespace testing;


TEST(TestCar, TestShow)
{
  CarLibrary::Car car = CarLibrary::Car("Fiat", "Mustang", "Red");
  EXPECT_EQ(car.Show(), "Mustang (Fiat): color Red");
}

TEST(TestCarFactory, TestCreateFord)
{
  CarLibrary::CarFactory::StartProduction(CarLibrary::CarProducer::FORD);
  CarLibrary::Car* car = CarLibrary::CarFactory::Create("Red");
  EXPECT_TRUE(car != nullptr);
  EXPECT_EQ(car != nullptr ? car->Show() : "", "Mustang (Ford): color Red");
  delete car;
}

TEST(TestCarFactory, TestCreateToyota)
{
  CarLibrary::CarFactory::StartProduction(CarLibrary::CarProducer::TOYOTA);
  CarLibrary::Car* car = CarLibrary::CarFactory::Create("Red");
  EXPECT_TRUE(car != nullptr);
  EXPECT_EQ(car != nullptr ? car->Show() : "", "Prius (Toyota): color Red");
  delete car;
}

TEST(TestCarFactory, TestCreateVolkswagen)
{
  CarLibrary::CarFactory::StartProduction(CarLibrary::CarProducer::VOLKSWAGEN);
  CarLibrary::Car* car = CarLibrary::CarFactory::Create("Red");
  EXPECT_TRUE(car != nullptr);
  EXPECT_EQ(car != nullptr ? car->Show() : "", "Golf (Volkswagen): color Red");
  delete car;
}

#endif // __TEST_CAR_H
