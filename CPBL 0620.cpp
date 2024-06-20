/*
Author: ethanul
�p�g�R�大�@ June 20th, 2024;
�w��ۥѨϥΡB�ק�B�o��üЩ��X�B�A�P���C
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#define NOM 20

using namespace std;

class team{
    public:
        std::string name;
        int W_pre, W_pro;
        int L_pre, L_pro;
        double WP_pre, WP_pro;  // winning percentage
        double championship;
};

string matches_left[NOM] = {"CW", "FU", "TR", "CT", "WU", "FR", "CT", "WU", "FR", "TF"
, "RU", "RC", "WF", "UC", "FR", "TR", "UF", "RT", "FT", "RF"};

string names[6] = {"UL", "RM", "CB", "FG", "WD", "TH"};
int wins[6] = {32, 27, 29, 24, 26, 22};
int loses[6] = {22, 24, 26, 27, 30, 31};
int powof2[NOM];


int main()
{
    int p = 1;
    for(int i = 0; i < NOM; i++){
        powof2[i] = p;
    p *= 2;
}
	team teams[6];
	for (int i = 0; i < 6; i++){
        teams[i].name = names[i];
        teams[i].W_pro = teams[i].W_pre = wins[i];
        teams[i].W_pro = teams[i].L_pre = loses[i];
        teams[i].W_pro = teams[i].WP_pre = (double)teams[i].W_pre / (double)(teams[i].W_pre + teams[i].L_pre);
        teams[i].championship = 0;
	}
	unsigned int result = 0b00000000000000000000;

	do{ // ��Ĺ�զX�a�|
        for (int i = 0; i < 6; i++){
            teams[i].L_pro = teams[i].L_pre;
            teams[i].W_pro = teams[i].W_pre;
        }
        int matching_teams[2]; //��ԲզX
        for (int i = 0; i < NOM; i++){ //��ԲզX�a�|��i������

            for (int c = 0; c < 2; c++){
                switch (matches_left[i][c]){ // ��i�����ɫȶ�(c=0)�B�D��(c=1)
                    case 'U':
                        matching_teams[c] = 0;
                        break;
                    case 'R':
                         matching_teams[c] = 1;
                        break;
                    case 'C':
                         matching_teams[c] = 2;
                        break;
                    case 'F':
                         matching_teams[c] = 3;
                        break;
                    case 'W':
                         matching_teams[c] = 4;
                        break;
                    case 'T':
                         matching_teams[c] = 5;
                        break;
                }
            }
            // matching_teams: {int1, int2}
            if ((result / powof2 [i] % 2) == 0) { // away win
                teams[ matching_teams[0]].W_pro ++;
                teams[ matching_teams[1]].L_pro ++;
            }else { // home win
                teams[ matching_teams[1]].W_pro ++;
                teams[ matching_teams[0]].L_pro ++;
            }
        }

        int max_w = 0;
        int max_cnt = 0;
        for (int i = 0; i < 4; i++){ // �u�ѥ|�����ʤ��i��A��X�̤j�ӳ�
            if(teams[i].W_pro >= max_w){
                max_w = teams[i].W_pro;
            }
        }
        for (int i = 0; i < 4; i++){ // �u�ѥ|�����ʤ��i��A��X�̤j�ӳ�
            if(teams[i].W_pro == max_w) max_cnt ++;
        }
        double w_div = (double)1 / (double)max_cnt;
        for (int i = 0; i < 4; i++){ // �u�ѥ|�����ʤ��i��A��X�̤j�ӳ�
            if(teams[i].W_pro == max_w) teams[i].championship += w_div;
            //cout << w_div;
        }

        result ++;
	}while(result < 0b100000000000000000000);
    cout << result << endl;
    double sum = 0;
    for(int i = 0; i < 6; i++){
        sum += teams[i].championship;
        cout << teams[i].name << ' ' ;
        printf("%.2f %.4f\n",teams[i].championship, teams[i].championship/(double)1048576);
    }
    cout << sum;
	//cout << teams[4].W << ' ' << teams[4].WP << ' ' << teams[4].name;
	return 0;
}
