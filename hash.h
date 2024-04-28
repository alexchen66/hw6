#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <list>

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
        HASH_INDEX_T result = 0;
        std::string copy_string = k;
        unsigned long long W[5] = {0, 0, 0, 0, 0};
        unsigned long long value = 0;

        int num_of_w = k.length() / 6;
        int num = num_of_w;
        // std::cout << "num_of_w: " << num_of_w << std::endl;
        int remainder = k.length() % 6;
        int counter = 0;
        while (num_of_w > 0)
        {
            // last 6*n characters 
            
            std::string temp_string = copy_string.substr(copy_string.length() - 6, copy_string.length());
            for (int i = 0; i < temp_string.length(); i++)
            {
                value += pow(36, 5-i) * letterDigitToNumber(temp_string[i]);
            }
            // std::cout << "value: " << value << std::endl;
            // std::cout << "counter: " << counter << std::endl;
            W[4 - counter] = value;
            // std::cout << "W[4]: " << W[4] << std::endl;
            // std::cout << "W[3]: " << W[3] << std::endl;
            // std::cout << "W[2]: " << W[2] << std::endl;
            // std::cout << "W[1]: " << W[1] << std::endl;
            // std::cout << "W[0]: " << W[0] << std::endl;
            copy_string = copy_string.substr(0, copy_string.length() - 6);
            num_of_w--;
            counter++;
            value = 0;
        }
        // now if num_of_w is not a multiple of 6, add those
        value = 0;
        for (int i = 0; i < remainder; i++)
        {
            value += pow(36, remainder - (i + 1)) * letterDigitToNumber(copy_string[i]);
            // std::cout << "value for remainder: " << value << std::endl;
        }
        // std::cout << "W[4]: " << W[4] << std::endl;
        // std::cout << "num_of_w: " << num_of_w << std::endl;
        if (value != 0)
        {
            W[4 - num] = value;
        }
        for (int i = 0; i < 5; i++)
        {
            result += rValues[i] * W[i];
        }
        // for (int i = 0; i < 5; i++)
        // {
        //     std::cout << W[i] << std::endl;
        // }
        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char lowered = (char)tolower(letter);
        if ('a' <= lowered && lowered <= 'z')
        {
            return lowered - 'a';
        }
        else if ('0' <= lowered && lowered <= '9')
        {
            return lowered - '0' + 26;
        }
        else
        {
            return 0;
        }
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
