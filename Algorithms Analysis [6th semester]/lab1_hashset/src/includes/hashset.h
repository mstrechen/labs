#ifndef _HASHSET_H_
#define _HASHSET_H_

#include<string>
#include<iostream>
#include<vector>
#include<forward_list>

namespace HashBasedDS{

using std::string;
using std::forward_list;
using std::vector;

using _ull_t_ = unsigned long long;
const _ull_t_ HASH_MULTIPLIER = 257;
const _ull_t_ HASH_MODULO = _ull_t_(1000*1000*1000) * 1000 + 39;

class HashPair {
public:
    HashPair(){}
    HashPair(const string & s) {
        this->from_iterable(s.begin(), s.end());
    }
    HashPair(const string & s, bool reverse) {
        if(reverse)
            this->from_iterable(s.rbegin(), s.rend());
        else
            this->from_iterable(s.begin(), s.end());
    }
    _ull_t_ get_index(_ull_t_ max_size) const {
        return (HASH_1 + HASH_2) % max_size;
    }
    bool operator == (const HashPair & other) const {
        return this->HASH_1 == other.HASH_1 && this->HASH_1 == other.HASH_1;
    }
    bool operator != (const HashPair & other) const {
        return !(this->operator==(other));
    }
private:
    template<typename iter_t>
    void from_iterable(iter_t begin, iter_t end){
        HASH_1 = 0;
        HASH_2 = 0;
        for(auto it = begin; it != end; ++it){
            HASH_1 *= HASH_MULTIPLIER;
            HASH_2 *= HASH_MULTIPLIER;
            HASH_1 += *it;
            HASH_2 += *it;
            HASH_1 %= HASH_MODULO;
            // HASH_2 is always calculated based by modulo 2^64
        }
    }
    _ull_t_ HASH_1, HASH_2;
};

struct StringAndHash{
    string s;
    HashPair hp;
    StringAndHash(const string & s): s(s), hp(s){}
    StringAndHash(StringAndHash && source): s(std::move(source.s)), hp(source.hp){}
    StringAndHash(const StringAndHash & source): s(source.s), hp(source.hp){}

    bool operator ==(const StringAndHash & other) const {
        return this->hp == other.hp && this->s == other.s;
    }
    
};

struct DefaultHashSetResizer{
    static size_t get_new_size(size_t old_size){
        return ((old_size + 10)/ 10) * 13;
    }
    static bool expansion_required(size_t size, size_t used_space){
        return size * 7 / 10 < used_space;
    }
};

template<typename HashSetResizer>
class BaseHashSet{
    using inner_container_t = forward_list<StringAndHash>;
    using outer_container_t = vector<inner_container_t>;
    using outer_it_t = outer_container_t::iterator;
    using inner_it_t = inner_container_t::iterator;
public:
    BaseHashSet(){};
    class iterator{
        friend BaseHashSet;
    public:
        iterator(outer_it_t outer_it,
                 inner_it_t inner_it,
                 outer_container_t & outer_container_ref):
            outer_it(outer_it),
            inner_it(inner_it),
            outer_container_ref(outer_container_ref)
            {push_to_the_limit();}
        const string & operator * () const{
            return inner_it->s;
        }
        string * operator -> () const{
            return &(inner_it->s);
        }
        const iterator & operator ++(){
            ++inner_it;
            push_to_the_limit();
            return *this;
        } 
        bool operator == (const iterator & other){

            if(this->outer_it != other.outer_it) return false;
            if(this->outer_it == this->outer_container_ref.end()) return true;
            if(this->inner_it == other.inner_it) return true;
            return false;
        }
        bool operator != (const iterator & other){
            return !(this->operator==(other));
        }
    private:
        void push_to_the_limit(){
            while(
                outer_it != outer_container_ref.end()
                && outer_it->end() == inner_it
            ){
                ++outer_it;
                if(outer_it != outer_container_ref.end())
                    inner_it = outer_it->begin();
                else
                    inner_it = inner_it_t();
            }
        }
        outer_it_t outer_it;
        inner_it_t inner_it;
        const outer_container_t & outer_container_ref;
        StringAndHash & string_and_hash(){
            return *inner_it;
        }
    };
    iterator begin(){
        if(_buckets.empty())
            return iterator(_buckets.begin(), inner_it_t(), this->_buckets);
        return iterator(_buckets.begin(), _buckets.front().begin(), this->_buckets);
    }
    iterator end(){
        return iterator(_buckets.end(), inner_it_t(), this->_buckets);
    }
    iterator find(const string & s){
        return find(StringAndHash(s));
    }
    size_t count(const string & s) {
        return size_t(find(s) != end());
    }
    void insert(const string & s){
        insert(StringAndHash(s));
    }
    void remove(const string & s){
        remove(StringAndHash(s));
    }
    size_t size() const {
        return _used_space;
    }
    bool empty() const {
        return _buckets.empty();
    }
private:
    size_t _used_space = 0;
    vector<forward_list<StringAndHash> > _buckets;

    iterator find(const StringAndHash & value){
        if(empty()) return end();
        size_t index = value.hp.get_index(_buckets.size());
        inner_it_t found = _buckets[index].end();
        for(inner_it_t it = _buckets[index].begin(); it != found; ++it){
            if(*it == value){
                found = it;
                break;
            }
        }
        if(found == _buckets[index].end()) return end();
        return iterator(_buckets.begin() + index, found, _buckets);
    }
    void insert(const StringAndHash & value){
        iterator found = find(value);
        if(found == end()){
            _used_space++;
            
            if(HashSetResizer::expansion_required(_buckets.size(), size())){
                extend();
            }
            size_t index = value.hp.get_index(_buckets.size());
            _buckets[index].push_front(value);
        }
    }
    void remove(const StringAndHash & value){
        iterator found = find(value);
        if(found != end()){
            _used_space--;
            inner_container_t & bucket = _buckets[index];
            if(found.inner_it == bucket){
                bucket.pop_front();
                return;
            }
            inner_it_t it_prev = bucket.begin(), it_curr = ++bucket.begin();
            while(it_curr != found.inner_it) ++it_prev, ++it_curr;
            bucket.erase_after(it_prev);
        }
    }
    void extend(){
        size_t new_size = HashSetResizer::get_new_size(_buckets.size());
        outer_container_t new_buckets(new_size);
        for(iterator it = begin(); it!= end(); ++it){
            auto & value = it.string_and_hash();
            size_t index = value.hp.get_index(new_size);
            new_buckets[index].push_front(std::move(value));
        }
        _buckets = move(new_buckets);
    }
};

using HashSet = BaseHashSet<DefaultHashSetResizer>;

}

#endif