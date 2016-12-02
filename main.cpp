#include<bits/stdc++.h>
//Consts
using math_t = long double;
constexpr math_t pi = atan(1)*4;

static math_t rad(math_t deg)
{
    return deg/180*pi;
}

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

void Q10_4(Problem::val_t v)
{
    // Mgh = 1/2 MVV + 1/2 Iww
    //   I = kMR^2 k=2/3 if is hollow
    // 2Mgh = MVV + 2/3 MRRww
    // 2gh = VV + 2/3 RRww
    //   V = wR
    // 2gh = VV + 2/3VV
    // V = sqrt( 6/5gh ) and h = d*sin(deg)
    constexpr math_t g = 9.8;
    math_t V = sqrt( 6.0/5*g*v["d"]*sin(rad(v["deg"])) );
    std::cout<<"v =  "<<V<<std::endl;
}

void Q10_5(Problem::val_t v)
{
    // By Q4 V^2 = 2gh/(1+k) k = 2/5 if is solid ball
    // V=2gh (slipping)
    // h = V/2g = 2gh/(1+k) / 2g = h/(1+k)
    math_t h2 = v["h"]/(1+2.0/5);
    std::cout<<"h =  "<<h2<<std::endl;
}

void Q10_6(Problem::val_t v)
{
    //all = 1/2MRR
    //del = 1/2
    //ans = all-del
    math_t ans = 1.0/2- 3.0/2/(pow(v["r"],4));
    std::cout<<"Y =  "<<ans<<std::endl;
}

void Q11_1(Problem::val_t v)
{
    //L=Iw
    math_t m = v["m"]/1000;//to KG
    math_t r = v["R"]/100/2;//to cm to Radius
    math_t I = 2.0/5.0*m*r*r;//I = kMR^2 k=2/5 if is solid ball
    math_t rad = v["rpm"]*2*pi/60;//to rad per sec
    std::cout<<"Angular momentum =  "<<I*rad*1E2<<std::endl;
}

void Q11_2(Problem::val_t v)
{
    //Iw=Iw
    math_t r = v["R"]/2;//to Radius
    math_t In = v["I"] + 4.0*v["M"]*r*r;
    math_t ans = v["I"]*v["rpm"]*2*pi/In;
    std::cout<<"angular speed =  "<<ans<<std::endl;
}

void Q11_3(Problem::val_t v)
{
    //Iw=Iw, 
    math_t r = v["R"]/2;//to Radius
    math_t rado = v["rpm"]*2*pi;//to rad
    math_t In = v["I"] + 4.0*v["M"]*r*r;
    math_t radn = v["I"]*rado/In;
    //J = 1/2 Iww
    math_t ans = ( v["I"]*rado*rado - In*radn*radn )*0.5;
    std::cout<<"total energy lost=  "<<ans*1E-2<<std::endl;
}
void Q11_4(Problem::val_t v)
{
    //S = V0t+1/2att
    //  a = (V-V0)/t
    //  V=0, a=-V0/t
    //S = V0t-1/2V0t = 1/2V0t
    //t = 2S/V0
    math_t S = v["d"]/100; //to meter
    math_t M = v["M"]/1000;//t kg
    math_t R = v["R"]/100;//to meter
    math_t t = 2*S/v["V"];
    math_t F = M*v["V"]/t;//F=ma
    math_t T = F*R;//Tor=F*R
    std::cout<<"torque =  "<<T*1E-3<<std::endl;
}

void Q11_5(Problem::val_t v)
{
    math_t M = v["M"]/1000;//t kg
    math_t d1 = v["d1"]/100;//to meter
    math_t d2 = v["d2"]/100;//to meter
    //Id = Icm + M*d*d;
    math_t IP = v["I"]+M*d1*d1;
    //wr = V
    math_t w = v["V"]/(d1+d2);
    //P = Iw
    math_t P = IP*w;
    std::cout<<"P angular momentum =  "<<P<<std::endl;
}


int main()
{
    std::map<std::pair<int,int>,Problem> problems;
    problems[{10,1}] = Problem(
        {
            {"Ms","太陽質量(the mass of Sun)",},
            {"times","倍數(? times the Sun’s mass)"},
            {"Ro","密度(uniform density of ? )"},
            {"dwdt","減速率(spin-down rate is ? )"},
        },Q10_1
    );
    problems[{10,2}] = Problem(
        {
            {"M","球質量(A ?-g baseball)",},
            {"v","速度(pitched at ?)"},
            {"w","轉速(spinning at ?)"},
            {"r","半徑(solid sphere of radius ?)"},
        },Q10_2
    );
    problems[{10,3}] = Problem(
        {
            {"V","讀取速度(linear speed of ?)",},
            {"R","直徑(cm-diameter CD)"},
        },Q10_3
    );
    problems[{10,4}] = Problem(
        {
            {"deg","傾角inclined at angle = ?"},
            {"d","斜面距離gone a distance d = ?"},
        },Q10_4
    );
    problems[{10,5}] = Problem(
        {
            {"h","初始高度starts at rest at height h = ?"},
        },Q10_5
    );
    problems[{10,6}] = Problem(
        {
            {"r","挖掉大小a hole of radius R/? is drilled"},
        },Q10_6
    );
    problems[{11,1}] = Problem(
        {
            {"R","直徑A ?-cm-diameter baseball"},
            {"m","重量mass ? g"},
            {"rpm","轉速spinning at ? rpm"},
        },Q11_1
    );
    problems[{11,2}] = Problem(
        {
            {"R","直徑?-m-diameter merry-go-round"},
            {"I","轉動慣量rotational inertia ?"},
            {"rpm","轉速? rev/s"},
            {"M","P孩重量?-kg children"},
        },Q11_2
    );
    problems[{11,3}] = problems[{11,2}];
    problems[{11,3}].run = Q11_3;
    problems[{11,4}] = Problem(
        {
            {"M","球重量?-g baseball"},
            {"V","球速moving horizontally at ?"},
            {"R","手長 ?cm from the player's shoulder"},
            {"d","後退距離recoils ? cm horizontally"},
        },Q11_4
    );
    problems[{11,5}] = Problem(
        {
            {"d1","d1=?"},
            {"d2","d2=?"},
            {"M","球棒重 ?-g wooden baseball bat "},
            {"I","質心轉動慣量 rotational inertia about its center of mass is ?"},
            {"V","轉速 its far end moves at ?"},
        },Q11_5
    );
    
    int id,pid;

    std::cout<<"Input tip: 1.2^10-5 請輸入 1.2E-5"<<std::endl;
    while(true){
        input<int,_stoi>("請輸入章節",id);
        input<int,_stoi>("請輸入題號",pid);
        if( problems.find({id,pid}) == problems.end() ){
            std::cout<<"No such problem!"<<std::endl;
            continue;
        }
        problems[{id,pid}].prepare();
        problems[{id,pid}].solve();
        std::cout<<std::endl;
    }
}

