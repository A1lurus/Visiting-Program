#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>

using namespace std;

const HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);

//________________________Colors__________________________     
enum ConsoleColors
{
    // Text
    black_t = 0, // black
    red_t = FOREGROUND_RED, // red
    green_t = FOREGROUND_GREEN, // green
    blue_t = FOREGROUND_BLUE, // blue
    wblue_t = FOREGROUND_GREEN | FOREGROUND_BLUE, // wblue
    orange_t = FOREGROUND_RED | FOREGROUND_GREEN, // orange
    purple_t = FOREGROUND_RED | FOREGROUND_BLUE, // purple
    gray_t = FOREGROUND_INTENSITY, // gray
    pink_t = FOREGROUND_INTENSITY | FOREGROUND_RED, // pink
    lime_t = FOREGROUND_INTENSITY | FOREGROUND_GREEN, // lime
    aqua_t = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE, // aqua
    yellow_t = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN, // yellow
    wpink_t = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE, // wpink
    white_t = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, // white

    // Backg
    black_b = 0, // black
    red_b = BACKGROUND_RED, // red
    green_b = BACKGROUND_GREEN, // green
    blue_b = BACKGROUND_BLUE, // blue
    wblue_b = BACKGROUND_GREEN | BACKGROUND_BLUE, // wblue
    orange_b = BACKGROUND_RED | BACKGROUND_GREEN, // orange
    purple_b = BACKGROUND_RED | BACKGROUND_BLUE, // purple
    gray_b = BACKGROUND_INTENSITY, // gray
    pink_b = BACKGROUND_INTENSITY | BACKGROUND_RED, // pink
    lime_b = BACKGROUND_INTENSITY | BACKGROUND_GREEN, // lime
    aqua_b = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE, // aqua
    yellow_b = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN, // yellow
    wpink_b = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE, // wpink
    white_b = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE, // white
};

struct account { 
    string name, surname, lang = "Eng", vuvod;
    int skip = 0, them = 0;

    account() = default;

    account(const string& a, const string& b, int c) :
        name(a), surname(b) {
        skip = c;
    }

    //______________________Student creation function____________________________
    void create() {
        string grup;

        ifstream ent("setting\\" + lang + "\\e_g.txt");
        getline(ent, vuvod);
        cout << vuvod;
        cin >> grup;

        ofstream g1(grup + ".txt", ios::app);

        getline(ent, vuvod);
        cout << vuvod;
        cin >> name >> surname;

        // Conclusion about exceeding the limit of the name or surname
        if (name.length() > 15 || surname.length() > 15) {
            ent.close();
            system("cls");
            ifstream lt("setting\\" + lang + "\\lim.txt");
            if (them == 0) {
                SetConsoleTextAttribute(cons, red_t);
                while (getline(lt, vuvod)) {
                    cout << vuvod;
                }
                lt.close();
                SetConsoleTextAttribute(cons, white_t);
            }
            else if (them == 1) {
                SetConsoleTextAttribute(cons, red_t | white_b);
                while (getline(lt, vuvod)) {
                    cout << vuvod;
                }
                lt.close();
                SetConsoleTextAttribute(cons, black_t | white_b);
            }
        }
        else {
            getline(ent, vuvod);
            cout << vuvod;
            cin >> skip;
            ent.close();
            g1 << name << " " << surname << " " << skip * 2 << '\n'; 
            // Conclusion that the student is recorded
            ifstream sw("setting\\" + lang + "\\s_w.txt");
            if (them == 0) {
                SetConsoleTextAttribute(cons, lime_t);
                while (getline(sw, vuvod)) {
                    cout << "\n" << vuvod << grup << ".txt" << '\n';
                }
                SetConsoleTextAttribute(cons, white_t);
            }
            else if (them == 1) {
                SetConsoleTextAttribute(cons, green_t | white_b);
                while (getline(sw, vuvod)) {
                    cout << "\n" << vuvod << grup << ".txt" << '\n';
                }
                SetConsoleTextAttribute(cons, black_t | white_b);
            }
            sw.close();
        }
        cout << "\n";
        g1.close();
        system("pause");
    }

    //____________________Output information about the group___________________________
    void look() {

        string buf, grup;
        int i = 0, sum = 0;

        ifstream ent("setting\\" + lang + "\\e_g.txt");
        getline(ent, vuvod);
        cout << vuvod;
        cin >> grup;
        ent.close();
        system("cls");

        ifstream g2(grup + ".txt");

        // Conclusion that the group was not found
        if (!g2.is_open()) {
            ifstream ero("setting\\" + lang + "\\eror_g.txt");
            if (them == 0){
                ero >> vuvod;
                SetConsoleTextAttribute(cons, red_t);
                cout << vuvod << " " << grup;
                getline(ero, vuvod);
                cout << vuvod << '\n' << '\n';
                SetConsoleTextAttribute(cons, white_t);
            }
            else if (them == 1) {
                ero >> vuvod;
                SetConsoleTextAttribute(cons, red_t | white_b);
                cout << vuvod << " " << grup;
                getline(ero, vuvod);
                cout << vuvod << '\n' << '\n';
                SetConsoleTextAttribute(cons, black_t | white_b);
            }
            ero.close();
            Sleep(3000);
        }
        else {
            // Output of group students in the table
            ifstream lm("setting\\" + lang + "\\l_m.txt");
            getline(lm, vuvod);
            cout << " __________________________________________________\n";
            cout << vuvod;
            cout << "\n|__________________________________________________|";
            lm.close();
            while (!g2.eof()) {
                g2 >> name >> surname >> skip;
                if (name == buf) {
                    break;
                }
                else {
                    cout << '\n' << "|" << left << setw(7) << setfill(' ') << i + 1 << left << setw(16) << setfill(' ') << name << left << setw(16) << setfill(' ') << surname << left << setw(11) << setfill(' ') << skip << "|" << '\n' << setw(51) << "|" << "|";
                    sum += skip;
                    i++;
                }
                buf = name;
            }
            cout << "\n|__________________________________________________|";

            // Output of general group statistics
            ifstream inf("setting\\" + lang + "\\info.txt");
            if (them == 0) {
                SetConsoleTextAttribute(cons, aqua_t);
                getline(inf, vuvod);
                cout << '\n' << '\n' << vuvod << i << '\n';
                getline(inf, vuvod);
                cout << vuvod << sum << '\n';
                getline(inf, vuvod);
                cout << vuvod << sum / i << '\n' << '\n';
                SetConsoleTextAttribute(cons, white_t);
            }
            else if (them == 1) {
                SetConsoleTextAttribute(cons, blue_t | white_b);
                getline(inf, vuvod);
                cout << '\n' << '\n' << vuvod << i << '\n';
                getline(inf, vuvod);
                cout << vuvod << sum << '\n';
                getline(inf, vuvod);
                cout << vuvod << sum / i << '\n' << '\n';
                SetConsoleTextAttribute(cons, black_t | white_b);
            }
            inf.close();
            g2.close();
            system("pause");
        }
    }

    //_____________________________Save to file___________________________________
    void zapol(string& z2, string& b) {

        ifstream bf2("buff.txt");
        ofstream g22(z2 + ".txt");

        while (!bf2.eof()){
            bf2 >> name >> surname >> skip;
            if (b == name) {
                break;
            }
            g22 << name << " " << surname << " " << skip << "\n";
            b = name;
        }
        bf2.close();
        g22.close();
        remove("buff.txt");
        system("cls");

        // Inference that the data is saved
        ifstream d("setting\\" + lang + "\\ok.txt");
        getline(d, vuvod);
        if (them == 0) {
            SetConsoleTextAttribute(cons, lime_t);
            cout << vuvod;
            SetConsoleTextAttribute(cons, white_t);
        }
        else if (them == 1) {
            SetConsoleTextAttribute(cons, green_t | white_b);
            cout << vuvod;
            SetConsoleTextAttribute(cons, black_t | white_b);
        }
        d.close();
        Sleep(3000);
    }

    //______________________________Delete_____________________________________
    void delet(string& x, string& y, string& z) {

        string buff;
        ifstream g4(z + ".txt");

        while (getline(g4, y)) {
            if (y.find(x) != string::npos) {
                y.clear();
                buff += y;
            }
            else {
                buff += y + '\n';
            }
        }
        g4.close();

        ofstream g5(z + ".txt");

        g5 << buff;
        remove("buff.txt");
        g5.close();
    }

    //________________________________Change_______________________________________
    void swap(string& x, string& z) {

        int vubir, povtor = 0;
        string buff;

        ofstream bf("buff.txt");
        ifstream g6(z + ".txt");
        ifstream n("setting\\" + lang + "\\new.txt");

            ifstream m_s("setting\\" + lang + "\\menu_swap.txt");
            while (getline(m_s, vuvod)) {
                cout << vuvod << '\n';
            }
            m_s.close();
            vubir = _getch();
            switch (vubir) {
            case 49:
                getline(n, vuvod);
                n.close();
                system("cls");
                while (!g6.eof()) {
                    g6 >> name >> surname >> skip;
                    if (name == buff) {
                        break;
                    }
                    else if (povtor == 1) {}
                    else if (name.find(x) != string::npos) {
                        cout << vuvod;
                        cin >> name;
                        povtor++;
                    }
                    bf << name << " " << surname << " " << skip << "\n";
                    buff = name;
                }
                bf.close();
                g6.close();
                zapol(z, buff);
                system("cls");
                break;

            case 50:
                getline(n, vuvod);
                getline(n, vuvod);
                n.close();
                system("cls");
                while (!g6.eof()) {
                    g6 >> name >> surname >> skip;
                    if (name == buff) {
                        break;
                    }
                    else if (povtor == 1) {}
                    else if (name.find(x) != string::npos) {
                        cout << vuvod;
                        cin >> surname;
                        povtor++;
                    }
                    bf << name << " " << surname << " " << skip << "\n";
                    buff = name;
                }
                bf.close();
                g6.close();
                zapol(z, buff);
                system("cls");
                break;

            case 51:
                getline(n, vuvod);
                getline(n, vuvod);
                getline(n, vuvod);
                n.close();
                system("cls");
                while (!g6.eof()) {
                    g6 >> name >> surname >> skip;
                    if (name == buff) {
                        break;
                    }
                    else if (povtor == 1) {}
                    else if (name.find(x) != string::npos) {
                        cout << vuvod;
                        cin >> skip;
                        skip *= 2;
                        povtor++;
                    }
                    bf << name << " " << surname << " " << skip << "\n";
                    buff = name;
                }
                bf.close();
                g6.close();
                zapol(z, buff);
                system("cls");
                break;

            case 27:
                system("cls");
                break;
            }
    }

    //____________________________Search for a student__________________________________
    void poisk() {

        string stud, buf, grup;

        ifstream ent("setting\\" + lang + "\\e_g.txt");
        getline(ent, vuvod);
        cout << vuvod;
        cin >> grup;
        ent.close();

        ifstream g3(grup + ".txt");

        // Conclusion that the group was not found
        if (!g3.is_open()) {
            system("cls");

            ifstream ero("setting\\" + lang + "\\eror_g.txt");
            if (them == 0) {
                ero >> vuvod;
                SetConsoleTextAttribute(cons, red_t);
                cout << vuvod << " " << grup;
                getline(ero, vuvod);
                cout << vuvod << '\n' << '\n';
                SetConsoleTextAttribute(cons, white_t);
            }
            else if (them == 1) {
                ero >> vuvod;
                SetConsoleTextAttribute(cons, red_t | white_b);
                cout << vuvod << " " << grup;
                getline(ero, vuvod);
                cout << vuvod << '\n' << '\n';
                SetConsoleTextAttribute(cons, black_t | white_b);
            }
            ero.close();
            Sleep(3000);
        }
        else {
            int snet = 0;
            ifstream es("setting\\" + lang + "\\e_ns.txt");
            getline(es, vuvod);
            cout << vuvod;
            cin >> stud;
            es.close();

            while (getline(g3, buf)) {
                if (buf.find(stud) != string::npos) {
                    int funk;
                    snet = 1;
                    do {
                        system("cls");

                        cout << '\n';
                        ifstream m_p("setting\\" + lang + "\\m_poisk.txt");
                        getline(m_p, vuvod);
                        // Withdrawal of the student
                        if (them == 0) {
                            SetConsoleTextAttribute(cons, aqua_t);
                            cout << vuvod << buf << '\n';
                            SetConsoleTextAttribute(cons, white_t);
                        }
                        else if (them == 1) {
                            SetConsoleTextAttribute(cons, blue_t | white_b);
                            cout << vuvod << buf << '\n';
                            SetConsoleTextAttribute(cons, black_t | white_b);
                        }
                        while (getline(m_p, vuvod)) {
                            cout << vuvod << '\n';
                        }
                        m_p.close();
                        funk = _getch();

                        ifstream sd("setting\\" + lang + "\\ok.txt");
                        switch (funk) {
                        case 49:
                            system("cls");
                            delet(stud, buf, grup);

                            getline(sd, vuvod);
                            getline(sd, vuvod);
                            // Conclusion that the student has been deleted
                            if (them == 0) {
                                SetConsoleTextAttribute(cons, lime_t);
                                cout << vuvod;
                                SetConsoleTextAttribute(cons, white_t);
                            }
                            else if (them == 1) {
                                SetConsoleTextAttribute(cons, green_t | white_b);
                                cout << vuvod;
                                SetConsoleTextAttribute(cons, black_t | white_b);
                            }
                            Sleep(3000);
                            funk = 27;
                            break;

                        case 50:
                            system("cls");
                            swap(stud, grup);
                            system("cls");
                            funk = 27;
                            break;

                        case 27:
                            return;

                        default:
                            cout << "\a";
                            system("cls");
                        }

                    } while (funk != 27);
                }
            }
            system("cls");
            if (snet == 0) {
                ifstream ers("setting\\" + lang + "\\eror_s.txt");
                getline(ers, vuvod);
                // Conclusion that the student was not found
                if (them == 0) {
                    SetConsoleTextAttribute(cons, red_t);
                    cout << vuvod;
                    SetConsoleTextAttribute(cons, white_t);
                }
                else if (them == 1) {
                    SetConsoleTextAttribute(cons, red_t | white_b);
                    cout << vuvod;
                    SetConsoleTextAttribute(cons, black_t | white_b);
                }
                ers.close();
                g3.close();
                Sleep(3000);
                system("cls");
            }
        }
    }

    //__________________________Preservation of language___________________________________
    void savel(int ac) {
        ofstream leng("setting\\Lang.txt");
        switch (ac) {
        case 1:
            lang = "Eng";
            leng << lang;
            leng.close();
            break;

        case 2:
            lang = "Ukr";
            leng << lang;
            leng.close();
            break;

        case 3:
            lang = "Rus";
            leng << lang;
            leng.close();
            break;
        }
    }

    //________________________________Language________________________________________
    void language() {

        int ch;

        do {
            ifstream ml("setting\\" + lang + "\\m_lang.txt");
            
            while (getline(ml, vuvod)) {
                cout << vuvod << '\n';
            }
            ch = _getch();

            switch (ch) {
            case 49:
                system("cls");
                savel(1);
                // Conclusion that English
                if (them == 0) {
                    SetConsoleTextAttribute(cons, lime_t);
                    cout << "English is successfully installed";
                    SetConsoleTextAttribute(cons, white_t);
                }
                else if (them == 1) {
                    SetConsoleTextAttribute(cons, green_t | white_b);
                    cout << "English is successfully installed";
                    SetConsoleTextAttribute(cons, black_t | white_b);
                }
                Sleep(3000);
                system("cls");
                break;

            case 50:
                system("cls");
                savel(2);
                // Conclusion that Ukr
                if (them == 0) {
                    SetConsoleTextAttribute(cons, lime_t);
                    cout << "Українську мову успішно встановлено";
                    SetConsoleTextAttribute(cons, white_t);
                }
                else if (them == 1) {
                    SetConsoleTextAttribute(cons, green_t | white_b);
                    cout << "Українську мову успішно встановлено";
                    SetConsoleTextAttribute(cons, black_t | white_b);
                }
                Sleep(3000);
                system("cls");
                break;

            case 51:
                system("cls");
                savel(3);
                // Conclusion that Rus
                if (them == 0) {
                    SetConsoleTextAttribute(cons, lime_t);
                    cout << "Русский язык успешно установлено";
                    SetConsoleTextAttribute(cons, white_t);
                }
                else if (them == 1) {
                    SetConsoleTextAttribute(cons, green_t | white_b);
                    cout << "Русский язык успешно установлено";
                    SetConsoleTextAttribute(cons, black_t | white_b);
                }
                Sleep(3000);
                system("cls");
                break;

            case 27:
                system("cls");
                break;

            default:
                system("cls");
                cout << "\a";
            }
        } while (ch != 27);

    }

    //________________________________Topic________________________________________
    void thema() {

        int ch;

        ofstream thm("setting\\Thema.txt");

        do {
            ifstream mth("setting\\" + lang + "\\menu_them.txt");
            while (getline(mth, vuvod)) {
                cout << vuvod << '\n';
            }
            ch = _getch();
            mth.close();

            switch (ch) {
            case 49:
                system("cls");
                them = 0;
                thm << them;
                SetConsoleTextAttribute(cons, white_t | black_b);
                system("cls");
                break;

            case 50:
                system("cls");
                them = 1;
                thm << them;
                SetConsoleTextAttribute(cons, black_t | white_b);
                system("cls");
                break;
            case 27:
                system("cls");
                break;

            default:
                system("cls");
                cout << "\a";
            }

        } while (ch != 27);
    }

    //_____________________________Settings___________________________________
    void set() {

        int ch;

        do {
            ifstream ms("setting\\" + lang + "\\m_set.txt");
            while (getline(ms, vuvod)) {
                cout << vuvod << '\n';
            }
            ch = _getch();
            ms.close();

            switch (ch) {
            case 49:
                system("cls");
                language();
                break;

            case 50:
                system("cls");
                thema();
                break;

            case 27:
                system("cls");
                break;

            default:
                system("cls");
                cout << "\a";
            }

        } while (ch != 27);
    }

    //_____________________Saving to file is sorted_________________________
    void write_group(const string& group, const int& type, int& p) {

        string a, b, povt;
        int c;
        vector<account> dat;
        ifstream in(group + ".txt");

        while (!in.eof()) {
            in >> a >> b >> c;

            if (povt == a) {
                break;
            }

            dat.push_back(account(a, b, c));

            povt = a;
        }

        in.close();

        switch (type){
        case 1:
            if (p == 49) {
                std::sort(dat.begin(), dat.end(), [](const account& a1, const account& b1) {
                    return a1.name < b1.name;
                    });
            }
            else if (p == 50) {
                std::sort(dat.begin(), dat.end(), [](const account& a1, const account& b1) {
                    return a1.name > b1.name;
                    });
            }
            break;

        case 2:
            if (p == 49) {
                std::sort(dat.begin(), dat.end(), [](const account& a1, const account& b1) {
                    return a1.surname < b1.surname;
                    });
            }
            else if (p == 50) {
                std::sort(dat.begin(), dat.end(), [](const account& a1, const account& b1) {
                    return a1.surname > b1.surname;
                    });
            }
            break;

        case 3:
            if (p == 49) {
                std::sort(dat.begin(), dat.end(), [](const account& a1, const account& b1) {
                    return a1.skip < b1.skip;
                    });
            }
            else if (p == 50) {
                std::sort(dat.begin(), dat.end(), [](const account& a1, const account& b1) {
                    return a1.skip > b1.skip;
                    });
            }
            break;
        }

        ofstream out(group + ".txt");

        for (auto elem : dat)
            out << elem.name << ' ' << elem.surname << ' ' << elem.skip << '\n';

        out.close();
    }

    //____________________________Sort menu_________________________________
    void sort() {

        int ch, por;
        string grup;

        ifstream ent("setting\\" + lang + "\\e_g.txt");
        getline(ent, vuvod);
        cout << vuvod;
        cin >> grup;
        ent.close();
        system("cls");

        ifstream g25(grup + ".txt");

        // Conclusion that the group was not found
        if (!g25.is_open()) {
            system("cls");

            ifstream ero("setting\\" + lang + "\\eror_g.txt");
            if (them == 0) {
                ero >> vuvod;
                SetConsoleTextAttribute(cons, red_t);
                cout << vuvod << " " << grup;
                getline(ero, vuvod);
                cout << vuvod << '\n' << '\n';
                SetConsoleTextAttribute(cons, white_t);
            }
            else if (them == 1) {
                ero >> vuvod;
                SetConsoleTextAttribute(cons, red_t | white_b);
                cout << vuvod << " " << grup;
                getline(ero, vuvod);
                cout << vuvod << '\n' << '\n';
                SetConsoleTextAttribute(cons, black_t | white_b);
            }
            Sleep(3000);
        }
        else {

            do {
                ifstream msort("setting\\" + lang + "\\m_sort.txt");
                for (int i = 0; i <= 12; i++) {
                    getline(msort, vuvod);
                    cout << vuvod << '\n';
                }
                ch = _getch();

                system("cls");

                if (ch != 27) {
                    while (getline(msort, vuvod)) {
                        cout << vuvod << '\n';
                    }
                    por = _getch();
                }
                msort.close();

                switch (ch) {
                case 49:
                    system("cls");
                    write_group(grup, 1, por);
                    break;

                case 50:
                    system("cls");
                    write_group(grup, 2, por);
                    break;

                case 51:
                    system("cls");
                    write_group(grup, 3, por);
                    break;

                case 27:
                    system("cls");
                    break;

                default:
                    system("cls");
                    cout << "\a";
                    break;
                }

            } while (ch != 27);

        }

    }
};

//_________________________________Main menu___________________________________
int main(){
    
    system("chcp 1251");
    account ac;
    int ch;

    // Getting information about the languageі
    ifstream lan("setting\\Lang.txt");
    lan >> ac.lang;
    lan.close();

    // Getting information about the topic
    ifstream thema("setting\\Thema.txt");
    thema >> ac.them;
    thema.close();
    if (ac.them == 0) {
        SetConsoleTextAttribute(cons, white_t | black_b);
    }
    else if (ac.them == 1) {
        SetConsoleTextAttribute(cons, black_t | white_b);
    }

    system("cls");

    do {

        ifstream mainm("setting\\"+ ac.lang +"\\main_m.txt");
        while (getline(mainm, ac.vuvod)) {
            cout << ac.vuvod << '\n';
        }
        mainm.close();
        ch = _getch();

        switch (ch) {
        case 49:
            system("cls");
            ac.create();
            system("cls");
            break;

        case 50:
            system("cls");
            ac.look();
            system("cls");
            break;

        case 51:
            system("cls");
            ac.poisk();
            system("cls");
            break;

        case 52:
            system("cls");
            ac.sort();
            system("cls");
            break;

        case 53:
            system("cls");
            ac.set();
            system("cls");
            break;

        case 27:
            system("cls");
            exit(0);
            break;

        default:
            cout << "\a";
            system("cls");
        }

    } while (ch != 27);
}