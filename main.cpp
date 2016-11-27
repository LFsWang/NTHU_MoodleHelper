#include<bits/stdc++.h>
//Consts
using math_t = long double;
constexpr math_t pi = atan(1)*4;

struct _stold{
    double operator()(std::string s){
        return std::stold(s);
    }
};
struct _stoi{
    int operator()(std::string s){
        return std::stod(s);
    }
};

template<typename T=math_t,class Conv=_stold>
bool input(std::string hint,T &in)
{
    std::string buf;
    bool flag;
    Conv cnv;
    do{
        flag = true;
        try{
            std::cout<<hint<<":";
            std::cin>>buf;
            in = cnv(buf);
        }catch(...)
        {
            flag = false;
        }
    }while(!flag);
    return true;
}

struct Problem{
    using val_t = std::map<std::string,math_t>;
    using func = void(val_t);
    
    std::vector<std::pair<std::string,std::string>> in;
    val_t v;
    func* run;

    Problem(){}
    Problem(decltype(in) i,func* f):in(i),run(f){}
    void prepare(){
        for(const auto &p:in)
        {
            input(p.second,v[p.first]);
        }
    }
    void solve(){
        if(!run){
            std::cout<<"No Solver!"<<std::endl;
            return;
        }
        std::cout<<std::endl;
        run(v);
        std::cout<<"========="<<std::endl;
    }
};

void Q10_1(Problem::val_t v)
{
    math_t M = v["Ms"] * v["times"];
    math_t R = pow( 3*M/(4*pi*v["Ro"]) , 1.0/3 );//M = 4/3 R^3 * pi
    math_t I = 2.0/5.0*M*R*R;//I = kMR^2 k=2/5 if is solid ball
    math_t tor = I * v["dwdt"];//Tor = Ia ex like F=ma
    std::cout<<"Estimate B =  "<<tor*1E-33<<std::endl;
}

void Q10_2(Problem::val_t v)
{
    math_t m = v["M"]/1000;//to kg
    math_t r = v["r"]/100;//to m
    math_t Km = m*v["v"]*v["v"]/2;//1/2mv^2
    math_t I = 2.0/5.0*m*r*r;//I = kMR^2 k=2/5 if is solid ball
    math_t Kt = I*v["w"]*v["w"]/2;//1/2Iw^2
    math_t prt = 100*Kt/(Kt+Km);
    std::cout<<"fraction(%) =  "<<prt<<std::endl;
}

void Q10_3(Problem::val_t v)
{
    math_t edg = v["R"]*pi;
    math_t rpm = v["V"]*100*60/edg;
    std::cout<<"rpm =  "<<rpm<<std::endl;
}
int main()
{
    std::map<std::pair<int,int>,Problem> problems;
    problems[{10,1}] = Problem(
        {
            {"Ms","�Ӷ���q(the mass of Sun)",},
            {"times","����(? times the Sun��s mass)"},
            {"Ro","�K��(uniform density of ? )"},
            {"dwdt","��t�v(spin-down rate is ? )"},
        },Q10_1
    );
    problems[{10,2}] = Problem(
        {
            {"M","�y��q(A ?-g baseball)",},
            {"v","�t��(pitched at ?)"},
            {"w","��t(spinning at ?)"},
            {"r","�b�|(solid sphere of radius ?)"},
        },Q10_2
    );
    problems[{10,3}] = Problem(
        {
            {"V","Ū���t��(linear speed of ?)",},
            {"R","���|(cm-diameter CD)"},
        },Q10_3
    );
    
    int id,pid;

    std::cout<<"Input tip: 1.2^10-5 �п�J 1.2E-5"<<std::endl;
    while(true){
        input<int,_stoi>("�п�J���`",id);
        input<int,_stoi>("�п�J�D��",pid);
        if( problems.find({id,pid}) == problems.end() ){
            std::cout<<"No such problem!"<<std::endl;
            continue;
        }
        problems[{id,pid}].prepare();
        problems[{id,pid}].solve();
        std::cout<<std::endl;
    }
}

