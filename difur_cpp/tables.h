#include <vector>
#define ld long double
const std::vector<std::vector<ld>> dorman_prince_5_table = {
    {1.0 / 5.0},
    {3.0 / 40.0, 9.0 / 40.0},
    {44.0 / 45.0, -56.0 / 15.0, 32.0 / 9.0},
    {19372.0 / 6561.0, -25360.0 / 2187.0, 64448.0 / 6561.0, -212.0 / 729.0},
    {9017.0 / 3168.0, -355.0 / 33.0, 46732.0 / 5247.0, 49.0 / 176.0, -5103.0 / 18656.0},
    {35.0 / 384.0, 0, 500.0 / 1113.0, 125.0 / 192.0, -2187.0 / 6784.0, 11.0 / 84.0}
};

const std::vector<std::vector<ld>> dorman_prince_8_table = {
    {0},
    {1.0 / 18.0},
    {1.0 / 48.0, 1.0 / 16.0},
    {1.0 / 32.0, 0.0, 3.0 / 32.0},
    {5.0 / 16.0, 0.0, -75.0 / 64.0, 75.0 / 64.0},
    {3.0 / 80.0, 0.0, 0.0, 3.0 / 16.0, 3.0 / 20.0},
    {29443841.0 / 614563906.0, 0.0, 0.0, 77736538.0 / 692538347.0, -28693883.0 / 1125000000.0, 23124283.0 / 1800000000.0},
    {16016141.0 / 946692911.0, 0.0, 0.0, 61564180.0 / 158732637.0, 22789713.0 / 633445777.0, 545815736.0 / 2771057229.0, -180193667.0 / 1043307555.0},
    {39632708.0 / 573591083.0, 0.0, 0.0, -433636366.0 / 683701615.0, -421739975.0 / 2616292301.0, 100302831.0 / 723423059.0, 790204164.0 / 839813087.0, 800635310.0 / 3783071287.0},
    {246121993.0 / 1340847787.0, 0.0, 0.0, -37695042795.0 / 15268766246.0, -309121744.0 / 1061227803.0, -12992083.0 / 490766935.0, 6005943493.0 / 2108947869.0, 393006217.0 / 1396673457.0, 123872331.0 / 1001029789.0},
    {-1028468189.0 / 846180014.0, 0.0, 0.0, 8478235783.0 / 508512852.0, 1311729495.0 / 1432422823.0, -10304129995.0 / 1701304382.0, -48777925059.0 / 3047939560.0, 15336726248.0 / 1032824649.0, -45442868181.0 / 3398467696.0, 3065993473.0 / 597172653.0},
    {185892177.0 / 718116043.0, 0.0, 0.0, -3185094517.0 / 667107341.0, -477755414.0 / 1098053517.0, -703635378.0 / 230739211.0, 5731566787.0 / 1027545527.0, 5232866602.0 / 850066563.0, -4093664535.0 / 808688257.0, 3962137247.0 / 1805957418.0, 65686358.0 / 487910083.0},
    {403863854.0 / 491063109.0, 0.0, 0.0, -5068492393.0 / 434740067.0, -411421997.0 / 543043805.0, 652783627.0 / 914296604.0, 11173962825.0 / 925320556.0, -13158990841.0 / 6184727034.0, 3936647629.0 / 1978049680.0, -160528059.0 / 685178525.0, 248638103.0 / 1413531060.0, 0.0},
    {14005451.0 / 335480064.0, 0.0, 0.0, 0.0, 0.0, -59238493.0 / 1068277825.0, 181606767.0 / 758867731.0, 561292985.0 / 797845732.0, -1041891430.0 / 1371343529.0, 760417239.0 / 1151165299.0, 118820643.0 / 751138087.0, -528747749.0 / 2220607170.0, 1.0 / 4.0},
    {14005451.0 / 335480064.0, 0.0, 0.0, 0.0, 0.0, -59238493.0 / 1068277825.0, 181606767.0 / 758867731.0, 561292985.0 / 797845732.0, -1041891430.0 / 1371343529.0, 760417239.0 / 1151165299.0, 118820643.0 / 751138087.0, -528747749.0 / 2220607170.0, 1.0 / 4.0, 0.0}
};