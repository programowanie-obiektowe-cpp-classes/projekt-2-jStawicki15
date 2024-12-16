#include "PrintHello.hpp"
#include "Automat.hpp"

void checkAction(std::string action);

int main()
{   
    Automat VM{};
    VM.printAutomat();
    bool vmWorking = true;
    int temp;
    std::string akcja;

    while (vmWorking)
    {
        std::cout<<"Wybierz numer produktu\n";
        std::cin>>akcja;

        //Potrząśnięcie powinno wywali exception może???
        
        if(akcja == "OFF")
        {
            vmWorking = false;
            std::cout<<"Automat zostanie wylaczony\n";
            continue;
        }
        else
        {
            //Tu konwersja może być ciekawa; może być wyjątek wywalany!
            try
            {
                checkAction(akcja);
                temp = std::stoi(akcja);
            }
            catch(const std::invalid_argument& err)
            {
                std::fprintf(stderr,"Invalid arg error: {}",err.what());
                std::cout<<"Podaj wlasciwa instrukcje!!!\n";
                continue;
            }
            catch(const std::runtime_error& err)
            {
                std::fprintf(stderr,"Runtime error: {}",err.what());
                std::cout<<err.what();
                vmWorking = false;
                continue;
            }

            VM.getDrink(temp);
            VM.printAutomat();
        }

    }
    
}

void checkAction(std::string action)
{
    if (action == "SHAKE")
    {
        throw std::runtime_error("!!!WYKYTO WSTRZAS AUTOMATU!!!");
    }
}
