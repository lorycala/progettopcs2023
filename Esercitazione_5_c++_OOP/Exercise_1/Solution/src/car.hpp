#ifndef __CAR_H
#define __CAR_H

#include <iostream>

using namespace std;

namespace CarLibrary {

  class Car
  {
    private:
      string producer;
      string model;
      string color;

    public:
      Car(const string& producer,
          const string& model,
          const string& color);

      string Show() { return model + " (" + producer + "): color " + color; }

  };


  enum struct CarProducer: char
  {
    UNKNOWN = 'U',
    FORD = 'F',
    TOYOTA = 'T',
    VOLKSWAGEN = 'V'
  };

  class CarFactory
  {
    private:
      static CarProducer producer;

    public:
      static void StartProduction(const CarProducer& producer);
      static Car* Create(const string& color);
  };
}

#endif // __CAR_H
