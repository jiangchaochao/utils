//
// Created by jiangc on 10/31/19.
//

#include "Timer.h"
/**
 * 将时间戳格式化成字符串日期
 * @param datetime    unix时间戳
 * @param type        要转换成的类型，参考TIME_TYPE  DATE_TIME:返回 2019-10-11 17:57:48 DATE_TIME:返回 2019-10-11
 * @param str         返回的结果缓冲区
 * @param len         缓冲区总长度
 */
void UnixToStrTime(long datetime, TIME_TYPE type, char* str, int len)
{
    if (NULL == str)
    {
        perror("str is NULL");
        return ;
    }
    struct tm * timeSet = gmtime(&datetime);
    timeSet->tm_hour+=8;
    if (type == DATE_TIME)
    {
        strftime(str,len, "%Y-%m-%d %H:%M:%S", timeSet);
    }else if (type == DATE)
    {
        strftime(str,len, "%Y-%m-%d", timeSet);
    }
    return ;
}

/**
 * 将格式化字符串转换成unix时间戳,目前仅支持日期+时间的格式转换(2019-10-11 17:57:48)
 * @param str_time    格式化的日期+时间字符串
 * @param time        返回的unix时间戳
 */
void StrTimeToUnix(char* str_time, long* time)
{
    struct tm stm;
    int iY, iM, iD, iH, iMin, iS;
    memset(&stm, 0, sizeof(stm));

    if (NULL == str_time)
    {
        perror("timeStamp is NULL");
        return ;
    }

    iY = atoi(str_time);
    iM = atoi(str_time + 5);
    iD = atoi(str_time + 8);
    iH = atoi(str_time + 11);
    iMin = atoi(str_time + 14);
    iS = atoi(str_time + 17);
    stm.tm_year = iY - 1900;
    stm.tm_mon = iM - 1;
    stm.tm_mday = iD;
    stm.tm_hour = iH - 16;
    stm.tm_min = iMin;
    stm.tm_sec = iS;
    *time = (long)mktime(&stm);

    return ;
}
