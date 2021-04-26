#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Player{
    public:
        int goals_scored;
        int index;
        int age;
        int seasons_played;
        int matches_played;
        string name;
        string club;
        string country;
        string position;
        //metods
        float goals_in_match();
        void read(istream&is);
        void write(ostream&os);
};
float Player::goals_in_match()
{
    return goals_scored/matches_played;
}
void Player::read (istream&is)
{
    string s, trash;
    is >> index;
    //if (s != "\n")is.setstate(ios::failbit);
    is >> name >> s;
    if (s != name) 
    {
        name += " ";
        name += s;
    }
    getline (is, trash);
    getline (is, position);
    getline (is, club, '\t');
    /*is >> s;
    if (s!="dla")
    {
        is.setstate(ios::failbit);
        getline (is, s, '\t');
    }*/
    getline (is, country);
    is >> s;
    if (s == "-")
        age = -1;
    else 
        age = stoi(s);
    is >> seasons_played >> matches_played >> goals_scored;
    /*string position_tmp;
    is >> index >> name >> surname >> name >> surname >> position >> position_tmp >> club >> country >> age >> seasons_played >> matches_played >> goals_scored;
    position += position_tmp;*/

}
void Player::write (ostream&os)
{
    os << index << '\t';
    os << name << '\t';
    os << position << '\t';
    os << club << '\t';
    os << country << '\t';
    os << age << '\t';
    os << seasons_played << '\t';
    os << matches_played << '\t';
    os << goals_scored;
}
class PlayerList
{
    vector <Player> footballers;
    int size;
    int capacity;
    public:
        void read(istream&is);
        void write(ostream&os);
        void add(const Player&p);
        float goals_in_match();
        Player oldest_one();   
        string index_to_name(int ind); 
};

void PlayerList::write(ostream&os)
{
    for (int i=0; i<footballers.size(); ++i)
    {
        footballers[i].write(os);
        cout << endl;
    }
}
void PlayerList::read(istream&is)
{
    //while (is)
    for (int i=0; i < 49; ++i)
    {
        Player p;
        p.read(is);
        footballers.push_back(p);
        if (!is)
            break;
    }
}

string PlayerList::index_to_name(int ind)
{
    for (int i=0; i < footballers.size(); ++i)
    {
        if (ind == i)
            return footballers[i].name;
    }
}
Player PlayerList::oldest_one()
{
    Player p = footballers[0];
    for (int i=1; i < footballers.size(); ++i)
    {
        if (p.age < footballers[i].age)
            p=footballers[i];
    }
    return p;
}
void test_read_write(){
    ifstream is("champions_league_best_goalscorers/data.txt");
    if(!is){
        cerr<<"Błąd otwarcia pliku"<<endl;
        return;
    }
    cout<< "TESTING READING FROM FILE:"<<endl << endl;
    //while (is)
    for (int i=0 ; i<49 ; ++i)
    {
        
        Player p;
        p.read(is);
        if (!is)
        {
            cout<<"tututut";
            break;
        }                          
        p.write(cout);
        cout<<endl;
    }
}
void reading_to_list_test()
{
    ifstream is("champions_league_best_goalscorers/data.txt");
    if(!is){
        cerr<<"Błąd otwarcia pliku"<<endl;
        return;
    }
    cout<< "TESTING READING FROM FILE:" << endl << endl;
    PlayerList players;
    players.read(is);
    players.write(cout);
}

int main ()
{
    //test_read_write();
    //reading_to_list_test();
    ifstream file ("champions_league_best_goalscorers/data.txt");
    if (!file)
    {
        cerr<<"Błąd otwarcia pliku"<<endl;
    }
    PlayerList players;
    players.read(file);
    Player p = players.oldest_one();
    cout << p.name;
    return 0;
}
