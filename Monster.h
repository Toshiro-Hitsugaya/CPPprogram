class Monster
{
private:
    double HP;
    bool live;
    double speed;
public:
    Monster(double hp);
    void attacked(double d);
    void reduceSpeed(double d);
    double get_x();
    double get_y();
    ~Monster();
};

Monster::Monster(double hp):HP(hp), live(true)
{

}

inline void Monster::attacked(double d)
{
    if(live) HP-=d;
    if(HP<0){
        HP=0;
        live=false;
    }
}

inline void Monster::reduceSpeed(double d)
{
    speed-=d;
}

inline double Monster::get_x()
{
    return 0;
}

inline double Monster::get_y()
{
    return 0;
}

Monster::~Monster()
{
}
