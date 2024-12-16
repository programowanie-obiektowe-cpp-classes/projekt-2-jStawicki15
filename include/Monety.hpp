#include<map>
#include <string>
class Monety
{
    public:
    Monety() = default;

    double getVal(int k)
    {
        switch (k)
        {
            case 0:
                return monety_["1gr"];
                break;
            case 1:
                return monety_["2gr"];
                break;
            case 2:
                return monety_["5gr"];
                break;
            case 3:
                return monety_["10gr"];
                break;
            case 4:
                return monety_["20gr"];
                break;
            case 5:
                return monety_["50gr"];
                break; 
            case 6:
                return monety_["1zl"];
                break;
            case 7:
                return monety_["2zl"];
                break;
            case 8:
                return monety_["5zl"];
                break;
            default:
                return 0;
                break;
        }
    }

    std::map<std::string, const double> monety_{
    {"1gr",0.01},
    {"2gr",0.02},
    {"5gr",0.05},
    {"10gr",0.1},
    {"20gr",0.2},
    {"50gr",0.5},
    {"1zl",1.0},
    {"2zl",2.0},
    {"5zl",5.0}};
};
