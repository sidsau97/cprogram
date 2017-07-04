#include <stdio.h>

/*
 * Devise a structure template that will hold the name of a month, a three-letter
 * bbreviation for the month, the number of days in the month, and the month
 * number.
*/
// expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘{’ token
struct _month {
    // full name
    char name[12];
    // abbreviation
    // expected identifier or ‘(’ before ‘[’ token
    // 数组的写法上要与java区分开来
    char abbr[3] ;
    // the number of days in the month
    int numOfDays;
};

struct  _month year[12] = {
    {"January","Jan",31},
    {"February","Feb",28},
    {"March","mar",31},
    {"April","Apr",30},
    {"May","May",31},
    {"June","Jun",30},
    {"July","Jul",31},
    {"August","Aug",30},
    {"Semptemper","Sem",30},
    {"October","Otc",31},
    {"November","Nov",30},
    {"December","Dec",31}
};

/*
 * Write a function that, when given the month number, returns the total days in the
 * year up to and including that month. Assume that the structure template of
 * question 3 and an appropriate array of such structures are declared externally.
 *
*/

int caculateDaysTillSpecificMonth(int monthNum){
    if(1 > monthNum){
        return  -1;
    }
    int days = 0;
    int i = 0;
    for( i = 0; i < monthNum;i++){
        // todo test
        days += year[i].numOfDays;
    }
    // format ‘%S’ expects argument of type ‘wchar_t *’, but argument 3 has type ‘char *’
    // 字符串格式化输出用 %s, 不要写成了大写
    return days;
}



int main (){
    // unnamed struct/union that defines no instances
    // 结构体后面需要加结构体变量的名称
    // variable ‘fruzt’ has initializer but incomplete type
    struct house {
        float sqft;
        int rooms;
        int stories;
        char address[40];
    };
    struct house fruzt = {1560.0, 6, 1, "22 Spiffo Road"};
    struct house *sign;
    sign = &fruzt;
    //  6 1
    printf("%d %d\n", fruzt.rooms, sign->stories);
    // 22 Spiffo Road
    printf("%s \n", fruzt.address);
    // S p
    printf("%c %c\n", sign->address[3], fruzt.address[4]);
    int days = caculateDaysTillSpecificMonth(6);
    printf("there are %d days till the end of %s\n",days,year[6 - 1].name);
    return 0;
}

