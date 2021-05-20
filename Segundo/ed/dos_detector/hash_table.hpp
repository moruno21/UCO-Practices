#ifndef __HASH_TABLE__
#define __HASH_TABLE__
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cassert>

#include <vector>
#include <list>
#include <utility>
#include <memory>

/**
 * @brief Implement the HashTable[K,V] ADT.
 * The template parameter keyToInt is a functional to transform
 * values of type K into size_t. It must be implement the interface:
 *    size_t operator()(K const&k)
 */
template <class K, class V, class keyToInt>
class HashTable
{
public:
    /** @name Life cicle.*/
    /** @{*/

    /**
      * @brief Create a new HashTable.
      * @post is_empty()
      * @post not is_valid()
      */
    HashTable(size_t m, uint64_t a = 32, uint64_t b = 3, uint64_t p = 4294967311l,
              keyToInt key_to_int = keyToInt())
    {
        //TODO

        this->m_ = m;                                           //Tamaño de la tabla
        this->hash_table_.resize(m_);                           //Al asignar el tamaño, hay que hacer un resize
        this->a_ = a;                                           //Parametro de la funcion hash
        this->b_ = b;                                           //Parametro de la funcion hash
        this->p_ = p;                                           //Parametro de la funcion hash
        this->key_to_int_ = key_to_int;                         //Clave a entero
        this->valid_keys_ = 0;                                  //Al comienzo, hay 0 claves validas
        this->current_iterator_ = this->hash_table_[0].begin(); //Asignamos el current
        this->current_index_ = 0;                               //Asignamos el current

        assert(is_empty());
        assert(!is_valid());
    }
    /** @}*/

    /** @name Observers*/
    /** @{*/

    /**
     * @brief Is the table empty?
     * @return true if it is empty.
     */
    bool is_empty()
    {
        //TODO
        return this->valid_keys_ == 0;
    }

    /**
     * @brief is the cursor at a valid position?
     * @return true if the cursor is at a valid position.
     */
    bool is_valid() const
    {
        //TODO
        if (this->hash_table_.size() == this->current_index_) //Si esta el cursor al final de la tabla, devolvemos falso
            return false;

        for (auto a = this->hash_table_[this->current_index_].begin(); a != this->hash_table_[this->current_index_].end(); a++)
        {                                     //Vamos recorriendo de una en una las posiciones de la tabla buscando el current
            if (a == this->current_iterator_) //Cuando lo encontremos devolvemos true
                return true;
        }
        return false;
    }

    /**
     * @brief Get the number of valid keys in the table.
     * @return the number of valid keys in the table.
     */
    size_t num_of_valid_keys() const
    {
        //TODO
        return this->valid_keys_;
    }

    /**
     * @brief Compute the load factor of the table.
     * @return the load factor of the table.
     */
    float load_factor() const
    {
        //TODO
        float factor = this->valid_keys_ / m_;
        return factor;
    }

    /**
     * @brief Has the table this key?
     * @param k the key to find.
     * @return true if the key is saved into the table.
     * @warning The cursor is not affected by this operation.
     */
    bool has(K const &k) const
    {
        //TODO
        //You can use find() but
        //you must remenber to restore the cursor at the end.
        unsigned long key_to_int = this->key_to_int_(k);                                                //Transformamos la clave en un entero
        size_t key_hash = hash(key_to_int);                                                             //Le pasamos el parametro a la funcion hash
        for (auto a = this->hash_table_[key_hash].begin(); a != this->hash_table_[key_hash].end(); a++) //Iteramos la tabla hash
        {
            if (k == a->first)
                return true;
        }
        return false;
    }

    /**
     * @brief Get the key at cursor.
     * @return return the key of the cursor.
     */
    K const &get_key() const
    {
        assert(is_valid());
        //TODO
        return this->current_iterator_->first;
    }

    /**
     * @brief Get tha value at cursor.
     * @return return the value of the cursor.
     */
    V const &get_value() const
    {
        assert(is_valid());
        //TODO
        return this->current_iterator_->second;
    }

    /**
     * @brief hash a key value k.
     * @return h = ((int(k)*a + b) % p) % m
     */
    size_t
    hash(uint64_t k) const
    {
        //TODO
        int h = ((k)*a_ + b_) % p_ % m_;
        return h;
    }

    /** @name Modifiers*/
    /** @{*/

    /**
     * @brief Find a key value.
     * @return true if the key is found.
     * @post !is_valid() or get_key()==k
     */
    bool find(K const &k)
    {
        bool is_found = false;

        //TODO
        //1. hash the key to get the table entry.
        //2. Is the table entry empty
        //2.1 yes, not found
        //2.2 else find into the chain (list) of the entry.
        // !!Remenber to update the cursor state.

        if (!this->is_empty()) //Solo entramos si no esta vacia
        {
            size_t key_to_int = this->key_to_int_(k); //Transformamos la clave k en entero
            auto i = this->hash(key_to_int);

            for (auto a = this->hash_table_[i].begin(); a != this->hash_table_[i].end(); a++)
            {                      //Buscamos en toda la tabla
                if (k == a->first) //Si la clave es igual a la clave de donde estamos buscando, entramos
                {
                    this->current_index_ = i;
                    this->current_iterator_ = a;
                    is_found = true;
                    break; //Salimos del bucle si ya lo hemos encontrado, no seguimos buscando
                }
            }
        }
        return is_found;
    }

    /**
     * @brief insert a new entry.
     * If the key is currently in the table, the value is updated.
     * @post is_valid()
     * @post get_key()==k
     * @post get_value()==v;
     * @post not old(has(k)) -> num_of_valid_keys() = old(num_of_valid_keys())+1
     */
    void insert(K const &k, V const &v)
    {
#ifndef NDEBUG //In Relase mode this macro is defined.
        bool old_has = has(k);
        size_t old_num_of_valid_keys = num_of_valid_keys();
#endif
        //TODO
        //1. find the key.
        //2.1 if it is found, reset the value part.
        //2.2 else, add the new pair (key,value) to the entry chain.
        //Remenber to update the cursor state and the valid keys counter.
        if (this->find(k))
            this->set_value(v);

        else
        {
            this->current_index_ = this->hash(this->key_to_int_(k));                   //Modificamos current
            this->hash_table_[this->current_index_].push_front(std::make_pair(k, v));  //Insertamos el nuevo valor con su clave
            this->valid_keys_++;                                                       //Aumentamos el numero de claves validas
            this->current_iterator_ = this->hash_table_[this->current_index_].begin(); //Modificamos current
            if (this->load_factor() > 0.9)                                             //Si nos pasamos del valor, hacemos un rehash
                this->rehash();
        }

        assert(is_valid());
        assert(get_key() == k);
        assert(get_value() == v);
        assert(old_has || (num_of_valid_keys() == old_num_of_valid_keys + 1));
    }

    /**
     * @brief remove the entry at the cursor position.
     * The cursor will be move to the next valid position if there is.
     * @pre is_valid()
     * @post !is_valid() || old(goto_next() && get_key())==get_key()
     * @post num_of_valid_keys() = old(num_of_valid_keys())-1
     */
    void remove()
    {
        assert(is_valid());
#ifndef NDEBUG //In Relase mode this macro is defined.
        size_t old_n_valid_keys = num_of_valid_keys();
#endif

        //TODO
        //First save the current cursor state.
        //Guardamos current en variables
        auto current_index_aux = this->current_index_;
        auto current_iterator_aux = this->current_iterator_;

        this->goto_next(); //move the cursor to next position.

        //TODO
        //Second, remove the old cursor position.
        this->hash_table_[current_index_aux].erase(current_iterator_aux); //Borramos el current que acabamos de guardar en la variable de arriba
        this->valid_keys_--;                                              //Reducimos el numero de claves en 1

        assert((num_of_valid_keys() + 1) == old_n_valid_keys);
        return;
    }

    /**
     * @brief set the value of the entry at the cursor position.
     */
    void set_value(const V &v)
    {
        assert(is_valid());
        //TODO
        this->current_iterator_->second = v;
    }

    /**
     * @brief rehash the table to double size.
     * @warning A new hash function is random selected.
     * @post old.is_valid() implies is_valid() && old.get_key()==get_key() && old.get_value()==get_value()
     */
    void rehash()
    {
#ifndef NDEBUG //In Relase mode this macro is defined.
        bool old_is_valid = is_valid();
        K old_key;
        V old_value;
        if (old_is_valid)
        {
            old_key = get_key();
            old_value = get_value();
        }
#endif
        //1. Save the state of the cursor.
        auto aux_key = current_iterator_->first;

        //2. Pick up at random a new h.
        uint64_t P = p_; ///*TODO use here the coefficiente P used for the hash function.*/ 0;
        const uint64_t a = 1 + static_cast<uint64_t>(std::rand() / (RAND_MAX + 1.0) * static_cast<double>(P - 1));
        const uint64_t b = static_cast<uint64_t>(std::rand() / (RAND_MAX + 1.0) * static_cast<double>(P));

        //3. Create a new table with double size with the new hash.
        size_t M = m_; ///*TODO use the current table size.*/ 0;
        HashTable<K, V, keyToInt> new_table(M * 2, a, b);

        //TODO
        //4. Traversal the old table inserting the values into the new.
        //4.1 goto to the first entry.
        //4.2 while isValid() do
        //4.3    insert in new table current pair key,value
        //4.4    goto next entry.

        this->goto_begin();
        while (this->is_valid())
        {
            K new_key = this->get_key();
            int new_value = this->get_value();
            new_table.insert(new_key, new_value);
            this->goto_next();
        }

        //TODO
        //5 commute the new_table with this.
        //THIS DEPENDS ON YOUR IMPLEMENTATION.
        //CHECK CAREFULY IF YOU NEED OR NOT TO
        //OVERLOAD THE ASSIGN OPERATOR.
        (*this) = new_table;

        //TODO
        //6. Before returning, the cursor must be restored
        //to the same state that old state.
        //
        this->find(aux_key);

        //post condition
        assert(!old_is_valid || (is_valid() && old_key == get_key() && old_value == get_value()));
    }

    /**
     * @brief move the cursor to the first valid entry.
     * @post is_empty() || is_valid()
     */
    void goto_begin()
    {
        //TODO
        for (size_t a = 0; a < this->hash_table_.size(); a++)
        {
            if (!this->hash_table_[a].empty()) //Entraremos en la primera entrada que no este vacia
            {
                this->current_index_ = a;                               //Actualizamos current
                this->current_iterator_ = this->hash_table_[a].begin(); //Actualizamos current
                break;                                                  //Salimos del bucle ya que no tenemos mas nada que buscar
            }
        }
        assert(is_empty() || is_valid());
    }

    /**
     * @brief Move the cursor to next valid position.
     * @post not is_valid() marks none any more valid entry exists.
     */
    void goto_next()
    {
        assert(is_valid());
        //TODO
        this->current_iterator_++;
        if (this->hash_table_[this->current_index_].end() == this->current_iterator_)
        {
            size_t a = this->current_index_;
            a++;
            while (this->hash_table_[a].empty() && a < this->hash_table_.size()) //Incrementamos a para usarla en las condiciones de abajo
                a++;                                                             //Buscamos una posicion que no este vacia

            if (!this->hash_table_[a].empty() && a < this->hash_table_.size())
            {
                this->current_index_ = a;                               //Asignamos la posicion que hemos encontrado en el bucle
                this->current_iterator_ = this->hash_table_[a].begin(); //Asignamos la posicion que hemos encontrado en el bucle
                assert(this->is_valid());                               //Hacemos la comprobacion aqui ya que es donde cambia el valor de current
            }

            else //Entramos si no hay posicion a la que ir, y nos vamos al final
                this->current_index_ = this->hash_table_.size();
        }
    }

protected:
    //TODO
    //Care must be taken about the type of the attributes.
    //It is recommended to use types that not imply to overload
    //the assign operator used in the rehash method.

    std::vector<std::list<std::pair<K, V>>> hash_table_;             //Tabla
    int m_;                                                          //Tamaño de la tabla
    size_t current_index_;                                           //Current
    typename std::list<std::pair<K, V>>::iterator current_iterator_; //Iterador del current
    unsigned long a_;                                                //Parametro constantes que se usan en la funcion hash
    unsigned long b_;                                                //Parametro constantes que se usan en la funcion hash
    unsigned long p_;                                                //Parametro constantes que se usan en la funcion hash
    keyToInt key_to_int_;                                            //Transformar las claves a enteros
    int valid_keys_;                                                 //Claves validas
};

#endif
