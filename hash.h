#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long wValues[5] = {0};
        int arrIndex = 4;
        int index = k.size()-1;

        while(index >= 0 && arrIndex >= 0){
          unsigned long long sum = 0;
          unsigned long long power = 1;

          for(int i = 0; i < 6 && index >= 0; i++){
            sum += power*letterDigitToNumber(k[index]);
            index--;
            power*=36;
          }

          wValues[arrIndex--] = sum;
        }

        HASH_INDEX_T output = 0;
        for(int i = 0; i < 5; i++){
          output += rValues[i]*wValues[i];
        }
        return output;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      if(letter >= '0' && letter <= '9'){
        return (letter - '0') + 26;
      } else if (letter >= 'A' && letter <= 'Z'){
        return (letter - 'A');
      } else if (letter >= 'a' && letter <= 'z'){
        return (letter - 'a');
      }
      return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
