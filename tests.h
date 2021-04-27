#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void test_read_write(){
    ifstream is("champions_league_best_goalscorers/data.txt");
    if(!is){
        cerr<<"Błąd otwarcia pliku"<<endl;
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