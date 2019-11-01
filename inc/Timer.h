//
// Created by jiangc on 10/31/19.
//

#ifndef UTILS_TIMER_H
#define UTILS_TIMER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum{
    DATE_TIME,
    DATE
}TIME_TYPE;
// unix 时间戳转格式化日期
extern void UnixToStrTime(long datetime, TIME_TYPE type, char* str, int len);
// 格式化日期转换成unix时间戳
extern void StrTimeToUnix(char* str_time, long* time);
#endif //UTILS_TIMER_H
