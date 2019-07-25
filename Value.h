#ifndef VALUE_H
#define VALUE_H

#include "header.h"

class Value
{
    public:
        Value();
        Value(const Value& value);
        virtual ~Value();

        int GetIntValue();
        void SetIntValue(int val);
        bool GetBoolValue();
        void SetBoolValue(bool val);
        vector<int>* GetMatrixValue();
        void SetMatrixValue(vector<int>* val);

    protected:

    private:
        int intValue;
        bool boolValue;
        vector<int>* matrixValue;
};

#endif // VALUE_H
