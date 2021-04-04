#ifndef __DEBUG_H__
#define __DEBUG_H__

namespace qLib
{
#define qDebug(fmt, arg...) printf("[%s, %d] "fmt, ##args)
}

#endif