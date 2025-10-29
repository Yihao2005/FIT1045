#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <limits>
#include <iomanip>
#include <sstream>

using std::stringstream;  // sstream

using std::string; // string

using std::vector; // vector

using std::to_string; // string
using std::stoi; // string
using std::stod; // string

using std::cout; // iostream
using std::cin; // iostream
using std::endl; // iostream

using std::numeric_limits; // limits
using std::streamsize; // iostream
using std::flush; // iostream

using std::random_device; // random
using std::mt19937; // random
using std::uniform_int_distribution; // random

using std::setprecision; // iomanip
using std::fixed; // iomanip

using std::system; // stdlib.h

const int UNIT_NUM =4; // The sequence of unit is always: ENG1011, ENG1012, ENG1005, FIT 1045

// Basic tools

int read_integer(string prompt)
{
    int number;
    cout<<prompt<<flush;
    cin>>number;
    while (cin.fail())
    {
        cout<<"Please enter an integer!"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<prompt<<flush;
        cin>>number;
    }
    return number;
}

void clear()
{
    system("clear");
}

string round_to(double a, int b)
{
    stringstream ss;
    double number;
    ss<<fixed<<setprecision(b)<<a;
    ss>>number;
    ss.clear();
    ss.str("");
    string number_s;
    ss<<number;
    ss>>number_s;
    return number_s;
}


//Random system

int random_int(int a, int b)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(a,b);

    int number = dist(gen);
    return number;

}

double random_double_from0to1()
{
    int a = random_int(0,10000);
    return a/10000.0;
}

double test_result(double ability_had, double ability_required)
{
    if (ability_had>=ability_required)
    {
        return 1;
    }

    double mark;

    if (ability_had <= 0.5*ability_required) //0.5
    {
        mark = ability_had/ability_required;
    }

    if (0.5*ability_required< ability_had&&ability_had<=0.6* ability_required) //0.5~0.6
    {
        mark = ability_had/ability_required + random_double_from0to1()*(0.7-ability_had/ability_required);
    }

    if (0.6*ability_required< ability_had&&ability_had<=0.7* ability_required) //0.6~0.7
    {
        mark = ability_had/ability_required + random_double_from0to1()*(0.8-ability_had/ability_required);
    }

    if (0.7*ability_required< ability_had&&ability_had<=0.8* ability_required) //0.7~0.8
    {
        mark = ability_had/ability_required + random_double_from0to1()*(0.9-ability_had/ability_required);
    }

    if (0.8*ability_required< ability_had) //0.8
    {
        mark = ability_had/ability_required + random_double_from0to1()*(1-ability_had/ability_required);
    }

    return mark;
}

//-----------------------------------------------------------------------------------------------------------------
// some data

class cuisine_timer
{
    public:
        int breakfast_chance;
        int lunch_chance;
        int dinner_chance;
        cuisine_timer()
        {
            breakfast_chance=1;
            lunch_chance=1;
            dinner_chance=1;
        }
};

class session_timer
{
    public:
        int ENG1011_project_timer ;
        int ENG1012_report1_timer ;
        int ENG1012_report2_timer ;
        int ENG1012_video_timer ;
        int ENG1012_reflection_timer ;
        int ENG1005_quiz_timer ;
        int ENG1005_project_timer ;
        int FIT1045_project_timer ;

        session_timer()
        {
            ENG1011_project_timer = 0;
            ENG1012_report1_timer =0;
            ENG1012_report2_timer =0;
            ENG1012_video_timer =0;
            ENG1012_reflection_timer =0;
            ENG1005_quiz_timer = 0;
            ENG1005_project_timer = 0;
            FIT1045_project_timer = 0;
        }
};

const int SIZE1 = 6;
const int SIZE2 = 8;
const int SIZE3 = 5;
const int SIZE4 = 1;
const int SIZEDB = 4;





//-----------------------------------------------------------------------------------------------------------------
// Time module 
enum week_day{
    Monday=1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
};

string read_day(week_day d)
{
    switch (d)
    {
        case Monday:
            return "Monday";

        case Tuesday:
            return "Tuesday";

        case Wednesday:
            return "Wednesday";

        case Thursday:
            return "Thursday";

        case Friday:
            return "Friday";

        case Saturday:
            return "Saturday";
        
        case Sunday:
            return "Sunday";
    }
}


class Time{
    private:
        int hour;
        week_day day;
        int n_th_week;
    public:
        Time(int h, week_day d, int n) //constructor
        {
            hour = h;
            day = d;
            n_th_week = n;
        }

        int get_hour()
        {
            return hour;
        }
        
        void time_pass(int hour_pass) // only validate when the hour_pass is less than 25
        {
            const int DAY_HOUR = 24;
            hour += hour_pass;
            if (hour>=DAY_HOUR)
            {
                hour -=DAY_HOUR;
            
                switch (day)
                {
                    case Monday:
                        day = Tuesday;
                        break;
                    case Tuesday:
                        day = Wednesday;
                        break;
                    case Wednesday:
                        day = Thursday;
                        break;
                    case Thursday:
                        day = Friday;
                        break;
                    case Friday:
                        day = Saturday;
                        break;
                    case Saturday:
                        day = Sunday;
                        break;
                    case Sunday:
                        day = Monday;
                        n_th_week ++;

                }
            }
        }

        void fresh_day(cuisine_timer& ct)
        {
            const double HOUR_GET_UP = 6;
            if (hour<HOUR_GET_UP)
            {
                hour = HOUR_GET_UP;
            }

            if(hour>HOUR_GET_UP)
            {
                hour = HOUR_GET_UP;
                switch (day)
                {
                    case Monday:
                        day = Tuesday;
                        break;
                    case Tuesday:
                        day = Wednesday;
                        break;
                    case Wednesday:
                        day = Thursday;
                        break;
                    case Thursday:
                        day = Friday;
                        break;
                    case Friday:
                        day = Saturday;
                        break;
                    case Saturday:
                        day = Sunday;
                        break;
                    case Sunday:
                        day = Monday;
                        n_th_week ++;
                }
            }

            ct.breakfast_chance++;
            ct.lunch_chance++;
            ct.dinner_chance++;
        }   


        int read_week()
        {
            return n_th_week;
        }
        
        week_day read_weekday()
        {
            return day;
        }

};

//-----------------------------------------------------------------------------------------------------------------

//ability and status module
const int ABILITY_LIMIT = 12;

class ability
{
    private:
        vector<double> ability_list;

    public:
        ability()
        {
            for (int i =0;i<UNIT_NUM;i++)
            {
                ability_list.push_back(0);
            }
        }
    
        ability(double E1, double E2, double E3, double F1)
        {
            
            ability_list.push_back(E1);
            ability_list.push_back(E2);
            ability_list.push_back(E3);
            ability_list.push_back(F1);
        }


        void ability_up(vector<double> ability_changes, Time time_now)
        {
            for (int i=0;i<UNIT_NUM;i++)
            {
                ability_list[i] += ability_changes[i];
                if (ability_list[i] >= time_now.read_week())
                {
                    ability_list[i] = time_now.read_week();
                }

                if (ability_list[i] >=ABILITY_LIMIT)
                {
                    ability_list[i] = ABILITY_LIMIT;
                }
            }

        }

        vector<double> show_ability()
        {
            return ability_list;
        }

        
        
};

enum emotion
{
    Bored,
    Hungry,
    Excited,
    Tired,
    Welbeing,
    

};

string print_emotion(emotion e)
{
    switch (e)
    {
        case Bored:
            return "Bored";

        case Hungry:
            return "Hungry";

        case Excited:
            return "Excited";

        case Tired:
            return "Tired";

        case Welbeing:
            return "Welbeing";

    }
}



class status
{
    private:
        double energy;
        double mood;
        ability A;
        emotion E;
    public:
        status(double e, double m, ability a, emotion em)
        {
            energy = e;
            mood = m;
            A =a;
            E = em;

        }
        
        void good_status()
        {
            const double E_G = 100;
            const double M_G = 100;

            energy = E_G;
            mood = M_G;
        }

        void calm_status()
        {
            const double E_C = 80;
            const double M_C = 80;

            energy = E_C;
            mood = M_C;
        }
        
        void bad_status()
        {
            const double E_B = 60;
            const double M_B = 60;

            energy = E_B;
            mood = M_B;
        }


        void energy_update(double energy_change)
        {
            const double ELIMIT = 100;
            energy += energy_change;
            if (energy>ELIMIT)
            {
                energy = ELIMIT;
            }
            if (energy<0)
            {
                energy = 0;
            }
        }

        void mood_update(double mood_change)
        {
            const double MLIMIT = 120;
            mood += mood_change;
            if (mood>MLIMIT)
            {
                mood = MLIMIT;
            }
            if (mood<0)
            {
                mood = 0;
            }
        }


        void ability_update(vector<double> ability_changes, Time time_now)//
        {
            A.ability_up(ability_changes,time_now);
        }

        void emotion_update()
        {
            const int MOOD_B1 = 20;
            const int MOOD_B2 = 100;
            const int ENERGY_B = 20;
            
            if (mood<=MOOD_B1 && energy<= ENERGY_B)
            {
                E = Tired;
            }
            else if (MOOD_B1< mood&&energy<=ENERGY_B)
            {
                E = Hungry;
            }
            else if (mood<=MOOD_B1&&energy>ENERGY_B)
            {
                E = Bored;
            }
            else if (mood>MOOD_B1 &&energy>ENERGY_B&&mood<=MOOD_B2)
            {
                E = Welbeing;
            }
            else if (mood>MOOD_B2 && energy>ENERGY_B)
            {
                E = Excited;
            }
        }

        vector<double> read_ability()
        {
            return A.show_ability();
        }

        double read_energy()
        {
            return energy;
        }

        double read_mood()
        {
            return mood;
        }

        emotion read_emotion()
        {
            return E;
        }
        
};      
//-----------------------------------------------------------------------------------------------------------------

//interaction (workshop ,applied, eat..)
class interaction
{
    private:
        double mood_cost;
        double energy_cost;
        vector<double> mark_changes;
        vector<double> ability_changes;
        int hour_used;
        string prompt;

    public:
        interaction(int m, int e, vector<double> mc, vector<double> ac, int h_u, string p)
        {
            mood_cost = m;
            energy_cost = e;
            mark_changes = mc;
            ability_changes = ac;
            hour_used = h_u;
            prompt = p;
        }

        int get_hour_used()
        {
            return hour_used;
        }

        virtual void happens(status &status_now,Time &time_now, vector<double> &Mark_list)
        {
            status_now.energy_update(energy_cost);
            status_now.mood_update(mood_cost);

            for (int i = 0;i<UNIT_NUM;i++)
            {
                Mark_list[i] += mark_changes[i];
            }

            status_now.ability_update(ability_changes,time_now);
            status_now.emotion_update();
            time_now.time_pass(hour_used);
        }

        double read_energy_cost()
        {
            return energy_cost;
        }

        double read_mood_cost()
        {
            return mood_cost;
        }
};

interaction read_interaction(double mc, double ec, vector<double> m_c, vector<double> a_c, int h_u, string p)
{
    interaction inter_action(mc,ec,m_c,a_c,h_u,p);
    return inter_action;
}

vector<double> read_vector4double(double a1,double a2, double a3, double a4){
    vector<double> v(4);
    v[0] = a1;
    v[1] = a2;
    v[2] = a3;
    v[3] = a4;
    return v;
}
//-----------------------------------------------------------------------------------------------------------------

//Mark
string Grade(double Mark)
{
    const int HD_B = 80;
    const int D_B = 70;
    const int C_B = 60;
    const int P_B = 50;
    
    if (Mark>=HD_B)
    {
        return "HD";
    }

    else if(D_B<=Mark && Mark<HD_B)
    {
        return "D";
    }

    else if(C_B<=Mark&& Mark<D_B)
    {
        return "C";
    }

    else if(P_B<=Mark&& Mark<C_B)
    {
        return "P";
    }

    else if(Mark<P_B)
    {
        return "Fail";
    }

    return "";
}


void print_mark(vector<double> Mar, status status_now)
{
    cout<<"ENG1011: "<<setprecision(2)<<Mar[0]<<" Grade: "<<Grade(Mar[0])<<endl;
    cout<<"ENG1012: "<<setprecision(2)<<Mar[1]*test_result(status_now.read_ability()[1],12.00)<<" Grade: "<<Grade(Mar[1]*test_result(status_now.read_ability()[1],12.00))<<endl;
    cout<<"ENG1005: "<<setprecision(2)<<Mar[2]<<" Grade: "<<Grade(Mar[2])<<endl;
    cout<<"FIT1045: "<<setprecision(2)<<Mar[3]*test_result(status_now.read_ability()[3],12.00)<<" Grade: "<<Grade(Mar[3]*test_result(status_now.read_ability()[3],12.00))<<endl;
}
//-----------------------------------------------------------------------------------------------------------------

//Have cusine system/ leisure time system (no influence on marks or ability)
void have_breakfast(status &status_now, Time &time_now, vector<double> &Mark_list)
{
    interaction coffee_bread = read_interaction(10,5,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Having coffee and bread");
    interaction tea_sandwich =  read_interaction(5,10,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Having tead and sandwich");
    interaction milk = read_interaction(2.5,2.5,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),0,"Having milk");

    cout<<"-------------------------------------------------------------------------"<<endl;    
    cout<<"Breakfast"<<endl;
    cout<<"What do you want to eat for breakfast:"<<endl;
    cout<<"1: coffee and bread"<<endl;
    cout<<"2: tea and sandwich"<<endl;
    cout<<"3. only milk"<<endl;
    
    const int MAX = 3;

    int selection = read_integer("Option: ");
    while (selection<1 || selection>MAX)
    {
        cout<<"Please enter an integer in the range!"<<endl;
        selection = read_integer("Option: ");
    }
    switch (selection)
    {
        case 1:
            coffee_bread.happens(status_now, time_now, Mark_list);
            break;
        case 2:
            tea_sandwich.happens(status_now, time_now, Mark_list);
            break;
        case 3:
            milk.happens(status_now, time_now, Mark_list);
    }
}

void have_lunch(status &status_now, Time &time_now, vector<double> &Mark_list)
{
    interaction fried_chicken_chip = read_interaction(40,20,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Having Fried chicken and chips");
    interaction chicken_curry_rice =  read_interaction(30,30,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Having chicken curry rice");
    interaction salad_with_yogrt = read_interaction(20,40,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Having salad with yogert");
    interaction chocolate_bars = read_interaction(15,15,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),0,"Having chocolate bar");
    
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"Lunch"<<endl;
    cout<<"What do you want to eat for lunch:"<<endl;
    cout<<"1: Fired chicken and chips"<<endl;
    cout<<"2: Chicken curry rice"<<endl;
    cout<<"3. Salad with yogrt"<<endl;
    cout<<"4. Chocolate bar"<<endl;
    
    const int MAX = 4;

    int selection = read_integer("Option: ");
    while (selection<1 || selection>MAX)
    {
        cout<<"Please enter an integer in the range!"<<endl;
        selection = read_integer("Option: ");
    }
    switch (selection)
    {
        case 1:
            fried_chicken_chip.happens(status_now, time_now, Mark_list);
            break;
        case 2:
            chicken_curry_rice.happens(status_now, time_now, Mark_list);
            break;
        case 3:
            salad_with_yogrt.happens(status_now, time_now, Mark_list);
            break;
        case 4:
            chocolate_bars.happens(status_now, time_now, Mark_list);
    }

}

void have_dinner(status &status_now, Time &time_now, vector<double> &Mark_list)
{
    interaction Spicy_chicken_burger_combo = read_interaction(50,30,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Having spicy chicken burger combo");
    interaction Hot_pot =  read_interaction(60,60,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),2,"Having hot pot");
    interaction Pasta = read_interaction(30,50,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Having pasta");
    interaction Lasagna = read_interaction(35,45,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Having lasagna");
    interaction instant_noddle = read_interaction(25,25,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),0,"Having instant noodle");

    cout<<"-------------------------------------------------------------------------"<<endl;    
    cout<<"Dinner"<<endl;
    cout<<"What do you want to eat for dinner:"<<endl;
    cout<<"1: Spicy chicken burger"<<endl;
    cout<<"2: Hot pot"<<endl;
    cout<<"3. Pasta"<<endl;
    cout<<"4. Lasagna"<<endl;
    cout<<"5. Instant noodle"<<endl;
    
    const int MAX = 5;

    int selection = read_integer("Option: ");
    while (selection<1 || selection>MAX)
    {
        cout<<"Please enter an integer in the range!"<<endl;
        selection = read_integer("Option: ");
    }
    switch (selection)
    {
        case 1:
            Spicy_chicken_burger_combo.happens(status_now, time_now, Mark_list);
            break;
        case 2:
            Hot_pot.happens(status_now, time_now, Mark_list);
            break;
        case 3:
            Pasta.happens(status_now, time_now, Mark_list);
            break;
        case 4:
            Lasagna.happens(status_now, time_now, Mark_list);
            break;
        case 5:
            instant_noddle.happens(status_now, time_now, Mark_list);


    }


}

void sleep_for_a_while(status &status_now, Time &time_now, vector<double> &Mark_list)
{
    interaction sleep_1hour = read_interaction(20,25,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Sleep for one hour");
    interaction sleep_2hour = read_interaction(30,60,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),2,"Sleep for two hours");

    cout<<"-------------------------------------------------------------------------"<<endl;    
    cout<<"Sleep for a while"<<endl;
    cout<<"How long do you want to sleep?"<<endl;
    cout<<"1. sleep for a while"<<endl;
    cout<<"2. sleep for a long time"<<endl;
    int selection = read_integer("Option: ");
    const int FIRST = 1;
    const int SECOND =2;
    
    while (selection != FIRST && selection !=SECOND)
    {
        cout<<"Please enter an integer in the range!"<<endl;
        selection = read_integer("Option: ");
    }
    switch (selection)
    {
        case 1:
            sleep_1hour.happens(status_now, time_now, Mark_list);
            break;

        case 2:
            sleep_2hour.happens(status_now, time_now, Mark_list);
            break;
    }
}

void play_video_game(status &status_now, Time &time_now, vector<double> &Mark_list)
{
    interaction play_1hour = read_interaction(20,-10,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Sleep for one hour");
    interaction play_2hour = read_interaction(40,-30,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),2,"Sleep for two hours");

    cout<<"-------------------------------------------------------------------------"<<endl;    
    cout<<"Play video game"<<endl;
    cout<<"How long do you want to play the video game?"<<endl;
    cout<<"1. play for a while"<<endl;
    cout<<"2. play for a long time"<<endl;
    int selection = read_integer("Option: ");
    const int FIRST = 1;
    const int SECOND =2;
    
    while (selection != FIRST && selection !=SECOND)
    {
        cout<<"Please enter an integer in the range!"<<endl;
        selection = read_integer("Option: ");
    }
    switch (selection)
    {
        case 1:
            if (status_now.read_energy()+play_1hour.read_energy_cost()<0 || status_now.read_mood()+play_1hour.read_mood_cost()<0)
            {
                
                return;
            }
            
            play_1hour.happens(status_now, time_now, Mark_list);
            break;

        case 2:
            if (status_now.read_energy()+play_2hour.read_energy_cost()<0 || status_now.read_mood()+play_2hour.read_mood_cost()<0)
            {
                
                return;
            }
        
            play_2hour.happens(status_now, time_now, Mark_list);
            break;
    }
}

void sport(status &status_now, Time &time_now, vector<double> &Mark_list)
{
    interaction walk = read_interaction(20,-15,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Walk for a while");
    interaction running =  read_interaction(25,-20,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Run for a while");
    interaction play_basketball = read_interaction(40,-30,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),2,"Play basketball");
    interaction play_soccer = read_interaction(50,-40,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),2,"Play soccer");
    interaction play_football = read_interaction(60,-50,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),2,"Play football");

    cout<<"-------------------------------------------------------------------------"<<endl;    
    cout<<"Sport"<<endl;
    cout<<"What kind of sport do you want to do:"<<endl;
    cout<<"1. Walk"<<endl;
    cout<<"2. Running"<<endl;
    cout<<"3. Play basketball"<<endl;
    cout<<"4. Play soccer"<<endl;
    cout<<"5. Play football"<<endl;
    
    const int MAX = 5;

    int selection = read_integer("Option: ");
    while (selection<1 || selection>MAX)
    {
        cout<<"Please enter an integer in the range!"<<endl;
        selection = read_integer("Option: ");
    }
    switch (selection)
    {
        case 1:
            if (status_now.read_energy()+walk.read_energy_cost()<0 || status_now.read_mood()+walk.read_mood_cost()<0)
            {
                
                return;
            }
            walk.happens(status_now, time_now, Mark_list);
            break;
        case 2:
            if (status_now.read_energy()+running.read_energy_cost()<0 || status_now.read_mood()+running.read_mood_cost()<0)
            {
                
                return;
            }
            
            running.happens(status_now, time_now, Mark_list);
            break;
        case 3:
            if (status_now.read_energy()+play_basketball.read_energy_cost()<0 || status_now.read_mood()+play_basketball.read_mood_cost()<0)
            {
                
                return;
            }
            play_basketball.happens(status_now, time_now, Mark_list);
            break;
        case 4:
            if (status_now.read_energy()+play_soccer.read_energy_cost()<0 || status_now.read_mood()+play_soccer.read_mood_cost()<0)
            {
                
                return;
            }
            play_soccer.happens(status_now, time_now, Mark_list);
            break;
        case 5:
            if (status_now.read_energy()+play_football.read_energy_cost()<0 || status_now.read_mood()+play_football.read_mood_cost()<0)
            {
                
                return;
            }
            play_football.happens(status_now, time_now, Mark_list);
    }
}

void relax(status &status_now, Time &time_now, vector<double> &Mark_list)
{
    cout<<"-------------------------------------------------------------------------"<<endl;    
    cout<<"Relax"<<endl;
    cout<<"What kind of activity do you want to participate:"<<endl;
    cout<<"1. Sleep for a while"<<endl;
    cout<<"2. Play video game"<<endl;
    cout<<"3. Sport"<<endl;

    const int MAX = 3;

    int selection = read_integer("Option: ");
    while (selection<1 || selection>MAX)
    {
        cout<<"Please enter an integer in the range!"<<endl;
        selection = read_integer("Option: ");
    }
    switch (selection)
    {
        case 1:
            sleep_for_a_while(status_now,time_now,Mark_list);
            break;
        case 2:
            play_video_game(status_now,time_now,Mark_list);
            break;
        case 3:
            sport(status_now,time_now,Mark_list);
            break;
    }
}



//-----------------------------------------------------------------------------------------------------------------

class unit
{
    protected:
        vector<interaction> study_list;

    public:
        unit() {}
};

class ENG1011 : public unit
{
    public: 
        ENG1011(status status_now)
        {
            study_list.push_back(read_interaction(-50,-50,read_vector4double(10/12.00,0,0,0),read_vector4double(2/12.00,0,0,0),2,"Attend workshop"));
            study_list.push_back(read_interaction(-60,-40,read_vector4double(5/12.00,0,0,0),read_vector4double(2/12.00,0,0,0),2,"Attend practical"));
            study_list.push_back(read_interaction(-20,-20,read_vector4double(0,0,0,0),read_vector4double(1/12.00,0,0,0),1,"Study for one hour"));
            study_list.push_back(read_interaction(-70,-70,read_vector4double(test_result(status_now.read_ability()[0],5.0)*7.5,0,0,0),read_vector4double(0,0,0,0),2,"Taking the content test 1"));
            study_list.push_back(read_interaction(-70,-70,read_vector4double(test_result(status_now.read_ability()[0],10.0)*7.5,0,0,0),read_vector4double(0,0,0,0),2,"Taking the content test 2"));
            study_list.push_back(read_interaction(-90,-90,read_vector4double(test_result(status_now.read_ability()[0],12.0)*50,0,0,0),read_vector4double(0,0,0,0),3,"Taking the Final examination"));
            study_list.push_back(read_interaction(-25,-25,read_vector4double(20/30.00,0,0,0),read_vector4double(0,0,0,0),1,"Work on the project"));
        }

        vector<interaction> list()
        {
            return study_list;
        }
};


class ENG1012 : public unit
{
    public:
        ENG1012(status status_now)
        {
            study_list.push_back(read_interaction(-50,-50,read_vector4double(0,0,0,0),read_vector4double(0,2/12.00,0,0),2,"Attend workshop"));
            study_list.push_back(read_interaction(-50,-50,read_vector4double(0,5,0,0),read_vector4double(0,2/12.00,0,0),2,"Attend workshop")); // special
            study_list.push_back(read_interaction(-60,-40,read_vector4double(0,10/10.00,0,0),read_vector4double(0,2/12.00,0,0),2,"Attend practical"));
            study_list.push_back(read_interaction(-20,-20,read_vector4double(0,0,0,0),read_vector4double(0,1/12.00,0,0),1,"Study for one hour"));
            study_list.push_back(read_interaction(-50,-50,read_vector4double(0,10*test_result(status_now.read_ability()[1],6.0),0,0),read_vector4double(0,0,0,0),2,"Attend interview"));
            study_list.push_back(read_interaction(-25,-25,read_vector4double(0,15/10.00,0,0),read_vector4double(0,0,0,0),1,"Work on the report 1"));
            study_list.push_back(read_interaction(-25,-25,read_vector4double(0,20/20.00,0,0),read_vector4double(0,0,0,0),1,"Work on the report 2"));
            study_list.push_back(read_interaction(-25,-25,read_vector4double(0,15/6.00,0,0),read_vector4double(0,0,0,0),1,"Work on the video"));
            study_list.push_back(read_interaction(-25,-25,read_vector4double(0,10/6.00,0,0),read_vector4double(0,0,0,0),1,"Work on the reflection"));
            study_list.push_back(read_interaction(-50,-50,read_vector4double(0,15*test_result(status_now.read_ability()[1],12.0),0,0),read_vector4double(0,0,0,0),2,"Attend presentation"));
        }

        vector<interaction> list()
        {
            return study_list;
        }
};


class ENG1005 : public unit
{
    public:
        ENG1005(status status_now, Time time_now)
        {
            study_list.push_back(read_interaction(-50,-50,read_vector4double(0,0,0,0),read_vector4double(0,0,2/12.00,0),2,"Attend workshop"));
            study_list.push_back(read_interaction(-60,-40,read_vector4double(0,0,5/12.00*test_result(status_now.read_ability()[2],time_now.read_week()),0),read_vector4double(0,0,2/12.00,0),2,"Attend practical"));
            study_list.push_back(read_interaction(-20,-20,read_vector4double(0,0,0,0),read_vector4double(0,0,1/12.00,0),1,"Study for one hour"));
            study_list.push_back(read_interaction(-30,-30,read_vector4double(0,0,5/12.00*test_result(status_now.read_ability()[2],time_now.read_week()),0),read_vector4double(0,0,0,0),1,"Take quiz"));
            study_list.push_back(read_interaction(-70,-70,read_vector4double(0,0,20/12.00*test_result(status_now.read_ability()[2],time_now.read_week()),0),read_vector4double(0,0,0,0),2,"Take project"));
            study_list.push_back(read_interaction(-70,-70,read_vector4double(0,0,20*test_result(status_now.read_ability()[2],time_now.read_week()),0),read_vector4double(0,0,0,0),2,"Take mid-semester"));
            study_list.push_back(read_interaction(-80,-80,read_vector4double(0,0,50*test_result(status_now.read_ability()[2],time_now.read_week()),0),read_vector4double(0,0,0,0),2,"Take Final"));
        }

        vector<interaction> list()
        {
            return study_list;
        }
};


class FIT1045 : public unit
{
    public:
        FIT1045(status stuatus_now, Time time_now)
        {
            study_list.push_back(read_interaction(-50,-50,read_vector4double(0,0,0,0),read_vector4double(0,0,0,2/12.00),2,"Attend workshop"));
            study_list.push_back(read_interaction(-60,-40,read_vector4double(0,0,0,0),read_vector4double(0,0,0,2/12.00),2,"Attend practical"));
            study_list.push_back(read_interaction(-20,-20,read_vector4double(0,0,0,0),read_vector4double(0,0,0,1/12.00),1,"Study for one hour"));
            study_list.push_back(read_interaction(-25,-25,read_vector4double(0,0,0,100/120.00),read_vector4double(0,0,0,0),1,"Work on the projecct"));
        }

        vector<interaction> list()
        {
            return study_list;
        }
};


void participate(interaction activity,status &status_now, Time &time_now, vector<double> &Mark_list)
{
    if (status_now.read_energy()+activity.read_energy_cost()<0 || status_now.read_mood()+activity.read_mood_cost()<0)
    {
        return;
    }
    activity.happens(status_now,time_now,Mark_list);
}

void participate(interaction activity,status &status_now, Time &time_now, vector<double> &Mark_list, int &project_timer)
{
    if (status_now.read_energy()+activity.read_energy_cost()<0 || status_now.read_mood()+activity.read_mood_cost()<0)
            {
                
                return;
            }
    project_timer++;
    activity.happens(status_now,time_now,Mark_list);
}

//-----------------------------------------------------------------------------------------------------------------

//Sleep system

void sleep(status &status_now, Time &time_now, cuisine_timer &ct)
{
    int hour_now = time_now.get_hour();
    if (hour_now<22 && hour_now>=20)
    {
        status_now.good_status();
        
    }

    else if (hour_now>=22 && hour_now<24)
    {
        status_now.calm_status();
    }

    else if (hour_now>=0 && hour_now<=6)
    {
        status_now.bad_status();
    }
    
    
    status_now.emotion_update();
    
    time_now.fresh_day(ct);
}

void snooze_for_a_while(status &status_now, Time &time_now, vector<double> &Mark_list)
{
    interaction snooze = read_interaction(20,20,read_vector4double(0,0,0,0),read_vector4double(0,0,0,0),1,"Snooze for one hour");
    snooze.happens(status_now,time_now,Mark_list);
}

//-----------------------------------------------------------------------------------------------------------------

//Time line system
 
void time_system_schedule(Time time_now, session_timer &st, vector<vector<double> > & Mark_Data_Base)
{

    //ENG1011
    vector<string> lists_1(6);
    lists_1[0] = "ENG1011 Workshop  12:00pm ~ 14:00pm";
    lists_1[1] = "ENG1011 Practical 16:00pm ~ 18:00pm";
    lists_1[2] = "ENG1011 Content test1 18:00pm ~ 20:00pm";
    lists_1[3] = "ENG1011 Content test2 18:00pm ~ 20:00pm";
    lists_1[4] = "ENG1011 Project      Week 6 ~ 11 Progress: "+round_to((Mark_Data_Base[0][4])/20.00*100,2)+"%";
    lists_1[5] = "ENG1011 Final     14:00pm ~ 17:00pm";
        
    vector<bool> list_1(6);

    for (int i =0; i < list_1.size(); i++)
    {
        list_1[i] = true;
    }
    
    if (time_now.read_week()>=1 && time_now.read_week()<=12 && time_now.read_weekday() == Monday)
    {
        list_1[0]=true;
    }
    else
    {
        list_1[0]=false;
    }

    if ( time_now.read_week()>=1 && time_now.read_week()<=12 && time_now.read_weekday() == Thursday)
    {
        list_1[1]=true;
    }
    else
    {
        list_1[1]=false;
    }

    if ( time_now.read_week()==5 && time_now.read_weekday() == Monday)
    {
        list_1[2]=true;
    }
    else
    {
        list_1[2]=false;
    }

    if (  time_now.read_week()==10 && time_now.read_weekday() == Monday)
    {
        list_1[3]=true;
    }
    else
    {
        list_1[3]=false;
    }

    if (time_now.read_week()>=6 &&time_now.read_week()<=11 && st.ENG1011_project_timer<30)
    {
        list_1[4]=true;
    }
    else
    {
        list_1[4]=false;
    }

    if (time_now.read_week()==14 && time_now.read_weekday() == Tuesday)
    {
        list_1[5]=true;
    }
    else
    {
        list_1[5]=false;
    }


    //ENG1012
    vector<string> lists_2(9);
    lists_2[0] = "ENG1012 Workshop  14:00pm ~ 16:00pm";
    lists_2[1] = "ENG1012 Practical 10:00am ~ 12:00pm";
    lists_2[2] = "ENG1012 Interview 10:00am ~ 12:00pm";
    lists_2[3] = "ENG1012 Presentation 10:00am ~ 12:00pm";//  to_string(round_to((Mark_Data_Base[1][7])/10.00*100,2))+"%";
    lists_2[4] = "ENG1012 Report1      Week 1 ~ 5 Progress: "+round_to((Mark_Data_Base[1][4])/15.00*100,2)+"%";
    lists_2[5] = "ENG1012 Video        Week 7 ~ 8 Progress: "+round_to((Mark_Data_Base[1][5])/15.00*100,2)+"%";
    lists_2[6] = "ENG1012 Report2      Week 9 ~ 13 Progress: "+round_to((Mark_Data_Base[1][6])/20.00*100,2)+"%";
    lists_2[7] = "ENG1012 Reflection   Week 11 ~ 13 Progress: "+round_to((Mark_Data_Base[1][7])/10.00*100,2)+"%";
    lists_2[8] = "ENG1012 Workshop (Attendance Mark: 5)  14:00pm ~ 16:00pm";
    
    vector<bool> list_2(9);

    for (int i =0; i < list_2.size(); i++)
    {
        list_2[i] = true;
    }
    
    if ( time_now.read_week()>=1 && time_now.read_week()<=11 && time_now.read_weekday() == Wednesday)
    {
        list_2[0]=true;
    }
    else
    {
        list_2[0]=false;
    }

    if (  ((time_now.read_week()>=1 && time_now.read_week()<=5)||(time_now.read_week()>=7 && time_now.read_week()<=11)) && time_now.read_weekday() == Tuesday)
    {
        list_2[1]=true;
    }
    else
    {
        list_2[1]=false;
    }

    if (  time_now.read_week()==6 && time_now.read_weekday() == Tuesday)
    {
        list_2[2]=true;
    }
    else
    {
        list_2[2]=false;
    }

    if (  time_now.read_week()==12 && time_now.read_weekday() == Tuesday)
    {
        list_2[3]=true;
    }
    else
    {
        list_2[3]=false;
    }

    if (time_now.read_week()>=1 &&time_now.read_week()<=5 && st.ENG1012_report1_timer<10)
    {
        list_2[4]=true;
    }
    else
    {
        list_2[4]=false;
    }

    if (time_now.read_week()>=7 &&time_now.read_week()<=8 && st.ENG1012_video_timer<6)
    {
        list_2[5]=true;
    }
    else
    {
        list_2[5]=false;
    }

    if (time_now.read_week()>=9 &&time_now.read_week()<=13 && st.ENG1012_video_timer<20)
    {
        list_2[6]=true;
    }
    else
    {
        list_2[6]=false;
    }

    if (time_now.read_week()>=11 &&time_now.read_week()<=13 && st.ENG1012_video_timer<6)
    {
        list_2[7]=true;
    }
    else
    {
        list_2[7]=false;
    }

    if (  time_now.read_week()==12 && time_now.read_weekday() == Wednesday)
    {
        list_2[8]=true;
    }
    else
    {
        list_2[8]=false;
    }


    //ENG1005
    vector<string> lists_3(6);
    lists_3[0] = "ENG1005 Workshop  10:00am ~ 12:00pm";
    lists_3[1] = "ENG1005 Practical 14:00pm ~ 16:00pm";
    lists_3[2] = "ENG1005 Mid-semester 10:00am ~ 12:00pm";
    lists_3[3] = "ENG1005 Quiz per week";
    lists_3[4] = "ENG1005 Project per week";
    lists_3[5] = "ENG1005 Final     14:00pm ~ 17:00pm";
        
    vector<bool> list_3(6);

    for (int i =0; i < list_3.size(); i++)
    {
        list_3[i] = true;
    }
    
    if (  time_now.read_week()>=1 && ((time_now.read_week()>=1 && time_now.read_week()<=6)||(time_now.read_week()>=8 && time_now.read_week()<=12)) && time_now.read_weekday() == Thursday)
    {
        list_3[0]=true;
    }
    else
    {
        list_3[0]=false;
    }

    if (  time_now.read_week()>=1 && time_now.read_week()<=12 && time_now.read_weekday() == Friday)
    {
        list_3[1]=true;
    }
    else
    {
        list_3[1]=false;
    }

    if (  time_now.read_week()==7 && time_now.read_weekday() == Thursday)
    {
        list_3[2]=true;
    }
    else
    {
        list_3[2]=false;
    }

    if (time_now.read_week()>=1 && time_now.read_week()<=12 && st.ENG1005_quiz_timer<time_now.read_week())
    {
        list_3[3]=true;
    }
    else
    {
        list_3[3]=false;
    }

    if (time_now.read_week()>=1 && time_now.read_week()<=12 && st.ENG1005_project_timer<time_now.read_week())
    {
        list_3[4]=true;
    }
    else
    {
        list_3[4]=false;
    }

    if (  time_now.read_week()==14 && time_now.read_weekday() == Friday)
    {
        list_3[5]=true;
    }
    else
    {
        list_3[5]=false;
    }


    //FIT1045
    vector<string> lists_4(3);
    lists_4[0] = "FIT1045 Workshop  10:00am ~ 12:00pm";
    lists_4[1] = "FIT1045 Practical 12:00pm ~ 14:00pm";//to_string(round_to((Mark_Data_Base[3][0])/100.00*100,2))+"%";
    lists_4[2] = "FIT1045 Project       Week1-13 Progress: "+round_to((Mark_Data_Base[3][0])/100.00*100,2)+"%";
        
         
    vector<bool> list_4(3);
 
    for (int i =0; i < list_4.size(); i++)
    {
        list_4[i] = true;
    }
    
    if (  (time_now.read_week()>=1 && time_now.read_week()<=12) && time_now.read_weekday() == Friday)
    {
        list_4[0]=true;
    }
    else
    {
        list_4[0]=false;
    }

    if (  time_now.read_week()>=1 && time_now.read_week()<=12 && time_now.read_weekday() == Wednesday)
    {
        list_4[1]=true;
    }
    else
    {
        list_4[1]=false;
    }

    if (time_now.read_week()>=1 && time_now.read_week()<=13 && st.FIT1045_project_timer<120)
    {
        list_4[2]=true;
    }
    else
    {
        list_4[2]=false;
    }

    vector<string> lists;
    for (int i=0;i<list_1.size();i++)
    {
        if (list_1[i] == true)
        {
            lists.push_back(lists_1[i]);
        }

    }

    for (int i=0;i<list_2.size();i++)
    {
        if (list_2[i] == true)
        {
            lists.push_back(lists_2[i]);
        }

    }
    
    for (int i=0;i<list_3.size();i++)
    {
        if (list_3[i] == true)
        {
            lists.push_back(lists_3[i]);
        }

    }

    for (int i=0;i<list_4.size();i++)
    {
        if (list_4[i] == true)
        {
            lists.push_back(lists_4[i]);
        }

    }

    
    cout<<"Schedule:"<<endl;
    for (int i=0;i<lists.size();i++)
    {
        cout<<lists[i]<<endl;
    }

}


//-----------------------------------------------------------------------------------------------------------------

//Display system

void end_page(vector<double> Mark_list, status status_now)
{
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<"You have finished this semester's learning! Congratulations!"<<endl;
    cout<<"Shown below is the grade you get in this semester:"<<endl;
    print_mark(Mark_list,status_now);
}

void end_page_intermission(vector<double> Mark_list, status status_now)
{
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<"Oops! You just intermiss your this semester's study!"<<endl;
    cout<<"Shown below is the grade you get in this semester:"<<endl;
    print_mark(Mark_list,status_now);
}

void show_information(status status_now, Time time_now, session_timer &st, vector<vector<double> > & Mark_Data_Base)
{
    clear();
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<"Week "<<time_now.read_week()<<" "<<read_day(time_now.read_weekday())<<"                         "<<"Time: "<<time_now.get_hour()<<":00"<<endl;
    cout<<"Energy: "<<status_now.read_energy()<<"                            "<<"Emotion: "<<print_emotion(status_now.read_emotion())<<endl;
    cout<<"Mood: "<<status_now.read_mood()<<endl;
    int week_number = time_now.read_week();
    if (week_number>12)
    {
        week_number = 12;
    }
    cout<<"Ability: "<<" ENG1011: "<<setprecision(3)<<status_now.read_ability()[0]<<"/"<<week_number<<" ENG1012: "<<setprecision(3)<<status_now.read_ability()[1]<<"/"<<week_number<<" ENG1005: "<<setprecision(3)<<status_now.read_ability()[2]<<"/"<<week_number<<" FIT1045: "<<setprecision(3)<<status_now.read_ability()[3]<<"/"<<week_number<<endl;
    cout<<endl;
    time_system_schedule(time_now,st, Mark_Data_Base);
    cout<<endl;

}

void unit_information(status status_now, Time time_now, session_timer &sc, vector<vector<double> > & Mark_Data_Base)
{
    show_information(status_now,time_now,sc, Mark_Data_Base);
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"Unit information:"<<endl;
    cout<<"ENG1011:"<<endl;
    cout<<"Workshop  12:00pm ~ 14:00pm Monday Week1-12            Mark: "<<Mark_Data_Base[0][0]<<"/10"<<endl;
    cout<<"Practical 16:00pm ~ 18:00pm Thursday Week1-12          Mark: "<<Mark_Data_Base[0][1]<<"/5 "<<endl;
    cout<<"Content test1 18:00pm ~ 20:00pm Monday Week5           Mark: "<<Mark_Data_Base[0][2]<<"/7.5"<<endl;
    cout<<"Content test2 18:00pm ~ 20:00pm Monday Week10          Mark: "<<Mark_Data_Base[0][3]<<"/7.5"<<endl;
    cout<<"Project      Week 6 ~ 11    Total hour needed: 30h     Mark: "<<Mark_Data_Base[0][4]<<"/20"<<endl;
    cout<<"Final     14:00pm ~ 17:00pm Tuesday Week14             Mark: "<<Mark_Data_Base[0][5]<<"/50"<<endl;
    cout<<endl;
    cout<<"ENG1012:"<<endl;
    cout<<"Workshop  14:00pm ~ 16:00pm Wednesday Week1-12         Mark: "<<Mark_Data_Base[1][0]<<"/5"<<endl;
    cout<<"Practical 10:00am ~ 12:00pm Tuesday Week1-5 7-11       Mark: "<<Mark_Data_Base[1][1]<<"/10 "<<endl;
    cout<<"Interview 10:00am ~ 12:00pm Tuesday Week6              Mark: "<<Mark_Data_Base[1][2]<<"/10"<<endl;
    cout<<"Presentation 10:00am ~ 12:00pm Tuesday Week12          Mark: "<<Mark_Data_Base[1][3]<<"/15"<<endl;
    cout<<"Report1      Week 1 ~ 5    Total hour needed: 10h      Mark: "<<Mark_Data_Base[1][4]<<"/15"<<endl;
    cout<<"Video        Week 7 ~ 8    Total hour needed: 6h       Mark: "<<Mark_Data_Base[1][5]<<"/15"<<endl;
    cout<<"Report2      Week 9 ~ 13    Total hour needed: 20h     Mark: "<<Mark_Data_Base[1][6]<<"/20"<<endl;
    cout<<"Reflection   Week 11 ~ 13    Total hour needed: 6h     Mark: "<<Mark_Data_Base[1][7]<<"/10"<<endl;
    cout<<endl;
    cout<<"ENG1005:"<<endl;
    cout<<"Workshop  10:00am ~ 12:00pm Thursday Week1-6 8-12      Mark: 0"<<endl;
    cout<<"Practical 14:00pm ~ 16:00pm Friday   Week1-12          Mark: "<<Mark_Data_Base[2][0]<<"/5 "<<endl;
    cout<<"Mid-semester 10:00am ~ 12:00pm Thursday Week7          Mark: "<<Mark_Data_Base[2][1]<<"/20"<<endl;
    cout<<"Quiz per week      1h/per week   Week1-12              Mark: "<<Mark_Data_Base[2][2]<<"/5"<<endl;
    cout<<"Project            2h/per week   Week1-12              Mark: "<<Mark_Data_Base[2][3]<<"/20"<<endl;
    cout<<"Final     14:00pm ~ 17:00pm Friday  Week14             Mark: "<<Mark_Data_Base[2][4]<<"/50"<<endl;
    cout<<endl;
    cout<<"FIT1045:"<<endl;
    cout<<"Workshop  10:00am ~ 12:00pm Friday Week1-12            Mark: 0"<<endl;
    cout<<"Practical 12:00pm ~ 14:00pm Wednesday   Week1-12       Mark: 0"<<endl;
    cout<<"Project       Week1-13     Total hour needed: 120h     Mark: "<<Mark_Data_Base[3][0]<<"/100"<<endl;
    cout<<endl;

    cout<<"1. Quit"<<endl;
    int selection = read_integer("Option: ");
    while (selection != 1)
    {
        cout<<"Please enter the integer in span!"<<endl;
        selection = read_integer("Option: ");
    }
    

}



int show_unit(vector<bool> list, vector<string> lists)
{
    vector<int> listi(list.size());
    for (int i =0; i<list.size();i++) 
    {
        listi[i] = 0;
    }

    int n = 1;
    for (int i =0; i<list.size(); i++)
    {
        if (list[i])
        {
            cout<<n<<". "<<lists[i]<<endl;
            listi[i] = n;
            n++;
        }
    }
    n--;
    int selection = read_integer("Option: ");
    while (selection<1||selection>n)
    {
        cout<<"Please enter an integer in the span!"<<endl;
        selection = read_integer("Option: ");
    }

    for (int i =0; i<list.size(); i++)
    {
        if (listi[i] == selection)
        {
            return i;
        }
    }
    return -1;
}


void do_ENG1011(status &status_now, Time &time_now, vector<double> &Mark_list, session_timer &st, vector<vector<double> > & Mark_Data_Base)
{
    double old_energy = status_now.read_energy();
    double old_mood = status_now.read_mood();
    double new_energy = old_energy+1; //just make them different for the first_time
    double new_mood = old_mood+1;//just make them different for the first_time;
    

    while (true)
    {
        ENG1011 eng1011(status_now);
        
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<<"ENG1011"<<endl;
        vector<string> lists(8);
        lists[0] = "Workshop";
        lists[1] = "Practical";
        lists[2] = "Content test 1";
        lists[3] = "Content test 2";
        lists[4] = "Project";
        lists[5] = "Final";
        lists[6] = "Self learning";
        lists[7] = "Exit";
        vector<bool> list(8);
        //cout<<"Hello"<<endl;
        for (int i =0; i < list.size(); i++)
        {
            list[i] = true;
        }
        
        if (time_now.get_hour()==12 && time_now.read_week()>=1 && time_now.read_week()<=12 && time_now.read_weekday() == Monday)
        {
            list[0]=true;
        }
        else
        {
            list[0]=false;
        }

        if (time_now.get_hour()==16 && time_now.read_week()>=1 && time_now.read_week()<=12 && time_now.read_weekday() == Thursday)
        {
            list[1]=true;
        }
        else
        {
            list[1]=false;
        }

        if (time_now.get_hour()==18 && time_now.read_week()==5 && time_now.read_weekday() == Monday)
        {
            list[2]=true;
        }
        else
        {
            list[2]=false;
        }

        if (time_now.get_hour()==18 && time_now.read_week()==10 && time_now.read_weekday() == Monday)
        {
            list[3]=true;
        }
        else
        {
            list[3]=false;
        }

        if (time_now.read_week()>=6 &&time_now.read_week()<=11 && st.ENG1011_project_timer<30)
        {
            list[4]=true;
        }
        else
        {
            list[4]=false;
        }

        if (time_now.get_hour()==14 && time_now.read_week()==14 && time_now.read_weekday() == Tuesday)
        {
            list[5]=true;
        }
        else
        {
            list[5]=false;
        }

        //cout<<"Hello!!!"<<endl;

        if(old_energy==new_energy&&old_mood==new_mood)
        {
            
            cout<<endl;
            cout<<"You don't have enough mood/energy to paricipate in this activity!"<<endl;
            cout<<endl;
        }

        old_energy = status_now.read_energy();
        old_mood = status_now.read_mood();

        switch (show_unit(list,lists))
        {
            case 0:
                
                participate(eng1011.list()[0],status_now,time_now,Mark_list);

                Mark_Data_Base[0][0] += 10/12.00;
                break;
            case 1:
                participate(eng1011.list()[1],status_now,time_now,Mark_list);
                Mark_Data_Base[0][1] += 5/12.00;
                break;
            case 2:
                participate(eng1011.list()[3],status_now,time_now,Mark_list);
                Mark_Data_Base[0][2] += test_result(status_now.read_ability()[0],5.0)*7.5;
                break;
            case 3:
                participate(eng1011.list()[4],status_now,time_now,Mark_list);
                Mark_Data_Base[0][3] += test_result(status_now.read_ability()[0],10.0)*7.5;
                break;
            case 4:
                participate(eng1011.list()[6],status_now,time_now,Mark_list,st.ENG1011_project_timer);
                Mark_Data_Base[0][4] += 20/30.00;
                break;
            case 5:
                participate(eng1011.list()[5],status_now,time_now,Mark_list);
                Mark_Data_Base[0][5] += test_result(status_now.read_ability()[0],12.0)*50;
                break;
            case 6:
                participate(eng1011.list()[2],status_now,time_now,Mark_list);
                break;
            case 7:
                clear();
                show_information(status_now,time_now, st, Mark_Data_Base);
                return;
        }
        new_energy = status_now.read_energy();
        new_mood = status_now.read_mood();

        show_information(status_now,time_now, st, Mark_Data_Base);


    }
}

void do_ENG1012(status &status_now, Time &time_now, vector<double> &Mark_list, session_timer &st, vector<vector<double> > & Mark_Data_Base)
{
    double old_energy = status_now.read_energy();
    double old_mood = status_now.read_mood();
    double new_energy = old_energy+1; //just make them different for the first_time
    double new_mood = old_mood+1;//just make them different for the first_time;

    while (true)
    {
        ENG1012 eng1012(status_now);
        
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<<"ENG1012"<<endl;
        vector<string> lists(11);
        lists[0] = "Workshop";
        lists[1] = "Practical";
        lists[2] = "Interview";
        lists[3] = "Presentation";
        lists[4] = "Report1";
        lists[5] = "Video";
        lists[6] = "Report2";
        lists[7] = "Reflection";
        lists[8] = "Workshop (Attendance Mark: 5)";
        lists[9] = "Self learning";
        lists[10] = "Exit";
        vector<bool> list(11);
 
        for (int i =0; i < list.size(); i++)
        {
            list[i] = true;
        }
        
        if (time_now.get_hour()==14 && time_now.read_week()>=1 && time_now.read_week()<=11 && time_now.read_weekday() == Wednesday)
        {
            list[0]=true;
        }
        else
        {
            list[0]=false;
        }

        if (time_now.get_hour()==10 && ((time_now.read_week()>=1 && time_now.read_week()<=5)||(time_now.read_week()>=7 && time_now.read_week()<=11)) && time_now.read_weekday() == Tuesday)
        {
            list[1]=true;
        }
        else
        {
            list[1]=false;
        }

        if (time_now.get_hour()==10 && time_now.read_week()==6 && time_now.read_weekday() == Tuesday)
        {
            list[2]=true;
        }
        else
        {
            list[2]=false;
        }

        if (time_now.get_hour()==10 && time_now.read_week()==12 && time_now.read_weekday() == Tuesday)
        {
            list[3]=true;
        }
        else
        {
            list[3]=false;
        }

        if (time_now.read_week()>=1 &&time_now.read_week()<=5 && st.ENG1012_report1_timer<10)
        {
            list[4]=true;
        }
        else
        {
            list[4]=false;
        }

        if (time_now.read_week()>=7 &&time_now.read_week()<=8 && st.ENG1012_video_timer<6)
        {
            list[5]=true;
        }
        else
        {
            list[5]=false;
        }

        if (time_now.read_week()>=9 &&time_now.read_week()<=13 && st.ENG1012_video_timer<20)
        {
            list[6]=true;
        }
        else
        {
            list[6]=false;
        }

        if (time_now.read_week()>=11 &&time_now.read_week()<=13 && st.ENG1012_video_timer<6)
        {
            list[7]=true;
        }
        else
        {
            list[7]=false;
        }

        if (time_now.get_hour()==14 && time_now.read_week()==12 && time_now.read_weekday() == Wednesday)
        {
            list[8]=true;
        }
        else
        {
            list[8]=false;
        }

        if(old_energy==new_energy&&old_mood==new_mood)
        {
            
            cout<<endl;
            cout<<"You don't have enough mood/energy to paricipate in this activity!"<<endl;
            cout<<endl;
        }

        old_energy = status_now.read_energy();
        old_mood = status_now.read_mood();

        switch (show_unit(list,lists))
        {
            case 0:
                participate(eng1012.list()[0],status_now,time_now,Mark_list);
                break;
            case 1:
                participate(eng1012.list()[2],status_now,time_now,Mark_list);
                Mark_Data_Base[1][1] += 10/10.00;
                break;
            case 2:
                participate(eng1012.list()[4],status_now,time_now,Mark_list);
                Mark_Data_Base[1][2] += 10*test_result(status_now.read_ability()[1],6.0);
                break;
            case 3:
                participate(eng1012.list()[9],status_now,time_now,Mark_list);
                Mark_Data_Base[1][3] += 15*test_result(status_now.read_ability()[1],12.0);
                break;
            case 4:
                participate(eng1012.list()[5],status_now,time_now,Mark_list,st.ENG1012_report1_timer);
                Mark_Data_Base[1][4] +=  15/10.00;
                break;
            case 5:
                participate(eng1012.list()[7],status_now,time_now,Mark_list,st.ENG1012_video_timer);
                Mark_Data_Base[1][5] += 15/6.00;
                break;
            case 6:
                participate(eng1012.list()[6],status_now,time_now,Mark_list,st.ENG1012_report2_timer);
                Mark_Data_Base[1][6] += 20/20.00;
                break;
            case 7:
                participate(eng1012.list()[8],status_now,time_now,Mark_list,st.ENG1012_reflection_timer);
                Mark_Data_Base[1][7] += 10/6.00;
                break;
            case 8:
                participate(eng1012.list()[1],status_now,time_now,Mark_list);
                Mark_Data_Base[1][0] += 5;
                break;
            case 9:
                participate(eng1012.list()[3],status_now,time_now,Mark_list);
                break;
            case 10:
                clear();
                show_information(status_now,time_now,st, Mark_Data_Base);
                return;
        }
        new_energy = status_now.read_energy();
        new_mood = status_now.read_mood();

        show_information(status_now,time_now,st, Mark_Data_Base);


    }
}


void do_ENG1005(status &status_now, Time &time_now, vector<double> &Mark_list, session_timer &st, vector<vector<double> > & Mark_Data_Base)
{
    double old_energy = status_now.read_energy();
    double old_mood = status_now.read_mood();
    double new_energy = old_energy+1; //just make them different for the first_time
    double new_mood = old_mood+1;//just make them different for the first_time;

    while (true)
    {
        ENG1005 eng1005(status_now,time_now);
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<<"ENG1005"<<endl;
        vector<string> lists(8);
        lists[0] = "Workshop";
        lists[1] = "Practical";
        lists[2] = "Mid-semester";
        lists[3] = "Quiz per week";
        lists[4] = "Project";
        lists[5] = "Final";
        lists[6] = "Self learning";
        lists[7] = "Exit";
        vector<bool> list(8);
        //cout<<"Hello"<<endl;
        for (int i =0; i < list.size(); i++)
        {
            list[i] = true;
        }
        
        if (time_now.get_hour()==10 && time_now.read_week()>=1 && ((time_now.read_week()>=1 && time_now.read_week()<=6)||(time_now.read_week()>=8 && time_now.read_week()<=12)) && time_now.read_weekday() == Thursday)
        {
            list[0]=true;
        }
        else
        {
            list[0]=false;
        }

        if (time_now.get_hour()==14 && time_now.read_week()>=1 && time_now.read_week()<=12 && time_now.read_weekday() == Friday)
        {
            list[1]=true;
        }
        else
        {
            list[1]=false;
        }

        if (time_now.get_hour()==10 && time_now.read_week()==7 && time_now.read_weekday() == Thursday)
        {
            list[2]=true;
        }
        else
        {
            list[2]=false;
        }

        if (time_now.read_week()>=1 && time_now.read_week()<=12 && st.ENG1005_quiz_timer<time_now.read_week())
        {
            list[3]=true;
        }
        else
        {
            list[3]=false;
        }

        if (time_now.read_week()>=1 && time_now.read_week()<=12 && st.ENG1005_project_timer<time_now.read_week())
        {
            list[4]=true;
        }
        else
        {
            list[4]=false;
        }

        if (time_now.get_hour()==14 && time_now.read_week()==14 && time_now.read_weekday() == Friday)
        {
            list[5]=true;
        }
        else
        {
            list[5]=false;
        }

        if(old_energy==new_energy&&old_mood==new_mood)
        {
            
            cout<<endl;
            cout<<"You don't have enough mood/energy to paricipate in this activity!"<<endl;
            cout<<endl;
        }

        old_energy = status_now.read_energy();
        old_mood = status_now.read_mood();

        switch (show_unit(list,lists))
        {
            case 0:
                participate(eng1005.list()[0],status_now,time_now,Mark_list);
                break;
            case 1:
                participate(eng1005.list()[1],status_now,time_now,Mark_list);
                Mark_Data_Base[2][0] += 5/12.00*test_result(status_now.read_ability()[2],time_now.read_week());
                break;
            case 2:
                participate(eng1005.list()[5],status_now,time_now,Mark_list);
                Mark_Data_Base[2][1] += 20*test_result(status_now.read_ability()[2],time_now.read_week());
                break;
            case 3:
                participate(eng1005.list()[3],status_now,time_now,Mark_list,st.ENG1005_quiz_timer);
                Mark_Data_Base[2][2] += 5/12.00*test_result(status_now.read_ability()[2],time_now.read_week());
                break;
            case 4:
                participate(eng1005.list()[4],status_now,time_now,Mark_list,st.ENG1005_project_timer);
                Mark_Data_Base[2][3] += 20/12.00*test_result(status_now.read_ability()[2],time_now.read_week());
                break;
            case 5:
                participate(eng1005.list()[6],status_now,time_now,Mark_list);
                 Mark_Data_Base[2][4] += 50*test_result(status_now.read_ability()[2],time_now.read_week());
                break;
            case 6:
                participate(eng1005.list()[2],status_now,time_now,Mark_list);
                break;
            case 7:
                clear();
                show_information(status_now,time_now,st,Mark_Data_Base);
                return;
        }
        new_energy = status_now.read_energy();
        new_mood = status_now.read_mood();

        show_information(status_now,time_now,st,Mark_Data_Base);


    }
}


void do_FIT1045(status &status_now, Time &time_now, vector<double> &Mark_list, session_timer &st, vector<vector<double> > & Mark_Data_Base)
{
    double old_energy = status_now.read_energy();
    double old_mood = status_now.read_mood();
    double new_energy = old_energy+1; //just make them different for the first_time
    double new_mood = old_mood+1;//just make them different for the first_time;

    while (true)
    {
        FIT1045 fit1045(status_now,time_now);
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<<"FIT1045"<<endl;
        vector<string> lists(5);
        lists[0] = "Workshop";
        lists[1] = "Practical";
        lists[2] = "Project";
        
        lists[3] = "Self learning";
        lists[4] = "Exit";
        vector<bool> list(5);
        for (int i =0; i < list.size(); i++)
        {
            list[i] = true;
        }
        
        if (time_now.get_hour()==10 && (time_now.read_week()>=1 && time_now.read_week()<=12) && time_now.read_weekday() == Friday)
        {
            list[0]=true;
        }
        else
        {
            list[0]=false;
        }

        if (time_now.get_hour()==12 && time_now.read_week()>=1 && time_now.read_week()<=12 && time_now.read_weekday() == Wednesday)
        {
            list[1]=true;
        }
        else
        {
            list[1]=false;
        }

        if (time_now.read_week()>=1 && time_now.read_week()<=13 && st.FIT1045_project_timer<120)
        {
            list[2]=true;
        }
        else
        {
            list[2]=false;
        }

        if(old_energy==new_energy&&old_mood==new_mood)
        {
            
            cout<<endl;
            cout<<"You don't have enough mood/energy to paricipate in this activity!"<<endl;
            cout<<endl;
        }

        old_energy = status_now.read_energy();
        old_mood = status_now.read_mood();

        switch (show_unit(list,lists))
        {
            case 0:
                participate(fit1045.list()[0],status_now,time_now,Mark_list);
                break;
            case 1:
                participate(fit1045.list()[1],status_now,time_now,Mark_list);
                break;
            case 2:
                participate(fit1045.list()[3],status_now,time_now,Mark_list,st.FIT1045_project_timer);
                Mark_Data_Base[3][0]+= 100/120.00;
                break;
            case 3:
                participate(fit1045.list()[2],status_now,time_now,Mark_list);
                break;
            case 4:
                clear();
                show_information(status_now,time_now,st, Mark_Data_Base);
                return;
        }
        new_energy = status_now.read_energy();
        new_mood = status_now.read_mood();

        show_information(status_now,time_now,st, Mark_Data_Base);
    }

}

void main_option0(int hour, vector<bool> &option_can_choose) // -1
{
    if (hour>=9&&hour<=19)
    {
        cout<<"-1. Relax"<<endl;
        option_can_choose[0] = true;
    }
    else if (hour>=6 &&hour<=7)
    {
        cout<<"-1. Snooze"<<endl;
        option_can_choose[0] = true;
    }

    else if (hour>=20 || hour<6)
    {
        cout<<"-1. Sleep"<<endl;
        option_can_choose[0] = true;
    }

    else
    {
        option_can_choose[0] = false;
    }
}

void do_option0(status &status_now, Time &time_now, vector<double> &Mark_list, cuisine_timer &ct) // -1
{
    int hour = time_now.get_hour();

    if (hour>=9&&hour<=19)
    {
        relax(status_now, time_now, Mark_list);
    }
    else if (hour>=6 &&hour<=7)
    {
        snooze_for_a_while(status_now, time_now, Mark_list);
    }

    else if (hour>=20 || hour<6) 
    {
        sleep(status_now, time_now,ct);
    }

}

void main_option1(int hour, vector<bool> &option_can_choose) // 0
{
    if (hour>=2 && hour <6)
    {
        option_can_choose[1] = false;
    }
    else
    {
        cout<<"0. Study"<<endl;
        option_can_choose[1] = true;
    }
}

void do_option1(status &status_now, Time &time_now, vector<double> &Mark_list, bool &intermission, session_timer &st,vector<vector<double> > & Mark_Data_Base)
{
    bool option_1_quit =false;

    while (option_1_quit == false)
    {
        show_information(status_now,time_now,st, Mark_Data_Base);
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<<"Study"<<endl;
        cout<<"0. Unit information"<<endl;
        cout<<"1. ENG1011"<<endl;
        cout<<"2. ENG1012"<<endl;
        cout<<"3. ENG1005"<<endl;
        cout<<"4. FIT1045"<<endl;
        cout<<"5. Quit"<<endl;
        cout<<"-1. Intermission"<<endl;

        const int MAX = 5;

        int selection = read_integer("Option: ");
        while (selection<-1 || selection>MAX)
        {
            cout<<"Please enter an integer in the range!"<<endl;
            selection = read_integer("Option: ");
        }
        switch (selection)
        {
            case -1:
                intermission = true;
                return;

            case 0:
                unit_information(status_now,time_now,st, Mark_Data_Base);
                break;
            case 1:
                do_ENG1011(status_now, time_now, Mark_list,st, Mark_Data_Base);
                break;
            case 2:
                do_ENG1012(status_now, time_now, Mark_list,st, Mark_Data_Base);
                break;
            case 3:
                do_ENG1005(status_now, time_now, Mark_list,st, Mark_Data_Base);
                break;
            case 4:
                do_FIT1045(status_now, time_now, Mark_list,st, Mark_Data_Base);
                break;
            case 5:
                option_1_quit = true;
                break;
        }
    }
}

void main_option2(int hour, vector<bool> &option_can_choose, cuisine_timer &ct)// 1
{
    if (hour>=7&&hour<=9&&ct.breakfast_chance==1)
    {
        cout<<"1. Have Breakfast"<<endl;
        option_can_choose[2] = true;
    }
    else if (hour>=11 &&hour<=13&&ct.lunch_chance==1)
    {
        cout<<"1. Have lunch"<<endl;
        option_can_choose[2] = true;
    }

    else if (hour>=17 && hour<=19&&ct.dinner_chance==1)
    {
        cout<<"1. Have dinner"<<endl;
        option_can_choose[2] = true;
    }

    else
    {
        option_can_choose[2] = false;
    }
}

void do_option2(status &status_now, Time &time_now, vector<double> &Mark_list, cuisine_timer &ct) // 1
{
    int hour = time_now.get_hour();
    if (hour>=7&&hour<=9&&ct.breakfast_chance == 1)
    {
        have_breakfast(status_now, time_now, Mark_list);
        ct.breakfast_chance--;
    }
    else if (hour>=11 &&hour<=13&&ct.lunch_chance == 1)
    {
        have_lunch(status_now, time_now, Mark_list);
        ct.lunch_chance--;
    }

    else if (hour>=17 && hour<=19&&ct.dinner_chance == 1)
    {
        have_dinner(status_now, time_now, Mark_list);
        ct.dinner_chance--;
    }

}





void main_page(status &status_now, Time &time_now, vector<double> &Mark_list, session_timer & st, cuisine_timer & ct, vector<vector<double> > & Mark_Data_Base)
{
    double old_energy = status_now.read_energy();
    double old_mood = status_now.read_mood();
    double new_energy = old_energy+1; //just make them different for the first_time
    double new_mood = old_mood+1;//just make them different for the first_time;
    bool intermission = false;
    
    while (true)
    {
        
        show_information(status_now,time_now,st, Mark_Data_Base);

        if(old_energy==new_energy&&old_mood==new_mood&&new_energy!=100&&new_mood!=120)
        {
            
            cout<<endl;
            cout<<"You don't have enough mood/energy to paricipate in this activity!"<<endl;
            cout<<endl;
        }

        vector<bool> option_can_choose(3);
        option_can_choose[0] = true;
        option_can_choose[1] = true;
        option_can_choose[2] = true;
        main_option0(time_now.get_hour(),option_can_choose);
        main_option1(time_now.get_hour(),option_can_choose);
        main_option2(time_now.get_hour(),option_can_choose,ct);
        int selection = read_integer("Option: ")+1;
        while (selection<0||selection>2||option_can_choose[selection]==false)
        {
            cout<<"Please enter an integer in the span!"<<endl;
            selection = read_integer("Option: ")+1;
        }
        selection --;

        old_energy = status_now.read_energy();
        old_mood = status_now.read_mood();

        switch (selection)
        {
            case -1:
                do_option0(status_now,time_now,Mark_list, ct);
                
                break;
            case 0:
                do_option1(status_now,time_now,Mark_list,intermission,st, Mark_Data_Base);
                break;

            case 1:
                do_option2(status_now,time_now,Mark_list,ct);
                break;
        }

        new_energy = status_now.read_energy();
        new_mood = status_now.read_mood();



        if (time_now.read_week() ==14 && time_now.read_weekday() ==Saturday)
        {
            clear();
            end_page(Mark_list, status_now);
            string exit;
            cout<<"Enter anything to exit!"<<endl;
            cin>>exit;
            clear();
            break;
        }

        if (intermission)
        {
            clear();
            end_page_intermission(Mark_list, status_now);
            string exit;
            cout<<"Enter anything to exit!"<<endl;
            cin>>exit;
            clear();
            break;
        }


    }

}



void Entry_pages(status &status_now, Time &time_now, vector<double> &Mark_list, session_timer &st, cuisine_timer &ct,vector<vector<double> > & Mark_Data_Base)
{
    clear();
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"                           Monash simulator                                      "<<endl;
    cout<<"1.Start                                                          "<<endl;
    cout<<"2.Quit"<<endl;

    int selection = read_integer("Option:");
    while (selection !=1 && selection !=2 )
    {
        cout<<"Please enter an integer in the span!"<<endl;
        selection = read_integer("Option:");
    }
    if (selection == 1)
    {
        clear();
        main_page(status_now, time_now, Mark_list,st,ct, Mark_Data_Base);
    }
    else if (selection == 2)
    {
        clear();
        return;
    }
    
}

//-----------------------------------------------------------------------------------------------------------------
//main function 
int main()
{
    
    vector<double> Mark_Data_Base_1(SIZE1);

    vector<double> Mark_Data_Base_2(SIZE2);

    vector<double> Mark_Data_Base_3(SIZE3);

    vector<double> Mark_Data_Base_4(SIZE4);

    vector<vector<double> > Mark_Data_Base(SIZEDB); 

    for(int i=0;i<6;i++)
    {
        Mark_Data_Base_1[i] = 0;
    }

    for(int i=1;i<8;i++)
    {
        Mark_Data_Base_2[i] = 0;
    }

    for(int i=2;i<5;i++)
    {
        Mark_Data_Base_3[i] = 0;
    }

    for(int i=3;i<1;i++)
    {
        Mark_Data_Base_4[i] = 0;
    }

    Mark_Data_Base[0] = Mark_Data_Base_1;
    Mark_Data_Base[1] = Mark_Data_Base_2;
    Mark_Data_Base[2] = Mark_Data_Base_3;
    Mark_Data_Base[3] = Mark_Data_Base_4;
    
    cuisine_timer ct;
    session_timer st;
    Time time_now(6,Monday,1);
    ability a(0,0,0,0);
    status status_1(100,100,a,Welbeing);
    vector<double> mark_list = read_vector4double(0,0,0,0);
    Entry_pages(status_1, time_now, mark_list, st, ct, Mark_Data_Base);

}