#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <cstring>
#include <utility>
#include <vector>
#include <stdbool.h>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <numeric>
#include <windows.h>
#include <cctype>
#include <queue>
#include <algorithm>
#include <fstream>
#include<sstream>
#include <bitset>
#include <stack>
#include <locale>
#include <codecvt>
#define FOR(i, n) for (int i = 0; i < n; i++)
#define ll long long
inline ll gcd(ll a, ll b){ll r;while (b){r = a % b;a = b;b = r;}return a;}
inline ll lcm(ll a, ll b) { return (a*b) / gcd(a, b) ; }

using namespace std;

class Subject { //S.Lâm
private:
    int class_code;
    string class_course, name, Module, note, weekday, time, week, classroom, type;
public:
    Subject(int x);
    void print_schedule();
    void print_Module();
    void print_choice();
    void print_exam();
    void search_by_name();
};
Subject::Subject(int user_code) { //G.Phong 
    class_code = user_code;
    ifstream class_file;
    int code;
    string temp_line;
    class_file.open("TKB.txt");
    if (!class_file.is_open()) {
        cout << "Không thể mở tệp TKB.txt!" << endl;
    }
    while (class_file >> code)
    {
        class_file.ignore(); // bỏ dấu ; sau mã lớp
        getline(class_file, temp_line);
        if(code == class_code) {
            break;
        }
    }
    stringstream line(temp_line);
    vector<string> fields;
    string temp;
    while (getline(line, temp, ';')) {
        fields.push_back(temp);
    }
    if (fields.size() >= 9) {
        class_course = fields[0];
        name = fields[1];
        Module = fields[2];
        note = fields[3];
        weekday = fields[4];
        time = fields[5];
        week = fields[6];
        classroom = fields[7];
        type = fields[8];
    } else {
        cout << "Dữ liệu không đầy đủ trong dòng " << temp_line << endl;
    }

    class_file.close();
}
/*Subjec(int user code) gốc :( // S.Lâm )
Subject::Subject(int user_code) {
    class_code = user_code;
    ifstream class_file;
    int code;
    string temp_line;
    char comma;

    class_file.open("TKB.txt");
    if (!class_file.is_open()) {
        cout << "Không thể mở tệp TKB.txt!" << endl;
    }
    while (class_file >> code)
    {
        class_file >> comma;
        getline(class_file, temp_line);
        if(code == class_code) {
            break;
        }
    }

    stringstream line(temp_line);
    getline(line, class_course, ';');
    getline(line, name, ';');
    getline(line, module, ';');
    getline(line, note, ';');
    getline(line, weekday, ';');
    getline(line, time, ';');
    getline(line, week, ';');
    getline(line, classroom, ';');
    getline(line, type, ';');

    class_file.close();
}
*/
void Subject::print_Module() { // ( S.Lâm )
    stringstream khoi_luong(Module);
    
    vector<int> each_num;
    int num; char sign;
    while(khoi_luong >> num >> sign) {
        each_num.push_back(num);
    }
    cout << each_num[0] << " tin chi, " << each_num[1] << " gio ly thuyet, " << each_num[2] << " gio bai tap, " << each_num[3] << " gio thi nghiem, " << each_num[4] << " gio tu hoc " << endl;    
}
void Subject::print_exam() { // ( G.Phong )
    ifstream class_file;
    int code;
    string temp_line;
    class_file.open("Exam_schedule.txt");

    if (!class_file.is_open()) {
        cout << "Không thể mở tệp Exam_schedule.txt" << endl;
        return;
    }
    bool found = false;
    while (class_file >> code) {
        getline(class_file, temp_line);
        if (code == class_code) {
            found = true;
            stringstream line(temp_line);
            vector<string> exam_info;
            string value;
            while (getline(line, value, ';')) {
                exam_info.push_back(value);
            }
            cout << "Thứ: " << exam_info[1]<< endl
                 << "Ngày thi: " << exam_info[2] << "/1/2025" << endl
                 << "Kíp thi (kíp 1 : 7h00 ; kíp 2 : 9h30 ; kíp 3 : 12h30 ; kíp 4 : 15h00): " << exam_info[3] << endl
                 << "Phòng thi: " << exam_info[4] << endl
                 << "Mã lớp thi: " << exam_info[5] << endl;
            break;
        }
    }

    if (!found) {
        cout << "Không tồn tại lịch thi cho mã lớp " << class_code << endl;
    }

    class_file.close();
}
void Subject::print_schedule() {
    cout << time << " thu :" << weekday << endl;
}
/* Subject::print_exam gốc : // ( S.Lâm )

void Subject::print_exam() {
    ifstream class_file;
    int code;
    string temp_line;
    class_file.open("Exam_schedule.txt");
    if (!class_file.is_open()) {
        cout << "Không thể mở tệp Exam_schedule.txt" << endl;
        return;
    }

    bool found = false; 
    while (class_file >> code) {
        getline(class_file, temp_line);
        if (code == class_code) {
            found = true; 
            stringstream line(temp_line);
            string comma, weekday, date_exam, kip_thi, room, part_code;
            getline(line, comma, ';');
            getline(line, weekday, ';');
            getline(line, date_exam, ';');
            getline(line, kip_thi, ';');
            getline(line, room, ';');
            getline(line, part_code, ';');
            cout << "Thứ: " << weekday << endl
                 << "Ngày thi: " << date_exam << "/1/2025" << endl
                 << "Kíp thi ( kíp 1 : 7h00 ; kíp 2 : 9h30 ; kíp 3 : 12h30 ; kíp 4 : 15h00): " << kip_thi << endl
                 << "Phòng thi: " << room << endl
                 << "Mã lớp thi: " << part_code << endl;
            break;
        }
    }
    if (!found) { 
        cout << "Không tồn tại lịch thi cho mã lớp " << class_code << endl;
    }

    class_file.close();
}
*/

bool Valid1(string input) { // ( G.Phong )
    if (input == "0") return true;
    
    if (!all_of(input.begin(), input.end(), ::isdigit) || input.length() != 6) {
        cout << "Ma lop khong hop le" << endl;
        return false;
    }
    return true;
}
bool ValidClassCode(string input) { // ( G.Phong )
    if (!all_of(input.begin(), input.end(), ::isdigit) || input.length() != 6) {
        cout << "Ma lop khong hop le" << endl;
        return false;
    }
    return true;
}
void searchAndProcessSubject() { // ( G.Phong )
    Subject tempUser(0);
    tempUser.search_by_name();
    cout << "Nhap ma lop ban muon tra: ";
    string newinput;
    cin >> newinput;
    if (!ValidClassCode(newinput)) {
        return;
    }
    int new_code = stoi(newinput);
    Subject user(new_code);
    user.print_choice();
}
void Subject::print_choice() { // S.Lâm ( G.Phong  fix )
    cout << "\n-----------MENU------------- " << endl 
         << "Tra cuu ma hoc phan - an phim 1" << endl 
         << "Tra cuu ten hoc phan - an phim 2" << endl 
         << "Tra cuu khoi luong tin chi - an phim 3" << endl
         << "Tra cuu cac lop hoc - an phim 4" << endl
         << "Tra cuu thoi gian hoc - an phim 5" << endl
         << "Tra cuu tuan hoc - an phim 6" << endl
         << "Tra cuu phong hoc - an phim 7" << endl
         << "Tra cuu loai lop - an phim 8" << endl
         << "Tra cuu lich thi - an phim 9" << endl
         << "Nhap ma lop moi - an phim 0" << endl
         << "Thoat chuong trinh - an phim x" << endl
         << "------------------------------" << endl;

    bool check = 1;
    while(check == 1) {
        char choice;
        cin >> choice;
        if(choice == 'x' || choice == 'X') {
            return; 
        }
        if (choice == '0') {
            cout << "Nhap ma lop hoc (neu khong nho ma lop nhan phim 0): ";
            string new_input;
            cin >> new_input;
            if (new_input == "0") {
                searchAndProcessSubject();
                return; 
            }
            if (ValidClassCode(new_input)) {
                int new_code = stoi(new_input);
                Subject user(new_code);
                user.print_choice(); 
                return; 
            } else {
                return;
            }
        }
        switch (choice) {
            case '1': cout << "Mã học phần : " << class_course << endl; break;

            case '2': cout << "Tên học phần : " << name << endl; break;

            case '3': cout << "Khối lượng học phần :"; print_Module(); break;

            case '4':cout <<"Thông tin về lớp học: " << note << endl; break;

            case '5':cout << "Thời gian học :"; print_schedule(); break;

            case '6':cout <<"Tuần học : " << week << endl; break;

            case '7':cout << "Phòng học : "<< classroom << endl; break;

            case '8':cout <<"Loại lóp học  : " << type << endl; break;

            case '9':cout << "Lịch thi : ";print_exam(); break;

            default: cout << "Lựa  chọn không hợp lệ!" << endl; break;
        }
    }
}

string remove_accents(string input) { // phần bỏ dấu nhờ Copilot làm
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring wide = converter.from_bytes(input);
    wstring result;

    for (wchar_t wc : wide) {
        switch (wc) {
            case L'à': case L'á': case L'ả': case L'ã': case L'ạ':
            case L'â': case L'ầ': case L'ấ': case L'ẩ': case L'ẫ': case L'ậ':
            case L'ă': case L'ằ': case L'ắ': case L'ẳ': case L'ẵ': case L'ặ':
                result += L'a'; break;
            case L'è': case L'é': case L'ẻ': case L'ẽ': case L'ẹ':
            case L'ê': case L'ề': case L'ế': case L'ể': case L'ễ': case L'ệ':
                result += L'e'; break;
            case L'ì': case L'í': case L'ỉ': case L'ĩ': case L'ị':
                result += L'i'; break;
            case L'ò': case L'ó': case L'ỏ': case L'õ': case L'ọ':
            case L'ô': case L'ồ': case L'ố': case L'ổ': case L'ỗ': case L'ộ':
            case L'ơ': case L'ờ': case L'ớ': case L'ở': case L'ỡ': case L'ợ':
                result += L'o'; break;
            case L'ù': case L'ú': case L'ủ': case L'ũ': case L'ụ':
            case L'ư': case L'ừ': case L'ứ': case L'ử': case L'ữ': case L'ự':
                result += L'u'; break;
            case L'ỳ': case L'ý': case L'ỷ': case L'ỹ': case L'ỵ':
                result += L'y'; break;
            case L'đ':
                result += L'd'; break;
            default:
                result += wc;
        }
    }

    return converter.to_bytes(result);
}
void Subject::search_by_name() { // ( G.Phong ) ( AI fix)
    cout << "Nhap ten hoc phan: ";
    string name_part;
    cin.ignore();
    getline(cin, name_part);
    transform(name_part.begin(), name_part.end(), name_part.begin(), ::tolower);
    string newname = remove_accents(name_part);
    stringstream ss(newname);
    vector<string> search_terms;
    string term;
    while (ss >> term) {
        search_terms.push_back(term);
    }
    vector<int> matched_codes;
    ifstream class_file("TKB.txt");
    int code;
    string temp_line;
    char comma;

    while (class_file >> code) {
        class_file >> comma;
        getline(class_file, temp_line);
        stringstream line(temp_line);
        string class_course, name;
        getline(line, class_course, ';');
        getline(line, name, ';');
        string rmaccent_name = remove_accents(name);
        transform(rmaccent_name.begin(), rmaccent_name.end(), rmaccent_name.begin(), ::tolower);
        bool all_terms_found = true;
        for (auto term : search_terms) {
            if (rmaccent_name.find(term) == string::npos) {
                all_terms_found = false;
                break;
            }
        }
        if (all_terms_found) {
            matched_codes.push_back(code);
            cout << code << "  " << name << endl;
        }

    }
    class_file.close();

    if (matched_codes.empty()) {
        cout << "Khong tim thay hoc phan nao." << endl;
        return;
    }
}
int main() {  // S.Lâm ( G.Phong  fix )
    SetConsoleOutputCP(65001);
    cout << "Nhap ma lop hoc (neu khong nho ma lop nhan phim 0): " << endl;
    string input;
    cin >> input;
    if (!Valid1(input)) {
        return 0;
    }
    int user_code = stoi(input);
    if (user_code == 0) {
        searchAndProcessSubject();
    } 
    else {
        Subject user(user_code);
        user.print_choice();
    }
    return 0;
}