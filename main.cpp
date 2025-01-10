#include <iostream>
#include <windows.h>
#include <utility>
#include <vector> // change to set
#include <algorithm>
#include <cmath>
const double TOLERANCE = 1e-6;
// better name the variables

void setPosition(int x, int y){
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //!!!!!!!!!
}

std::pair<int, int> ConsoleSize(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return std::pair<int, int>((info.srWindow.Right - info.srWindow.Left + 1), (info.srWindow.Bottom - info.srWindow.Top + 1));
}

std::vector<double> stabilization_points(double r, int interactions){
    std::vector<double> values;
    double state = 0.5;
    for(int i = 0; i < interactions; i++){
        state = r*state*(1-state);
    }git commit ""
    while(true){ // do it more efficiently 
        double new_state = r*state*(1-state);
        bool found = false;
        for (double x : values){
            if(std::fabs(x - new_state) < TOLERANCE){
                found = true;
                break;
            }
        }
        if(found == true){
            break;
        }
        if (values.size() >= 16){
            break;
        }
        values.push_back(new_state);
        state = new_state;
    }
    return values;
}

int main(){
    
    std::pair<int, int> consolesize = ConsoleSize();
    setPosition((consolesize.first-12)/2, consolesize.second/2);
    std::cout << "Hello " << consolesize.first << " " << consolesize.second;
    for (double i = 0; i <= 3.8; i = i + 0.01){
        std::vector<double> x = stabilization_points(i, 100);
        for (double value : x){
            setPosition(i*37.0, (1-value)*38.0);
            std::cout << ".";
        }
    }


    int x;
    std::cin >> x;
    return 0;
}