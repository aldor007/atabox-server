#ifndef BASE_DATA_PROVIDER
#define BASE_DATA_PROVIDER

#include <vector>
#include <map>
enum class DBStatus {Open, Closed, Error};

template <typename KeyClass, typename ValueClass>
class BaseDataProvider {
    protected:
        DBStatus connecionStatus;

    public:
        virtual ValueClass get(KeyClass key);
        virtual bool set(KeyClass key, ValueClass value);
        virtual std::map<KeyClass, ValueClass> getAllKV();
        DBStatus getStatus() {
            return this->connecionStatus;
        }

        virtual ~BaseDataProvider();
};
#endif
