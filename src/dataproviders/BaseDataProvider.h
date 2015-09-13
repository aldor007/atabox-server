#ifndef BASE_DATA_PROVIDER
#define BASE_DATA_PROVIDER

#include <vector>
#include <map>

#include <utils/jsonextend.h>

enum class DBStatus {Open, Closed, Error};

template <typename KeyClass, typename ValueClass>
class BaseDataProvider {
    protected:
        DBStatus connecionStatus;

    public:
        virtual ValueClass get(KeyClass key) = 0;
        virtual bool put(KeyClass key, ValueClass value) = 0;
        virtual std::map<KeyClass, ValueClass> getAllKV() = 0;
        DBStatus getStatus() const {
            return this->connecionStatus;
        }

        virtual ~BaseDataProvider() {

        }
};

typedef BaseDataProvider<jsonextend, jsonextend> AtaboxBaseDataProvider;

#endif
