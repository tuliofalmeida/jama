#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

namespace Identifiers{
    struct to{
        to(uint32_t interval) : interval(interval) {}

        uint32_t interval;
    };
    struct from{
        from(uint32_t interval) : interval(interval) {}

        uint32_t interval;

        uint32_t* operator > (to b){
            uint32_t* ret = new uint32_t[2];
            ret[0] = this->interval;
            ret[1] = b.interval;
            return ret;
        }

        uint32_t* operator > (uint32_t b){
            uint32_t* ret = new uint32_t[2];
            ret[0] = this->interval;
            ret[1] = b;
            return ret;
        }

        uint32_t operator- (uint32_t b){
            return this->interval - b;
        }

        uint32_t operator+ (uint32_t b){
            return this->interval + b;
        }

        void operator = (uint32_t b){
            this->interval = b;
        }

        from operator --(int){
            return *this;
        }
    };
}
#endif // IDENTIFIERS_H
