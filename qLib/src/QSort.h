#ifndef __SORT_H__
#define __SORT_H__

#include "QObject.h"
#include "QArray.h"

namespace qLib
{

class Sort : public QObject
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator =(const Sort&);

    template <typename T>
    static void swap(T& obj1, T&obj2)
    {
        T obj3(obj1);
        obj1 = obj2;
        obj2 = obj3;
    }

    template <typename T>
    static void merge(T array[], T helper[], int begin, int end, bool min2max)
    {
        if(begin < end)
        {
            int mid = (begin + end) / 2;

            merge(array, helper, begin, mid, min2max);
            merge(array, helper, mid + 1, end, min2max);
            merge(array, helper, begin, mid, end, min2max);
        }
    }

    template <typename T>
    static void merge(T array[], T helper[], int begin, int mid, int end, bool min2max)
    {
        int i = begin;
        int j = mid + 1;
        int k = begin;

        while((i <= mid) && (j <= end))
        {
            if(min2max ? (array[i] < array[j]) : (array[j] < array[i]))
            {
                helper[k++] = array[i++];
            }
            else
            {
                helper[k++] = array[j++];
            }
        }

        while(i <= mid)
        {
            helper[k++] = array[i++];
        }

        while (j <= end)
        {
            helper[k++] = array[j++];
        }

        for(int i = begin; i <= end; i++)
        {
            array[i] = helper[i];
        }
    }

    template <typename T>
    static void quick(T array[], int begin, int end, bool min2max)
    {
        int i = begin;
        int j = end;
        T temp = array[i];

        while(i < j)
        {
            while((i < j) && (min2max ? (temp < array[j]) : (array[j] < temp))) j--;

            if(i < j)
            {
                array[i++] = array[j];
            }

            while((i < j) && (min2max ? (array[i] < temp) : (temp < array[i]))) i++;

            if(i < j)
            {
                array[j--] = array[i];
            }
        }

        array[i] = temp;

        if(begin < i) quick(array, begin, i - 1, min2max);
        if(i < end) quick(array, j + 1, end, min2max);
    }

public:
    template <typename T>
    static void select(T array[], int len, bool min2max = true)
    {
        for(int i = 0; i < len - 1; i++)
        {
            int min = i;

            for(int j = i + 1; j < len; j++)
            {
                if(min2max ? (array[j] < array[min]) : (array[min] < array[j]))
                {
                    min = j;
                }
            }

            if(min != i)
            {
                swap(array[min], array[i]);
            }
        }
    }

    template <typename T>
    static void insert(T array[], int len, bool min2max = true)
    {
        for(int i = 1; i < len; i++)
        {
            int k = i;
            T e = array[i];

            for(int j = i - 1; (j >= 0) && (min2max ? (e < array[j]) : (array[j] < e)); j--)
            {
                array[j + 1] = array[j];
                k = j;
            }

            if(k != i)
            {
                array[k] = e;
            }
        }
    }

    template <typename T>
    static void bubble(T array[], int len, bool min2max = true)
    {
        bool exchange = true;

        for(int i = 0; (i < len - 1) && exchange; i++)
        {
            exchange = false;

            for(int j = len - 1; j > i; j--)
            {
                if(min2max ? (array[j] < array[j - 1]) : (array[j - 1] < array[j]))
                {
                    swap(array[j], array[j - 1]);
                    exchange = true;
                }
            }
        }
    }

    template <typename T>
    static void shell(T array[], int len, bool min2max = true)
    {
        int d = len;

        do
        {
            d = d / 3 + 1;

            for(int i = d; i < len; i += d)
            {
                int k = i;
                T e = array[i];

                for(int j = i - d; (j >= 0) && (min2max ? (e < array[j]) : (array[j] < e)); j -= d)
                {
                    array[j + d] = array[j];
                    k = j;
                }

                if(k != i)
                {
                    array[k] = e;
                }
            }
        } while(d > 1);
    }

    template <typename T>
    static void merge(T array[], int len, bool min2max = true)
    {
        T* helper = new T[len];

        if(helper != NULL)
        {
            merge(array, helper, 0, len - 1, min2max);
        }

        delete[] helper;
    }

    template <typename T>
    static void quick(T array[], int len, bool min2max = true)
    {
        quick(array, 0, len - 1, min2max);
    }

    template <typename T>
    static void select(QArray<T>& array, bool min2max = true)
    {
        select(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void insert(QArray<T>& array, bool min2max = true)
    {
        insert(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void bubble(QArray<T>& array, bool min2max = true)
    {
        bubble(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void shell(QArray<T>& array, bool min2max = true)
    {
        shell(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void merge(QArray<T>& array, bool min2max = true)
    {
        merge(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void quick(QArray<T>& array, bool min2max = true)
    {
        quick(array.array(), array.length(), min2max);
    }
};

}

#endif // SORT_H
