#ifndef BASE_DATA_PROVIDER
#define BASE_DATA_PROVIDER

#include <vector>
enum class DBStatus {Open, Closed};

template <typename KeyClass, typename ValueClass>
class BaseDataProvider {
    protected:
        DBStatus connecionStatus;

    public:
        virtual ValueClass get(KeyClass key);
        virtual bool set(KeyClass key, ValueClass value);
        virtual std::vector<ValueClass> getrangevalue(KeyClass startkey, KeyClass endkey);
        DBStatus getStatus() {
            return this->connecionStatus;
        }

        virtual ~BaseDataProvider();
};
#endif
