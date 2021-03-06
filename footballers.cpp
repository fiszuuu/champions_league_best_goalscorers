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
        string nation;
        string position;
        //metods
        float goals_in_match()const;
        void read(istream&is);
        void write(ostream&os);
        bool is_dead()const;
};
float Player::goals_in_match()const
{
    return goals_scored/matches_played;
}
void Player::read (istream&is)
{
    string s;
    is >> index;
    getline (is, s);
    getline (is, name, '\t');
    getline (is, s);
    getline (is, position);
    getline (is, club, '\t');
    getline (is, nation);
    is >> s;
    if (s == "-")
        age = -1;
    else 
        age = atoi(s.c_str());
    is >> seasons_played >> matches_played >> goals_scored;
}
void Player::write (ostream&os)
{
    os << index << '\t';
    os << name << '\t';
    os << position << '\t';
    os << club << '\t';
    os << nation << '\t';
    os << age << '\t';
    os << seasons_played << '\t';
    os << matches_played << '\t';
    os << goals_scored;
}
bool Player::is_dead()const
{
    if (age == -1) return true;
    return false;
}

class PlayerList
{
    vector <Player> footballers;
    public:
        void read(istream&is);
        void write(ostream&os);
        void add(const Player&p);
        Player oldest_one()const;   
        string index_to_name(int ind)const;
        vector <Player> specified_nation (string nation)const;
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
    while (is)
    //for (int i=0; i < 49; ++i)
    {
        Player p;
        p.read(is);
        if (!is)
            break;
        footballers.push_back(p);
    }
}
string PlayerList::index_to_name(int ind)const
{
    --ind;
    for (int i=0; i < footballers.size(); ++i)
    {
        if (ind == i)
            return footballers[i].name;
    }
    return "-1"; 
}
Player PlayerList::oldest_one()const
{
    Player p = footballers[0];
    for (int i=1; i < footballers.size(); ++i)
    {
        if (p.age < footballers[i].age)
            p=footballers[i];
    }
    return p;
}
vector <Player> PlayerList::specified_nation (string nation)const
{
    //detecting bad capitalization from user e.g. pOLskA
    if (nation[0]> 96 && nation[0] <123) 
        nation[0]-=('a'-'A');
    for (int i=1; i < nation.size(); ++i)
    {
        if (nation[i] < 91 && nation[i] > 64)
            nation[i] += ('a'-'A');
    }


    vector <Player> footballers_from;
    for (int i=0; i < footballers.size(); ++i)
    {
        if (nation == footballers[i].nation)
            footballers_from.push_back(footballers[i]);
    }
    if (footballers_from.empty()) 
    {
        cerr << "ERROR: There are no players from given nation("<<nation << ")" << endl;
        //cerr << "Did you remeber to start with capitalaized letter";
    }
    return footballers_from;
}


//TESTING

void test_read_write(){
    ifstream is("champions_league_best_goalscorers/data.txt");
    if(!is){
        cerr<<"B????d otwarcia pliku"<<endl;
        return;
    }
    cout<< "TESTING READING FROM FILE:"<<endl << endl;
    while (is)
    //for (int i=0 ; i<49 ; ++i)
    {
        
        Player p;
        p.read(is);
        if (!is)
        {
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
        cerr<<"ERROR: File opening didn't succeed"<<endl;
        return;
    }
    cout<< "TESTING READING FROM FILE:" << endl << endl;
    PlayerList players;
    players.read(is);
    players.write(cout);
}
void oldest_one_test()
{
    ifstream file ("champions_league_best_goalscorers/data.txt");
    if (!file)
    {
        cout<<"ERROR: File opening didn't succeed"<<endl;
        return;
    }
    PlayerList players;
    players.read(file);
    Player p = players.oldest_one();
    cout << p.name <<endl;
}
void index_to_name_test(int ind)
{
    ifstream file ("champions_league_best_goalscorers/data.txt");
    if (!file)
    {
        cout<<"ERROR: File opening didn't succeed"<<endl;
        return;
    }
    PlayerList players;
    players.read(file);
    cout << players.index_to_name(ind) << endl;
}
void specified_nation_test(string nation)
{
    ifstream file ("champions_league_best_goalscorers/data.txt");
    if (!file)
    {
        cout<<"ERROR: File opening didn't succeed"<<endl;
        return;
    }
    PlayerList players;
    players.read(file);
    vector <Player> pfn = players.specified_nation(nation);
    for (int i=0; i < pfn.size(); ++i)
    {
        pfn[i].write(cout);
        cout << endl;
    }
}

int main ()
{
    //test_read_write();
    //reading_to_list_test();
    //index_to_name_test(13);
    //oldest_one_test();
    specified_nation_test("pOLska");
    return 0;
}
