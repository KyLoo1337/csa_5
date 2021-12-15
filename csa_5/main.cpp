/*
 * Задача о гостинице-2 (умные клиенты). В гостинице 10 номеров с
 * ценой 200 рублей, 10 номеров с ценой 400 рублей и 5 номеров с ценой 600
 * руб. Клиент, зашедший в гостиницу, обладает некоторой суммой и получает
 * номер по своим финансовым возможностям, если тот свободен. Если среди
 * доступных клиенту номеров нет свободных, клиент уходит искать ночлег в
 * другое место. Создать многопоточное приложение, моделирующее работу
 * гостиницы
*/

/*
 * cинхропримитив: управляющий и рабочие.
 */
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

void errMessage() {
    cout << "incorrect qualifier value!\n"
            "  Waited:\n"
            "     command infile outfile\n";
}

int rooms200 = 0;
int rooms400 = 0;
int rooms600 = 0;
bool end1 = false;

void Hostess() {
    while(!end1) {
        if (rooms200 > 10)
            rooms200 = 10;
        if (rooms400 > 10)
            rooms400 = 10;
        if (rooms600 > 5)
            rooms600 = 5;
    }
}

void RentRoom(int money) {
    if(money < 200) {
        return;
    }
    else if (money < 400) {
        if (rooms200 < 10)
            rooms200++;
    }
    else if (money < 600) {
        if(rooms400 < 10)
            rooms400++;
    }
    else {
        if(rooms600 < 5)
            rooms600++;
    }
}

int main(int args, char* argv[]) {
    ifstream inf(argv[1]);
    ofstream otf;
    otf.open (argv[2]);
    if (!inf || !otf)
    {
        errMessage();
        exit(1);
    }
    thread hostess(Hostess);
    hostess.detach();
    while(inf) {
        if(rooms600 == 5 && rooms400 == 10 && rooms200 == 10){
            otf << "Hostel is full" << endl;
            otf << "Rooms:"
                   "Price 200: " << rooms200 << endl
                << "Price 400: " << rooms400 << endl
                << "Price 600: " << rooms600 << endl;
            end1 = true;
            exit(0);
        }
        int a;
        inf >> a;
        thread(RentRoom, a).join();
    }
    end1 = true;
    otf << "Rooms:"
           "Price 200: " << rooms200 << endl
        << "Price 400: " << rooms400 << endl
        << "Price 600: " << rooms600 << endl;
    otf.close();
    inf.close();
    return 0;
}