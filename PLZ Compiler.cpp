#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct City
{
    string name;
    string additional;
    struct City* next = nullptr;
};

ostream& operator<<(ostream& out, City* x)
{
    City* temp = x;
    while (temp != nullptr)
    {
        out << temp->name;
        if (temp->additional[0] != ',' && temp->additional != "")
        {
            out << " ";
        }
        out << temp->additional;
        if (temp->next != nullptr)
        {
            out << "|";
        }
        temp = temp->next;
    }
    return out;
}

void read(string name, struct City* arrOfPointers[], int length)
{
    ifstream myfile;
    string myline;
    myfile.open (name);
    if (myfile.is_open())
    {
        cout << "read file " << '"' << name << '"' << " ... done" << endl;
        getline (myfile, myline);
        while (getline(myfile, myline))
        {
            string temp, temp2, temp3;
            int i = 0, tempInt;
            City* newCity = new City;
            while (myline[i] != ';')
            {
                temp += myline[i];
                i++;
            }
            while(myline[i+1] != ';')
            {
                temp2 += myline[i+1];
                i++;
            }
            while(myline[i+2] != ';')
            {
                temp3 += myline[i+2];
                i++;
            }
            newCity->name = temp;
            newCity->additional = temp2;
            tempInt = stoi(temp3);
            if(arrOfPointers[tempInt] != nullptr)
            {
                City* tempCity = new City;
                tempCity = newCity;
                tempCity->next = arrOfPointers[tempInt];
                arrOfPointers[tempInt] = tempCity;
            }
            arrOfPointers[tempInt] = newCity;
        }
    }
    else
    {
        cout << "ERROR! ";
    }

}

void print(struct City* arrOfCities[], int length, int forCity, int toCity)
{
    for (int i = forCity; i <= toCity; i++)
    {
        if(arrOfCities[i] != nullptr)
        {
            cout<< i << " " << arrOfCities[i] << endl;
        }
    }
}

void html(string name, City* arrOfCities[], int length, int fromCity, int toCity)
{
    ofstream myFile(name+".html");

    myFile << "<!DOCTYPE html>" << endl << "<html>" << endl << "<head>" << endl << "<title>";
    myFile << "PLZ in Germany from " << fromCity << " to " << toCity << "</title>" << endl;
    myFile << "</head>" << endl << "<body>" << endl << "<h1>" << "PLZ in Germany from " << fromCity << " to " << toCity;
    myFile << "</h1>" << endl << "<table border=" << "1" << ">" << endl << "<tr><th>PLZ</th><th>Area</th></tr>" << endl;
    for (int i = fromCity; i <= toCity; i++)
    {
        if(arrOfCities[i] != nullptr)
        {
            myFile << "<tr><td>"<< i << "</td><td>" << arrOfCities[i] << "</td></tr>" << endl;
        }
    }
    myFile << "</table>" << endl << "</body>" << endl << "</html>" << endl;
}

int main()
{
    char choice;
    int tempInt, tempInt2;
    string temp, temp2, temp3, name;
    City* cities[100000];
    cout << "please input file name: ";
    cin >> temp;
    read(temp, cities, 100000);
    do
    {
        cout << "q quit" << endl;
        cout << "c city" << endl;
        cout << "f from to" << endl;
        cout << "w write HTML file" << endl << ">>";
        cin >> choice;
        switch(choice)
        {
        case 'q':
            cout << "farewell...";
            return 0;
        case 'c':
            cout << "please input zip code: ";
            cin >> temp2;
            temp3 = temp2;
            for (int i = temp2.length(); i < 5; i++)
            {
                temp2 += "0";
            }
            tempInt = stoi(temp2);
            for (int i = temp3.length(); i < 5; i++)
            {
                temp3 += "9";
            }
            tempInt2 = stoi(temp3);
            print(cities, 100000, tempInt, tempInt2);
            break;
        case 'f':
            cout << "from which zip code: ";
            cin >> tempInt;
            cout << "up to which zip code: ";
            cin >> tempInt2;
            print(cities, 100000, tempInt, tempInt2);
            break;
        case 'w':
            cout << "please input file name: ";
            cin >> name;
            cout <<  "from which zip code: ";
            cin >> tempInt;
            cout << "up to which zip code: ";
            cin >> tempInt2;
            html(name, cities, 100000, tempInt, tempInt2);
            cout << "start writing HTML file " << '"' << name << '"' << " ... done" << endl;
        }
    }
    while (choice != 'q');
    return 0;
}
